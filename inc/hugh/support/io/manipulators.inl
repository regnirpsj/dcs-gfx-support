// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/manipulators.inl                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_MANIPULATORS_INL)

#define HUGH_SUPPORT_IO_MANIPULATORS_INL

// includes, system

//#include <>

// includes, project

#include <hugh/support/io/format_saver.hpp>

namespace hugh {
  
  namespace support {

    namespace ostream {
      
      // functions, inlined (inline)

      template <typename CTy>
      inline /* explicit */
      delimeter<CTy>::delimeter(std::array<CTy, 3> const& a)
        : value(a)
      {}
    
      template <typename CTy>
      inline /* explicit */
      delimeter<CTy>::delimeter(CTy a, CTy b, CTy c)
        : value({ a, b, c, })
      {}

      template <typename CTy>
      inline /* explicit */
      indent<CTy>::indent(std::basic_string<CTy> const& a)
        : value(a)
      {}
    
      template <typename CTy>
      inline /* explicit */
      indent<CTy>::indent(unsigned a, CTy b)
        : value(a, b)
      {}

      inline /* explicit */
      remove::remove(unsigned a)
        : value(a)
      {}

      
      template <typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, delimeter<CTy> const& a)
      {                                        
        format_punct<CTy>& fmt(const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)));
      
        fmt.delim_left  = a.value[0];
        fmt.delim_right = a.value[1];
        fmt.separator   = a.value[2];

        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, indent<CTy> const& a)
      {                                        
        format_punct<CTy>& fmt(const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)));
      
        fmt.indent = a.value;

        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, remove const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

        if (cerberus) {
          using pos_type = typename std::basic_ostream<CTy,CTr>::pos_type;
          
          if (pos_type(-1) == os.tellp()) {
            switch (a.value) {
            case 0:  /* do nothing */                             break;
            case 1:  os << '\b';                                  break;
            default: os << std::basic_string<CTy>(a.value, '\b'); break;
            }
          } else {
            pos_type const current(os.tellp());
      
            os.seekp(std::min(std::max(pos_type(0),
                                       pos_type(current - pos_type(a.value))),
                              current),
                     std::ios_base::beg);
          }
        }
        
        return os;
      }
      
    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_IO_MANIPULATORS_INL)
