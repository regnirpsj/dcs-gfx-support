// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/string.hpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_STRING_HPP)

#define HUGH_SUPPORT_STRING_HPP

// includes, system

#include <string> // std::string, std::wstring

// includes, project

#include <hugh/support/export.h>

namespace hugh {
  
  namespace support {
  
    // types, exported (class, enum, struct, union, typedef)
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    HUGH_SUPPORT_EXPORT std::wstring string_to_wstring(std::string  const&);
    HUGH_SUPPORT_EXPORT std::string  wstring_to_string(std::string  const&);
    HUGH_SUPPORT_EXPORT std::string  wstring_to_string(std::wstring const&);
  
  } // namespace support {
  
} // namespace hugh {
  
#endif // #if !defined(HUGH_SUPPORT_STRING_HPP)
