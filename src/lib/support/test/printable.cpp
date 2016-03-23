// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/printable.cpp                                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <iomanip> // std::boolalpha
#include <memory>  // std::unique_ptr<>
#include <ostream> // std::ostream

// includes, project

#include <hugh/support/printable.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)
  
  class printable_derived : public hugh::support::printable {

  public:

    explicit printable_derived()
      : hugh::support::printable(),
        attribute_b_            (false),
        attribute_f_            (-3.141f)
    {}
    
    virtual void print_on(std::ostream& os) const
    {
      os << '['
         << std::boolalpha << attribute_b_ << ','
         <<                   attribute_f_
         << ']';
    }

  private:

    bool  attribute_b_;
    float attribute_f_;
    
  };

  class printable_derived_derived : public printable_derived {

  public:

    explicit printable_derived_derived()
      : printable_derived(),
        attribute_c_  ('?'),
        attribute_u_  (42)
    {}
    
    virtual void print_on(std::ostream& os) const
    {
      os << '[';

      printable_derived::print_on(os);
      
      os << ','
         << std::boolalpha << attribute_c_ << ','
         <<                   attribute_u_
         << ']';
    }

  private:

    char     attribute_c_;
    unsigned attribute_u_;
    
  };
  
  // variables, internal
  
  // functions, internal

} // namespace {
  
// variables, exported
  
// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_printable_derived)
{
  BOOST_TEST_MESSAGE('\n'
                     << "printable_derived:         " << printable_derived()         << '\n'
                     << "printable_derived_derived: " << printable_derived_derived());
  BOOST_CHECK(true);
}

BOOST_AUTO_TEST_CASE(test_hugh_support_printable_derived_via_base)
{
  std::unique_ptr<hugh::support::printable> p(new printable_derived_derived);
  
  BOOST_TEST_MESSAGE('\n'
                     << "printable: " << *p);
  BOOST_CHECK(true);
}
