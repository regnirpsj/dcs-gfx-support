// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/printable.hpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_PRINTABLE_HPP)

#define HUGH_SUPPORT_PRINTABLE_HPP

// includes, system

#include <iosfwd> // std::basic_ostream<> (fwd)

// includes, project

#include <hugh/support/export.h>

namespace hugh {
  
  namespace support {

    // types, exported (class, enum, struct, union, typedef)

    class HUGH_SUPPORT_EXPORT printable {

    public:

      virtual ~printable();
    
      virtual void print_on(std::ostream&)  const =0;
      virtual void print_on(std::wostream&) const;
    
    };

    // variables, exported (extern)

    // functions, inlined (inline)

    // functions, exported (extern)

    template <typename CTy, typename CTr>
    std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, printable const&);

  } // namespace support {

} // namespace hugh {

#include <hugh/support/printable.inl>

#endif // #if !defined(HUGH_SUPPORT_PRINTABLE_HPP)
