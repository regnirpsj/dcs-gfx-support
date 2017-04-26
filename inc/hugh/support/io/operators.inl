// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2017 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/io/operators.inl                                                   */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_OPERATORS_INL)

#define HUGH_SUPPORT_IO_OPERATORS_INL

// includes, system

//#include <>

// includes, project

#include <hugh/support/io/format_saver.hpp>
#include <hugh/support/string.hpp>
#include <hugh/support/type_info.hpp>

namespace hugh {
  
  namespace support {

    namespace ostream {
      
      // functions, inlined (inline)

#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename CTy, typename CTr,
                typename ResultTy, typename... ArgTy>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::function<ResultTy(ArgTy...)> const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
    
        if (cerberus) {
          os << support::demangle(typeid(a)) << "@" << &a;
        }

        return os;
      }
#endif    

      template <typename CTy, typename CTr,
                typename T, typename U>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::pair<T, U> const& a)
      {
        return os << static_cast<std::pair<T const, U const> const&>(a);
      }
    
      template <typename CTy, typename CTr,
                typename T, typename U>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::pair<T const, U const> const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);
    
        if (cerberus) {
          format_punct<CTy> const& fmt(get_facet<format_punct<CTy>>(os));

          if (fmt.formatted) {
            os << fmt.delim_left << a.first << fmt.separator << a.second << fmt.delim_right;
          } else {
            os << a.first << fmt.space << a.second;
          }
        }
      
        return os;
      }

      namespace detail {

        template <typename CTy, typename CTr,
                  typename Container>
        inline std::basic_ostream<CTy,CTr>&
        print_container_on(std::basic_ostream<CTy,CTr>& os, Container const& a, bool b)
        {
          typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

          if (cerberus) {
            format_punct<CTy> const& fmt(get_facet<format_punct<CTy>>(os));

            if (fmt.formatted) {
              os << fmt.delim_left;

              for (auto const& e : a) {
                os << fmt.indent << e << fmt.separator;
              }
      
              if (!b) {
                os << remove(1);
              }
        
              os << fmt.delim_right;
            } else {
              for (auto const& e : a) {
                os << e << fmt.space;
              }
            }
          }
          
          return os;
        }
        
      } // namespace detail {
      
      template <typename CTy, typename CTr,
                typename T, std::size_t N>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::array<T,N> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::deque<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::forward_list<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
#if !defined(_MSC_VER) || (defined(_MSC_VER) && (_MSC_VER > 1700))
      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::initializer_list<T> a)
      {
        return detail::print_container_on(os, a, (0 < a.size()));
      }
#endif
      
      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::list<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::map<K,T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::multimap<K,T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::multiset<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }

      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::set<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::unordered_map<K,T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename K, typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::unordered_multimap<K,T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }
      
      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::unordered_multiset<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }

      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::unordered_set<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }

      template <typename CTy, typename CTr,
                typename T>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, std::vector<T> const& a)
      {
        return detail::print_container_on(os, a, a.empty());
      }

      inline std::ostream&
      operator<<(std::ostream& os, std::wstring const& a)
      {
        return os << support::wstring_to_string(a);
      }
      
    } // namespace ostream {

  } // namespace support {
  
} // namespace hugh {

namespace std {

  template <typename CTy, typename CTr,
            typename T, typename D>
  inline basic_ostream<CTy,CTr>&
  operator<<(basic_ostream<CTy,CTr>& os, unique_ptr<T,D> const& a)
  {
    typename basic_ostream<CTy,CTr>::sentry const cerberus(os);
    
    if (cerberus) {
      os << a.get();
    }
      
    return os;
  }
  
} // namespace std {

#endif // #if !defined(HUGH_SUPPORT_IO_OPERATORS_INL)
