// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  gli/gtx/io.inl                                                                  */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_GLI_GTX_IO_INL)

#define HUGH_GLI_GTX_IO_INL

// includes, system

#include <array>                  // std::array<>
#include <boost/io/ios_state.hpp> // boost::io::ios_all_saver
#include <glm/gtx/io.hpp>         // glm::io::operator<<
#include <iomanip>                // std::fixed, std::setprecision
#include <ostream>                // std::basic_ostream<>
#include <string>                 // std::string

// includes, project

//#include <>

namespace gli {
    
  // functions, inlined (inline)

  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, format const& a)
  {
    static std::array<std::string, FORMAT_LAST+1> const format_name = {
      {
        "R8_UNORM",
        "RG8_UNORM",
        "RGB8_UNORM",
        "RGBA8_UNORM",
        "R16_UNORM",
        "RG16_UNORM",
        "RGB16_UNORM",
        "RGBA16_UNORM",
        "R8_SNORM",
        "RG8_SNORM",
        "RGB8_SNORM",
        "RGBA8_SNORM",
        "R16_SNORM",
        "RG16_SNORM",
        "RGB16_SNORM",
        "RGBA16_SNORM",
        "R8U",
        "RG8U",
        "RGB8U",
        "RGBA8U",
        "R16U",
        "RG16U",
        "RGB16U",
        "RGBA16U",
        "R32U",
        "RG32U",
        "RGB32U",
        "RGBA32U",
        "R8I",
        "RG8I",
        "RGB8I",
        "RGBA8I",
        "R16I",
        "RG16I",
        "RGB16I",
        "RGBA16I",
        "R32I",
        "RG32I",
        "RGB32I",
        "RGBA32I",
        "R16F",
        "RG16F",
        "RGB16F",
        "RGBA16F",
        "R32F",
        "RG32F",
        "RGB32F",
        "RGBA32F",
        "RGB9E5",
        "RG11B10F",
        "R3G3B2",
        "R5G6B5",
        "RGB5A1",
        "RGBA4",
        "RGB10A2",
        "D16",
        "D24X8",
        "D24S8",
        "D32F",
        "D32FS8X24",
        "RGB_DXT1",
        "RGBA_DXT1",
        "RGBA_DXT3",
        "RGBA_DXT5",
        "R_ATI1N_UNORM",
        "R_ATI1N_SNORM",
        "RG_ATI2N_UNORM",
        "RG_ATI2N_SNORM",
        "RGB_BP_UNSIGNED_FLOAT",
        "RGB_BP_SIGNED_FLOAT",
        "RGB_BP_UNORM",
        "RGB_PVRTC_4BPPV1",
        "RGB_PVRTC_2BPPV1",
        "RGBA_PVRTC_4BPPV1",
        "RGBA_PVRTC_2BPPV1",
        "ATC_RGB",
        "ATC_RGBA_EXPLICIT_ALPHA",
        "ATC_RGBA_INTERPOLATED_ALPHA",
        "RGBA_ASTC_4x4",
        "RGBA_ASTC_5x4",
        "RGBA_ASTC_5x5",
        "RGBA_ASTC_6x5",
        "RGBA_ASTC_6x6",
        "RGBA_ASTC_8x5",
        "RGBA_ASTC_8x6",
        "RGBA_ASTC_8x8",
        "RGBA_ASTC_10x5",
        "RGBA_ASTC_10x6",
        "RGBA_ASTC_10x8",
        "RGBA_ASTC_10x10",
        "RGBA_ASTC_12x10",
        "RGBA_ASTC_12x12",
        "SRGB8",
        "SRGB8_ALPHA8",
        "SRGB_DXT1",
        "SRGB_ALPHA_DXT1",
        "SRGB_ALPHA_DXT3",
        "SRGB_ALPHA_DXT5",
        "SRGB_BP_UNORM",
        "SRGB_PVRTC_2BPPV1",
        "SRGB_PVRTC_4BPPV1",
        "SRGB_ALPHA_PVRTC_2BPPV1",
        "SRGB_ALPHA_PVRTC_4BPPV1",
        "SRGB8_ALPHA8_ASTC_4x4",
        "SRGB8_ALPHA8_ASTC_5x4",
        "SRGB8_ALPHA8_ASTC_5x5",
        "SRGB8_ALPHA8_ASTC_6x5",
        "SRGB8_ALPHA8_ASTC_6x6",
        "SRGB8_ALPHA8_ASTC_8x5",
        "SRGB8_ALPHA8_ASTC_8x6",
        "SRGB8_ALPHA8_ASTC_8x8",
        "SRGB8_ALPHA8_ASTC_10x5",
        "SRGB8_ALPHA8_ASTC_10x6",
        "SRGB8_ALPHA8_ASTC_10x8",
        "SRGB8_ALPHA8_ASTC_10x10",
        "SRGB8_ALPHA8_ASTC_12x10",
        "SRGB8_ALPHA8_ASTC_12x12",
      }
    };
    
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      os << ((a < signed(format_name.size())) ? format_name[a] : "UNKNOWN");
    }

    return os;
  }
  
  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, texture1D const& a)
  {
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      using glm::io::operator<<;
      
      boost::io::ios_all_saver const ias(os);
    
      os << "[1d:"
         << a.faces()      << ','
         << a.layers()     << ','
         << a.levels()     << ",["
         << a.dimensions() << "],"
         << a.format()     << ','
         << a.size()
         << ']';
    }

    return os;
  }

  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, texture2D const& a)
  {
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      boost::io::ios_all_saver const ias(os);
      
      os << "[2d:"
         << a.faces()      << ','
         << a.layers()     << ','
         << a.levels()     << ','
         << a.dimensions() << ','
         << a.format()     << ','
         << a.size()
         << ']';
    }

    return os;
  }

  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, texture3D const& a)
  {
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      boost::io::ios_all_saver const ias(os);
      
      os << "[3d:"
         << a.faces()      << ','
         << a.layers()     << ','
         << a.levels()     << ','
         << a.dimensions() << ','
         << a.format()     << ','
         << a.size()
         << ']';
    }

    return os;
  }
  
} // namespace gli {

#endif // #if !defined(HUGH_GLI_GTX_IO_INL)
