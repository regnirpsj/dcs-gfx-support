// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/printable.cpp                                                      */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// include i/f header

#include "hugh/support/printable.hpp"

// includes, system

#include <ostream>   // std::ostream
#include <sstream>   // std::ostringstream
#include <stdexcept> // std::logic_error

// includes, project

#include <hugh/support/string.hpp>

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

    namespace ostream {

      namespace printable {
        
        // variables, exported
  
        // functions, exported

        /* virtual */
        base::~base()
        {
          TRACE("hugh::support::ostream::printable::base::~base");
        }
  
        /* virtual */ void
        base::print_on(std::ostream&) const
        {
          TRACE_NEVER("hugh::support::ostream::printable::base::print_on(std::ostream)");

          throw std::logic_error("pure virtual function "
                                 "'hugh::support::ostream::printable::base::print_on' called");
        }

        /* virtual */ void
        base::print_on(std::wostream& wos) const
        {
          TRACE_NEVER("hugh::support::ostream::printable::base::print_on(std::wostream)");

          std::ostringstream ostr;
    
          print_on(ostr);

          wos << string_to_wstring(ostr.str());
        }

      } // namespace printable {

    } // namespace ostream {
    
  } // namespace support {

} // namespace hugh {
