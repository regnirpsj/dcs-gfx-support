// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/position_saver.hpp                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_POSITION_SAVER_HPP)

#define HUGH_SUPPORT_IO_POSITION_SAVER_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <iosfwd>                // std::basic_istream<> (fwd decl),
                                 // std::basic_iostream<> (fwd decl),
                                 // std::basic_ostream<> (fwd decl)

// includes, project

//#include <>

namespace hugh {

  namespace support {

    namespace istream {
      
      // types, exported (class, enum, struct, union, typedef)

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      class basic_position_saver : private boost::noncopyable {

      public:

        explicit basic_position_saver(std::basic_istream<CTy,CTr>&);
                ~basic_position_saver();

        void restore();

      private:

        using stream_type = std::basic_istream<CTy,CTr>;
        using pos_type    = typename stream_type::pos_type;

        stream_type&   s_;
        pos_type const p_;

      };

      using position_saver  = basic_position_saver<char>;
      using wposition_saver = basic_position_saver<wchar_t>;
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace istream {
    
    namespace ostream {
      
      // types, exported (class, enum, struct, union, typedef)

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      class basic_position_saver : private boost::noncopyable {

      public:

        explicit basic_position_saver(std::basic_ostream<CTy,CTr>&);
                ~basic_position_saver();

        void restore();

      private:

        using stream_type = std::basic_ostream<CTy,CTr>;
        using pos_type    = typename stream_type::pos_type;

        stream_type&   s_;
        pos_type const p_;

      };

      using position_saver  = basic_position_saver<char>;
      using wposition_saver = basic_position_saver<wchar_t>;
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace ostream {

    namespace iostream {
      
      // types, exported (class, enum, struct, union, typedef)

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      class basic_position_saver : public istream::basic_position_saver<CTy,CTr>,
                                   public ostream::basic_position_saver<CTy,CTr> {

      public:

        explicit basic_position_saver(std::basic_iostream<CTy,CTr>&);
                ~basic_position_saver();

        void restore();

      };

      using position_saver  = basic_position_saver<char>;
      using wposition_saver = basic_position_saver<wchar_t>;
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace iostream {

  } // namespace support {
  
} // namespace hugh {

#include <hugh/support/io/position_saver.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_POSITION_SAVER_HPP)
