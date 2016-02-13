cmake_minimum_required (VERSION 3.3.2)
set(CMAKE_SYSTEM_VERSION 8.1)

#Find packages
find_package(Doxygen)

#Project settings
option(BUILD_DOCUMENTATION "Create and install the HTML based API documentation (requires Doxygen)" ${DOXYGEN_FOUND})

if(BUILD_DOCUMENTATION)
    if(NOT DOXYGEN_FOUND)
        message(FATAL_ERROR "Doxygen is needed to build the documentation.")
    endif()
	
    set(doxyfile_in ${CMAKE_CURRENT_SOURCE_DIR}/Doxyfile.in)
    set(doxyfile ${CMAKE_CURRENT_BINARY_DIR}/Doxyfile)
    
	configure_file(${doxyfile_in} ${doxyfile} @ONLY)
	add_custom_target(doc ALL ${DOXYGEN_EXECUTABLE} ${doxyfile}
		WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
		COMMENT "Generating API documentation.." VERBATIM)

endif()

