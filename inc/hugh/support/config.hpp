// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/config.hpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_CONFIG_HPP)

#define HUGH_SUPPORT_CONFIG_HPP

// includes, system

#include <boost/system/api_config.hpp> // BOOST_POSIX_API || BOOST_WINDOWS_API

// includes, project

//#include <>

// macros

#if defined(__GNUC__)
#  define __GNUC_VER (__GNUC__ * 10000 + __GNUC_MINOR__ * 100 + __GNUC_PATCHLEVEL__)
#endif

#if defined(__clang__)
#  define __CLANG_VER (__clang_major__ * 10000 + __clang_minor__ * 100 + __patch_patchlevel__)
#endif

// noexcept
#if defined(_MSC_VER) && (_MSC_VER < 1900)
#  define noexcept
#endif

// thread_local
#if defined(__GNUC__) && (__GNUC_VER < 40800) && !defined(__clang__)
#  pragma message("Note: using GCC '__thread' implement 'thread_local' c++ keyword")
#  define thread_local __thread
#elif defined(_MSC_VER) && (_MSC_VER < 1900)
#  pragma message("Note: using __declspec(thread) to implement 'thread_local' c++ keyword")
#  define thread_local __declspec(thread)
#endif

namespace hugh {
  
  namespace support {
  
    // types, exported (class, enum, struct, union, typedef)

    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)
  
  } // namespace support {

} // namespace hugh {
    
#endif // #if !defined(HUGH_SUPPORT_CONFIG_HPP)
