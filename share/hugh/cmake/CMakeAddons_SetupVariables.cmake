# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

# Boost
set(BOOST_MINIMUM_VERSION "1.55.0")

if(CMAKE_HOST_WIN32)
  foreach(version "1.59.0" "1.57.0" "1.55.0")
    set(BOOST_ROOT "C:/Tools/boost/${version}")
    if(EXISTS "${BOOST_ROOT}" AND IS_DIRECTORY "${BOOST_ROOT}")
      break()
    endif()
  endforeach()
  if(NOT EXISTS "${BOOST_ROOT}" OR NOT IS_DIRECTORY "${BOOST_ROOT}")
    message(FATAL "unable to find a valid BOOST root directory!")
  endif()
  if(WIN64)
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib64-msvc-${CMAKE_VS_PLATFORM_TOOLSET}")
  else()
    set(BOOST_LIBRARYDIR "${BOOST_ROOT}/lib32-msvc-${CMAKE_VS_PLATFORM_TOOLSET}")
  endif()
  if(NOT EXISTS "${BOOST_LIBRARYDIR}" OR NOT IS_DIRECTORY "${BOOST_LIBRARYDIR}")
    cma_print_variable(BOOST_LIBRARYDIR)
    unset(BOOST_LIBRARYDIR)
  endif()

  set(Boost_DEBUG               FALSE)
  set(Boost_USE_STATIC_LIBS     ON)
  set(Boost_USE_MULTITHREAD     ON)

  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
  # add_definitions("-DBOOST_ALL_DYN_LINK")
  
  find_package(Boost ${BOOST_MINIMUM_VERSION})
  if(Boost_FOUND)
    if(EXISTS "${Boost_LIBRARY_DIR}" AND IS_DIRECTORY "${Boost_LIBRARY_DIR}")
      set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} /LIBPATH:${Boost_LIBRARY_DIR}")
      set(CMAKE_MODULE_LINKER_FLAGS "${CMAKE_MODULE_LINKER_FLAGS} /LIBPATH:${Boost_LIBRARY_DIR}")
      set(CMAKE_EXE_LINKER_FLAGS    "${CMAKE_EXE_LINKER_FLAGS} /LIBPATH:${Boost_LIBRARY_DIR}")
    endif()
  endif()
elseif(CMAKE_HOST_UNIX)
  set(Boost_DEBUG               FALSE)
  # set(Boost_USE_STATIC_LIBS     ON)
  set(Boost_USE_MULTITHREAD     ON)

  add_definitions(${Boost_LIB_DIAGNOSTIC_DEFINITIONS})
  add_definitions("-DBOOST_ALL_DYN_LINK")
endif()

# GLM
add_definitions("-DGLM_FORCE_EXPLICIT_CTOR")
add_definitions("-DGLM_FORCE_CXX11")
add_definitions("-DGLM_FORCE_INLINE")
add_definitions("-DGLM_FORCE_RADIANS")  
# add_definitions("-DGLM_FORCE_SIZE_FUNC")
# add_definitions("-DGLM_FORCE_SIZE_T_LENGTH")
# add_definitions("-DGLM_MESSAGES")
add_definitions("-DGLM_META_PROG_HELPERS")
add_definitions("-DGLM_PRECISION_HIGHP_FLOAT")
add_definitions("-DGLM_PRECISION_HIGHP_INT")
add_definitions("-DGLM_SWIZZLE")
