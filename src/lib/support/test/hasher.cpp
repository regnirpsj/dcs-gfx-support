// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/test/hasher.cpp                                                    */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

// includes, system

#include <unordered_map> // std::unordered_map<>

// includes, project

#include <hugh/support/hasher.hpp> // add'l 'std::hash<>' specializations

// internal unnamed namespace

namespace {
  
  // types, internal (class, enum, struct, union, typedef)

  // variables, internal
  
  // functions, internal

} // namespace {

// variables, exported
  
// functions, exported

#define BOOST_TEST_MAIN
#include <boost/test/unit_test.hpp>

BOOST_AUTO_TEST_CASE(test_hugh_support_hasher)
{
  using pair_type   = std::pair<unsigned, double>;
  using mapped_type = unsigned;
  using hash_type   = std::hash<pair_type>;
  using ud_hash_map = std::unordered_map<pair_type, mapped_type, hash_type>;
  
  ud_hash_map hmap;

  hmap.insert(std::make_pair(std::make_pair(1, 1.0), 0));
  hmap.insert(std::make_pair(std::make_pair(2, 2.0), 1));
  
  BOOST_CHECK(2 == hmap.size());
}
