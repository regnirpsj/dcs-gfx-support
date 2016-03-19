# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

if(${PROJECT_NAME}_BLD_UTEST)
  if(VERBOSE)
    message(STATUS "Enabling unit-test building")
  endif()

  if(${PROJECT_NAME}_RUN_CTEST)
    if(VERBOSE)
      message(STATUS "Enabling CTest unit-test execution")
    endif()
    enable_testing()
    set(FNAME "CTestConfig.cmake.in")
    if(NOT EXISTS "cmake/${FNAME}")
      set(FNAME "${CMAKE_CURRENT_LIST_DIR}/${FNAME}")
    else()
      set(FNAME "cmake/${FNAME}")
    endif()
    configure_file(${FNAME} ${PROJECT_BINARY_DIR}/CTestConfig.cmake @ONLY)
  elseif(${PROJECT_NAME}_RUN_UTEST)
    if(VERBOSE)
      message(STATUS "Enabling unit-test execution")
    endif()
  else()
    if(VERBOSE)
      message(STATUS "Disabling unit-test execution")
    endif()
  endif()
  
  add_custom_target(check)
  set_property(TARGET check PROPERTY FOLDER "Tests")
  add_dependencies(check test_all)
else()
  if(VERBOSE)
    message(STATUS "Disabling unit-test building")
  endif()
endif()
