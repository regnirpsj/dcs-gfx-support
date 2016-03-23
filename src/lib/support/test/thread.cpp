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

#include <iostream> // std::cout

// includes, project

#include <hugh/support/thread.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_stats)
{
  using namespace hugh::support;

  clock::duration const sleep_time(std::chrono::milliseconds(50));
  clock::duration       lapse;
  timer const           t;
  
  for (unsigned i(0); i < 20; ++i) {
    clock::duration const start(t.lapse());
    {
      sleep(( 9 * sleep_time) / 10);
      lapse = t.lapse();
      sleep((11 * sleep_time) / 10);
    }
    clock::duration const stop(t.lapse());
    
    dump_thread_stats(std::cout, "test_support_stats",
                      stop - start, lapse - start, false, 4);

    sleep(sleep_time / 100);
  }
}
