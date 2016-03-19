// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  glm/gtx/morton.inl                                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_GLM_GTX_MORTON_INL)

#define HUGH_GLM_GTX_MORTON_INL

// includes, system

#include <glm/glm.hpp>      // glm::?vec[2-4]
#include <glm/gtc/vec1.hpp> // glm::?vec1

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
#  include <typeinfo>
#  include <hugh/support/type_info.hpp>
#endif

namespace glm {

  namespace morton {
    
    namespace detail {

      /*
       * [http://asgerhoedt.dk/?tag=morton-code]
       */
       
      template <unsigned N>
      inline unsigned
      compact_by(unsigned)
      {
        TRACE("glm::morton::detail::compact_by<N> (" + std::to_string(N) + ")");
        
        return unsigned(~0);
      }
      
      template <unsigned N>
      inline unsigned
      separate_by(unsigned)
      {
        TRACE("glm::morton::detail::separate_by<N> (" + std::to_string(N) + ")");
        
        return unsigned(~0);
      }

      template <>
      inline unsigned
      compact_by<0>(unsigned x)
      {
        TRACE("glm::morton::detail::compact_by<0>");
        
        return x;
      }
      
      template <>
      inline unsigned
      separate_by<0>(unsigned x)
      {
        TRACE("glm::morton::detail::separate_by<0>");
        
        return x;
      }

