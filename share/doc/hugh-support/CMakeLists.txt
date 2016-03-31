# -*- Mode:cmake -*-

####################################################################################################
#                                                                                                  #
# Copyright (C) 2016 University of Hull                                                            #
#                                                                                                  #
####################################################################################################

cma_print_current_directory()

if(${PROJECT_NAME}_DOC_DEV OR ${PROJECT_NAME}_DOC_USR)
  find_package(Doxygen REQUIRED)

  string(TOLOWER ${CMAKE_PROJECT_NAME} DOC_INSTALL_DIR)
endif()

if(${PROJECT_NAME}_DOC_DEV)
  if(VERBOSE)
    message(STATUS "Generation of developer documentation enabled")
  endif()
  configure_file(Doxyfile.dev.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.dev @ONLY IMMEDIATE)
  add_custom_target(devdoc
                    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.dev
		    SOURCES ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.dev)

  # build before install
  install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" --build . --target devdoc)")

  install(DIRECTORY   ${CMAKE_CURRENT_BINARY_DIR}/dev
          DESTINATION ${${PROJECT_NAME}_DOC_DIRECTORY}/${DOC_INSTALL_DIR}
	  COMPONENT   ${${PROJECT_NAME}_DOC_COMPONENT_NAME})
  install(FILES       ${CMAKE_CURRENT_BINARY_DIR}/devdoc.tag.xml
          DESTINATION ${${PROJECT_NAME}_DOC_DIRECTORY}/${DOC_INSTALL_DIR}
	  COMPONENT   ${${PROJECT_NAME}_DOC_COMPONENT_NAME})
else()
  if(VERBOSE)
    message(STATUS "Generation of developer documentation disabled")
  endif()
endif()

if(${PROJECT_NAME}_DOC_USR)
  if(VERBOSE)
    message(STATUS "Generation of user documentation enabled")
  endif()
  configure_file(Doxyfile.usr.in ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.usr @ONLY IMMEDIATE)
  add_custom_target(usrdoc
                    COMMAND ${DOXYGEN_EXECUTABLE} ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.usr
		    SOURCES ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile.usr)

  # build before install
  install(CODE "execute_process(COMMAND \"${CMAKE_COMMAND}\" --build . --target usrdoc)")

  install(DIRECTORY   ${CMAKE_CURRENT_BINARY_DIR}/usr
          DESTINATION ${${PROJECT_NAME}_DOC_DIRECTORY}/${DOC_INSTALL_DIR}
          COMPONENT   ${${PROJECT_NAME}_DOC_COMPONENT_NAME})
  install(FILES       ${CMAKE_CURRENT_BINARY_DIR}/usrdoc.tag.xml
          DESTINATION ${${PROJECT_NAME}_DOC_DIRECTORY}/${DOC_INSTALL_DIR}
	  COMPONENT   ${${PROJECT_NAME}_DOC_COMPONENT_NAME})
else()
  if(VERBOSE)
    message(STATUS "Generation of user documentation disabled")
  endif()
endif()
