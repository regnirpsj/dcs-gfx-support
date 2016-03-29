# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

add_custom_target(coverage_zero)
add_custom_target(coverage_collect)

if(${PROJECT_NAME}_COVERAGE)
  if(NOT LCOV)
    set(LCOV $ENV{LCOV})
    if(NOT LCOV)
      find_program(LCOV lcov DOC "GCOV front-end")
    endif()
    if(NOT LCOV)
      message(SEND_ERROR "Error: unable to find GCOV front-end (lcov)")
    endif()
  endif()
  
  if(LCOV)
    set(LCOV_ARGS $ENV{LCOV_ARGS})
    
    if(NOT VERBOSE)
      list(APPEND LCOV_ARGS "--quiet")
    endif()
    
    if(VERBOSE)
      message(STATUS "Found GCOV front-end: ${LCOV} ${LCOV_ARGS}")
    endif()
    
    if(FALSE)
      cma_print_variable(LCOV_ARGS)
      cma_print_variable(${PROJECT_NAME}_COVERAGE_EXCLUDE)
      cma_print_variable(${PROJECT_NAME}_COVERAGE_INCLUDE)
    endif()
    
    # see [https://cmake.org/pipermail/cmake/2005-October/007343.html]
    separate_arguments(LCOV_ARGS)
    separate_arguments(${PROJECT_NAME}_COVERAGE_EXCLUDE)
    separate_arguments(${PROJECT_NAME}_COVERAGE_INCLUDE)
    
    if(FALSE)
      cma_print_variable(LCOV_ARGS)
      cma_print_variable(${PROJECT_NAME}_COVERAGE_EXCLUDE)
      cma_print_variable(${PROJECT_NAME}_COVERAGE_INCLUDE)
    endif()
    
    add_custom_command(TARGET coverage_zero POST_BUILD
      COMMAND ${LCOV} ${LCOV_ARGS} --zerocounters --directory .
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
    
    add_custom_command(TARGET coverage_collect POST_BUILD
      COMMAND ${LCOV} ${LCOV_ARGS} --output-file coverage.info --directory . --capture
      COMMAND ${LCOV} ${LCOV_ARGS} --output-file coverage.info --extract coverage.info ${${PROJECT_NAME}_COVERAGE_INCLUDE}
      COMMAND ${LCOV} ${LCOV_ARGS} --output-file coverage.info --remove coverage.info ${${PROJECT_NAME}_COVERAGE_EXCLUDE}
      COMMAND ${LCOV} ${LCOV_ARGS} --list coverage.info
      BYPRODUCTS   coverage.info
      WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  endif()
endif()

if(NOT ${PROJECT_NAME}_COVERAGE OR NOT LCOV)
  if(NOT LCOV)
    message(STATUS "Using dummy coverage commands")
  endif()
  add_custom_command(TARGET coverage_zero POST_BUILD
    COMMAND echo "coverage_zero: coverage processing disabled, nothing to do"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  add_custom_command(TARGET coverage_collect POST_BUILD
    COMMAND echo "coverage_collect: coverage processing disabled, nothing to do"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
