// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/position_saver.inl                                              */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_POSITION_SAVER_INL)

#define HUGH_SUPPORT_IO_POSITION_SAVER_INL

// includes, system

//#include <>

// includes, project

//#include <>

namespace hugh {
  
  namespace support {

    namespace istream {
      
      // functions, inlined (inline)

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_position_saver<CTy,CTr>::basic_position_saver(std::basic_istream<CTy,CTr>& s)
        : boost::noncopyable(),
          s_                (s),
          p_                (s_.tellg())
      {}

      template <typename CTy, typename CTr>
      inline
      basic_position_saver<CTy,CTr>::~basic_position_saver()
      {
        restore();
      }

      template <typename CTy, typename CTr>
      inline void
      basic_position_saver<CTy,CTr>::restore()
      {
        s_.seekg(p_);
      }
      
    } // namespace istream {
    
    namespace ostream {
      
      // functions, inlined (inline)

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_position_saver<CTy,CTr>::basic_position_saver(std::basic_ostream<CTy,CTr>& s)
        : boost::noncopyable(),
          s_                (s),
          p_                (s_.tellp())
      {}

      template <typename CTy, typename CTr>
      inline
      basic_position_saver<CTy,CTr>::~basic_position_saver()
      {
        restore();
      }

      template <typename CTy, typename CTr>
      inline void
      basic_position_saver<CTy,CTr>::restore()
      {
        s_.seekp(p_);
      }
      
    } // namespace ostream {

    namespace iostream {
      
      // functions, inlined (inline)

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_position_saver<CTy,CTr>::basic_position_saver(std::basic_iostream<CTy,CTr>& s)
        : istream::basic_position_saver<CTy,CTr>(s),
          ostream::basic_position_saver<CTy,CTr>(s)
      {}

      template <typename CTy, typename CTr>
      inline
      basic_position_saver<CTy,CTr>::~basic_position_saver()
      {
        restore();
      }

      template <typename CTy, typename CTr>
      inline void
      basic_position_saver<CTy,CTr>::restore()
      {
        ostream::basic_position_saver<CTy,CTr>::restore();
        istream::basic_position_saver<CTy,CTr>::restore();
      }
      
    } // namespace iostream {

  } // namespace support {
  
} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_IO_POSITION_SAVER_INL)
