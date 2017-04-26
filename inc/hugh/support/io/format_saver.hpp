// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/format_saver.hpp                                                */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_FORMAT_SAVER_HPP)

#define HUGH_SUPPORT_IO_FORMAT_SAVER_HPP

// includes, system

#include <boost/io_fwd.hpp>      // basic_ios_all_saver<> (fwd decl)
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <iosfwd>                // std::basic_ios<> (fwd decl)
#include <locale>                // std::locale, std::locale::facet, std::locale::id
#include <string>                // std::basic_string<>

// includes, project

//#include <>

namespace hugh {

  namespace support {

    namespace ostream {
      
      // types, exported (class, enum, struct, union, typedef)

      /**
       * \brief describes the formatting attributes when inserting a container into a
       * \c std::ostream
       */
      template <typename CTy>
      class format_punct : public std::locale::facet {

        using char_type = CTy;

      public:

        static std::locale::id id;

        bool                         formatted;
        char_type                    delim_left;
        char_type                    delim_right;
        char_type                    separator;
        std::basic_string<char_type> indent;
        char_type                    space;
      
        explicit format_punct(size_t = 0);
        explicit format_punct(format_punct const&);

      };
      
      /**
       * \brief an \c std::ostream format saver similar to \c boost::io::basic_ios_all_saver
       */
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      class basic_format_saver : private boost::noncopyable {
    
      public:

        explicit basic_format_saver(std::basic_ios<CTy,CTr>&);
              
      private:

        boost::io::basic_ios_all_saver<CTy> const ias_;

      };

      using format_saver  = basic_format_saver<char>;
      using wformat_saver = basic_format_saver<wchar_t>;
      
      // variables, exported (extern)

      // functions, inlined (inline)

      template <typename FTy, typename CTy, typename CTr = std::char_traits<CTy>>
      FTy const& get_facet(std::basic_ios<CTy,CTr>&);

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ios<CTy,CTr>& formatted(std::basic_ios<CTy,CTr>&);
    
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ios<CTy,CTr>& unformatted(std::basic_ios<CTy,CTr>&);

      // functions, exported (extern)

    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#include <hugh/support/io/format_saver.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_FORMAT_SAVER_HPP)
