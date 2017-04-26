// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/io_position_saver.cpp                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::stringstream

// includes, project

#include <hugh/support/io/position_saver.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_support_io_position_saver)
{
  using namespace hugh::support;
  
  std::string       text("1234567890");
  std::stringstream iostr;

  {
    ostream::position_saver const ops(iostr);

    iostr << text;
  }

  BOOST_CHECK       (0 == iostr.tellp());
  BOOST_TEST_MESSAGE('\n' << iostr.str());

  {
    istream::position_saver const ips(iostr);

    iostr >> text;
  } 
  
  BOOST_CHECK       (0 == iostr.tellg());
  BOOST_TEST_MESSAGE('\n' << iostr.str() << ':' << text);
  
  {
    iostream::position_saver const iops(iostr);

    std::reverse(text.begin(), text.end());
    
    iostr << text;
    iostr >> text;
  } 

  BOOST_CHECK       (0 == iostr.tellp());
  BOOST_CHECK       (0 == iostr.tellg());
  BOOST_TEST_MESSAGE('\n' << iostr.str() << ':' << text);
}
