// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/printable.inl                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_PRINTABLE_INL)

#define HUGH_SUPPORT_PRINTABLE_INL

// includes, system

#include <ostream> // std::basic_ostream<>

// includes, project

// #include <>

namespace hugh {
  
  namespace support {
  
    // functions, inlined (inline)

    template <typename CTy, typename CTr>
    inline std::basic_ostream<CTy,CTr>&
    operator<<(std::basic_ostream<CTy,CTr>& os, printable const& a)
    {
      typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
    
      if (cerberus) {
        a.print_on(os);
      }
    
      return os;
    }
  
  } // namespace support {

} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_PRINTABLE_INL)
