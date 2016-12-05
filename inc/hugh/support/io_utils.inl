// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  support/io_utils.inl                                                            */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_IO_UTILS_INL)

#define HUGH_SUPPORT_IO_UTILS_INL

// includes, system

#include <boost/io/ios_state.hpp> // boost::io::ios_all_saver
#include <istream>                // std::basic_istream<>
#include <ostream>                // std::basic_ostream<>

// includes, project

#include <hugh/support/string.hpp>
#include <hugh/support/type_info.hpp>

namespace hugh {
  
  namespace support {

    namespace istream {
    
      // functions, inlined (inline)

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_position_saver<CTy,CTr>::basic_position_saver(std::basic_istream<CTy,CTr>& s)
        : boost::noncopyable(),
          s_                (s),
          p_                (s_.tellg())
      {}

      template <typename CTy, typename CTr>
      inline
      basic_position_saver<CTy,CTr>::~basic_position_saver()
      {
        restore();
      }

      template <typename CTy, typename CTr>
      inline void
      basic_position_saver<CTy,CTr>::restore()
      {
        s_.seekg(p_);
      }
    
    } // namespace istream {

    namespace ostream {
    
      // functions, inlined (inline)

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_position_saver<CTy,CTr>::basic_position_saver(std::basic_ostream<CTy,CTr>& s)
        : boost::noncopyable(),
          s_                (s),
          p_                (s_.tellp())
      {}
  
      template <typename CTy, typename CTr>
      inline
      basic_position_saver<CTy,CTr>::~basic_position_saver()
      {
        restore();
      }

      template <typename CTy, typename CTr>
      inline void
      basic_position_saver<CTy,CTr>::restore()
      {
        s_.seekp(p_);
      }
    
      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_scoped_redirect<CTy,CTr>::basic_scoped_redirect(std::basic_ostream<CTy,CTr>& a,
                                                            std::basic_ostream<CTy,CTr>& b)
        : boost::noncopyable(),
          list_             (1, std::make_pair(&a, a.rdbuf(b.rdbuf())))
      {}

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_scoped_redirect<CTy,CTr>::basic_scoped_redirect(ostream_initializer_list a,
                                                            std::basic_ostream<CTy,CTr>& b)
        : boost::noncopyable(),
          list_             ()
      {
        for (auto s : a) {
          if (nullptr != s) {
            list_.push_back(std::make_pair(s, s->rdbuf(b.rdbuf())));
          }
        }
      }
      
      template <typename CTy, typename CTr>
      inline
      basic_scoped_redirect<CTy,CTr>::~basic_scoped_redirect()
      {
        for (auto& p : list_) {
          p.first->rdbuf(p.second);
        }
      }
      
      template <typename CTy>
      inline /* explicit */
      format_punct<CTy>::format_punct(size_t a)
        : std::locale::facet(a),
          formatted         (true),
          delim_left        ('('),
          delim_right       (')'),
          separator         (','),
          indent            (),
          space             (' ')
      {}
    
      template <typename CTy>
      inline /* explicit */
      format_punct<CTy>::format_punct(format_punct const& a)
        : std::locale::facet(0),
          formatted         (a.formatted),
          delim_left        (a.delim_left),
          delim_right       (a.delim_right),
          separator         (a.separator),
          indent            (a.indent),
          space             (a.space)
      {}

      template <typename CTy> std::locale::id format_punct<CTy>::id;

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_format_saver<CTy,CTr>::basic_format_saver(std::basic_ios<CTy,CTr>& a)
        : boost::noncopyable(),
          ias_              (a)
      {   
        a.imbue(std::locale(a.getloc(), new format_punct<CTy>(get_facet<format_punct<CTy>>(a))));
      }
      
      template <typename CTy>
      inline /* explicit */
      delimeter<CTy>::delimeter(std::array<CTy, 3> const& a)
        : value(a)
      {}
    
      template <typename CTy>
      inline /* explicit */
      delimeter<CTy>::delimeter(CTy a, CTy b, CTy c)
        : value({ a, b, c, })
      {}

      template <typename CTy>
      inline /* explicit */
      indent<CTy>::indent(std::basic_string<CTy> const& a)
        : value(a)
      {}
    
      template <typename CTy>
      inline /* explicit */
      indent<CTy>::indent(unsigned a, CTy b)
        : value(a, b)
      {}

      inline /* explicit */
      remove::remove(unsigned a)
        : value(a)
      {}

      template <typename T, typename R>
      inline /* explicit */
      enumeration<T,R>::enumeration(enum_type a, enum_range const& b)
        : value(a), range(b)
      {}

