// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/signal_handler.cpp                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>   // std::array<>
#include <csignal> // std::raise
#include <cstdlib> // EXIT_*
#include <tuple>   // std::tuple<>

// includes, project

#include <hugh/support/chrono.hpp>
#include <hugh/support/signal_handler.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal

#if defined(_WIN32)
  unsigned const signal_test_size( 6);
#else
  unsigned const signal_test_size(29);
#endif
  
  std::array<std::tuple<signed /* signo   */,
                        signed /* raised  */,
                        bool   /* handled */>, signal_test_size> signal_test = {
    {
      std::make_tuple(SIGABRT,   -1, false),
      std::make_tuple(SIGFPE,    -1, false),
      std::make_tuple(SIGILL,    -1, false),      
      std::make_tuple(SIGINT,    -1, false),
      std::make_tuple(SIGSEGV,   -1, false),
      std::make_tuple(SIGTERM,   -1, false),
#if !defined(_WIN32)
      std::make_tuple(SIGALRM,   -1, false),
      std::make_tuple(SIGBUS,    -1, false),
      std::make_tuple(SIGCHLD,   -1, false),
      std::make_tuple(SIGCONT,   -1, false),
      std::make_tuple(SIGHUP,    -1, false),
      std::make_tuple(SIGPIPE,   -1, false),
      std::make_tuple(SIGPOLL,   -1, false),
      std::make_tuple(SIGPROF,   -1, false),
      std::make_tuple(SIGPWR,    -1, false),
      std::make_tuple(SIGQUIT,   -1, false),
      std::make_tuple(SIGSTKFLT, -1, false),
      std::make_tuple(SIGSYS,    -1, false),
      std::make_tuple(SIGTRAP,   -1, false),
      std::make_tuple(SIGTSTP,   -1, false),
      std::make_tuple(SIGTTIN,   -1, false),
      std::make_tuple(SIGTTOU,   -1, false),
      std::make_tuple(SIGURG,    -1, false),
      std::make_tuple(SIGUSR1,   -1, false),
      std::make_tuple(SIGUSR2,   -1, false),
      std::make_tuple(SIGVTALRM, -1, false),
      std::make_tuple(SIGWINCH,  -1, false),
      std::make_tuple(SIGXCPU,   -1, false),
      std::make_tuple(SIGXFSZ,   -1, false),
#endif
    }
  };
  
  // functions, internal
  
  void
  signal_handler(signed signo)
  {
    TRACE("<unnamed>::signal_handler(" + std::to_string(signo) + ") [" +
          hugh::support::signal_name(signo) + "]");

    for (auto& s : signal_test) {
      if (signo == std::get<0>(s)) {
        std::get<2>(s) = true;
      }
    }    
  }
  
  signed
  raise_signal(signed signo)
  {
    TRACE("<unnamed>::raise_signal");
    
    // current linux/glibc implementation provides raise(2) as a wrapper for tgkill(2), which sends
    // the signal to the current thread/thread group but not all threads in the process; need to
    // find out how to make the signal-handler thread part of the parent thread's group!
#if !defined(_WIN32)
    return ::kill(::getpid(), signo);
#else
    return ::raise(signo);
#endif
  }
  
} // namespace {

int
main()
{
  TRACE("main");

  using namespace hugh;

#if !defined(_WIN32)
  support::signal_handler::handler_function_type
    urg_handler(support::signal_handler::instance->handler(SIGURG));
#endif
  
  support::signal_handler::handler_function_type
    fpe_handler(support::signal_handler::instance->handler(SIGFPE));
  
  for (auto& s : signal_test) {
    support::signal_handler::instance->handler(std::get<0>(s), signal_handler);
  }
  
  int                            result(EXIT_SUCCESS);
  support::clock::duration const delay(std::chrono::microseconds(725));
  
  for (auto& s : signal_test) {
    std::get<1>(s) = raise_signal(std::get<0>(s));
  
    support::sleep(delay);
  
    if ((0 != std::get<1>(s)) || !std::get<2>(s)) {
      std::cout << "unhandled signal: " << support::signal_name(std::get<0>(s)) << std::endl;
      
      result = EXIT_FAILURE;
    }
  }

  if (EXIT_FAILURE != result) {
#if !defined(_WIN32)
    support::signal_handler::instance->handler(SIGURG, urg_handler);
#endif
    
    support::signal_handler::instance->handler(SIGFPE, fpe_handler);

#if !defined(_WIN32)
    raise_signal(SIGURG); // ignored,   direct handler
#endif
    
    //raise_signal(SIGFPE); // abort,   indirect handler
    support::sleep(delay);
  }
  
  return result;
}
