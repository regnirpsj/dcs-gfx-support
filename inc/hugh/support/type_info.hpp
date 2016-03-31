// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/type_info.hpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_TYPE_INFO_HPP)

#define HUGH_SUPPORT_TYPE_INFO_HPP

// includes, system

#include <new>    // std::nothrow_t, std::nothrow (for caller convenience)
#include <string> // std::string

// includes, project

#include <hugh/support/config.hpp>
#include <hugh/support/export.h>

namespace std {

  class type_info;

}

namespace hugh {
  
  namespace support {
  
    // types, exported (class, enum, struct, union, typedef)

    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    /**
     * \brief returns the demangled type name of an object
     *
     * returns the demangled type name of an object represented by an \c std::type_info object
     *
     * \param  tinfo \c std::type_info object of an actual object
     *
     * \retval demangled type name
     *
     * \throw  std::bad_alloc
     * \throw  std::domain_error
     * \throw  std::invalid_argument
     */
    HUGH_SUPPORT_EXPORT std::string demangle(std::type_info const&);

    /**
     * \brief returns the demangled type name of an object
     *
     * returns the demangled type name of an object represented by an \c std::type_info object
     * this version internally calls the throwing \c support::demangle function and catches any
     * \c std::exceptions. in such a case the unmangled type name is returned.
     *
     * \param  tinfo        \c std::type_info object of an actual object
     * \param  std::nothrow \c std::nothrow signature disambiguation tag
     *
     * \retval demangled type name or unmangled name if demangling fails
     *
     * \throw  nothing
     */
    HUGH_SUPPORT_EXPORT std::string demangle(std::type_info const&, std::nothrow_t const&) noexcept;
  
  } // namespace support {

} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_TYPE_INFO_HPP)
