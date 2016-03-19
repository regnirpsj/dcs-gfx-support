// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/hasher.inl                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_HASHER_INL)

#define HUGH_SUPPORT_HASHER_INL

// includes, system

#include <boost/functional/hash.hpp> // boost::hash_value<>
#include <functional>                // std::hash<>

// includes, project

//#include <>

namespace std {
  
  // functions, inlined (inline)

  template <typename T1, typename T2>
  inline size_t
  hash<pair<T1, T2>>::operator()(pair<T1, T2> const& a) const
  {
    return boost::hash_value(a);
  }

  template <typename T>
  inline size_t
  hash<boost::intrusive_ptr<T>>::operator()(boost::intrusive_ptr<T> const& a) const
  {
    return boost::hash_value(a);
  }
  
} // namespace std {

#endif // #if !defined(HUGH_SUPPORT_HASHER_INL)
