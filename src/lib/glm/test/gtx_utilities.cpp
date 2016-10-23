// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/test/gtx_utilities.cpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <array>                 // std::array<>
#include <glm/gtc/constants.hpp> // glm::pi
#include <glm/gtc/random.hpp>    // glm::*Rand
#include <glm/gtc/vec1.hpp>      // glm::vec1
#include <glm/gtx/io.hpp>        // glm::operator<<
#include <glm/gtx/transform.hpp> // glm::rotate, glm::scale, glm::translate>

// includes, project

#include <glm/gtx/utilities.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>
#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_glm_gtx_utilities_op_literal_deg)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
  BOOST_CHECK(glm::pi<double>() == 180.0 _deg);

  BOOST_TEST_MESSAGE(std::setprecision(12)
                     << "glm::pi<double>():" << glm::pi<double>()
                     << " =?= 180.0_deg:"    << 180.0 _deg);
#else
  BOOST_CHECK(glm::pi<double>() == 180.0_deg);

  BOOST_TEST_MESSAGE(std::setprecision(12)
                     << "glm::pi<double>():" << glm::pi<double>()
                     << " =?= 180.0_deg:"    << 180.0_deg);
#endif
}

BOOST_AUTO_TEST_CASE(test_hugh_glm_gtx_utilities_op_literal_rad)
{
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
  BOOST_CHECK(glm::pi<double>() == 180.0 _deg);

  BOOST_TEST_MESSAGE(std::setprecision(12)
                     << "glm::pi<double>():" << glm::pi<double>()
                     << " =?= 180.0_deg:"    << 180.0 _deg);
#else
  BOOST_CHECK(180.0_deg == glm::pi<double>());

  BOOST_TEST_MESSAGE(std::setprecision(12)
                     << "180.0_deg:"              << 180.0_deg
                     << " =?= glm::pi<double>():" << glm::pi<double>());
#endif
}

using rev_types = boost::mpl::list<glm::vec1,  glm::vec2,  glm::vec3,  glm::vec4,
                                   glm::dvec1, glm::dvec2, glm::dvec3, glm::dvec4>;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_hugh_glm_gtx_utilities_rev, T, rev_types)
{
  BOOST_CHECK(glm::rev(T(glm::two_pi<typename T::value_type>())) == T(0.0));
}

BOOST_AUTO_TEST_CASE(test_hugh_glm_gtx_utilities_sgn)
{
  BOOST_CHECK(glm::sgn(-1) < 0);
  BOOST_CHECK(glm::sgn(+1) > 0);
}

BOOST_AUTO_TEST_CASE(test_hugh_glm_gtx_utilities_decompose)
{
  glm::mat4 const      m;
  glm::decompose const d(m);

  BOOST_CHECK(glm::mat4() == d.rotation);
  BOOST_CHECK(glm::mat4() == d.scale);
  BOOST_CHECK(glm::mat4() == d.translation);  
}

