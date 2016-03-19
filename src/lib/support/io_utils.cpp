// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io_utils.cpp                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/io_utils.hpp"

// includes, system

#include <array>  // std::array<>
#include <bitset> // std::bitset<>

// includes, project

// #include <>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal
  
} // namespace {

namespace hugh {
  
  namespace support {

    namespace istream  {
    
      // variables, exported
  
      // functions, exported
    
    } // namespace istream  {
  
    namespace ostream  {
    
      // variables, exported
  
      // functions, exported

      /* explicit */
      binary::binary(unsigned a)
        : value_(a)
      {}

      /* virtual */ void
      binary::print_on(std::ostream& os) const
      {
#if 0
        os << '[' << std::bitset<32>(value_) << ']';
#else
        static std::array<std::pair<unsigned const, unsigned const>, 8> const blocks = {
          {
            std::make_pair(0xf0000000, 28),
            std::make_pair(0x0f000000, 24),
            std::make_pair(0x00f00000, 20),
            std::make_pair(0x000f0000, 16),
            std::make_pair(0x0000f000, 12),
            std::make_pair(0x00000f00,  8),
            std::make_pair(0x000000f0,  4),
            std::make_pair(0x0000000f,  0),
          }
        };
      
        os << '[';
      
        for (auto b : blocks) {
          os << std::bitset<4>((value_ & b.first) >> b.second) << '.';
        }
      
        os << "\b]";
#endif
      }
    
    } // namespace ostream  {

    namespace iostream  {
    
      // variables, exported
  
      // functions, exported
    
    } // namespace iostream  {
  
  } // namespace support {
  
} // namespace hugh {
