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

#include <csignal> // std::raise
#include <cstdlib> // EXIT_*

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

  bool handled_fpe (false);
  bool handled_int (false);
  bool handled_term(false);
  
  // functions, internal
  
  void
  signal_handler(signed signo)
  {
    TRACE("<unnamed>::signal_handler(" + std::to_string(signo) + ") [" +
          hugh::support::signal_name(signo) + "]");
    
    switch (signo) {
    case SIGFPE:  handled_fpe  = true; break;
    case SIGINT:  handled_int  = true; break;
    case SIGTERM: handled_term = true; break;
    default:                           break;
    }
  }
  
  signed
  raise_signal(signed signo)
  {
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

  support::signal_handler::instance->handler(SIGFPE,  signal_handler);
  support::signal_handler::instance->handler(SIGINT,  signal_handler);
  support::signal_handler::instance->handler(SIGTERM, signal_handler);

  int result(EXIT_SUCCESS);

  {
    static support::clock::duration const delay(std::chrono::microseconds(725));
    
    int const raised_sigfpe(raise_signal(SIGFPE));
  
    support::sleep(delay);
  
    if ((0 != raised_sigfpe) || !handled_fpe) {
      std::cout << "unhandled signal: " << hugh::support::signal_name(SIGFPE) << std::endl;
      
      result = EXIT_FAILURE;
    }

    int const raised_sigint(raise_signal(SIGINT));
  
    support::sleep(delay);
  
    if ((0 != raised_sigint) || !handled_int) {
      std::cout << "unhandled signal: " << hugh::support::signal_name(SIGINT) << std::endl;
      
      result = EXIT_FAILURE;
    }

    int const raised_sigterm(raise_signal(SIGTERM));
  
    support::sleep(delay);
  
    if ((0 != raised_sigterm) || !handled_term) {
      std::cout << "unhandled signal: " << hugh::support::signal_name(SIGTERM) << std::endl;
      
      result = EXIT_FAILURE;
    }
  }
  
  return result;
}
