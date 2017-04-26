// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/scoped_redirect.inl                                             */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_SCOPED_REDIRECT_INL)

#define HUGH_SUPPORT_IO_SCOPED_REDIRECT_INL

// includes, system

//#include <>

// includes, project

//#include <>

namespace hugh {
  
  namespace support {

    namespace ostream {
      
      // functions, inlined (inline)
      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_scoped_redirect<CTy,CTr>::basic_scoped_redirect(std::basic_ostream<CTy,CTr>& a,
                                                            std::basic_ostream<CTy,CTr>& b)
        : boost::noncopyable(),
          list_             (1, std::make_pair(&a, a.rdbuf(b.rdbuf())))
      {}

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_scoped_redirect<CTy,CTr>::basic_scoped_redirect(ostream_initializer_list a,
                                                            std::basic_ostream<CTy,CTr>& b)
        : boost::noncopyable(),
          list_             ()
      {
        for (auto s : a) {
          if (nullptr != s) {
            list_.push_back(std::make_pair(s, s->rdbuf(b.rdbuf())));
          }
        }
      }

      template <typename CTy, typename CTr>
      inline
      basic_scoped_redirect<CTy,CTr>::~basic_scoped_redirect()
      {
        for (auto& p : list_) {
          p.first->rdbuf(p.second);
        }
      }
      
    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_IO_SCOPED_REDIRECT_INL)
