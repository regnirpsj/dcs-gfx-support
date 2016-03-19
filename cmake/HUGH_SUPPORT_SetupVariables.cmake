# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

if(VERBOSE)
  message(STATUS "Loading ${PROJECT_NAME} variables")
endif()

include(CMakeAddons_SetupVariables)

# GL[I|M]
set(GLI_MINIMUM_VERSION "0.8.0")
set(GLM_MINIMUM_VERSION "0.9.7")
if(CMAKE_HOST_WIN32)
  set(GLI_ROOT_DIR "C:/Tools/gli/gli-git")
  set(GLM_ROOT_DIR "C:/Tools/glm/glm-git")
elseif(CMAKE_HOST_UNIX)
  set(GLI_ROOT_DIR "~/Projects/others/gli-git")
  set(GLM_ROOT_DIR "~/Projects/others/glm-regnirpsj-git")
endif()
if(DEFINED ENV{GLI_ROOT_DIR})
  set(GLI_ROOT_DIR $ENV{GLI_ROOT_DIR})
endif()
if(DEFINED ENV{GLM_ROOT_DIR})
  set(GLM_ROOT_DIR $ENV{GLM_ROOT_DIR})
endif()

if(HUGH_TRACE_ALL)
  if(VERBOSE)
    message(STATUS "Enabling run-time tracing for complete project!")
  endif()
  add_definitions("-DHUGH_ALL_TRACE")
endif()
