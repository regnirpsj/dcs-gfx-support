// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/refcounted.cpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>                   // std::array<>
#include <boost/intrusive_ptr.hpp> // boost::intrusive_ptr<>
#include <condition_variable>      // std::condition_variable
#include <iomanip>                 // std::setfill, std::setw
#include <memory>                  // std::unique_ptr<>
#include <mutex>                   // std::mutex
#include <thread>                  // std::thread

// includes, project

#include <hugh/support/chrono.hpp>
#include <hugh/support/refcounted.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  class refcounted_test : public hugh::support::refcounted<refcounted_test> { /* ... */ };

  class refcount_user {

  public:

    explicit refcount_user(refcounted_test* a)
      : rt_(a)
    {}

    ~refcount_user()
    {}
    
  private:

    boost::intrusive_ptr<refcounted_test> rt_;
    
  };
  
  // variables, internal
  
  // functions, internal
  
} // namespace {

// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_refcounted_ctor)
{
  boost::intrusive_ptr<refcounted_test> a(new refcounted_test);

  BOOST_CHECK(1 == a->use_count());
  {
    refcount_user b(a.get());

    BOOST_CHECK(2 == a->use_count());
  }
  BOOST_CHECK(1 == a->use_count());
}

BOOST_AUTO_TEST_CASE(test_hugh_support_refcounted_replace)
{
  boost::intrusive_ptr<refcounted_test> a(new refcounted_test);

  BOOST_CHECK(1 == a->use_count());
  {
    boost::intrusive_ptr<refcounted_test> b(a);

    BOOST_CHECK(a == b.get());
    BOOST_CHECK(2 == b->use_count());
    BOOST_CHECK(2 == a->use_count());
    
    b = new refcounted_test;

    BOOST_CHECK(a != b.get());
    BOOST_CHECK(1 == b->use_count());
    BOOST_CHECK(1 == a->use_count());
  }
  BOOST_CHECK(1 == a->use_count());
}

#if 0
BOOST_AUTO_TEST_CASE(test_hugh_support_refcounted_async)
{
  std::string const                     l(20, '-'); 
  boost::intrusive_ptr<refcounted_test> a(new refcounted_test);

  BOOST_CHECK       (1 == a->use_count());
  BOOST_TEST_MESSAGE(std::right << std::setfill(' ') << std::setw(6)
                     <<std::this_thread::get_id() << ':' << a->use_count() << '\n' << l);

  {
    std::array<std::unique_ptr<std::thread>, 9> tp = { { } };
    unsigned                                    f(0);
    std::condition_variable                     cv;
    std::mutex                                  m;
    
    for (auto& t : tp) {
      t.reset(new std::thread([&]{
            refcount_user const b(a.get());

            {
              std::lock_guard<std::mutex> lk(m);

              ++f;
              
              BOOST_CHECK       (1           <  a->use_count());
              BOOST_CHECK       (tp.size()+1 >= a->use_count());
              BOOST_TEST_MESSAGE(std::right << std::setfill(' ') << std::setw(6)
                                 << std::this_thread::get_id() << ':' << a->use_count()
                                 << ':' << f);
            }

            cv.notify_one();
          }));
    
      t->detach();
    }
    
    {
      std::unique_lock<std::mutex> lk(m);
      
      cv.wait(lk, [&]{ return tp.size() <= f; });
    }
  }

  BOOST_CHECK       (1 == a->use_count());
  BOOST_TEST_MESSAGE(l << '\n'
                     << std::right << std::setfill(' ') << std::setw(6)
                     << std::this_thread::get_id() << ':' << a->use_count());
}
#endif
