// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/string.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/thread.hpp"

// includes, system

#define GLIBCXX_NO_CODECVT 20150212

#if !defined(__GLIBCXX__) || (defined(__GLIBCXX__) && (__GLIBCXX__ > GLIBCXX_NO_CODECVT))
#  include <codecvt> // std::codecvt_utf8<>
#endif

#include <locale>    // std::wstring_convert<>

// includes, project

// #include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {
  
  namespace support {
  
    // variables, exported
  
    // functions, exported
  
    std::wstring
    string_to_wstring(std::string const& a)
    {
      TRACE("hugh::support::string_to_wstring");
    
      return std::wstring(a.begin(), a.end());
    }

    std::string
    wstring_to_string(std::string const& a)
    {
      TRACE("hugh::support::wstring_to_string(std::string)");

      return a;
    }

    std::string
    wstring_to_string(std::wstring const& a)
    {
      TRACE("hugh::support::wstring_to_string(std::wstring)");

#if defined(__GLIBCXX__) && (__GLIBCXX__ <= GLIBCXX_NO_CODECVT)
      return std::string(a.begin(), a.end());
#else
      return std::wstring_convert<std::codecvt_utf8<wchar_t>, wchar_t>().to_bytes(a);
#endif
    }

  } // namespace support {

} // namespace hugh {
