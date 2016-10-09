// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/gtx/utilities.cpp                                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "glm/gtx/utilities.hpp"

// includes, system

#include <cmath>                 // std::sqrt
#include <glm/gtx/transform.hpp> // glm::inverse, glm::rotate, glm::translate

// includes, project

// #include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace glm {
  
  // variables, exported

  namespace convert {
    
    /* extern */ mat4 const opengl_to_d3d(translate(vec3(0.0, 0.0, 0.5)) *
                                          scale    (vec3(1.0, 1.0, 0.5)));
    /* extern */ mat4 const d3d_to_opengl(inverse(opengl_to_d3d));
    
  } // namespace convert {
  
  // functions, exported

  /* explicit */
  decompose::decompose(mat4 const& a)
  {
    TRACE("glm::decompose::decompose");

    convert::transform(a, trs, rotation, scale, translation);
  }
  
  namespace convert {
    
    mat4
    transform(mat4 const& m, decompose::order t)
    {
      TRACE("glm::convert::transform(mat4 const&, decompose::order)");
    
      mat4 rot, scale, trans;

      return transform(m, t, rot, scale, trans);
    }
  
    mat4
    transform(mat4 const& m, decompose::order t, mat4& R, mat4& S, mat4& T)
    {
      TRACE("glm::convert::transform(mat4 const&, decompose::order, mat4&, mat4&, mat4&)");

      mat4 const& C(m);
      mat4        A(C);

      A[3] = vec4(0.0, 0.0, 0.0, 1.0);
    
      S = transpose(A) * A;
    
      for (unsigned i(0); i < 3; ++i) {
        S[i][i] = std::sqrt(S[i][i]); 
      }
    
      mat4 const S_inv (inverse(S));
      mat4 const R1    (A * S_inv);
      mat4 const R1_inv(inverse(R1));
      mat4 const R2    (S_inv * A);
      mat4 const R2_inv(inverse(R2));
    
      switch (t) {
      case decompose::rst: T = S_inv  * R1_inv * C;      R = R1; break;
      case decompose::rts: T = R1_inv * C      * S_inv;  R = R1; break;
      case decompose::srt: T = R2_inv * S_inv  * C;      R = R2; break;
      case decompose::str: T = S_inv  * C      * R2_inv; R = R2; break;
      case decompose::trs: T = C      * S_inv  * R1_inv; R = R1; break;
      case decompose::tsr: T = C      * R2_inv * S_inv;  R = R2; break;
      }
    
      mat4 result;

      switch (t) {
      case decompose::rst: result = R * S * T; break;
      case decompose::rts: result = R * T * S; break;
      case decompose::srt: result = S * R * T; break;
      case decompose::str: result = S * T * R; break;
      case decompose::trs: result = T * R * S; break;
      case decompose::tsr: result = T * S * R; break;
      }

      return result;
    }
    
  } // namespace convert {
  
} // namespace glm {
