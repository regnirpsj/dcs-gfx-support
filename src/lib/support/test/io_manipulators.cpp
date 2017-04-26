// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/io_manipulators.cpp                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <iostream> // std::cout, std::endl
#include <sstream>  // std::ostringstream

// includes, project

#include <hugh/support/io/manipulators.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_support_io_manipulators_remove_buffered_stream)
{
  using namespace hugh::support;
  using ostream::remove;

  unsigned const               count(6);
  std::ostringstream           ostr;
  std::ostringstream::pos_type tellp[4];
    
  tellp[0] = ostr.tellp(); ostr << "Hello, Monde!";
  tellp[1] = ostr.tellp(); ostr << remove(count);
  tellp[2] = ostr.tellp(); ostr << "World!";
  tellp[3] = ostr.tellp();
  
  BOOST_CHECK(ostr.good() && !ostr.bad());
  BOOST_CHECK(tellp[1] == tellp[3]);
  BOOST_CHECK(count == (tellp[3] - tellp[2]));
  
  BOOST_TEST_MESSAGE(ostr.str()
                     << " ["
                     << tellp[0] << ':'
                     << tellp[1] << ':'
                     << tellp[2] << ':'
                     << tellp[3]
                     << ']');
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_manipulators_remove_unbuffered_stream)
{
  using namespace hugh::support;
  using ostream::remove;

  unsigned const         count(6);
  std::ostream::pos_type tellp[4];
  
  tellp[0] = std::cout.tellp(); std::cout << "hello, monde!";
  tellp[1] = std::cout.tellp(); std::cout << remove(count);
  tellp[2] = std::cout.tellp(); std::cout << "world!";
  tellp[3] = std::cout.tellp();
  
  BOOST_CHECK(std::cout.good() && !std::cout.bad());
  BOOST_CHECK(tellp[1] == tellp[3]);
  
  BOOST_TEST_MESSAGE(" ["
                     << tellp[0] << ':'
                     << tellp[1] << ':'
                     << tellp[2] << ':'
                     << tellp[3]
                     << ']');
}
