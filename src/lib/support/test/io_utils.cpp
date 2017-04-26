// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/io_utils.cpp                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <boost/concept_check.hpp> // boost::ignore_unused_variable_warning<>
#include <iomanip>                 // std::setfill, std:setw
#include <iostream>                // std::cout, std::endl
#include <memory>                  // std::unique_ptr<>
#include <sstream>                 // std::ostringstream
#include <typeinfo>                // typeid usage

// includes, project

#include <hugh/support/io_utils.hpp>
#include <hugh/support/string.hpp>
#include <hugh/support/type_info.hpp>

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
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>



