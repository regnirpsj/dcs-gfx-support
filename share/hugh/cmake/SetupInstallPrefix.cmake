# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

if(NOT CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/install")

  if(DEFINED ENV{HUGH_INSTALL_PREFIX})
    set(CMAKE_INSTALL_PREFIX $ENV{HUGH_INSTALL_PREFIX})
  endif()
endif()

if(VERBOSE)
  message(STATUS "CMAKE_INSTALL_PREFIX set to '" ${CMAKE_INSTALL_PREFIX} "'")
endif()
