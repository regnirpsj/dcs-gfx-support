# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

install(DIRECTORY ${CMAKE_SOURCE_DIR}/inc/boost
        DESTINATION ${${PROJECT_NAME}_HEADER_DIRECTORY}
	COMPONENT   ${${PROJECT_NAME}_HDR_COMPONENT_NAME}
        PATTERN "*~" EXCLUDE)

add_subdirectory(test EXCLUDE_FROM_ALL)
