// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/printer.hpp                                                     */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_PRINTER_HPP)

#define HUGH_SUPPORT_IO_PRINTER_HPP

// includes, system

#include <iosfwd> // std::basic_ostream<> (fwd decl)

// includes, project

#include <hugh/support/export.h>
#include <hugh/support/printable.hpp>

namespace hugh {

  namespace support {

    namespace ostream {
      
      // types, exported (class, enum, struct, union, typedef)
      
      class HUGH_SUPPORT_EXPORT binary : public support::printable {

      public:

        explicit binary(unsigned);

        virtual void print_on(std::ostream&) const;
      
      private:

        unsigned value_;
      
      };
    
      /**
       * \brief enum printer
       */
      template <typename T, typename R>
      struct enumeration { 

        using enum_type  = T;
        using enum_range = R;
        
        enum_type const   value;
        enum_range const& range;

        explicit enumeration(enum_type /* value */, enum_range const& /* range */);

      };

      /**
       * \brief enum printer
       */
      template <typename T, typename R>
      struct bitmask { 

        using bitmask_type  = T;
        using bitmask_range = R;
        
        bitmask_type const   value;
        bitmask_range const& range;

        explicit bitmask(bitmask_type /* value */, bitmask_range const& /* range */);

      };
      
      // variables, exported (extern)

      // functions, inlined (inline)

      template <typename T, typename R>
      enumeration<T,R> enumerate(T, R const&);
      
      template <typename T, typename R, typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              enumeration<T,R> const&);
      
      template <typename T, typename R>
      bitmask<T,R> flags(T, R const&);

      template <typename T, typename R, typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              bitmask<T,R> const&);
      
      // functions, exported (extern)

    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#include <hugh/support/io/printer.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_PRINTER_HPP)
