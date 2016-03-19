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
        "UNDEFINED",
        "RG4_UNORM_PACK8",
        "RGBA4_UNORM_PACK16",
        "BGRA4_UNORM_PACK16",
        "R5G6B5_UNORM_PACK16",
        "B5G6R5_UNORM_PACK16",
        "RGB5A1_UNORM_PACK16",
        "BGR5A1_UNORM_PACK16",
        "A1RGB5_UNORM_PACK16",
        "R8_UNORM_PACK8",
        "R8_SNORM_PACK8",
        "R8_USCALED_PACK8",
        "R8_SSCALED_PACK8",
        "R8_UINT_PACK8",
        "R8_SINT_PACK8",
        "R8_SRGB_PACK8",
        "RG8_UNORM_PACK8",
        "RG8_SNORM_PACK8",
        "RG8_USCALED_PACK8",
        "RG8_SSCALED_PACK8",
        "RG8_UINT_PACK8",
        "RG8_SINT_PACK8",
        "RG8_SRGB_PACK8",
        "RGB8_UNORM_PACK8",
        "RGB8_SNORM_PACK8",
        "RGB8_USCALED_PACK8",
        "RGB8_SSCALED_PACK8",
        "RGB8_UINT_PACK8",
        "RGB8_SINT_PACK8",
        "RGB8_SRGB_PACK8",
        "BGR8_UNORM_PACK8",
        "BGR8_SNORM_PACK8",
        "BGR8_USCALED_PACK8",
        "BGR8_SSCALED_PACK8",
        "BGR8_UINT_PACK8",
        "BGR8_SINT_PACK8",
        "BGR8_SRGB_PACK8",
        "RGBA8_UNORM_PACK8",
        "RGBA8_SNORM_PACK8",
        "RGBA8_USCALED_PACK8",
        "RGBA8_SSCALED_PACK8",
        "RGBA8_UINT_PACK8",
        "RGBA8_SINT_PACK8",
        "RGBA8_SRGB_PACK8",
        "BGRA8_UNORM_PACK8",
        "BGRA8_SNORM_PACK8",
        "BGRA8_USCALED_PACK8",
        "BGRA8_SSCALED_PACK8",
        "BGRA8_UINT_PACK8",
        "BGRA8_SINT_PACK8",
        "BGRA8_SRGB_PACK8",
        "RGBA8_UNORM_PACK32",
        "RGBA8_SNORM_PACK32",
        "RGBA8_USCALED_PACK32",
        "RGBA8_SSCALED_PACK32",
        "RGBA8_UINT_PACK32",
        "RGBA8_SINT_PACK32",
        "RGBA8_SRGB_PACK32",
        "RGB10A2_UNORM_PACK32",
        "RGB10A2_SNORM_PACK32",
        "RGB10A2_USCALED_PACK32",
        "RGB10A2_SSCALED_PACK32",
        "RGB10A2_UINT_PACK32",
        "RGB10A2_SINT_PACK32",
        "BGR10A2_UNORM_PACK32",
        "BGR10A2_SNORM_PACK32",
        "BGR10A2_USCALED_PACK32",
        "BGR10A2_SSCALED_PACK32",
        "BGR10A2_UINT_PACK32",
        "BGR10A2_SINT_PACK32",
        "R16_UNORM_PACK16",
        "R16_SNORM_PACK16",
        "R16_USCALED_PACK16",
        "R16_SSCALED_PACK16",
        "R16_UINT_PACK16",
        "R16_SINT_PACK16",
        "R16_SFLOAT_PACK16",
        "RG16_UNORM_PACK16",
        "RG16_SNORM_PACK16",
        "RG16_USCALED_PACK16",
        "RG16_SSCALED_PACK16",
        "RG16_UINT_PACK16",
        "RG16_SINT_PACK16",
        "RG16_SFLOAT_PACK16",
        "RGB16_UNORM_PACK16",
        "RGB16_SNORM_PACK16",
        "RGB16_USCALED_PACK16",
        "RGB16_SSCALED_PACK16",
        "RGB16_UINT_PACK16",
        "RGB16_SINT_PACK16",
        "RGB16_SFLOAT_PACK16",
        "RGBA16_UNORM_PACK16",
        "RGBA16_SNORM_PACK16",
        "RGBA16_USCALED_PACK16",
        "RGBA16_SSCALED_PACK16",
        "RGBA16_UINT_PACK16",
        "RGBA16_SINT_PACK16",
        "RGBA16_SFLOAT_PACK16",
        "R32_UINT_PACK32",
        "R32_SINT_PACK32",
        "R32_SFLOAT_PACK32",
        "RG32_UINT_PACK32",
        "RG32_SINT_PACK32",
        "RG32_SFLOAT_PACK32",
        "RGB32_UINT_PACK32",
        "RGB32_SINT_PACK32",
        "RGB32_SFLOAT_PACK32",
        "RGBA32_UINT_PACK32",
        "RGBA32_SINT_PACK32",
        "RGBA32_SFLOAT_PACK32",
        "R64_UINT_PACK64",
        "R64_SINT_PACK64",
        "R64_SFLOAT_PACK64",
        "RG64_UINT_PACK64",
        "RG64_SINT_PACK64",
        "RG64_SFLOAT_PACK64",
        "RGB64_UINT_PACK64",
        "RGB64_SINT_PACK64",
        "RGB64_SFLOAT_PACK64",
        "RGBA64_UINT_PACK64",
        "RGBA64_SINT_PACK64",
        "RGBA64_SFLOAT_PACK64",
        "RG11B10_UFLOAT_PACK32",
        "RGB9E5_UFLOAT_PACK32",
        "D16_UNORM_PACK16",
        "D24_UNORM_PACK32",
        "D32_SFLOAT_PACK32",
        "S8_UINT_PACK8",
        "D16_UNORM_S8_UINT_PACK32",
        "D24_UNORM_S8_UINT_PACK32",
        "D32_SFLOAT_S8_UINT_PACK64",
        "RGB_DXT1_UNORM_BLOCK8",
        "RGB_DXT1_SRGB_BLOCK8",
        "RGBA_DXT1_UNORM_BLOCK8",
        "RGBA_DXT1_SRGB_BLOCK8",
        "RGBA_DXT3_UNORM_BLOCK16",
        "RGBA_DXT3_SRGB_BLOCK16",
        "RGBA_DXT5_UNORM_BLOCK16",
        "RGBA_DXT5_SRGB_BLOCK16",
        "R_ATI1N_UNORM_BLOCK8",
        "R_ATI1N_SNORM_BLOCK8",
        "RG_ATI2N_UNORM_BLOCK16",
        "RG_ATI2N_SNORM_BLOCK16",
        "RGB_BP_UFLOAT_BLOCK16",
        "RGB_BP_SFLOAT_BLOCK16",
        "RGBA_BP_UNORM_BLOCK16",
        "RGBA_BP_SRGB_BLOCK16",
        "RGB_ETC2_UNORM_BLOCK8",
        "RGB_ETC2_SRGB_BLOCK8",
        "RGBA_ETC2_UNORM_BLOCK8",
        "RGBA_ETC2_SRGB_BLOCK8",
        "RGBA_ETC2_UNORM_BLOCK16",
        "RGBA_ETC2_SRGB_BLOCK16",
        "R_EAC_UNORM_BLOCK8",
        "R_EAC_SNORM_BLOCK8",
        "RG_EAC_UNORM_BLOCK16",
        "RG_EAC_SNORM_BLOCK16",
        "RGBA_ASTC_4X4_UNORM_BLOCK16",
        "RGBA_ASTC_4X4_SRGB_BLOCK16",
        "RGBA_ASTC_5X4_UNORM_BLOCK16",
        "RGBA_ASTC_5X4_SRGB_BLOCK16",
        "RGBA_ASTC_5X5_UNORM_BLOCK16",
        "RGBA_ASTC_5X5_SRGB_BLOCK16",
        "RGBA_ASTC_6X5_UNORM_BLOCK16",
        "RGBA_ASTC_6X5_SRGB_BLOCK16",
        "RGBA_ASTC_6X6_UNORM_BLOCK16",
        "RGBA_ASTC_6X6_SRGB_BLOCK16",
        "RGBA_ASTC_8X5_UNORM_BLOCK16",
        "RGBA_ASTC_8X5_SRGB_BLOCK16",
        "RGBA_ASTC_8X6_UNORM_BLOCK16",
        "RGBA_ASTC_8X6_SRGB_BLOCK16",
        "RGBA_ASTC_8X8_UNORM_BLOCK16",
        "RGBA_ASTC_8X8_SRGB_BLOCK16",
        "RGBA_ASTC_10X5_UNORM_BLOCK16",
        "RGBA_ASTC_10X5_SRGB_BLOCK16",
        "RGBA_ASTC_10X6_UNORM_BLOCK16",
        "RGBA_ASTC_10X6_SRGB_BLOCK16",
        "RGBA_ASTC_10X8_UNORM_BLOCK16",
        "RGBA_ASTC_10X8_SRGB_BLOCK16",
        "RGBA_ASTC_10X10_UNORM_BLOCK16",
        "RGBA_ASTC_10X10_SRGB_BLOCK16",
        "RGBA_ASTC_12X10_UNORM_BLOCK16",
        "RGBA_ASTC_12X10_SRGB_BLOCK16",
        "RGBA_ASTC_12X12_UNORM_BLOCK16",
        "RGBA_ASTC_12X12_SRGB_BLOCK16",
        "RGB_PVRTC1_8X8_UNORM_BLOCK32",
        "RGB_PVRTC1_8X8_SRGB_BLOCK32",
        "RGB_PVRTC1_16X8_UNORM_BLOCK32",
        "RGB_PVRTC1_16X8_SRGB_BLOCK32",
        "RGBA_PVRTC1_8X8_UNORM_BLOCK32",
        "RGBA_PVRTC1_8X8_SRGB_BLOCK32",
        "RGBA_PVRTC1_16X8_UNORM_BLOCK32",
        "RGBA_PVRTC1_16X8_SRGB_BLOCK32",
        "RGBA_PVRTC2_4X4_UNORM_BLOCK8",
        "RGBA_PVRTC2_4X4_SRGB_BLOCK8",
        "RGBA_PVRTC2_8X4_UNORM_BLOCK8",
        "RGBA_PVRTC2_8X4_SRGB_BLOCK8",
        "RGB_ETC_UNORM_BLOCK8",
        "RGB_ATC_UNORM_BLOCK8",
        "RGBA_ATCA_UNORM_BLOCK16",
        "RGBA_ATCI_UNORM_BLOCK16",
        "L8_UNORM_PACK8",
        "A8_UNORM_PACK8",
        "LA8_UNORM_PACK8",
        "L16_UNORM_PACK16",
        "A16_UNORM_PACK16",
        "LA16_UNORM_PACK16",
        "BGR8_UNORM_PACK32",
        "BGR8_SRGB_PACK32",
        "RG3B2_UNORM_PACK8",
      }
    };
    
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      os << ((a < signed(format_name.size())) ? format_name[a] : format_name[0]);
    }

    return os;
  }

  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, target const& a)
  {
    static std::array<std::string, TARGET_LAST+1> const target_name = {
      {
        "1D",
        "1D_ARRAY",
        "2D",
        "2D_ARRAY",
        "3D",
        "RECT",
        "RECT_ARRAY",
        "CUBE",
        "CUBE_ARRAY",
      }
    };
    
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      os << ((a < signed(target_name.size())) ? target_name[a] : "UNKNOWN");
    }

    return os;
  }
  
  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, texture1d const& a)
  {
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      using glm::io::operator<<;
      
      boost::io::ios_all_saver const ias(os);
    
      os << "[1d:"
         << a.faces()      << ','
         << a.layers()     << ','
         << a.levels()     << ','
         << a.format()     << ','
         << a.target()     << ','
         << a.size()
         << ']';
    }

    return os;
  }

  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, texture2d const& a)
  {
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      boost::io::ios_all_saver const ias(os);
      
      os << "[2d:"
         << a.faces()      << ','
         << a.layers()     << ','
         << a.levels()     << ','
         << a.format()     << ','
         << a.target()     << ','
         << a.size()
         << ']';
    }

    return os;
  }

  template <typename CTy, typename CTr>
  inline std::basic_ostream<CTy,CTr>&
  operator<<(std::basic_ostream<CTy,CTr>& os, texture3d const& a)
  {
    typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
      
    if (cerberus) {
      boost::io::ios_all_saver const ias(os);
      
      os << "[3d:"
         << a.faces()      << ','
         << a.layers()     << ','
         << a.levels()     << ','
         << a.format()     << ','
         << a.target()     << ','
         << a.size()
         << ']';
    }

    return os;
  }
  
} // namespace gli {

#endif // #if !defined(HUGH_GLI_GTX_IO_INL)
