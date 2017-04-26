// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/io_scoped_redirect.cpp                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <iostream> // std::cer, std::clog, std::cout
#include <sstream>  // std::stringstream

// includes, project

#include <hugh/support/io/scoped_redirect.hpp>

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

BOOST_AUTO_TEST_CASE(test_hugh_support_io_scoped_redirect)
{
  using namespace hugh::support;

  {
    std::ostringstream ostr;

    {
      ostream::scoped_redirect const sor_cerr(std::cerr, ostr);
      ostream::scoped_redirect const sor_clog(std::clog, ostr);
      ostream::scoped_redirect const sor_cout(std::cout, ostr);

      std::cerr << "abc";
      std::clog << "ijk";
      std::cout << "xyz";
    }

    BOOST_CHECK       (!ostr.str().empty());
    BOOST_CHECK       (9 == ostr.str().length());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }

  {
    std::ostringstream ostr;

    {
      ostream::scoped_redirect const sor_call({ &std::cerr, &std::clog, &std::cout }, ostr);

      std::cerr << "zyx";
      std::clog << "kji";
      std::cout << "cba";
    }

    BOOST_CHECK       (!ostr.str().empty());
    BOOST_CHECK       (9 == ostr.str().length());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }

  {
    std::ostringstream ostr;

    {
      ostream::scoped_redirect const sor_call({ &std::cerr, &std::clog, &std::cout }, ostr);

      std::cerr << "zyx";
      std::clog << "kji";
      std::cout << "cba";
    }

    BOOST_CHECK       (!ostr.str().empty());
    BOOST_CHECK       (9 == ostr.str().length());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }

  {
    std::ostringstream ostr;

    {
      ostream::scoped_redirect const sor_nullptr({ nullptr }, ostr);

      BOOST_TEST_MESSAGE('\n' << "nebelbeisiebleben");
    }

    BOOST_CHECK(ostr.str().empty());
  }

  {
    std::ostringstream ostr;

    {
      ostream::scoped_redirect const sor_empty({ }, ostr);

      BOOST_TEST_MESSAGE('\n' << "nebelbeisiebleben");
    }

    BOOST_CHECK(ostr.str().empty());
  }
}
