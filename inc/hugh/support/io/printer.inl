// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/printer.inl                                                     */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_PRINTER_INL)

#define HUGH_SUPPORT_IO_PRINTER_INL

// includes, system

//#include <>

// includes, project

//#include <>

namespace hugh {
  
  namespace support {

    namespace ostream {
      
      // functions, inlined (inline)

      template <typename T, typename R>
      inline /* explicit */
      enumeration<T,R>::enumeration(enum_type a, enum_range const& b)
        : value(a), range(b)
      {}

      template <typename T, typename R>
      inline /* explicit */
      bitmask<T,R>::bitmask(bitmask_type a, bitmask_range const& b)
        : value(a), range(b)
      {}

      template <typename T, typename R>
      inline enumeration<T,R>
      enumerate(T a, R const& b)
      {
        return enumeration<T,R>(a, b);
      }

      template <typename T, typename R, typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, enumeration<T,R> const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

        if (cerberus) {
          bool found(false);

          for (auto const& e : a.range) {
            if (e.first == a.value) {
              os << e.second;

              found = true;

              break;
            }
          }

          if (!found) {
            os << "INVALID (" << signed(a.value) << ')';
          }
        }
        
        return os;
      }
      
      template <typename T, typename R>
      inline bitmask<T,R>
      flags(T a, R const& b)
      {
        return bitmask<T,R>(a, b);
      }

      template <typename T, typename R, typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, bitmask<T,R> const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

        if (cerberus) {
          using pos_type = typename std::basic_ostream<CTy,CTr>::pos_type;

          pos_type const pos_old(os.tellp());
          
          for (auto f : a.range) {
            if (a.value & f.first) {
              os << f.second << '|';
            }
          }
          
          os << remove(1);

          pos_type const pos_new(os.tellp());
          
          if ((pos_type(-1) != pos_old) && (0 == (pos_new - pos_old))) {
            os << "NONE";
          }
        }
        
        return os;
      }
      
    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_IO_PRINTER_INL)
