// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/io_operators.cpp                                              */
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

#include <hugh/support/io/manipulators.hpp>
#include <hugh/support/io/operators.hpp>
#include <hugh/support/io/scoped_redirect.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  std::array<unsigned const, 19> const number_array = {
    {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0
    }
  };

  std::array<std::pair<unsigned const, double const>, 19> const key_value_array = {
    {
#if defined(_MSC_VER) && (_MSC_VER <= 1700)
      std::make_pair(0, 0.0),
      std::make_pair(1, 0.1),
      std::make_pair(2, 0.2),
      std::make_pair(3, 0.3),
      std::make_pair(4, 0.4),
      std::make_pair(5, 0.5),
      std::make_pair(6, 0.6),
      std::make_pair(7, 0.7),
      std::make_pair(8, 0.8),
      std::make_pair(9, 0.9),
      std::make_pair(8, 0.8),
      std::make_pair(7, 0.7),
      std::make_pair(6, 0.6),
      std::make_pair(5, 0.5),
      std::make_pair(4, 0.4),
      std::make_pair(3, 0.3),
      std::make_pair(2, 0.2),
      std::make_pair(1, 0.1),      
      std::make_pair(0, 0.0),
#else
      {0, 0.0}, {1, 0.1}, {2, 0.2}, {3, 0.3}, {4, 0.4}, {5, 0.5}, {6, 0.6}, {7, 0.7}, {8, 0.8},
      {9, 0.9},
      {8, 0.8}, {7, 0.7}, {6, 0.6}, {5, 0.5}, {4, 0.4}, {3, 0.3}, {2, 0.2}, {1, 0.1}, {0, 0.0},
#endif
    }
  };
  
  // functions, internal

  bool
  dummy_function_for_std_function_test(float a)
  {
    return 0.0 < a;
  }
  
  template <typename CTy>
  std::basic_string<CTy>
  demangle(std::type_info const& t)
  {
    return hugh::support::demangle(t);
  }
  
  template <>
  std::wstring
  demangle<wchar_t>(std::type_info const& t)
  {
    return hugh::support::string_to_wstring(demangle<char>(t));
  }

  template <typename CTy, typename CTr>
  bool
  test_array(std::basic_ostream<CTy, CTr>& os)
  {
    TRACE("<unnamed>::test_sequence");
    
    auto const s(number_array);

    using namespace hugh::support;
    
    ostream::basic_format_saver<CTy> fs(os);
    
    using ostream::operator<<;
    
    os << '\n'
       << demangle<CTy>(typeid(s)) << ": formatted\n"
       << ostream::formatted << s
       << '\n'
       << demangle<CTy>(typeid(s)) << ": unformatted\n"
       << ostream::unformatted << ' ' << s;

    return !s.empty() && os.good();
  }
  
  template <typename Sequence, typename CTy, typename CTr>
  bool
  test_sequence(std::basic_ostream<CTy, CTr>& os)
  {
    TRACE("<unnamed>::test_sequence");
    
    Sequence const s(number_array.begin(), number_array.end());

    using namespace hugh::support;
    
    ostream::basic_format_saver<CTy> fs(os);
    
    using ostream::operator<<;
    
    os << '\n'
       << demangle<CTy>(typeid(s)) << ": empty\n"
       << ostream::formatted << Sequence()
       << '\n'
       << demangle<CTy>(typeid(s)) << ": formatted\n"
       << ostream::formatted << s
       << '\n'
       << demangle<CTy>(typeid(s)) << ": unformatted\n"
       << ostream::unformatted << ' ' << s;

    return !s.empty() && os.good();
  }

  template <typename Sequence, typename CTy, typename CTr>
  bool
  test_associative(std::basic_ostream<CTy, CTr>& os)
  {
    TRACE("<unnamed>::test_associative");
    
    Sequence const s(key_value_array.begin(), key_value_array.end());

    using namespace hugh::support;
    
    ostream::basic_format_saver<CTy> fs(os);
    
    using ostream::operator<<;
    
    os << '\n'
       << demangle<CTy>(typeid(s)) << ": empty\n"
       << ostream::formatted << Sequence()
       << '\n'
       << demangle<CTy>(typeid(s)) << ": formatted\n"
       << ostream::formatted << s
       << '\n'
       << demangle<CTy>(typeid(s)) << ": unformatted\n"
       << ostream::unformatted << ' ' << s;

    return !s.empty() && os.good();
  }

  template <typename CTy, typename CTr>
  bool
  test_initializer_list(std::basic_ostream<CTy, CTr>& os)
  {
    TRACE("<unnamed>::test_initializer_list");

    bool result(true);
    
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
    using namespace hugh::support;
    
    {
      auto const s = { 0.1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8,
                       1.9,
                       1.8, 1.7, 1.6, 1.5, 1.4, 1.3, 1.2, 1.1, 0.1, };
      
      ostream::basic_format_saver<CTy> fs(os);
      
      using ostream::operator<<;

      os << '\n'
         << demangle<CTy>(typeid(s)) << ": formatted\n"
         << ostream::formatted
         << ostream::delimeter<CTy>('{', '}', ':') << s
         << '\n'
         << demangle<CTy>(typeid(s)) << ": unformatted\n"
         << ostream::unformatted << ' ' << s;

      result &= os.good();
    }

    {
      auto const s = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };

      ostream::basic_format_saver<CTy> fs(os);
      
      using ostream::operator<<;

      os << '\n'
         << demangle<CTy>(typeid(s)) << ": formatted\n"
         << ostream::formatted << s
         << '\n'
         << demangle<CTy>(typeid(s)) << ": unformatted\n"
         << ostream::unformatted << ' ' << s;

      result &= os.good();
    }
