// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/trace.cpp                                                          */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/trace.hpp"

// includes, system

#include <array>   // std::array<>
#include <cassert> // assert
#include <iomanip> // std::dec, std::hex, std::right, std::setfill, std::setprocision
#include <memory>  // std::unique_ptr<>
#include <ostream> // std::ostream
#include <sstream> // std::ostringstream
#include <utility> // std::pair<>

// includes, project

#include <hugh/support/chrono.hpp>    // support::clock, support::timer
#include <hugh/support/chrono_io.hpp> // std::chrono::operator<<
#include <hugh/support/thread.hpp>    // support::lock_guard<>, support::mutex, thread_local

#define HUGH_USE_UNIQUE_PTR

#if defined(_MSC_VER) // M$ sucks, including their handling of statics!
#  undef HUGH_USE_UNIQUE_PTR
#endif

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal

  // per thread indentation depth
  thread_local unsigned                       trace_depth(0);

  // intra-thread output lock
#if defined(HUGH_USE_UNIQUE_PTR)
  std::unique_ptr<hugh::support::simple_lock> trace_lock (nullptr);
#else
  hugh::support::simple_lock*                 trace_lock (nullptr);
#endif

  // global time tagged to process start
#if defined(HUGH_USE_UNIQUE_PTR)
  std::unique_ptr<hugh::support::timer>       trace_timer(nullptr);
#else
  hugh::support::timer*                       trace_timer(nullptr);
#endif
  
  // functions, internal

  void
  init_local_statics()
  {
    static bool initialized(false);

    if (!initialized || !trace_lock || !trace_timer) {
      std::ios_base::Init const _;

#if defined(HUGH_USE_UNIQUE_PTR)
      trace_lock. reset(new hugh::support::simple_lock);
      trace_timer.reset(new hugh::support::timer);
#else
      trace_lock  = new hugh::support::simple_lock;
      trace_timer = new hugh::support::timer;
#endif
      
      initialized = true;
    }

#if 0
    {
      std::cout << '['
                << "0x"
                << std::setfill('0')
                << std::setw(8)
                << std::hex
                << support::this_thread::get_id()
                << ':'
                << std::string(14, ' ')
                << ':'
                << std::string( 7, ' ')
                << ']'
                << "    support::trace::<unnamed>::init_local_statics:\n";
    }
#endif

    assert(initialized);
    assert(nullptr != trace_lock);
    assert(nullptr != trace_timer);
  }
  
} // namespace {

namespace hugh {
  
  namespace support {
  
    // variables, exported
  
    // functions, exported

    /* explicit */
    trace::trace(std::string const& msg, std::ostream& os)
      : boost::noncopyable(),
        msg_              (msg),
        os_               (os),
        start_            (),
        stop_             ()
    {
      enter(this, msg_, os_);
    }

    trace::~trace()
    {
      leave(this, msg_, os_);
    }

    /* static */ void
    trace::enter(std::string const& msg, std::ostream& os)
    {
      enter(nullptr, msg, os);
    }

    /* static */ void
    trace::leave(std::string const& msg, std::ostream& os)
    {
      leave(nullptr, msg, os);
    }

    /* static */ std::string
    trace::prefix()
    {
      return prefix(nullptr, false);
    }

    /* static */ void
    trace::enter(trace* ctx, std::string const& msg, std::ostream& os)
    {
      init_local_statics();

      if (ctx) {
        ctx->start_ = trace_timer->lapse();
      }

      {
        support::simple_lock_guard const lg(*trace_lock);
    
        os << prefix(ctx, false) << "-> " << msg << '\n';
      }
    
      ++trace_depth;
    }

    /* static */ void
    trace::leave(trace* ctx, std::string const& msg, std::ostream& os)
    {
      init_local_statics();

      if (ctx) {
        ctx->stop_ = trace_timer->lapse();
      }

      --trace_depth;
     
      {
        support::simple_lock_guard const lg(*trace_lock);

        os << prefix(ctx, true) << "<- " << msg << '\n';
      }
    }
  
    /* static */ std::string
    trace::prefix(trace* ctx, bool show_duration)
    {
      init_local_statics();
    
      auto const stamp((ctx) ? ((show_duration) ? ctx->stop_ : ctx->start_) : trace_timer->lapse());
    
      using std::chrono::duration_cast;
      using std::chrono::microseconds;
    
      std::ostringstream ostr;
    
      ostr << '['
           << "0x"
           << std::setfill('0')
           << std::setw(8)
           << std::hex
           << support::this_thread::get_id()
           << ':'
           << std::setfill(' ')
           << std::setw(12)
           << std::dec
           << duration_cast<microseconds>(stamp).count()
           << "us:";

      static unsigned duration_width(5);
      static unsigned suffix_width  (2);
    
      if (ctx && show_duration) {
        static std::array<std::pair<double const, std::string const>, 11> const suffixes = {
          {
            { 1000.00, "ns" },
            { 1000.00, "us" },
            { 1000.00, "ms" },
            {   60.00, "s " },
            {   60.00, "m " },
            {   24.00, "h " },
            {  365.25, "d " },
            { 1000.00, "aj" }, // see [http://www.wikipedia.org/wiki/Year] 
            { 1000.00, "ka" }, // .5ka max for 64bit float
            { 1000.00, "Ma" },
            {    1.00, "Ga" }, // requires 85bit float
          }
        };

        using std::chrono::nanoseconds;
      
        double   duration(double(duration_cast<nanoseconds>(ctx->stop_ - ctx->start_).count()));
        unsigned idx     (0);
      
        while ((idx < suffixes.size()) && (suffixes[idx].first < duration)) {
          duration /= suffixes[idx].first;

          ++idx;
        }

        // corrected duration w/ unit as suffix and no space delimter (e.g. 1234ns)
        ostr << std::setfill(' ')
             << std::setw(duration_width)
             << std::setprecision(1)
             << std::fixed
             << std::right
             << duration 
             << suffixes[idx].second;
      } else {
        ostr << std::string(duration_width + suffix_width, ' ');
      }
    
      ostr << ']'
           << std::string((trace_depth * 3) + 1, ' ');

      return ostr.str();
    }
  
  } // namespace support {
  
} // namespace hugh {
