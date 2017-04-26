// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/io_printer.cpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>   // std::array<>
#include <iomanip> // std::setw, std::setfill

// includes, project

#include <hugh/support/io/manipulators.hpp>
#include <hugh/support/io/printer.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_io_printer_binary)
{
  using namespace hugh::support;

  unsigned const n(1234567890);

  {
    std::ostringstream ostr;
    
    ostr << n << " -> "
         << ostream::unformatted << ostream::binary(n);
    
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }

  {
    std::ostringstream ostr;
    
    ostr << n << " -> "
         << ostream::delimeter<char>('[', ']', '.') << ostream::formatted << ostream::binary(n);
    
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_printer_enumeration)
{
  enum class type {
    T1 = 1, T2 = 2, T3 = -1, T4 = 0,
  };
  
  static std::array<std::pair<type const, std::string const>, 4> const types = {
    std::make_pair(type::T1, "type::T1"),
    std::make_pair(type::T2, "type::T2"),
    std::make_pair(type::T3, "type::T3"),
    std::make_pair(type::T4, "type::T4"),
  };
  
  for (auto t : types) {
    using hugh::support::ostream::enumerate;

    std::ostringstream ostr;

    ostr << enumerate(t.first, types);

    BOOST_CHECK       (t.second == ostr.str());
    BOOST_TEST_MESSAGE(ostr.str());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_printer_bitmask)
{
  static std::array<unsigned const, 27> const primes_plus = {
    0, 1,
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
  };
  static std::array<std::pair<unsigned const, std::string const>, 8> const masks = {
    std::make_pair(0x0040, "SIXTYFOUR"),
    std::make_pair(0x0020, "THIRTYTWO"),
    std::make_pair(0x0010, "  SIXTEEN"),
    std::make_pair(0x0008, "    EIGHT"),
    std::make_pair(0x0004, "     FOUR"),
    std::make_pair(0x0002, "      TWO"),
    std::make_pair(0x0001, "      ONE"),
    std::make_pair(0x0000, "     ZERO"),
  };
  
  for (auto f : primes_plus) {
    using hugh::support::ostream::flags;
    using hugh::support::ostream::remove;
    
    std::ostringstream ostr;

    ostr << flags(f, masks) << remove(1);
      
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE(   std::setw(2) << std::setfill('0')                               << f
                       << ":0x"
                       << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << f
                       << ':'
                       << ostr.str());
  }
}