#else
    boost::ignore_unused_variable_warning(os);
#endif

    return result;
  }

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_array)
{
  using namespace hugh::support;
  
  {
    std::ostringstream             ostr;
    ostream::scoped_redirect const sor(std::cout, ostr);
    
    BOOST_CHECK       (test_array(std::cout));
    BOOST_TEST_MESSAGE(ostr.str());
  }
  
  {
    std::wostringstream             ostr;
    ostream::wscoped_redirect const sor(std::wcout, ostr);
    
    BOOST_CHECK       (test_array(std::wcout));
    BOOST_TEST_MESSAGE(wstring_to_string(ostr.str()));
  }
}

using seq_types = boost::mpl::list<std::deque<unsigned>,
                                   std::forward_list<unsigned>,
                                   std::list<unsigned>,
                                   std::multiset<unsigned>,
                                   std::set<unsigned>,
                                   std::unordered_multiset<unsigned>,
                                   std::unordered_set<unsigned>,
                                   std::vector<unsigned>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_io_utils_seq_types, T, seq_types)
{
  using namespace hugh::support;
  
  {
    std::ostringstream             ostr;
    ostream::scoped_redirect const sor(std::cout, ostr);
    
    BOOST_CHECK       (test_sequence<T>(std::cout));
    BOOST_TEST_MESSAGE(ostr.str());
  }
  
  {
    std::wostringstream             ostr;
    ostream::wscoped_redirect const sor(std::wcout, ostr);
    
    BOOST_CHECK       (test_sequence<T>(std::wcout));
    BOOST_TEST_MESSAGE(wstring_to_string(ostr.str()));
  }
}

using assoc_types = boost::mpl::list<std::map<unsigned,double>,
                                     std::multimap<unsigned,double>,
                                     std::unordered_map<unsigned,double>,
                                     std::unordered_multimap<unsigned,double>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_io_utils_assoc_types, T, assoc_types)
{
  using namespace hugh::support;
  
  {
    std::ostringstream             ostr;
    ostream::scoped_redirect const sor(std::cout, ostr);
    
    BOOST_CHECK       (test_associative<T>(std::cout));
    BOOST_TEST_MESSAGE(ostr.str());
  }
  
  {
    std::wostringstream             ostr;
    ostream::wscoped_redirect const sor(std::wcout, ostr);
    
    BOOST_CHECK       (test_associative<T>(std::wcout));
    BOOST_TEST_MESSAGE(wstring_to_string(ostr.str()));
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_initializer_list)
{
  using namespace hugh::support;
  
  {
    std::ostringstream             ostr;
    ostream::scoped_redirect const sor(std::cout, ostr);
    
    BOOST_CHECK       (test_initializer_list(std::cout));
    BOOST_TEST_MESSAGE(ostr.str());
  }
  
  {
    std::wostringstream             ostr;
    ostream::wscoped_redirect const sor(std::wcout, ostr);
    
    BOOST_CHECK       (test_initializer_list(std::wcout));
    BOOST_TEST_MESSAGE(wstring_to_string(ostr.str()));
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_std_function)
{
  using function_type = std::function<bool (float)>;

  {
    function_type f = dummy_function_for_std_function_test;
    
    BOOST_CHECK(f);
    
    std::ostringstream ostr;

    using hugh::support::ostream::operator<<;
    
    ostr << '\n' << f;
    
    BOOST_TEST_MESSAGE(ostr.str());
  }

  {
    function_type f = [](float a){ return 0.0 > a; };
    
    BOOST_CHECK(f);
    
    std::ostringstream ostr;

    using hugh::support::ostream::operator<<;
    
    ostr << '\n' << f;
    
    BOOST_TEST_MESSAGE(ostr.str());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_std_unique_ptr)
{
  std::unique_ptr<unsigned> p(new unsigned(42));
  
  BOOST_CHECK(nullptr != p.get());

  std::ostringstream ostr;

  ostr << "\nstd::unique_ptr<unsigned>:" << p << ':' << *p;
  
  BOOST_TEST_MESSAGE(ostr.str());
}
