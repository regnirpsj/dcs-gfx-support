// -*- Mode:C++ -*-

/**************************************************************************************************/
/*                                                                                                */
/* Copyright (C) 2016 University of Hull                                                          */
/*                                                                                                */
/**************************************************************************************************/
/*                                                                                                */
/*  module     :  hugh/support/signal_handler.hpp                                                 */
/*  project    :                                                                                  */
/*  description:                                                                                  */
/*                                                                                                */
/**************************************************************************************************/

#if !defined(HUGH_SUPPORT_SIGNAL_HANDLER_HPP)

#define HUGH_SUPPORT_SIGNAL_HANDLER_HPP

// includes, system


#include <boost/utility/mutexed_singleton.hpp> // boost::singleton<>
#include <functional>                          // std::function<>

// includes, project

#include <hugh/support/config.hpp>
#include <hugh/support/export.h>

namespace hugh {
  
  namespace support {
  
    // types, exported (class, enum, struct, union, typedef)

    class HUGH_SUPPORT_EXPORT signal_handler : public boost::mutexed_singleton<signal_handler> {

      BOOST_SINGLETON_PLACEMENT_DECLARATION;

    public:

      using handler_function_type = std::function<void (signed)>;

      ~signal_handler();

      handler_function_type handler(signed                /* signo   */);
      handler_function_type handler(signed                /* signo   */,
                                    handler_function_type /* handler */);

    private:

      template<class T, int DS, typename ST> friend class boost::mutexed_singleton;

      explicit signal_handler(boost::restricted);

    };
  
    // variables, exported (extern)

    // functions, inlined (inline)
  
    // functions, exported (extern)

    HUGH_SUPPORT_EXPORT std::string signal_name(signed);
  
  } // namespace support {

} // namespace hugh {

#endif // #if !defined(HUGH_SUPPORT_SIGNAL_HANDLER_HPP)
