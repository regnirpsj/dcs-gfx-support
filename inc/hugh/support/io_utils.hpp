// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io_utils.hpp                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_UTILS_HPP)

#define HUGH_SUPPORT_IO_UTILS_HPP

// includes, system

#include <array>                 // std::array<>
#include <boost/io_fwd.hpp>      // basic_ios_all_saver<> (fwd)
#include <boost/noncopyable.hpp> // boost::noncopyable
#include <functional>            // std::function<>
#include <iosfwd>                // std::basic_istream<>, std::basic_iostream<>,
                                 // std::basic_ostream<> (fwd decl), std::streampos
#include <locale>                // std::locale, std::locale::facet, std::locale::id
#include <string>                // std::basic_string<>
#include <utility>               // std::pair<>

// includes, project

#include <hugh/support/config.hpp>
#include <hugh/support/export.h>
#include <hugh/support/printable.hpp>

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

      class HUGH_SUPPORT_EXPORT binary : public printable {

      public:

        explicit binary(unsigned);

        virtual void print_on(std::ostream&) const;
      
      private:

        unsigned value_;
      
      };
    
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

      /**
       * \brief (temporarily) redirect \c std::ostream content to another \c std::ostream
       *
       * example:
       *
       * \code{.cpp}
       *  {
       *  #if defined(HUGH_ALL_TRACE)
       *    std::ofstream                           logfile ("log.txt");
       *    support::ostream::scoped_redirect const sor_cerr(std::cerr, logfile);
       *    support::ostream::scoped_redirect const sor_clog(std::clog, logfile);
       *    support::ostream::scoped_redirect const sor_cout(std::cout, logfile);
       *  #endif
       *
       *    std::cout << "this will end up in 'log.txt'" << std::endl;
       *  }
       * \endcode
       *
       * \see http://stackoverflow.com/questions/4753153/redirecting-stdcout
       */
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      class basic_scoped_redirect : private boost::noncopyable {
      
      public:
      
        explicit basic_scoped_redirect(std::basic_ostream<CTy,CTr>& /* src */,
                                       std::basic_ostream<CTy,CTr>& /* dst */);
                ~basic_scoped_redirect();
      
      private:

        using stream_type    = std::basic_ostream<CTy,CTr>;
        using streambuf_type = std::basic_streambuf<CTy,CTr>;
      
        stream_type&    s_;
        streambuf_type* b_;
      
      };

      using scoped_redirect  = basic_scoped_redirect<char>;
      using wscoped_redirect = basic_scoped_redirect<wchar_t>;
      
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
       * \brief (experimental) char remover (will probably never work)
       */
      struct remove { 

        unsigned const value;

        explicit remove(unsigned /* #chars */);

      };
    
      // variables, exported (extern)
    
      // functions, inlined (inline)

      template <typename FTy, typename CTy, typename CTr = std::char_traits<CTy>>
      FTy const& get_facet(std::basic_ios<CTy,CTr>&);
    
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ios<CTy,CTr>& formatted(std::basic_ios<CTy,CTr>&);
    
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ios<CTy,CTr>& unformatted(std::basic_ios<CTy,CTr>&);
    
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, delimeter<CTy> const&);

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, indent<CTy> const&);

      template <typename CTy, typename CTr = std::char_traits<CTy>>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, remove const&);

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename CTy, typename CTr,
                typename ResultTy, typename... ArgTy>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::function<ResultTy(ArgTy...)> const&);
#endif
    
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, std::pair<T, T> const&);
    
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::pair<T const, T const> const&);

      template <typename CTy, typename CTr,
                typename T, typename U>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, std::pair<T, U> const&);
    
      template <typename CTy, typename CTr,
                typename T, typename U>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::pair<T const, U const> const&);
    
      template <typename CTy, typename CTr,
                template <typename, std::size_t> class Container, class V, std::size_t N>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, Container<V,N> const&);
    
      template <typename CTy, typename CTr,
                template <typename, typename> class Container, class V, class A>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, Container<V,A> const&);
    
      template <typename CTy, typename CTr,
                template <typename, typename, typename> class Container, class K, class C, class A>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              Container<K,C,A> const&);
    
      template <typename CTy, typename CTr,
                template <typename, typename, typename, typename> class Container, class K, class V,
                class C, class A>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              Container<K,V,C,A> const&);
    
      template <typename CTy, typename CTr,
                template <typename, typename, typename, typename, typename> class Container,
                class K, class V, class H, class C, class A>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              Container<K,V,H,C,A> const&);
    
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::initializer_list<T>);
#endif
    
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
    
namespace std {

  template <typename T, typename D> class unique_ptr;

  /**
   * \brief \c std::ostream operator<< for std::unique_ptr<> instances
   */
  template <typename CTy, typename CTr,
            typename T, typename D>
  basic_ostream<CTy,CTr>& operator<<(basic_ostream<CTy,CTr>&, unique_ptr<T,D> const&);
  
} // namespace std {

#include <hugh/support/io_utils.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_UTILS_HPP)
