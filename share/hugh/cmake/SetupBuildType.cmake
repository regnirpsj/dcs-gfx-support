# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

if("x" STREQUAL "x${CMAKE_BUILD_TYPE}")
  set(CMAKE_BUILD_TYPE "RelWithDebInfo")
endif()

if(VERBOSE)
  message(STATUS "CMAKE_BUILD_TYPE set to '" ${CMAKE_BUILD_TYPE} "'")
endif()
