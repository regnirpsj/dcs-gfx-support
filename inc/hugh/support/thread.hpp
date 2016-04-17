// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/thread.hpp                                                         */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_THREAD_HPP)

#define HUGH_SUPPORT_THREAD_HPP

// includes, system

#include <boost/asio/io_service.hpp> // boost::asio::io_service[::work]
#include <boost/noncopyable.hpp>     // boost::noncopyable
#include <boost/thread.hpp>          // boost::thread::hardware_concurrency, boost::thread_group
#include <iosfwd>                    // std::ostream (fwd)
#include <memory>                    // std::unique_ptr<>
#include <mutex>                     // std::mutex, std::lock_guard<>
#include <string>                    // std::string
#include <thread>                    // std::this_thread, std::thread

// includes, project

#include <hugh/support/chrono.hpp> // support::clock::duration
#include <hugh/support/config.hpp>

namespace hugh {
  
  namespace support {

    namespace thread {

      // types, exported (class, enum, struct, union, typedef)

      /**
       * \see http://stackoverflow.com/questions/19500404
       * \see http://think-async.com/Asio/Recipes
       */
      class pool : private boost::noncopyable {

      public:

        explicit pool(unsigned /* size */ = boost::thread::hardware_concurrency()+1);
        /*   */ ~pool();

        unsigned size() const;
        
        template <typename F> void submit(F&&);
        
      private:

        using io_service   = boost::asio::io_service;
        using work         = boost::asio::io_service::work;
        using thread_group = boost::thread_group;
        
        io_service            svc_;
        std::unique_ptr<work> wrk_;
        thread_group          grp_;
        
      };
      
      // variables, exported (extern)

      // functions, inlined (inline)
  
      // functions, exported (extern)
      
    } // namespace thread {
    
    // types, exported (class, enum, struct, union, typedef)

    namespace this_thread = std::this_thread;
    
    using recursive_lock       = std::recursive_mutex;
    using recursive_lock_guard = std::lock_guard<recursive_lock>;
    using simple_lock          = std::mutex;
    using simple_lock_guard    = std::lock_guard<simple_lock>;
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    HUGH_SUPPORT_EXPORT
    void dump_thread_stats(std::ostream&          /* output_stream     */,
                           std::string const&     /* context_string    */,
                           clock::duration const& /* timeout/interval  */,
                           clock::duration const& /* actual activity   */,
                           bool                   /* thread_was_paused */,
                           unsigned               /* dump modulo       */ = 10);

  } // namespace support {

} // namespace hugh {

#include <hugh/support/thread.inl>

#endif // #if !defined(HUGH_SUPPORT_THREAD_HPP)
