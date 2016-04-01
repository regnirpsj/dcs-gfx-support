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
        using char_type = std::ostream::char_type;
        
        format_punct<char_type> const& fmt(get_facet<format_punct<char_type>>(os));

        if (fmt.formatted) {
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
      
          os << fmt.delim_left;
      
          for (auto b : blocks) {
            os << std::bitset<4>((value_ & b.first) >> b.second) << fmt.separator;
          }
      
          os << remove(1)
             << fmt.delim_right;
        } else {
          os << std::bitset<32>(value_);
        }
      }
    
    } // namespace ostream  {

    namespace iostream  {
    
      // variables, exported
  
      // functions, exported
    
    } // namespace iostream  {
  
  } // namespace support {
  
} // namespace hugh {
