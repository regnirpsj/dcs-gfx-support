// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/signal_handler.cpp                                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/signal_handler.hpp"

// includes, system

#include <array>         // std::array<>
#include <csignal>       // ::sigfillset, ::pthread_sigmask
#include <cstdlib>       // std::abort, std::exit
#include <cstring>       // ::strsignal
#include <iomanip>       // std::boolalpha
#include <iostream>      // std::cerr
#include <thread>        // std::thread
#include <unordered_map> // std::unordered_map<>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  using handler_map_type = std::unordered_map<signed,
                                              hugh::support::signal_handler::handler_function_type>;
  
  // variables, internal

  bool                         initialized(false);
  handler_map_type             handler_map;
  std::unique_ptr<std::thread> handler_thread(nullptr);
  
  // functions, internal

  void
  default_handler_indirect(int /* signo */, ::siginfo_t* value, void* /* user_data */)
  {
    TRACE("hugh::support::signal_handler::<unnamed>::default_handler_indirect");
    
    handler_map[value->si_signo](value->si_signo);
  }

  void
  default_handler(signed signo)
  {
    TRACE("hugh::support::signal_handler::<unnamed>::default_handler(" + std::to_string(signo) +
          ") [" + hugh::support::signal_name(signo) + "]");
    
    volatile bool ignore_signal(false);
    volatile bool create_core(false);
    volatile bool fatal_exit(false);

    switch (signo) {
    case SIGUSR1:
    case SIGUSR2:
    case SIGCHLD:
    case SIGTSTP:
    case SIGCONT:
    case SIGTTIN:
    case SIGTTOU:
    case SIGPROF:
    case SIGURG:
    case SIGVTALRM:
      // case SIGCLD:
    case SIGWINCH:
      ignore_signal = true;
      break;
    }

    switch (signo) {
    case SIGQUIT:
    case SIGILL:
    case SIGABRT:
    case SIGFPE:
    case SIGSEGV:
    case SIGBUS:
    case SIGSYS:
    case SIGTRAP:
    case SIGXCPU:
    case SIGXFSZ:
      // case SIGIOT:
      // case SIGLOST:
      create_core = true;
      break;

    case SIGALRM:
    case SIGPIPE:
      fatal_exit = true;
      break;

    case SIGHUP:
    case SIGINT:
    case SIGTERM:
    case SIGPOLL:
      // case SIGEMT:
    case SIGSTKFLT:
      // case SIGIO:
    case SIGPWR:
      break;

    default:
      break;
    }

#if 0
    {
      std::cerr << '\n'
                << "support::signal_handler::<unnamed>::default_handler: "
                << "caught signal '" << ::strsignal(signo)              << "'; "
                << "ignore:"         << std::boolalpha << ignore_signal << ", "
                << "core:"           << std::boolalpha << create_core   << ", "
                << "fatal:"          << std::boolalpha << fatal_exit    << ", "
                << '\n';
    }
#endif

    if (ignore_signal) {
      return;
    }

    if (create_core) {
      std::abort();
    }

    if (fatal_exit) {
      std::exit(EXIT_FAILURE);
    }

    std::exit(EXIT_SUCCESS);
  }

  void
  signal_thread_function()
  {
    TRACE("hugh::support::signal_handler::<unnamed>::signal_thread_function");
    
    bool done(false);

    while (!done) {
      TRACE_NEVER("hugh::support::signal_handler::<unnamed>::signal_thread_function[loop]");
      
      ::sigset_t signal_mask;

      // unblock all signals and refill the mask for signals to be handled

      ::sigfillset     (&signal_mask);
      ::pthread_sigmask(SIG_SETMASK, &signal_mask, 0);

      ::siginfo_t value;

      // wait for signal

      bool evaluate(true);

      if (-1 == ::sigwaitinfo(&signal_mask, &value)) {
        if (EINTR != errno)
          std::abort();
        else
          evaluate = false;
      }

      // block all signal and handle current one

      ::pthread_sigmask(SIG_BLOCK, &signal_mask, 0);

#if 0
      {
        std::cerr << '\n'
                  << "support::signal_handler::<unnamed>::signal_thread_function: "
                  << ((evaluate) ? "" : "!") << "evaluating signal "
                  << ::strsignal(value.si_signo)
                  << '\n';
      }
#endif
        
      if (evaluate) {
        handler_map[value.si_signo](value.si_signo);
      }
    }
  }
  
  void
  initialize()
  {
    TRACE("hugh::support::signal_handler::<unnamed>::initialize");
    
    if (!initialized) {
      static std::array<signed const, 3> const sync_signals = {
        {
          SIGSEGV, SIGFPE, SIGILL,
        }
      };
      
      ::sigset_t signal_mask;

      ::sigfillset(&signal_mask);

      for (unsigned i(0); i < sync_signals.size(); ++i) {
        ::sigdelset(&signal_mask, sync_signals[i]);
      }
      
      for (unsigned i(1); i < _NSIG; ++i) {
        handler_map[i] = default_handler;
      }
      
      struct sigaction sa;

      sa.sa_sigaction = default_handler_indirect;
      sa.sa_flags     = SA_SIGINFO;

      ::sigemptyset(&sa.sa_mask);

      for (unsigned i(0); i < sync_signals.size(); ++i) {
        ::sigaction(sync_signals[i], &sa, 0);
      }
      
      ::sigfillset     (&signal_mask);
      ::pthread_sigmask(SIG_SETMASK, &signal_mask, 0);
      {
        handler_thread.reset(new std::thread(signal_thread_function));
      }
      ::pthread_sigmask(SIG_BLOCK, &signal_mask, 0);
      
      // avoid exception when 'handler_thread' is destructed
      handler_thread->detach();

      initialized = true;
    }
  }

} // namespace {

namespace hugh {
  
  namespace support {
  
    // variables, exported
  
    // functions, exported

    signal_handler::~signal_handler()
    {
      TRACE("hugh::support::signal_handler::signal_handler");
    }

    signal_handler::handler_function_type
    signal_handler::handler(signed signo)
    {
      TRACE("hugh::support::signal_handler::handler(get)");
    
      return handler_map[signo];
    }

    signal_handler::handler_function_type
    signal_handler::handler(signed signo, handler_function_type new_handler)
    {
      TRACE("hugh::support::signal_handler::handler(set)");
    
      handler_function_type old_handler(handler_map[signo]);

      if (new_handler) {
        handler_map[signo] = new_handler;
      }
    
      return old_handler;
    }

    /* explicit */
    signal_handler::signal_handler(boost::restricted)
    {
      TRACE("hugh::support::signal_handler::signal_handler");
    
      initialize();
    }

    std::string
    signal_name(signed signo)
    {
      TRACE("hugh::support::signal_name");

      std::string result("UNKNOWN SIGNAL");

      if ((0 < signo) && (_NSIG > signo)) {
        result = sys_siglist[signo];
      }
    
      return result;
    }
  
  } // namespace support {

} // namespace hugh {