      template <>
      inline unsigned
      compact_by<1>(unsigned x)
      {
        TRACE("glm::morton::detail::compact_by<1>");
        
        x &= 0x55555555;                   // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0
        x  = (x ^ (x >>  1)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
        x  = (x ^ (x >>  2)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
        x  = (x ^ (x >>  4)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
        x  = (x ^ (x >>  8)) & 0x0000ffff; // x = ---- ---- ---- ---- fedc ba98 7654 3210
        
        return x;
      }
      
      template <>
      inline unsigned
      separate_by<1>(unsigned x)
      {
        TRACE("glm::morton::detail::separate_by<1>");
        
        x &= 0x0000ffff;                   // x = ---- ---- ---- ---- fedc ba98 7654 3210
        x  = (x ^ (x <<  8)) & 0x00ff00ff; // x = ---- ---- fedc ba98 ---- ---- 7654 3210
        x  = (x ^ (x <<  4)) & 0x0f0f0f0f; // x = ---- fedc ---- ba98 ---- 7654 ---- 3210
        x  = (x ^ (x <<  2)) & 0x33333333; // x = --fe --dc --ba --98 --76 --54 --32 --10
        x  = (x ^ (x <<  1)) & 0x55555555; // x = -f-e -d-c -b-a -9-8 -7-6 -5-4 -3-2 -1-0

        return x;
      }

      template <>
      inline unsigned
      compact_by<2>(unsigned x)
      {
        TRACE("glm::morton::detail::compact_by<2>");

        x &= 0x49249249;                   // x = -a-- 9--8 --7- -6-- 5--4 --3- -2-- 1--0
        x  = (x ^ (x >>  2)) & 0x430c30c3; // x = -a-- --98 ---- 76-- --54 ---- 32-- --10
        x  = (x ^ (x >>  4)) & 0x0f00f00f; // x = ---- -a98 ---- ---- 7654 ---- ---- 3210
        x  = (x ^ (x >>  8)) & 0x000ff00f; // x = ---- ---- ---- -a98 7654 ---- ---- 3210
        x  = (x ^ (x >>  8)) & 0x000007ff; // x = ---- ---- ---- ---- ---- -a98 7654 3210
        
        return x;
      }
      
      template <>
      inline unsigned
      separate_by<2>(unsigned x)
      {
        TRACE("glm::morton::detail::separate_by<2>");

        x &= 0x000007ff;                   // x = ---- ---- ---- ---- ---- -a98 7654 3210
        x  = (x ^ (x <<  8)) & 0x000ff00f; // x = ---- ---- ---- -a98 7654 ---- ---- 3210
        x  = (x ^ (x <<  8)) & 0x0f00f00f; // x = ---- -a98 ---- ---- 7654 ---- ---- 3210
        x  = (x ^ (x <<  4)) & 0x430c30c3; // x = -a-- --98 ---- 76-- --54 ---- 32-- --10
        x  = (x ^ (x <<  2)) & 0x49249249; // x = -a-- 9--8 --7- -6-- 5--4 --3- -2-- 1--0
        
        return x;
      }

      template <>
      inline unsigned
      compact_by<3>(unsigned x)
      {
        TRACE("glm::morton::detail::compact_by<3>");
        
        x &= 0x11111111;                   // x = ---7 ---6 ---5 ---4 ---3 ---2 ---1 ---0
        x  = (x ^ (x >>  3)) & 0x03030303; // x = ---- --76 ---- --54 ---- --32 ---- --10
        x  = (x ^ (x >>  6)) & 0x000f000f; // x = ---- ---- ---- 7654 ---- ---- ---- 3210
        x  = (x ^ (x >> 12)) & 0x000000ff; // x = ---- ---- ---- ---- ---- ---- 7654 3210
        
        return x;
      }
      
      template <>
      inline unsigned
      separate_by<3>(unsigned x)
      {
        TRACE("glm::morton::detail::separate_by<3>");

        x &= 0x000000ff;                   // x = ---- ---- ---- ---- ---- ---- 7654 3210
        x  = (x ^ (x << 12)) & 0x000f000f; // x = ---- ---- ---- 7654 ---- ---- ---- 3210
        x  = (x ^ (x <<  6)) & 0x03030303; // x = ---- --76 ---- --54 ---- --32 ---- --10
        x  = (x ^ (x <<  3)) & 0x11111111; // x = ---7 ---6 ---5 ---4 ---3 ---2 ---1 ---0
        
        return x;
      }

      template <>
      inline unsigned
      compact_by<4>(unsigned x)
      {
        TRACE("glm::morton::detail::compact_by<4>");
        
        x &= 0x42108421;                   // x = -6-- --5- ---4 ---- 3--- -2-- --1- ---0
        x  = (x ^ (x >>  4)) & 0x40300C03; // x = -6-- ---- --54 ---- ---- 32-- ---- --10
        x  = (x ^ (x >>  8)) & 0x0070000f; // x = ---- ---- -654 ---- ---- ---- ---- 3210
        x  = (x ^ (x >> 16)) & 0x0000007f; // x = ---- ---- ---- ---- ---- ---- -654 3210
        
        return x;
      }
      
      template <>
      inline unsigned
      separate_by<4>(unsigned x)
      {
        TRACE("glm::morton::detail::separate_by<4>");
        
        x &= 0x0000007f;                   // x = ---- ---- ---- ---- ---- ---- -654 3210
        x  = (x ^ (x << 16)) & 0x0070000f; // x = ---- ---- -654 ---- ---- ---- ---- 3210
        x  = (x ^ (x <<  8)) & 0x40300C03; // x = -6-- ---- --54 ---- ---- 32-- ---- --10
        x  = (x ^ (x <<  4)) & 0x42108421; // x = -6-- --5- ---4 ---- 3--- -2-- --1- ---0
        
        return x;
      }
      
    } // namespace detail {
    
    // functions, inlined (inline)

    template <unsigned N, typename T>
    inline std::array<T, N>
    decode(T const& v)
    {
      TRACE("glm::morton::decode<" + std::to_string(N) + "," + support::demangle(typeid(T)) + ">");

      std::array<T, N> result;

      for (unsigned i(0); i < N; ++i) {
        result[i] = detail::compact_by<N-1>(v >> i);
      }
      
      return result;
    }
    
    template <unsigned N, typename T>
    inline T
    encode(std::array<T, N> const& v)
    {
      TRACE("glm::morton::encode<" + std::to_string(N) + "," + support::demangle(typeid(T)) + ">");
      T result(detail::separate_by<N-1>(v[0]));

      for (unsigned i(1); i < N; ++i) {
        result |= (detail::separate_by<N-1>(v[i]) << i);
      }
      
      return result;
    }

    // tvec1<T,P>
    
    template <>
    inline ivec1
    decode(ivec1::value_type const& a)
    {
      auto const result(decode<1>(a));
      
      return ivec1(result[0]);
    }

    template <>
    inline ivec1::value_type
    encode(ivec1 const& a)
    {
      return encode<1, ivec1::value_type>({a.x});
    }

    template <>
    inline uvec1
    decode(uvec1::value_type const& a)
    {
      auto const result(decode<1>(a));
      
      return uvec1(result[0]);
    }

    template <>
    inline uvec1::value_type
    encode(uvec1 const& a)
    {
      return encode<1, uvec1::value_type>({a.x});
    }

    // tvec2<T,P>
    
    template <>
    inline ivec2
    decode(ivec2::value_type const& a)
    {
      auto const result(decode<2>(a));
      
      return ivec2(result[0], result[1]);
    }

    template <>
    inline ivec2::value_type
    encode(ivec2 const& a)
    {
      return encode<2, ivec2::value_type>({a.x, a.y});
    }

    template <>
    inline uvec2
    decode(uvec2::value_type const& a)
    {
      auto const result(decode<2>(a));
      
      return uvec2(result[0], result[1]);
    }

    template <>
    inline uvec2::value_type
    encode(uvec2 const& a)
    {
      return encode<2, uvec2::value_type>({a.x, a.y});
    }

    // tvec3<T,P>
    
    template <>
    inline ivec3
    decode(ivec3::value_type const& a)
    {
      auto const result(decode<3>(a));
      
      return ivec3(result[0], result[1], result[2]);
    }

    template <>
    inline ivec3::value_type
    encode(ivec3 const& a)
    {
      return encode<3, ivec3::value_type>({a.x, a.y, a.z});
    }

    template <>
    inline uvec3
    decode(uvec3::value_type const& a)
    {
      auto const result(decode<3>(a));
      
      return uvec3(result[0], result[1], result[2]);
    }

    template <>
    inline uvec3::value_type
    encode(uvec3 const& a)
    {
      return encode<3, uvec3::value_type>({a.x, a.y, a.z});
    }

    // tvec4<T,P>
    
    template <>
    inline ivec4
    decode(ivec4::value_type const& a)
    {
      auto const result(decode<4>(a));
      
      return ivec4(result[0], result[1], result[2], result[3]);
    }

    template <>
    inline ivec4::value_type
    encode(ivec4 const& a)
    {
      return encode<4, ivec4::value_type>({a.x, a.y, a.z, a.w});
    }

    template <>
    inline uvec4
    decode(uvec4::value_type const& a)
    {
      auto const result(decode<4>(a));
      
      return uvec4(result[0], result[1], result[2], result[3]);
    }

    template <>
    inline uvec4::value_type
    encode(uvec4 const& a)
    {
      return encode<4, uvec4::value_type>({a.x, a.y, a.z, a.w});
    }

#if 0
    template <typename T>
    inline T
    decode(typename T::value_type const&)
    {
      static_assert(false, "unimplemented generic version 'glm::morton::decode'");

      return T();
    }

    template <typename T>
    inline typename T::value_type
    encode(T const&)
    {
      static_assert(false, "unimplemented generic version 'glm::morton::encode'");
      
      return typename T::value_type();
    }
#endif
    
  } // namespace morton {
  
} // namespace glm {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_GLM_GTX_MORTON_INL)
