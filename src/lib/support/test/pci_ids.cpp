// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/pci_ids.cpp                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

//#include <>

// includes, project

#include <hugh/support/pci_ids.hpp>

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
#include <boost/test/output_test_stream.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_pci_vendor_name)
{
  using namespace hugh::support;

  pci::vendor const v(0x8086);
  
  BOOST_CHECK(!v.name().empty());
}

BOOST_AUTO_TEST_CASE(test_hugh_support_pci_vendor_print_on)
{
  using namespace hugh::support;

  pci::vendor const v(0x8086);
  
  BOOST_CHECK(!v.name().empty());

  boost::test_tools::output_test_stream output;

  v.print_on(output);

  BOOST_TEST_MESSAGE(output.str());
}
