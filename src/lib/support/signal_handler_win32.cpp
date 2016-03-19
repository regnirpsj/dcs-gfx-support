// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh//support/signal_handler_win32.cpp                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/signal_handler.hpp"

// includes, system

#include <array>         // std::array<>
#include <csignal>       // ::signal
#include <cstdlib>       // std::abort, std::exit
#include <iomanip>       // std::boolalpha
#include <iostream>      // std::cerr
#include <unordered_map> // std::unordered_map<>
#include <utility>       // std::pair<>

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

  std::array<std::pair<signed const, std::string const>, 6> const supported_signals = {
    {
      std::make_pair(SIGINT,  "SIGINT"),
      std::make_pair(SIGILL,  "SIGILL"),
      std::make_pair(SIGABRT, "SIGABRT"),
      std::make_pair(SIGFPE,  "SIGFPE"),
      std::make_pair(SIGSEGV, "SIGSEGV"),
      std::make_pair(SIGTERM, "SIGTERM"),
    }
  };
  
  bool             initialized(false);
  handler_map_type handler_map;
  
  // functions, internal

  void
  default_handler(signed signo)
  {
    TRACE("hugh::support::signal_handler::<unnamed>::default_handler");

    if (handler_map.end() != handler_map.find(signo)) {
      handler_map[signo](signo);
    } else {
      volatile bool create_core(false);

      switch (signo) {
      case SIGILL:
      case SIGABRT:
      case SIGFPE:
      case SIGSEGV:
        create_core = true;
        break;
        
      case SIGINT:
      case SIGTERM:
        break;
        
      default:
        break;
      }

#if 0
      {
        std::cerr << '\n'
                  << "support::signal_handler::<unnamed>::default_handler: "
                  << "caught signal '" << signo                         << "'; "
                  << "core:"           << std::boolalpha << create_core << ", "
                  << '\n';
      }
#endif

      if (create_core) {
        std::abort();
      }

      std::exit(EXIT_SUCCESS);
    }
  }

  
  void
  initialize()
  {
    TRACE("hugh::support::signal_handler::<unnamed>::initialize");
    
    if (!initialized) {
      for (auto s : supported_signals) {
        if (0 != s.first) {
          ::signal(s.first, &default_handler);
        }
      }
      
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

      for (auto s : supported_signals) {
        if (signo == s.first) {
          result = s.second;

          break;
        }
      }
    
      return result;
    }
  
  } // namespace support {

} // namespace hugh {
