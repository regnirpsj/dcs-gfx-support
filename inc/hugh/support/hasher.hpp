// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/hasher.hpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_HASHER_HPP)

#define HUGH_SUPPORT_HASHER_HPP

// includes, system

#include <boost/intrusive_ptr.hpp> // boost::intrusive_ptr<>
#include <string>                  // std::string
#include <utility>                 // std::pair<>

// includes, project

#include <hugh/support/config.hpp>

namespace std {
  
  // types, exported (class, enum, struct, union, typedef)

  template <typename T1, typename T2>
  struct hash<pair<T1, T2>> {
      
    size_t operator()(pair<T1, T2> const&) const;
      
  };

  template <typename T>
  struct hash<boost::intrusive_ptr<T>> {

    size_t operator()(boost::intrusive_ptr<T> const&) const;
    
  };
  
  template <>
  struct hash<string const> {
    
    size_t operator()(string const& a) const
    {
      return hash<string>()(a);
    }
    
  };
  
  // variables, exported (extern)

  // functions, inlined (inline)
  
  // functions, exported (extern)

} // namespace std {

#include <hugh/support/hasher.inl>

#endif // #if !defined(UKACHULLDCS_08961_SUPPORT_HASHER_HPP)
