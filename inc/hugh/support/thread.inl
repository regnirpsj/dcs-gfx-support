// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/thread.inl                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_THREAD_INL)

#define HUGH_SUPPORT_THREAD_INL

// includes, system

//#include <>

// includes, project

//#include <>

#define HUGH_USE_TRACE
#undef HUGH_USE_TRACE
#include <hugh/support/trace.hpp>
#if defined(HUGH_USE_TRACE) || defined(HUGH_ALL_TRACE)
#  include <typeinfo>
#  include <hugh/support/type_info.hpp>
#endif

namespace hugh {
  
  namespace support {
    
    namespace thread {

      // functions, inlined (inline)

      namespace detail {

        /*
         * \see https://stackoverflow.com/questions/17211263
         */
        template <typename F>
        struct move_wrapper : F {
    
          move_wrapper(F&& f) : F(std::move(f)) {}

          move_wrapper(move_wrapper&&)            =default;
          move_wrapper& operator=(move_wrapper&&) =default;

          move_wrapper(const move_wrapper&);
          move_wrapper& operator=(const move_wrapper&);
    
        };
        
        template <typename T>
        inline auto
        move_handler(T&& t) -> move_wrapper<typename std::decay<T>::type>
        {
          return std::move(t);
        }
        
      } // namespace detail {
      
      template <typename F>
      inline void
      pool::submit(F&& f)
      {
        TRACE("hugh::support::thread::pool::submit<" + demangle(typeid(F)) + ">");
        
        svc_.post(detail::move_handler(f));
      }
      
    } // namespace thread {

  } // namespace support {
  
} // namespace hugh {

#if defined(HUGH_USE_TRACE)
#  undef HUGH_USE_TRACE
#endif

#endif // #if !defined(HUGH_SUPPORT_THREAD_INL)
