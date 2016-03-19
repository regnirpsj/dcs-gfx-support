// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  proto.inl                                                                       */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(PREFIX_PROTO_INL)

#define PREFIX_PROTO_INL

// includes, system

#include <>

// includes, project

#include <>

#define PREFIX_USE_TRACE
#undef PREFIX_USE_TRACE
#include <hugh/support/trace.hpp>
//#if defined(PREFIX_USE_TRACE) || defined(PREFIX_ALL_TRACE)
//#  include <typeinfo>
//#  include <support/type_info.hpp>
//#endif

namespace hugh {
  
  // functions, inlined (inline)
  
} // namespace hugh {

#if defined(PREFIX_USE_TRACE)
#  undef PREFIX_USE_TRACE
#endif

#endif // #if !defined(PREFIX_PROTO_INL)
