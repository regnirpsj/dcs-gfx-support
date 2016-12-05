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

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_manipulator_remove)
{
  using namespace hugh::support;
  using ostream::remove;

  unsigned const count(6);
  
  { // buffered stream
    std::ostringstream           ostr;
    std::ostringstream::pos_type tellp[4];
    
    tellp[0] = ostr.tellp(); ostr << "Hello, Monde!";
    tellp[1] = ostr.tellp(); ostr << remove(count);
    tellp[2] = ostr.tellp(); ostr << "World!";
    tellp[3] = ostr.tellp();
    
    BOOST_CHECK(ostr.good() && !ostr.bad());
    BOOST_CHECK(tellp[1] == tellp[3]);
    BOOST_CHECK(count == (tellp[3] - tellp[2]));
    
    BOOST_TEST_MESSAGE(ostr.str()
                       << " ["
                       << tellp[0] << ':'
                       << tellp[1] << ':'
                       << tellp[2] << ':'
                       << tellp[3]
                       << ']');
  }
  
  { // unbuffered stream
    std::ostream::pos_type tellp[4];

    tellp[0] = std::cout.tellp(); std::cout << "hello, monde!";
    tellp[1] = std::cout.tellp(); std::cout << remove(count);
    tellp[2] = std::cout.tellp(); std::cout << "world!";
    tellp[3] = std::cout.tellp();
    
    BOOST_CHECK(std::cout.good() && !std::cout.bad());
    BOOST_CHECK(tellp[1] == tellp[3]);
    
    BOOST_TEST_MESSAGE(" ["
                       << tellp[0] << ':'
                       << tellp[1] << ':'
                       << tellp[2] << ':'
                       << tellp[3]
                       << ']');
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_manipulator_enumeration)
{
  enum class type {
    T1 = 1, T2 = 2, T3 = -1, T4 = 0,
  };
  
  static std::array<std::pair<type const, std::string const>, 4> const types = {
    std::make_pair(type::T1, "type::T1"),
    std::make_pair(type::T2, "type::T2"),
    std::make_pair(type::T3, "type::T3"),
    std::make_pair(type::T4, "type::T4"),
  };
  
  for (auto t : types) {
    using hugh::support::ostream::enumerate;

    std::ostringstream ostr;

    ostr << enumerate(t.first, types);

    BOOST_CHECK       (t.second == ostr.str());
    BOOST_TEST_MESSAGE(ostr.str());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_manipulator_bitmask)
{
  static std::array<unsigned const, 27> const primes_plus = {
    0, 1,
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97,
  };
  static std::array<std::pair<unsigned const, std::string const>, 8> const masks = {
    std::make_pair(0x0040, "SIXTYFOUR"),
    std::make_pair(0x0020, "THIRTYTWO"),
    std::make_pair(0x0010, "  SIXTEEN"),
    std::make_pair(0x0008, "    EIGHT"),
    std::make_pair(0x0004, "     FOUR"),
    std::make_pair(0x0002, "      TWO"),
    std::make_pair(0x0001, "      ONE"),
    std::make_pair(0x0000, "     ZERO"),
  };
  
  for (auto f : primes_plus) {
    using hugh::support::ostream::flags;
    using hugh::support::ostream::remove;
    
    std::ostringstream ostr;

    ostr << flags(f, masks) << remove(1);
      
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE(   std::setw(2) << std::setfill('0')                               << f
                       << ":0x"
                       << std::setw(2) << std::setfill('0') << std::hex << std::uppercase << f
                       << ':'
                       << ostr.str());
  }
}

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

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_binary)
{
  using namespace hugh::support;

  unsigned const n(1234567890);

  {
    std::ostringstream ostr;
    
    ostr << n << " -> "
         << ostream::unformatted << ostream::binary(n);
    
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }

  {
    std::ostringstream ostr;
    
    ostr << n << " -> "
         << ostream::delimeter<char>('[', ']', '.') << ostream::formatted << ostream::binary(n);
    
    BOOST_CHECK       (!ostr.str().empty());
    BOOST_TEST_MESSAGE('\n' << ostr.str());
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_position_saver)
{
  using namespace hugh::support;

  std::string       text("1234567890");
  std::stringstream iostr;
  
  {
    ostream::position_saver const ops(iostr);

    iostr << text;
  }

  BOOST_CHECK       (0 == iostr.tellp());
  BOOST_TEST_MESSAGE('\n' << iostr.str());
  
  {
    istream::position_saver const ips(iostr);

    iostr >> text;
  }

  BOOST_CHECK       (0 == iostr.tellg());
  BOOST_TEST_MESSAGE('\n' << iostr.str() << ':' << text);
  
  {
    iostream::position_saver const ops(iostr);

    std::reverse(text.begin(), text.end());
    
    iostr << text;
    iostr >> text;
  }

  BOOST_CHECK       (0 == iostr.tellp());
  BOOST_CHECK       (0 == iostr.tellg());
  BOOST_TEST_MESSAGE('\n' << iostr.str() << ':' << text);
}

BOOST_AUTO_TEST_CASE(test_hugh_support_io_utils_scoped_redirect)
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
