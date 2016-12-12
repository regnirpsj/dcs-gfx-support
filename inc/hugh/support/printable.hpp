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

#include <hugh/support/config.hpp>
#include <hugh/support/export.h>

namespace hugh {
  
  namespace support {

    namespace ostream {

      namespace printable {
        
        // types, exported (class, enum, struct, union, typedef)

        class HUGH_SUPPORT_EXPORT base {
        
        public:
        
          virtual ~base();
        
          virtual void print_on(std::ostream&)  const =0;
          virtual void print_on(std::wostream&) const;
        
        };

        template <typename T>
        class mixin : virtual public T {
    
        public:
    
          using T::print_on;
    
        };

        // variables, exported (extern)

        // functions, inlined (inline)
        
        template <typename CTy, typename CTr>
        std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&, base const&);

        // functions, exported (extern)
        
      } // namespace printable {

    } // namespace ostream {

    // types, exported (class, enum, struct, union, typedef)
    
    using printable = ostream::printable::mixin<ostream::printable::base>;
    
    // variables, exported (extern)

    // functions, inlined (inline)

    // functions, exported (extern)

  } // namespace support {

} // namespace hugh {

#include <hugh/support/printable.inl>

#endif // #if !defined(HUGH_SUPPORT_PRINTABLE_HPP)
