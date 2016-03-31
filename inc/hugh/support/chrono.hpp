// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/chrono.hpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_CHRONO_HPP)

#define HUGH_SUPPORT_CHRONO_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <chrono>                // std::chrono::*
#include <iosfwd>                // std::ostream (fwd)
#include <string>                // std::string

// includes, project

#include <hugh/support/config.hpp>
#include <hugh/support/export.h>

namespace hugh {
  
  namespace support {
  
    // types, exported (class, enum, struct, union, typedef)

    class HUGH_SUPPORT_EXPORT clock : private boost::noncopyable {

    public:

      using duration   = std::chrono::nanoseconds;
      using rep        = duration::rep;
      using period     = duration::period;
      using time_point = std::chrono::time_point<clock, duration>;
    
      static bool const     is_monotonic; // = true
      static duration const resolution;
    
      static time_point now() throw();
    
    };

    class HUGH_SUPPORT_EXPORT timer : private boost::noncopyable {

    public:

      using duration   = clock::duration;
      using time_point = clock::time_point;

      explicit timer();
      ~timer();

      time_point reset();
      duration   lapse() const;

    private:
    
      time_point start_;

    };

    class HUGH_SUPPORT_EXPORT timer_guard : private boost::noncopyable {

    public:

      using duration = clock::duration;
    
      explicit timer_guard(duration&);
      ~timer_guard();
    
    private:
    
      duration& duration_;
      timer     timer_;

    };
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    HUGH_SUPPORT_EXPORT void        sleep(clock::duration const&);
    HUGH_SUPPORT_EXPORT std::string date_time_iso8601();

    /**
     * \brief inserts a \c clock::time_point into an \c std::ostream (or derived)
     *
     * inserts a \c clock::time_point into an \c std::ostream (or derived). the \c clock::time_point
     * object is inserted as a \c clock::duration by subtracting an static internal
     * \c clock::time_point from it, which is initialized once at process startup.
     *
     * \param  os \c std::ostream&
     * \param  a  \c clock::time_point
     *
     * \return modified ostream
     *
     * \throw  nothing
     */
    HUGH_SUPPORT_EXPORT std::ostream& operator<<(std::ostream&, clock::time_point const&);
  
  } // namespace support {

} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_CHRONO_HPP)
