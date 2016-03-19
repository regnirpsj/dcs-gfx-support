# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

# .rst:
# cma_setup_test(PREFIX SOURCES .. [DEPENDENCIES ..] [ADDITIONAL ..] [WINRT] [DEBUG])
#   PREFIX       -
#   SOURCES      -
#   DEPENDENCIES -
#   ADDITIONAL   -
#   WINRT        -
#   DEBUG        -
#
function(cma_setup_test TST_PREFIX)
  include(CMakeParseArguments)
  include(functions/cma_utilities)
  
  set(OARGS WINRT DEBUG)
  set(SARGS)
  set(MARGS SOURCES ADDITIONAL DEPENDENCIES)
  cmake_parse_arguments(TST "${OARGS}" "${SARGS}" "${MARGS}" ${ARGN})

  if(NOT TST_SOURCES)
    message(SEND_ERROR "Error: cma_setup_test() called without any source files")
    return()
  endif()

  if(TST_DEBUG OR VERBOSE)
    message(STATUS "cma_setup_test(${TST_PREFIX};${ARGN}) variable setup:\n"
      "   TST_PREFIX       = ${TST_PREFIX}\n"
      "   TST_SOURCES      = ${TST_SOURCES}\n"
      "   TST_ADDITIONAL   = ${TST_ADDITIONAL}\n"
      "   TST_DEPENDENCIES = ${TST_DEPENDENCIES}")
  endif()

  set(TST_EXES)
  set(TST_TESTS)
  
  foreach(APP ${TST_SOURCES})
    get_filename_component(EXE "test_${TST_PREFIX}_${APP}" NAME_WE)
    add_executable(${EXE} EXCLUDE_FROM_ALL ${APP} ${TST_ADDITIONAL})

    if(TST_WINRT)
      cma_add_winrt_props(${EXE})
    endif()

    #set_property(TARGET ${EXE} PROPERTY FOLDER "Tests/${TST_PREFIX}")
    
    target_link_libraries(${EXE} ${TST_DEPENDENCIES})
    add_test(${EXE} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${EXE})
    list(APPEND TST_EXES ${EXE})
    
    get_filename_component(TEST "unit_test_${TST_PREFIX}_${APP}" NAME_WE)
    add_custom_target(${TEST} COMMAND ${EXE} DEPENDS ${EXE} SOURCES ${APP} ${TST_ADDITIONAL})
    list(APPEND TST_TESTS ${TEST})

    cma_add_target_to_list(${EXE} CMAKE_TARGET_LIST)
  endforeach()
  
  if(TST_DEBUG OR VERBOSE)
    message(STATUS "cma_setup_test(${TST_PREFIX};${ARGN}) target setup:\n"
      "   TST_EXES         = ${TST_EXES}\n"
      "   TST_TESTS        = ${TST_TESTS}")
  endif()
  
  if(${PROJECT_NAME}_BLD_UTEST)
    if(NOT TARGET test_libs)
      add_custom_target(test_libs)
      #set_property(TARGET test_libs PROPERTY FOLDER "Tests")
    endif()

    if(NOT TARGET test_all)
      add_custom_target(test_all)
      #set_property(TARGET test_all PROPERTY FOLDER "Tests")
      add_dependencies(test_all test_libs)
    endif()

    if(${PROJECT_NAME}_RUN_CTEST)
      if(TARGET test_${TST_PREFIX})
	add_dependencies(test_${TST_PREFIX} ${TST_EXES})
      else()
	add_custom_target(test_${TST_PREFIX} COMMAND ${CMAKE_CTEST_COMMAND} DEPENDS ${TST_EXES})
      endif()
    elseif(${PROJECT_NAME}_RUN_UTEST)
      if(TARGET test_${TST_PREFIX})
	add_dependencies(test_${TST_PREFIX} ${TST_TESTS})
      else()
	add_custom_target(test_${TST_PREFIX} DEPENDS ${TST_TESTS})
      endif()
    else()
      if(TARGET test_${TST_PREFIX})
	add_dependencies(test_${TST_PREFIX} ${TST_EXES})
      else()
	add_custom_target(test_${TST_PREFIX} DEPENDS ${TST_EXES})
      endif()
    endif()

    #set_property(TARGET test_${TST_PREFIX} PROPERTY FOLDER "Tests/${TST_PREFIX}")
    add_dependencies(test_libs test_${TST_PREFIX})
  endif()
endfunction()
