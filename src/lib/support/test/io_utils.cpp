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

#include <array>                   // std::array<>
#include <boost/concept_check.hpp> // boost::ignore_unused_variable_warning<>
#include <cstdlib>                 // EXIT_SUCCESS
#include <forward_list>            // std::forward_list<>
#include <iostream>                // std::cout, std::endl
#include <list>                    // std::list<>
#include <map>                     // std::map<>
#include <memory>                  // std::unique_ptr<>
#include <set>                     // std::set<>
#include <sstream>                 // std::ostringstream
#include <typeinfo>                // typeid usage
#include <unordered_map>           // std::unordered_map<>
#include <vector>                  // std::vector<>

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

  std::array<unsigned const, 10> const number_array = {
    {
      0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
    }
  };

  std::array<std::pair<unsigned const, double const>, 10> const key_value_array = {
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
#else
      {0, 0.0}, {1, 0.1}, {2, 0.2}, {3, 0.3}, {4, 0.4},
      {5, 0.5}, {6, 0.6}, {7, 0.7}, {8, 0.8}, {9, 0.9},
#endif
    }
  };
  
  // functions, internal

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
       << ostream::unformatted << ' ' << s
       << std::endl;

    return !s.empty();
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
       << ostream::unformatted << ' ' << s
       << std::endl;

    return !s.empty();
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
       << ostream::unformatted << ' ' << s
       << std::endl;

    return !s.empty();
  }

  template <typename CTy, typename CTr>
  bool
  test_initializer_list(std::basic_ostream<CTy, CTr>& os)
  {
    TRACE("<unnamed>::test_initializer_list");
    
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
    using namespace hugh::support;
    
    {
      auto const s = { 0.1, 1.1, 1.2, 1.3, 1.4, 1.5, 1.6, 1.7, 1.8, 1.9 };
      
      ostream::basic_format_saver<CTy> fs(os);
      
      using ostream::operator<<;

      os << '\n'
         << demangle<CTy>(typeid(s)) << ": formatted\n"
         << ostream::formatted
         << ostream::delimeter<CTy>('{', '}', ':') << s
         << '\n'
         << demangle<CTy>(typeid(s)) << ": unformatted\n"
         << ostream::unformatted << ' ' << s
         << std::endl;
    }

    {
      auto const s = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 0 };

      ostream::basic_format_saver<CTy> fs(os);
      
      using ostream::operator<<;

      os << '\n'
         << demangle<CTy>(typeid(s)) << ": formatted\n"
         << ostream::formatted << s
         << '\n'
         << demangle<CTy>(typeid(s)) << ": unformatted\n"
         << ostream::unformatted << ' ' << s
         << std::endl;
    }
#else
    boost::ignore_unused_variable_warning(os);
#endif

    return true;
  }
  
} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_manipulator_remove)
{
  using namespace hugh::support;
  using ostream::remove;
  
  {
    std::ostringstream ostr;

    ostr << "Hello, Monde!" << remove(6) << "World!";

    BOOST_CHECK(ostr.good() && !ostr.bad());
    
    std::cout << ostr.str() << std::endl;

    BOOST_CHECK(std::cout.good() && !std::cout.bad());
  }

#if 0
  {
    std::cout << "hello, monde!" << remove(6) << "world!";

    BOOST_CHECK(std::cout.good() && !std::cout.bad());

    std::cout << std::endl;
  }
#endif
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_array)
{
  BOOST_CHECK(test_array(std::cout));
  BOOST_CHECK(test_array(std::wcout));
}

using seq_types = boost::mpl::list<std::forward_list<unsigned>,
                                   std::list<unsigned>,
                                   std::set<unsigned>,
                                   std::vector<unsigned>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_io_utils_seq_types, T, seq_types)
{
  BOOST_CHECK(test_sequence<T>(std::cout));
  BOOST_CHECK(test_sequence<T>(std::wcout));
}

using assoc_types = boost::mpl::list<std::map<unsigned,double>,
                                     std::unordered_map<unsigned,double>>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_support_io_utils_assoc_types, T, assoc_types)
{
  BOOST_CHECK(test_associative<T>(std::cout));
  BOOST_CHECK(test_associative<T>(std::wcout));
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_initializer_list)
{
  BOOST_CHECK(test_initializer_list(std::cout));
  BOOST_CHECK(test_initializer_list(std::wcout));
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_std_unique_ptr)
{
  std::unique_ptr<unsigned> p(new unsigned(42));
  
  BOOST_CHECK       (nullptr != p.get());
  BOOST_TEST_MESSAGE("\nstd::unique_ptr<unsigned>:" << p << ':' << *p);
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_binary)
{
  using binary = hugh::support::ostream::binary;

  unsigned const     n(1234567890);
  std::ostringstream ostr;

  ostr << n << " -> " << binary(n);

  BOOST_CHECK       (!ostr.str().empty());
  BOOST_TEST_MESSAGE('\n' << ostr.str());
}
