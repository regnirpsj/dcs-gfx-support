// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/thread.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/thread.hpp"

// includes, system

#include <algorithm> // std::max<>
#include <iomanip>   // std::setfill, std::setw
#include <ostream>   // std::ostream
#include <sstream>   // std::ostringstream

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal

  thread_local unsigned frame_count(1);
  
  // functions, internal

} // namespace {

namespace hugh {
  
  namespace support {

    namespace thread {

      // variables, exported
  
      // functions, exported
      
      /* explicit */
      pool::pool(unsigned a)
        : boost::noncopyable(),
          svc_              (),
          wrk_              (new work(svc_)),
          grp_              ()
      {
        TRACE("hugh::support::thread::pool::pool");

        unsigned nthr(std::max(unsigned(1), a));
        
        while (nthr--) {
          grp_.create_thread(boost::bind(&io_service::run, &svc_));
        }
      }
      
      pool::~pool()
      {
        TRACE("hugh::support::thread::pool::~pool");

        wrk_.reset   ();
        grp_.join_all();
        svc_.stop    ();
      }

      unsigned
      pool::size() const
      {
        TRACE("hugh::support::thread::pool::size");

        return grp_.size();
      }
      
    } // namespace thread {
    
    // variables, exported
  
    // functions, exported

    void
    dump_thread_stats(std::ostream&          os,
                      std::string const&     ctx,
                      clock::duration const& timeout,
                      clock::duration const& activity,
                      bool                   thread_was_paused,
                      unsigned               modulo)
    {
      if (thread_was_paused || (0 == (frame_count % modulo))) {
        std::ostringstream ostr;

        ostr << '#' << std::setfill('0') << std::setw(6) << frame_count << ": ";

        clock::duration distance;

        using std::chrono::milliseconds;
        using std::chrono::duration_cast;

        if (thread_was_paused) {
          ostr << "idle for  ";
          distance = timeout - activity;

          ostr << std::setfill('0') << std::setw(6)
               << duration_cast<milliseconds>(distance).count() << " msec";
        } else {
          if (timeout > activity) {
            ostr << "slept for ";
            distance = timeout - activity;
          } else {
            ostr << "missed by ";
            distance = activity - timeout;
          }

          ostr << std::setfill('0') << std::setw(6)
               << duration_cast<milliseconds>(distance).count() << " msec";;
        }

        os << trace::prefix() << ' ' << ctx << ": " << ostr.str() << '\n';
      }

      ++frame_count;
    }
  
  } // namespace support {
  
} // namespace hugh {
