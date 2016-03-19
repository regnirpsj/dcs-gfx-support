// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/test/gtx_limits.cpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <glm/gtc/quaternion.hpp> // glm::?quat
#include <glm/gtc/vec1.hpp>       // glm::?vec1
#include <typeinfo>               // typedid

// includes, project

#include <glm/gtx/limits.hpp>
#include <hugh/support/type_info.hpp>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

#define BOOST_TEST_MAIN
#include <boost/test/included/unit_test.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  template <typename T>
  void
  check_epsilon()
  {
    static unsigned const max_precision(std::numeric_limits<long double>::digits10);
    
    typedef std::numeric_limits<T>                      numlimits_t;
    typedef std::numeric_limits<typename T::value_type> numlimits_t_value;
    
    BOOST_CHECK(numlimits_t::epsilon() == numlimits_t_value::epsilon());

    std::string const prefix(hugh::support::demangle(typeid(numlimits_t)) + "::epsilon:");
    
    BOOST_TEST_MESSAGE(prefix
                       << std::string(100 - prefix.length(), ' ')
                       << std::fixed
                       << std::right
                       << std::setfill(' ')
                       << std::setprecision(max_precision)
                       << std::setw(2 + max_precision)
                       << numlimits_t::epsilon());
  }
  
  // variables, internal
  
  // functions, internal

} // namespace {

#include <boost/test/test_case_template.hpp>
#include <boost/mpl/list.hpp>

typedef boost::mpl::list<glm::dmat2, glm::dmat3, glm::dmat4,
                         glm::mat2,  glm::mat3,  glm::mat4> mat_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_glm_limits_mat, T, mat_types)
{
  check_epsilon<T>();
}

typedef boost::mpl::list<glm::quat, glm::fquat, glm::dquat> quat_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_glm_limits_quat, T, quat_types)
{
  check_epsilon<T>();
}

typedef boost::mpl::list<glm::bvec1, glm::bvec2, glm::bvec3, glm::bvec4,
                         glm::dvec1, glm::dvec2, glm::dvec3, glm::dvec4,
                         glm::vec1,  glm::vec2,  glm::vec3,  glm::vec4,
                         glm::ivec1, glm::ivec2, glm::ivec3, glm::ivec4,
                         glm::uvec1, glm::uvec2, glm::uvec3, glm::uvec4> vec_types;

BOOST_AUTO_TEST_CASE_TEMPLATE(test_glm_limits_vec, T, vec_types)
{
  check_epsilon<T>();
}
