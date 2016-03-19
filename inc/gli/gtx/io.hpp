// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  gli/gtx/io.hpp                                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_GLI_GTX_IO_HPP)

#define HUGH_GLI_GTX_IO_HPP

// includes, system

#include <gli/gli.hpp> // gli::format, gli::texture?D
#include <iosfwd>      // std::basic_ostream<> (fwd)

// includes, project

// #include <>

namespace gli {
    
  // types, exported (class, enum, struct, union, typedef)

  // variables, exported (extern)

  // functions, inlined (inline)

  template <typename CTy, typename CTr>
  std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, format const&);
  template <typename CTy, typename CTr>
  std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, target const&);
  template <typename CTy, typename CTr>
  std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, texture1d const&);
  template <typename CTy, typename CTr, typename T>
  std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, texture2d const&);
  template <typename CTy, typename CTr>
  std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, texture3d const&);
  
  // functions, exported (extern)
  
} // namespace gli {

#include <gli/gtx/io.inl>

#endif // #if !defined(HUGH_GLI_GTX_IO_HPP)
