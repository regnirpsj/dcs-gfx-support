// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/scoped_redirect.hpp                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_SCOPED_REDIRECT_HPP)

#define HUGH_SUPPORT_IO_SCOPED_REDIRECT_HPP

// includes, system

#include <boost/noncopyable.hpp> // boost::noncopyable
#include <initializer_list>      // std::initializer_list<>
#include <iosfwd>                // std::basic_ostream<> (fwd decl)
#include <utility>               // std::pair<>
#include <vector>                // std::vector<>

// includes, project

//#include <>

namespace hugh {

  namespace support {
    
    namespace ostream {
      
      // types, exported (class, enum, struct, union, typedef)

      /**
       * \brief (temporarily) redirect \c std::ostream content to another \c std::ostream
       *
       * example:
       *
       * \code{.cpp}
       *  {
       *  #if defined(HUGH_ALL_TRACE)
       *    using namespace hugh::support;
       *
       *    std::ofstream                  logfile ("log.txt");
       *    ostream::scoped_redirect const sor_cerr(std::cerr, logfile);
       *    ostream::scoped_redirect const sor_clog(std::clog, logfile);
       *    ostream::scoped_redirect const sor_cout(std::cout, logfile);
       *  #endif
       *
       *    std::cerr << "this will end up in 'log.txt'" << std::endl;
       *    std::clog << "this will end up in 'log.txt'" << std::endl;
       *    std::cout << "this will end up in 'log.txt'" << std::endl;
       *  }
       * \endcode
       *
       * \code{.cpp}
       *  {
       *  #if defined(HUGH_ALL_TRACE)
       *    using namespace hugh::support;
       *
       *    std::ostringstream             ostr;
       *    ostream::scoped_redirect const sor_call({ &std::cerr, &std::clog, &std::cout }, ostr);
       *  #endif
       *
       *    std::cerr << "this will end up in 'ostr.str()'" << std::endl;
       *    std::clog << "this will end up in 'ostr.str()'" << std::endl;
       *    std::cout << "this will end up in 'ostr.str()'" << std::endl;
       *  }
       * \endcode
       *
       * \see http://stackoverflow.com/questions/4753153/redirecting-stdcout
       */
      template <typename CTy, typename CTr = std::char_traits<CTy>>
      class basic_scoped_redirect : private boost::noncopyable {

      public:

        using ostream_initializer_list = std::initializer_list<std::basic_ostream<CTy,CTr>*>;

        explicit basic_scoped_redirect(std::basic_ostream<CTy,CTr>& /* src  */,
                                       std::basic_ostream<CTy,CTr>& /* dst  */);
        explicit basic_scoped_redirect(ostream_initializer_list     /* srcs */,
                                       std::basic_ostream<CTy,CTr>& /* dst  */);
                ~basic_scoped_redirect();

      private:

        using stream_type             = std::basic_ostream<CTy,CTr>;
        using streambuf_type          = std::basic_streambuf<CTy,CTr>;
        using stream_buffer_pair_type = std::pair<stream_type*, streambuf_type*>;
        using stream_buffer_list_type = std::vector<stream_buffer_pair_type>;

        stream_buffer_list_type list_;

      };

      using scoped_redirect  = basic_scoped_redirect<char>;
      using wscoped_redirect = basic_scoped_redirect<wchar_t>;
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#include <hugh/support/io/scoped_redirect.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_SCOPED_REDIRECT_HPP)