      template <typename T, typename R>
      inline /* explicit */
      bitmask<T,R>::bitmask(bitmask_type a, bitmask_range const& b)
        : value(a), range(b)
      {}
      
      template <typename FTy, typename CTy, typename CTr>
      inline FTy const&
      get_facet(std::basic_ios<CTy,CTr>& ios)
      {
        if (!std::has_facet<FTy>(ios.getloc())) {
          ios.imbue(std::locale(ios.getloc(), new FTy));
        } 
      
        return std::use_facet<FTy>(ios.getloc());
      }
    
      template <typename CTy, typename CTr>
      inline std::basic_ios<CTy,CTr>&
      formatted(std::basic_ios<CTy,CTr>& os)
      {
        const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)).formatted = true;
      
        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ios<CTy,CTr>&
      unformatted(std::basic_ios<CTy,CTr>& os)
      {
        const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)).formatted = false;
      
        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, delimeter<CTy> const& a)
      {                                        
        format_punct<CTy>& fmt(const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)));
      
        fmt.delim_left  = a.value[0];
        fmt.delim_right = a.value[1];
        fmt.separator   = a.value[2];

        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, indent<CTy> const& a)
      {                                        
        format_punct<CTy>& fmt(const_cast<format_punct<CTy>&>(get_facet<format_punct<CTy>>(os)));
      
        fmt.indent = a.value;

        return os;
      }

      template <typename CTy, typename CTr>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, remove const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

        if (cerberus) {
          using pos_type = typename std::basic_ostream<CTy,CTr>::pos_type;
          
          if (pos_type(-1) == os.tellp()) {
            switch (a.value) {
            case 0:  /* do nothing */                             break;
            case 1:  os << '\b';                                  break;
            default: os << std::basic_string<CTy>(a.value, '\b'); break;
            }
          } else {
            pos_type const current(os.tellp());
      
            os.seekp(std::min(std::max(pos_type(0),
                                       pos_type(current - pos_type(a.value))),
                              current),
                     std::ios_base::beg);
          }
        }
        
        return os;
      }

      template <typename T, typename R>
      inline enumeration<T,R>
      enumerate(T a, R const& b)
      {
        return enumeration<T,R>(a, b);
      }

      template <typename T, typename R, typename CTy, typename CTr = std::char_traits<CTy>>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, enumeration<T,R> const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

        if (cerberus) {
          bool found(false);

          for (auto const& e : a.range) {
            if (e.first == a.value) {
              os << e.second;

              found = true;

              break;
            }
          }

          if (!found) {
            os << "INVALID (" << signed(a.value) << ')';
          }
        }
        
        return os;
      }
      
      template <typename T, typename R>
      inline bitmask<T,R>
      flags(T a, R const& b)
      {
        return bitmask<T,R>(a, b);
      }

      template <typename T, typename R, typename CTy, typename CTr = std::char_traits<CTy>>
      inline std::basic_ostream<CTy,CTr>&
      operator<<(std::basic_ostream<CTy,CTr>& os, bitmask<T,R> const& a)
      {
        typename std::basic_ostream<CTy,CTr>::sentry const cerberus(os);

        if (cerberus) {
          using pos_type = typename std::basic_ostream<CTy,CTr>::pos_type;

          pos_type const pos_old(os.tellp());
          
          for (auto f : a.range) {
            if (a.value & f.first) {
              os << f.second << '|';
            }
          }
          
          os << remove(1);

          pos_type const pos_new(os.tellp());
          
          if ((pos_type(-1) != pos_old) && (0 == (pos_new - pos_old))) {
            os << "NONE";
          }
        }
        
        return os;
      }

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
  
    namespace iostream {
    
      // functions, inlined (inline)

      template <typename CTy, typename CTr>
      inline /* explicit */
      basic_position_saver<CTy,CTr>::basic_position_saver(std::basic_iostream<CTy,CTr>& s)
        : istream::basic_position_saver<CTy,CTr>(s),
          ostream::basic_position_saver<CTy,CTr>(s)
      {}

      template <typename CTy, typename CTr>
      inline
      basic_position_saver<CTy,CTr>::~basic_position_saver()
      {
        restore();
      }

      template <typename CTy, typename CTr>
      inline void
      basic_position_saver<CTy,CTr>::restore()
      {
        ostream::basic_position_saver<CTy,CTr>::restore();
        istream::basic_position_saver<CTy,CTr>::restore();
      }
    
    } // namespace iostream {
    
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

#endif // #if !defined(HUGH_SUPPORT_IO_UTILS_INL)
