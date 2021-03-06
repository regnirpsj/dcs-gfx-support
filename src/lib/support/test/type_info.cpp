// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/type_info.cpp                                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <string>   // std::string
#include <typeinfo> // typeid usage
#include <vector>   // std::vector<>

// includes, project

#include <hugh/support/type_info.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  class udt_base { /* ... */ };

  class udt_derived : public udt_base { /* ... */ };

  using string_list_type = std::vector<std::string>;
  
  // variables, internal
  
  // functions, internal
  
} // namespace {
  
// variables, exported
  
// functions, exported  

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

using types = boost::mpl::list<bool,
                               char,
                               int,
                               float,
                               double,
                               udt_derived,
                               string_list_type>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_type_info_demangle, T, types)
{
  using namespace hugh::support;
  
  BOOST_CHECK       (typeid(T) == typeid(T));
  BOOST_TEST_MESSAGE(demangle(typeid(T)) << "\t: " << typeid(T).name());
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_type_info_demangle_nothrow, T, types)
{
  using namespace hugh::support;
  
  BOOST_CHECK       (typeid(T) == typeid(T));
  BOOST_TEST_MESSAGE(demangle(typeid(T), std::nothrow) << "\t: " << typeid(T).name());
}
