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

list(APPEND ${PROJECT_NAME}_COVERAGE_EXCLUDE 'inc/boost/*')
list(APPEND ${PROJECT_NAME}_COVERAGE_EXCLUDE 'support/chrono_io.hpp')
list(APPEND ${PROJECT_NAME}_COVERAGE_EXCLUDE 'support/ratio_io.hpp')
