// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/test/gtx_morton.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <cmath>                  // std::pow<>
#include <glm/gtc/vec1.hpp>       // glm::?vec1
#include <glm/gtx/io.hpp>         // glm::operator<<
#include <glm/gtx/type_trait.hpp> // glm::type<>

// includes, project

#include <glm/gtx/morton.hpp>
#include <hugh/support/io_utils.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

#define HUGH_GLM_GTX_MORTON_VERBOSE
#undef HUGH_GLM_GTX_MORTON_VERBOSE

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal

  std::array<unsigned long const, 5> const size = {
    {
#if 1
      1048576, 1024, 102, 32, 16,
#else
      unsigned(std::pow(2, 31)) - 1,
      unsigned(std::pow(2, 16)) - 1,
      unsigned(std::pow(2, 10)) - 1,
      unsigned(std::pow(2,  8)) - 1,
      unsigned(std::pow(2,  6)) - 1,
#endif
    }
  };
  
  // functions, internal
  
  template <typename T, unsigned N>
  void
  print_variant()
  {
    std::ostringstream ostr;

    ostr << std::right
         << std::setw(12) << unsigned(std::pow(size[N-1], N))
         << std::left
         << ": array<" + hugh::support::demangle(typeid(T)) << ',' << N << '>';
    
    BOOST_TEST_MESSAGE(ostr.str());
  }

  template <template <typename, glm::precision> class V, typename T, glm::precision P>
  void
  print_variant(V<T,P> const&)
  {
    static unsigned const N(glm::type<V,T,P>::components);
    
    std::ostringstream ostr;

    ostr << std::right
         << std::setw(12) << unsigned(std::pow(size[N-1], N))
         << std::left
         << ": " << hugh::support::demangle(typeid(V<T,P>));
    
    BOOST_TEST_MESSAGE(ostr.str());
  }
  
} // namespace {

#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1900))

using array_types = boost::mpl::list<signed, unsigned>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_array1, T, array_types)
{
  print_variant<T,1>();
  
  for (signed x(size[0]); x >= 0; --x) {
    std::array<T,1> const v({T(x)});
    T const               c(glm::morton::encode<1>(v));
    std::array<T,1> const e(glm::morton::decode<1>(c));

    BOOST_CHECK(v == e);

    using hugh::support::ostream::operator<<;
    
#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
    using hugh::support::ostream::operator<<;
    
    std::cout << "v:" << std::setw(2) << v << ", "
              << "c:" << std::setw(2) << c << ", "
              << "e:" << std::setw(2) << e
              << std::endl;
#endif
  }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_array2, T, array_types)
{
  print_variant<T,2>();
  
  for (signed x(size[1]); x >= 0; --x) {
    for (signed y(size[1]); y >= 0; --y) {
      std::array<T,2> const v({T(x), T(y)});
      T const               c(glm::morton::encode<2>(v));
      std::array<T,2> const e(glm::morton::decode<2>(c));

      BOOST_CHECK(v == e);

#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
      using hugh::support::ostream::operator<<;
      
      std::cout << "v:" << std::setw(2) << v << ", "
                << "c:" << std::setw(3) << c << ", "
                << "e:" << std::setw(2) << e
                << std::endl;
#endif
    }
  }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_array3, T, array_types)
{
  print_variant<T,3>();
  
  for (signed x(size[2]); x >= 0; --x) {
    for (signed y(size[2]); y >= 0; --y) {
      for (signed z(size[2]); z >= 0; --z) {
        std::array<T,3> const v({T(x), T(y), T(z)});
        T const               c(glm::morton::encode<3>(v));
        std::array<T,3> const e(glm::morton::decode<3>(c));
        
        BOOST_CHECK(v == e);
        
#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
        using hugh::support::ostream::operator<<;
        
        std::cout << "v:" << std::setw(2) << v << ", "
                  << "c:" << std::setw(3) << c << ", "
                  << "e:" << std::setw(2) << e
                  << std::endl;
#endif
      }
    }
  }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_array4, T, array_types)
{
  print_variant<T,4>();
  
  for (signed x(size[3]); x >= 0; --x) {
    for (signed y(size[3]); y >= 0; --y) {
      for (signed z(size[3]); z >= 0; --z) {
        for (signed w(size[3]); w >= 0; --w) {
          std::array<T,4> const v({T(x), T(y), T(z), T(w)});
          T const               c(glm::morton::encode<4>(v));
          std::array<T,4> const e(glm::morton::decode<4>(c));

          BOOST_CHECK(v == e);

#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
          using hugh::support::ostream::operator<<;
          
          std::cout << "v:" << std::setw(2) << v << ", "
                    << "c:" << std::setw(4) << c << ", "
                    << "e:" << std::setw(2) << e
                    << std::endl;
#endif
        }
      }
    }
  }
}

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_array5, T, array_types)
{
  print_variant<T,5>();
  
  for (signed x(size[4]); x >= 0; --x) {
    for (signed y(size[4]); y >= 0; --y) {
      for (signed z(size[4]); z >= 0; --z) {
        for (signed u(size[4]); u >= 0; --u) {
          for (signed w(size[4]); w >= 0; --w) {
            std::array<T,5> const v({T(x), T(y), T(z), T(u), T(w)});
            T const               c(glm::morton::encode<5>(v));
            std::array<T,5> const e(glm::morton::decode<5>(c));

            BOOST_CHECK(v == e);

#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
            using hugh::support::ostream::operator<<;
            
            std::cout << "v:" << std::setw(2) << v << ", "
                      << "c:" << std::setw(4) << c << ", "
                      << "e:" << std::setw(2) << e
                      << std::endl;
#endif
          }
        }
      }
    }
  }
}
#endif // #if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1800))

