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

  set(LCOV_ARGS $ENV{LCOV_ARGS})

  if(TRUE OR VERBOSE)
    message(STATUS "Found GCOV front-end: ${LCOV} ${LCOV_ARGS}")
  endif()

  add_custom_command(TARGET coverage_zero POST_BUILD
    COMMAND ${LCOV} --zerocounters --directory .
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

  add_custom_command(TARGET coverage_collect POST_BUILD
    COMMAND ${LCOV} ${LCOV_ARGS} --output-file coverage.info --directory . --capture
    COMMAND ${LCOV} ${LCOV_ARGS} --output-file coverage.info --extract coverage.info '${CMAKE_SOURCE_DIR}/*'
    COMMAND ${LCOV} ${LCOV_ARGS} --output-file coverage.info --remove coverage.info ${${PROJECT_NAME}_COVERAGE_EXCLUDE}
    COMMAND ${LCOV} ${LCOV_ARGS} --list coverage.info
    BYPRODUCTS   coverage.info
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
else()
  add_custom_command(TARGET coverage_zero POST_BUILD
    COMMAND echo "coverage_zero: coverage processing disabled, nothing to do"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
  add_custom_command(TARGET coverage_collect POST_BUILD
    COMMAND echo "coverage_collect: coverage processing disabled, nothing to do"
    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})
endif()
