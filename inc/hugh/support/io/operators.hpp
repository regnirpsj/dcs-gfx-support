// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/operators.hpp                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_OPERATORS_HPP)

#define HUGH_SUPPORT_IO_OPERATORS_HPP

// includes, system

#include <array>                 // std::array<>
#include <deque>                 // std::deque<>
#include <forward_list>          // std::forward_list<>
#include <functional>            // std::function<>
#include <initializer_list>      // std::initializer_list<>
#include <iosfwd>                // std::basic_ostream<> (fwd decl)
#include <list>                  // std::list<> 
#include <map>                   // std::map<>, std::multimap<>
#include <set>                   // std::multiset<>, std::set<>
#include <string>                // std::basic_string<>
#include <unordered_map>         // std::unordered_map<>, std::unordered_multimap<>
#include <unordered_set>         // std::unordered_multiset<>, std::unordered_set<>
#include <utility>               // std::pair<>
#include <vector>                // std::vector<>

// includes, project

//#include <>

namespace hugh {

  namespace support {

    namespace ostream {
      
      // types, exported (class, enum, struct, union, typedef)

      // variables, exported (extern)

      // functions, inlined (inline)
  
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename CTy, typename CTr,
                typename ResultTy, typename... ArgTy>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::function<ResultTy(ArgTy...)> const&);
#endif
      
      template <typename CTy, typename CTr,
                typename T, typename U>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::pair<T, U> const&);
    
      template <typename CTy, typename CTr,
                typename T, typename U>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::pair<T const, U const> const&);

      template <typename CTy, typename CTr,
                typename T, std::size_t N>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::array<T,N> const&);
      
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::deque<T> const&);
      
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::forward_list<T> const&);

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::initializer_list<T>);
#endif
      
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::list<T> const&);

      template <typename CTy, typename CTr,
                typename K, typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::map<K,T> const&);
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::multimap<K,T> const&);
      
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::multiset<T> const&);

      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::set<T> const&);
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::unordered_map<K,T> const&);
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::unordered_multimap<K,T> const&);
      
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::unordered_multiset<T> const&);

      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::unordered_set<T> const&);
      
      template <typename CTy, typename CTr,
                typename T>
      std::basic_ostream<CTy,CTr>& operator<<(std::basic_ostream<CTy,CTr>&,
                                              std::vector<T> const&);

      std::ostream& operator<<(std::ostream&, std::wstring const&);
      
      // functions, exported (extern)

    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

namespace std {

  template <typename T, typename D> class unique_ptr;

  // types, exported (class, enum, struct, union, typedef)

  // variables, exported (extern)

  // functions, inlined (inline)
  
  /**
   * \brief \c std::ostream operator<< for std::unique_ptr<> instances
   */
  template <typename CTy, typename CTr,
            typename T, typename D>
  basic_ostream<CTy,CTr>& operator<<(basic_ostream<CTy,CTr>&, unique_ptr<T,D> const&);

  // functions, exported (extern)
  
} // namespace std {

#include <hugh/support/io/operators.inl>

#endif // #if !defined(HUGH_SUPPORT_IO_OPERATORS_HPP)
