// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/refcounted.hpp                                                     */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_REFCOUNTED_HPP)

#define HUGH_SUPPORT_REFCOUNTED_HPP

// includes, system

#include <boost/smart_ptr/intrusive_ref_counter.hpp> // boost::intrusive_ref_counter<>

// includes, project

//#include <>

namespace hugh {
  
  namespace support {
  
    // types, exported (class, enum, struct, union, typedef)

    template <typename T>
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1800))
    using refcounted =        boost::intrusive_ref_counter<T, boost::thread_safe_counter>;
#else
    class refcounted : public boost::intrusive_ref_counter<T, boost::thread_safe_counter> {
    };
#endif
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)
  
  } // namespace support {

} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_REFCOUNTED_HPP)
