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
#include <sstream> // std::[w]ostringstream

// includes, project

#include <hugh/support/printable.hpp>
#include <hugh/support/string.hpp>
#include <hugh/support/type_info.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  namespace derived {
    
    class printable : public hugh::support::printable {

    public:

      explicit printable()
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

    namespace derived {
      
      class printable : public ::derived::printable {

      public:

        explicit printable()
          : ::derived::printable(),
            attribute_c_      ('?'),
            attribute_u_      (42)
        {}
    
        virtual void print_on(std::ostream& os) const
        {
          os << '[';

          ::derived::printable::print_on(os);
      
          os << ','
             << std::boolalpha << attribute_c_ << ','
             <<                   attribute_u_
             << ']';
        }

      private:

        char     attribute_c_;
        unsigned attribute_u_;
    
      };

    } // namespace derived {
    
  } // namespace derived {
  
  namespace derived1 {
    
    class printable : public hugh::support::printable {

    public:

      explicit printable()
        : hugh::support::printable(),
          attribute_u_            (+1),
          attribute_s_            (-1)
      {}
    
      virtual void print_on(std::ostream& os) const
      {
        os << '['
           << attribute_u_ << ','
           << attribute_s_
           << ']';
      }

    private:

      unsigned attribute_u_;
      signed   attribute_s_;
    
    };

  } // namespace derived1 {
  
  // variables, internal
  
  // functions, internal

} // namespace {
  
// variables, exported
  
// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

using ostream_types = boost::mpl::list<std::ostringstream,
                                       std::wostringstream>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_printable_derived, T, ostream_types)
{
  using hugh::support::demangle;
  
  T ostr;

  // using 'demangle(typeid(T)).c_str()' to allow insertion of narrow string in either stream type
  ostr << '\n' << demangle(typeid(T)).c_str() << '\n'
       << "derived::printable:          " << derived::printable()          << '\n'
       << "derived::derived::printable: " << derived::derived::printable();

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE(hugh::support::wstring_to_string(ostr.str()));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_printable_derived_via_base, T, ostream_types)
{
  using hugh::support::demangle;
  using hugh::support::printable;
  
  std::unique_ptr<printable> p(new derived::derived::printable);

  T ostr;
  
  // using 'demangle(typeid(T)).c_str()' to allow insertion of narrow string in either stream type
  ostr << '\n' << demangle(typeid(T)).c_str() << '\n'
       << "printable: " << *p;
  
  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE(hugh::support::wstring_to_string(ostr.str()));
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_printable_print_on_throw, T, ostream_types)
{
  class derived : public hugh::support::printable {

  public:

    virtual void print_on(std::ostream& os) const
    {
      hugh::support::printable::print_on(os);
    }
    
  };

  std::unique_ptr<hugh::support::printable> p(new derived);
  T                                         ostr;
  
  BOOST_REQUIRE_THROW(p->print_on(ostr), std::logic_error);
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_printable_multiple_inheritance, T, ostream_types)
{
  class final : public derived::derived::printable,
                public derived1::printable {

  public:

    virtual void print_on(std::ostream& os) const
    {
      os << '[';

      derived::derived::printable::print_on(os);
      
      os << ',';

      derived1::printable::print_on(os);
      
      os << ']';
    }
    
  };

  using hugh::support::demangle;
  
  T ostr;

  // using 'demangle(typeid(T)).c_str()' to allow insertion of narrow string in either stream type
  ostr << '\n' << demangle(typeid(T)).c_str() << '\n'
       << "final: " << final();

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE(hugh::support::wstring_to_string(ostr.str()));
}
