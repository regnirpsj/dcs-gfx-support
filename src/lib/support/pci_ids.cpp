// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/pci_ids.cpp                                                        */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/pci_ids.hpp"

// includes, system

#include <ostream> // std::basic_ostream<>

// includes, project

extern "C" {
  
#  include <pci/pci.h>

}

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

namespace hugh {

  namespace support {

    namespace pci {

      // variables, exported
  
      // functions, exported

      /* explicit */
      vendor::vendor(unsigned a)
        : id_  (a),
          name_()
      {
        struct pci_access* pacc(pci_alloc());
        
        pci_init(pacc);
        
        char buf[1024];
        
        pci_lookup_name(pacc, buf, sizeof(buf), PCI_LOOKUP_VENDOR, id_);

        name_ = buf;
        
        pci_cleanup(pacc);
      }

      std::string const&
      vendor::name() const
      {
        return name_;
      }      
        
      /* virtual */ void
      vendor::print_on(std::ostream& os) const
      {
        os << name();
      }
      
    } // namespace pci {
    
  } // namespace support {
  
} // namespace hugh {
