// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/trace.cpp                                                     */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <sstream> // std::ostringstream

// includes, project

// #include <>

#define HUGH_USE_TRACE
// #undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  struct init_test_base {

    virtual ~init_test_base()
    {
      TRACE("<unnamed>::init_test_base::~init_test_base");
    }
    
    virtual void method()
    {
      TRACE("<unnamed>::init_test_base::method");
    }

  protected:

    explicit init_test_base()
    {
      TRACE("<unnamed>::init_test_base::init_test_base");
    }
    
  };
  
  struct static_init_test : public init_test_base {
    
    static_init_test()
      : init_test_base()
    {
      TRACE("<unnamed>::static_init_test::static_init_test");
    }
  
    virtual ~static_init_test()
    {
      TRACE("<unnamed>::static_init_test::~static_init_test");
    }
    
  } static_init_test_default_instance;

  struct dynamic_init_test : public init_test_base {
    
    dynamic_init_test()
      : init_test_base()
    {
      TRACE("<unnamed>::dynamic_init_test::dynamic_init_test");
    }
  
    virtual ~dynamic_init_test()
    {
      TRACE("<unnamed>::dynamic_init_test::~dynamic_init_test");
    }

    virtual void method()
    {
      TRACE("<unnamed>::dynamic_init_test::method");

      init_test_base::method();
    }
    
  };
  
  // variables, internal
  
  // functions, internal

  void
  test_func()
  {
    TRACE("<unnamed>::test_func");
    
    {
      TRACE("<unnamed>::test_func: scope");
      
      static_init_test  static_init_test_instance;
      dynamic_init_test dynamic_init_test_instance;
    }  
  }

} // namespace {

// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_trace)
{
  TRACE_FUNC;

  dynamic_init_test dynamic_init_test_instance;
  
  test_func();

  dynamic_init_test_instance.method();
  
  BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_hugh_support_trace_prefix)
{
  TRACE_FUNC;
  
  std::string const pfx1(hugh::support::trace::prefix());
  std::string const pfx2(hugh::support::trace::prefix());

  BOOST_CHECK(pfx1 != pfx2);
  
  std::ostringstream ostr;

  ostr << pfx1 << ".\n" << pfx2 << '.';

  BOOST_TEST_MESSAGE(ostr.str());
}
