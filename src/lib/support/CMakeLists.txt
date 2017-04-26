# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016-2017 University of Hull                                                       #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(PkgConfig)
pkg_check_modules(LIBPCI libpci)

if(LIBPCI_FOUND)
  include_directories(SYSTEM ${LIBPCI_INCLUDE_DIRS})
endif()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED
             COMPONENTS chrono date_time filesystem program_options system thread)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})

set(SRC)
LIST(APPEND SRC chrono.cpp)
LIST(APPEND SRC chrono_io.cpp)
LIST(APPEND SRC hasher.cpp)

LIST(APPEND SRC io/format_saver.cpp)
LIST(APPEND SRC io/manipulators.cpp)
LIST(APPEND SRC io/operators.cpp)
LIST(APPEND SRC io/position_saver.cpp)
LIST(APPEND SRC io/printer.cpp)
LIST(APPEND SRC io/scoped_redirect.cpp)

if(LIBPCI_FOUND)
  LIST(APPEND SRC pci_ids.cpp)
endif()
LIST(APPEND SRC printable.cpp)
LIST(APPEND SRC refcounted.cpp)
if(CMAKE_HOST_WIN32)
  LIST(APPEND SRC signal_handler_win32.cpp)
elseif(CMAKE_HOST_UNIX)
  LIST(APPEND SRC signal_handler_posix.cpp)
endif()
LIST(APPEND SRC string.cpp)
LIST(APPEND SRC thread.cpp)
LIST(APPEND SRC trace.cpp)
LIST(APPEND SRC type_info.cpp)

#add_definitions(-DHUGH_ALL_TRACE)

set(LIBS)
list(APPEND LIBS ${Boost_LIBRARIES})
if(LIBPCI_FOUND)
  list(APPEND LIBS ${LIBPCI_LIBRARIES})
endif()
if(CMAKE_HOST_UNIX)
  # 'pthread_sigmask' used in signal_handler_posix.cpp
  list(APPEND LIBS pthread)
endif()

set(LIB hugh_support)

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} INCDIR hugh/support)
cma_setup_export(${LIB})

add_subdirectory(test EXCLUDE_FROM_ALL)
