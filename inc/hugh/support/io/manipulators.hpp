// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/manipulators.hpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_MANIPULATORS_HPP)

#define HUGH_SUPPORT_IO_MANIPULATORS_HPP

// includes, system

#include <array>  // std::array<>
#include <iosfwd> // std::basic_ostream<> (fwd decl)
#include <string> // std::basic_string<>

// includes, project

//#include <>

namespace hugh {

  namespace support {

    namespace ostream {
      
      // types, exported (class, enum, struct, union, typedef)

      /**
       * \brief delimeter description: left/right braces and element separator
       */
      template <typename CTy>
      struct delimeter { 
    
        std::array<CTy, 3> const value;

        explicit delimeter(std::array<CTy, 3> const& = {'[', ']', ','});
        explicit delimeter(CTy /* left */, CTy /* right */, CTy /* separator */ = ',');

      };

      /**
       * \brief indentation description
       */
      template <typename CTy>
      struct indent { 
    
        std::basic_string<CTy> const value;

        explicit indent(std::basic_string<CTy> const& = "");
        explicit indent(unsigned /* #chars */, CTy /* char proto */ = '\0');
      
      };

      /**
       * \brief char remover
       */
      struct remove { 

        unsigned const value;

        explicit remove(unsigned /* #chars */);

      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
      
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, delimeter<CTy> const&);

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, indent<CTy> const&);

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, remove const&);
      
      // functions, exported (extern)

    } // namespace ostream {
    
  } // namespace support {
  
} // namespace hugh {

#include <hugh/support/io/manipulators.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_MANIPULATORS_HPP)