//glm::bvec1,
//glm::dvec1,
//glm::vec1,
using vec1_types = boost::mpl::list<glm::ivec1,glm::uvec1>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_vec1, T, vec1_types)
{
  print_variant(T());
  
  for (signed x(size[0]); x >= 0; --x) {
    using V = typename T::value_type;
    
    T const v(x);
    V const c(glm::morton::encode   (v));
    T const e(glm::morton::decode<T>(c));

    BOOST_CHECK(v == e);

#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
    BOOST_TEST_MESSAGE("v:" << glm::io::width(2) << v << ", "
                       << "c:" << std::setw(2)      << c << ", "
                       << "e:" << glm::io::width(2) << e);
#endif
  }
}

//glm::bvec2,
//glm::dvec2,
//glm::vec2,
using vec2_types = boost::mpl::list<glm::ivec2,glm::uvec2>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_vec2, T, vec2_types)
{
  print_variant(T());
  
  for (signed x(size[1]); x >= 0; --x) {
    for (signed y(size[1]); y >= 0; --y) {
      using V = typename T::value_type;
    
      T const v(x, y);
      V const c(glm::morton::encode   (v));
      T const e(glm::morton::decode<T>(c));

      BOOST_CHECK(v == e);

#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
      BOOST_TEST_MESSAGE("v:" << glm::io::width(2) << v << ", "
                         << "c:" << std::setw(3)      << c << ", "
                         << "e:" << glm::io::width(2) << e);
#endif
    }
  }
}

//glm::bvec3,
//glm::dvec3,
//glm::vec3,
using vec3_types = boost::mpl::list<glm::ivec3,glm::uvec3>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_vec3, T, vec3_types)
{
  print_variant(T());
  
  for (signed x(size[2]); x >= 0; --x) {
    for (signed y(size[2]); y >= 0; --y) {
      for (signed z(size[2]); z >= 0; --z) {
        using V = typename T::value_type;
    
        T const v(x, y, z);
        V const c(glm::morton::encode   (v));
        T const e(glm::morton::decode<T>(c));
        
        BOOST_CHECK(v == e);
        
#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
        BOOST_TEST_MESSAGE("v:" << glm::io::width(2) << v << ", "
                           << "c:" << std::setw(3)      << c << ", "
                           << "e:" << glm::io::width(2) << e);
#endif
      }
    }
  }
}

//glm::bvec4,
//glm::dvec4,
//glm::vec4,
using vec4_types = boost::mpl::list<glm::ivec4,glm::uvec4>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_morton_vec4, T, vec4_types)
{
  print_variant(T());
  
  for (signed x(size[3]); x >= 0; --x) {
    for (signed y(size[3]); y >= 0; --y) {
      for (signed z(size[3]); z >= 0; --z) {
        for (signed w(size[3]); w >= 0; --w) {
          using V = typename T::value_type;
          
          T const v(x, y, z, w);
          V const c(glm::morton::encode   (v));
          T const e(glm::morton::decode<T>(c));
      
          BOOST_CHECK(v == e);

#if defined(HUGH_GLM_GTX_MORTON_VERBOSE)
          BOOST_TEST_MESSAGE("v:" << glm::io::width(2) << v << ", "
                             << "c:" << std::setw(3)      << c << ", "
                             << "e:" << glm::io::width(2) << e);
#endif
        }
      }
    }
  }
}
