# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

find_package(Boost ${BOOST_MINIMUM_VERSION} REQUIRED)
find_package(GLM   ${GLM_MINIMUM_VERSION}   REQUIRED)

include_directories(SYSTEM ${Boost_INCLUDE_DIR})
include_directories(SYSTEM ${GLM_INCLUDE_DIR})

set(SRC)
list(APPEND SRC "gtx/limits.cpp")
list(APPEND SRC "gtx/morton.cpp")
list(APPEND SRC "gtx/utilities.cpp")

set(LIBS)
list(APPEND LIBS hugh_support)

set(LIB "hugh_glm")

cma_setup_library(${LIB} SOURCES ${SRC} DEPENDENCIES ${LIBS} INCDIR "glm")
cma_setup_export(${LIB} PATH "glm")

add_subdirectory(test EXCLUDE_FROM_ALL)
