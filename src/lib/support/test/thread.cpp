// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/thread.cpp                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <future>  // std::future<>, std::packaged_task<>
#include <sstream> // std::ostringstream

// includes, project

#include <hugh/support/thread.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  // variables, internal
  
  // functions, internal
  
} // namespace {

// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_thread_pool_ctor)
{
  using namespace hugh::support;

  {
    std::unique_ptr<thread::pool> p(new thread::pool(1));
  
    BOOST_CHECK(nullptr != p);
    BOOST_CHECK(1       == p->size());
  }

  {
    std::unique_ptr<thread::pool> p(new thread::pool(0));
  
    BOOST_CHECK(nullptr != p);
    BOOST_CHECK(1       == p->size());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_thread_pool_submit)
{
  TRACE("test_hugh_support_thread_pool_submit");
  
  using namespace hugh::support;

  clock::duration const d(std::chrono::microseconds(250));
  unsigned const        c((3 * boost::thread::hardware_concurrency()) + 1);
  unsigned const        l((4*c)/3);
  thread::pool          p(c);

  BOOST_CHECK(c == p.size());
  
  {
    TRACE("test_hugh_support_thread_pool_submit:1:" + std::to_string(p.size()) + ":" +
          std::to_string(l));
    
    for (unsigned i(0); i < l; ++i) {
      p.submit([=](){
          //TRACE("test_hugh_supprt_thread_pool_submit:1:lambda" + std::to_string(i));
          
          sleep(d + std::chrono::microseconds(i % 10));
        });
    }
  }

  {
    TRACE("test_hugh_support_thread_pool_submit:2:" + std::to_string(p.size()) + ":" +
          std::to_string(l));

    std::vector<std::future<unsigned>> fl;
    
    for (unsigned i(0); i < l; ++i) {
      std::packaged_task<unsigned ()> t([=](){
          //TRACE("test_hugh_support_thread_pool_submit:2:lambda" + std::to_string(i));
          
          sleep(d + std::chrono::microseconds(i % 10));
          
          return i;
        });
      
      fl.push_back(t.get_future());
      
      p.submit(t);
    }

    for (auto& f : fl) {
      f.get();
    }
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_stats)
{
  using namespace hugh::support;

  clock::duration const sleep_time(std::chrono::milliseconds(11));
  clock::duration       lapse;
  timer const           t;
  std::ostringstream    ostr;
  
  for (unsigned i(0); i < 20; ++i) {
    clock::duration const start(t.lapse());
    {
      sleep(( 9 * sleep_time) / 10);
      lapse = t.lapse();
      sleep((11 * sleep_time) / 10);
    }
    clock::duration const stop(t.lapse());

    BOOST_CHECK(stop > start);
    
    dump_thread_stats(ostr, "test_support_stats", stop - start, lapse - start, false, 4);

    sleep(sleep_time / 100);
  }

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE( ostr.str());
}
