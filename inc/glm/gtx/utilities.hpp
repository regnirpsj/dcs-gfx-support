// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/gtx/utilities.hpp                                                           */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_GLM_GTX_UTILITIES_HPP)

#define HUGH_GLM_GTX_UTILITIES_HPP

// includes, system

#include <glm/glm.hpp> // glm::*

// includes, project

#include <glm/export.h>

namespace glm {
  
  // types, exported (class, enum, struct, union, typedef)

  struct HUGH_GLM_EXPORT decompose {
        
  public:

    enum order { rst, rts, srt, str, trs, tsr, };
    
    mat4 rotation;
    mat4 scale;
    mat4 translation;
    
    explicit decompose(mat4 const&);
    
  };
  
  // variables, exported (extern)

  namespace convert {

    /**
     * \brief transformtion to be left multiplied to an opengl projection matrix for use in a
     *        D3D11 pipeline
     */
    extern HUGH_GLM_EXPORT mat4 const opengl_to_d3d;

    /**
     * \brief glm::inverse(opengl_to_d3d); \see opengl_to_d3d
     */
    extern HUGH_GLM_EXPORT mat4 const d3d_to_opengl;
    
  } // namespace convert {
  
  // functions, inlined (inline)  
  
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1900))
  /**
   * \brief user-defined literals for distinguishing degrees and radians
   *
   * float const a1(90_deg);                  // 90 degree in radians
   * float const a2(glm::pi<float>() / 4.0);  // 90 degree in radians
   */
  //@{
  constexpr double operator "" _deg(unsigned long long);
  constexpr double operator "" _deg(long double);
  constexpr double operator "" _rad(unsigned long long);
  constexpr double operator "" _rad(long double);
  //@}
#else
#  pragma message("Note: user-defined string literal operators not supported ")
#  pragma message("      using (unreliable) macro workaround for _deg/_rad")
#endif // !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1800))

  /**
   * \brief convert the input angle (in radians) to be between [0, 2*pi]
   *
   * \param  a
   *
   * \return a -> [0, 2*pi]
   */
  template <typename T> T rev(T);
  
  /**
   * \brief compute the sign[um] of T
   *
   * \param  a
   *
   * \return sign(a) + identity(a)
   */
  template <typename T> signed sgn(T);
  
  // functions, exported (extern)

  namespace convert {
    
    /**
     * \brief converts the input matrix into its equivalent as
     *        determined by \c decompose::order
     *        input matrix may contain rotation, scale, or
     *        translation; however, shear etc. are not allowed
     *
     * \return converted matrix
     */
    HUGH_GLM_EXPORT mat4 transform(mat4 const&, decompose::order);
  
    /**
     * \brief converts the input matrix into its equivalent as
     *        determined by \c decompose::order
     *        input matrix may contain rotation, scale, or
     *        translation; however, shear etc. are not allowed
     *
     * \return converted matrix as well as rotation, scale, and translation parts
     */
    HUGH_GLM_EXPORT mat4 transform(mat4 const&      /* input            */,
                                   decompose::order /* output order     */,
                                   mat4&            /* rotation part    */,
                                   mat4&            /* scale part       */,
                                   mat4&            /* translation part */);
    
  } // namespace convert {

} // namespace glm {

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1900))
// for convenience, to avoid cumbersome lines like 'using glm::operator "" _deg;'
using glm::operator "" _deg;
using glm::operator "" _rad;
#else
// poor solution to still keep _deg/_rad around, so '180.0_deg' should still work, well actually it
// must then be '180.0 _deg'; will possible break at the most inconvenient of times
# define _deg * (3.14159265358979323846264338327950288 / 180.0)
# define _rad
#endif // !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1800))

#include <glm/gtx/utilities.inl>

#endif // #if !defined(HUGH_GLM_GTX_UTILITIES_HPP)