BOOST_AUTO_TEST_CASE(test_hugh_glm_gtx_utilities_convert_transform)
{
  using matrix_pair = std::pair<glm::mat4 const, glm::mat4 const>;
  
#if defined(_MSC_VER) && (_MSC_VER <= 1900)
  glm::vec3::value_type const angle(float(45 _deg));
#else
  glm::vec3::value_type const angle(float(45_deg));
#endif
  
  glm::mat4 const ir(glm::rotate   (angle, glm::vec3(glm::gaussRand(  0.0, 20.0),
                                                     glm::gaussRand(  0.0, 20.0),
                                                     glm::gaussRand(  0.0, 20.0))));
  glm::mat4 const is(glm::scale    (       glm::vec3(glm::linearRand( 0.1, 10.0),
                                                     glm::linearRand( 0.1, 10.0),
                                                     glm::linearRand( 0.1, 10.0))));
  glm::mat4 const it(glm::translate(       glm::vec3(glm::linearRand(-1.0,  1.0),
                                                     glm::linearRand(-1.0,  1.0),
                                                     glm::linearRand(-1.0,  1.0))));
  
  std::array<std::pair<glm::mat4, std::string>, 7> const input_xform_list = {
    {
      std::make_pair(glm::mat4(),  "Identity"),
      std::make_pair(ir * is * it, "RST"),
      std::make_pair(ir * it * is, "RTS"),
      std::make_pair(is * ir * it, "SRT"),
      std::make_pair(is * it * ir, "STR"),
      std::make_pair(it * ir * is, "TRS"),
      std::make_pair(it * is * ir, "TSR"),
    }
  };
  
  std::array<std::pair<glm::decompose::order, std::string>, 6> const decompose_order_list = {
    {
      std::make_pair(glm::decompose::rst, "RST"),
      std::make_pair(glm::decompose::rts, "RTS"),
      std::make_pair(glm::decompose::srt, "SRT"),
      std::make_pair(glm::decompose::str, "STR"),
      std::make_pair(glm::decompose::trs, "TRS"),
      std::make_pair(glm::decompose::tsr, "TSR"),
    }
  };

  static float const epsilon(1024 * std::numeric_limits<float>::epsilon());

  BOOST_TEST_MESSAGE("epsilon used for equality comparison to pass: " << std::fixed << epsilon);
  
  for (auto ix : input_xform_list) {
    for (auto e : decompose_order_list) {
      glm::mat4 r, s, t;
    
      glm::mat4 const   x(glm::convert::transform(ix.first, e.first, r, s, t));
      matrix_pair const p(std::make_pair(ix.first, x));

      BOOST_TEST_MESSAGE(glm::io::precision(7) << glm::io::width(1 + 1 + 1 + 7)
                         << ix.second << ':' << std::string(47 - ix.second.length(), ' ')
                         << e.second << ':' << p << '\n');
      
      for (unsigned i(0); i < 4; ++i) {
        for (unsigned j(0); j < 4; ++j) {
          BOOST_CHECK(std::abs(p.first[i][j] - p.second[i][j]) <= epsilon);
        }
      }
    }
  }
  
  for (auto ix : input_xform_list) {
    for (auto e : decompose_order_list) {
      glm::mat4 const   x(glm::convert::transform(ix.first, e.first));
      matrix_pair const p(std::make_pair(ix.first, x));

      BOOST_TEST_MESSAGE(glm::io::precision(7) << glm::io::width(1 + 1 + 1 + 7)
                         << ix.second << ':' << std::string(47 - ix.second.length(), ' ')
                         << e.second << ':' << p << '\n');
      
      for (unsigned i(0); i < 4; ++i) {
        for (unsigned j(0); j < 4; ++j) {
          BOOST_CHECK(std::abs(p.first[i][j] - p.second[i][j]) <= epsilon);
        }
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(test_hugh_glm_gtx_utilities_swizzle)
{
  glm::vec4 const cv(1,2,3,4);

  BOOST_CHECK(glm::vec4(1,2,3,4) == cv);

  {
    glm::vec4 const v(cv.xyzw);

    BOOST_CHECK(cv == v);
  }
  
  {
    glm::vec4 const v(cv.xyzw());

    BOOST_CHECK(cv == v);
  }

  {
    glm::vec4 const v(cv.rgba);

    BOOST_CHECK(cv == v);
  }

  {
    glm::vec4 const v(cv.rgba());

    BOOST_CHECK(cv == v);
  }

  {
    glm::vec4 const v(cv.stpq);

    BOOST_CHECK(cv == v);
  }

  {
    glm::vec4 const v(cv.stpq());

    BOOST_CHECK(cv == v);
  }

  {
    glm::vec4 const v(cv.yx, cv.zz);

    BOOST_CHECK(glm::vec4(cv.yx, cv.zz) == v);
  }
    
  {
    glm::vec4 const v(cv.yx(), cv.zz());

    BOOST_CHECK(glm::vec4(cv.yx(), cv.zz()) == v);
  }
}
