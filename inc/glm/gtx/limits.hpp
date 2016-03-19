// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/gtx/limits.hpp                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_GLM_GTX_LIMITS_HPP)

#define HUGH_GLM_GTX_LIMITS_HPP

// includes, system

#include <glm/glm.hpp>            // glm::tvec[1,2,3,4]<>, glm::tmat[2,3,4]x[2,3,4]<>
#include <glm/gtc/quaternion.hpp> // glm::tquat<>
#include <limits>                 // std::numeric_limits<>

// includes, project

//#include <>

namespace std {
  
  // types, exported (class, enum, struct, union, typedef)

  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat2x2<T,P>>
    : public std::numeric_limits<typename glm::tmat2x2<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat2x3<T,P>>
    : public std::numeric_limits<typename glm::tmat2x3<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat2x4<T,P>>
    : public std::numeric_limits<typename glm::tmat2x4<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat3x2<T,P>>
    : public std::numeric_limits<typename glm::tmat3x2<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat3x3<T,P>>
    : public std::numeric_limits<typename glm::tmat3x3<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat3x4<T,P>>
    : public std::numeric_limits<typename glm::tmat3x4<T,P>::value_type> { /* */ };

  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat4x2<T,P>>
    : public std::numeric_limits<typename glm::tmat4x2<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat4x3<T,P>>
    : public std::numeric_limits<typename glm::tmat4x3<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tmat4x4<T,P>>
    : public std::numeric_limits<typename glm::tmat4x4<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tquat<T,P>>
    : public std::numeric_limits<typename glm::tquat<T,P>::value_type> { /* */ };
  
  template <typename T, glm::precision P>
  struct numeric_limits<glm::tvec1<T,P>>
    : public std::numeric_limits<typename glm::tvec1<T,P>::value_type> { /* */ };

  template <typename T, glm::precision P>
  struct numeric_limits<glm::tvec2<T,P>>
    : public std::numeric_limits<typename glm::tvec2<T,P>::value_type> { /* */ };

  template <typename T, glm::precision P>
  struct numeric_limits<glm::tvec3<T,P>>
    : public std::numeric_limits<typename glm::tvec3<T,P>::value_type> { /* */ };

  template <typename T, glm::precision P>
  struct numeric_limits<glm::tvec4<T,P>>
    : public std::numeric_limits<typename glm::tvec4<T,P>::value_type> { /* */ };
  
  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)
  
} // namespace std {

#endif // #if !defined(HUGH_GLM_GTX_LIMITS_HPP)
