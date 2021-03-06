# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

# 'signal_handler' unit testing not possible with boost::test
set(SRC)
list(APPEND SRC signal_handler.cpp)

set(LIBS)
list(APPEND LIBS ${LIB})

cma_setup_test(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})

# the remainder of 'support::' uses boost::test
find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED COMPONENTS unit_test_framework)

include_directories(SYSTEM ${Boost_INLCUDE_DIR})

set(SRC)
list(APPEND SRC chrono.cpp)
list(APPEND SRC hasher.cpp)
list(APPEND SRC io_format_saver.cpp)
list(APPEND SRC io_manipulators.cpp)
list(APPEND SRC io_operators.cpp)
list(APPEND SRC io_position_saver.cpp)
list(APPEND SRC io_printer.cpp)
list(APPEND SRC io_scoped_redirect.cpp)
LIST(APPEND SRC pci_ids.cpp)
list(APPEND SRC printable.cpp)
list(APPEND SRC refcounted.cpp)
list(APPEND SRC thread.cpp)
list(APPEND SRC trace.cpp)
list(APPEND SRC type_info.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${LIB})
list(APPEND LIBS ${Boost_LIBRARIES})

cma_setup_test(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS})
