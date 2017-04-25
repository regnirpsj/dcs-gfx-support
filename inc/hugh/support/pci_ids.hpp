// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/pci_ids.hpp                                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_PCI_IDS_HPP)

#define HUGH_SUPPORT_PCI_IDS_HPP

// includes, system

// #include <>

// includes, project

#include <hugh/support/printable.hpp>

namespace hugh {

  namespace support {

    namespace pci {
      
      // types, exported (class, enum, struct, union, typedef)

      class HUGH_SUPPORT_EXPORT vendor : public printable {

      public:

        explicit vendor(unsigned);
        
        std::string const& name()  const;
        
        virtual void print_on(std::ostream&) const;
        
      private:

        unsigned const id_;
        std::string    name_;
        
      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)

    } // namespace pci {
    
  } // namespace support {
  
} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_PCI_IDS_HPP)
