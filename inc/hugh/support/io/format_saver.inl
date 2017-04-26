// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/format_saver.inl                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_FORMAT_SAVER_INL)

#define HUGH_SUPPORT_IO_FORMAT_SAVER_INL

// includes, system

#include <boost/io/ios_state.hpp> // boost::io::ios_all_saver

// includes, project

//#include <>

namespace hugh {
  
  namespace support {

    namespace ostream {
      
      // functions, inlined (inline)

      template <typename CTy>
      inline /* explicit */
      format_punct<CTy>::format_punct(size_t a)
        : std::locale::facet(a),
          formatted         (true),
          delim_left        ('('),
          delim_right       (')'),
          separator         (','),
          indent            (),
          space             (' ')
      {}
    
      template <typename CTy>
      inline /* explicit */
      format_punct<CTy>::format_punct(format_punct const& a)
        : std::locale::facet(0),
          formatted         (a.formatted),
          delim_left        (a.delim_left),
          delim_right       (a.delim_right),
          separator         (a.separator),
          indent            (a.indent),
          space             (a.space)
      {}

      template <typename CTy> std::locale::id format_punct<CTy>::id;

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_format_saver<CTy,CTr>::basic_format_saver(std::basic_ios<CTy,CTr>& a)
        : boost::noncopyable(),
          ias_              (a)
      {   
        a.imbue(std::locale(a.getloc(), new format_punct<CTy>(get_facet<format_punct<CTy>>(a))));
      }
      
      template <typename FTy, typename CTy, typename CTr>
      inline FTy const&
      get_facet(std::basic_ios<CTy,CTr>& ios)
      {
        if (!std::has_facet<FTy>(ios.getloc())) {
          ios.imbue(std::locale(ios.getloc(), new FTy));
        } 
      
        return std::use_facet<FTy>(ios.getloc());
      }
      
      template <typename CTy, typename CTr>
      inline std::basic_ios<CTy,CTr>&
      formatted(std::basic_ios<CTy,CTr>& os)
      {
        const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)).formatted = true;
      
        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ios<CTy,CTr>&
      unformatted(std::basic_ios<CTy,CTr>& os)
      {
        const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)).formatted = false;
      
        return os;
      }
      
    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_IO_FORMAT_SAVER_INL)
