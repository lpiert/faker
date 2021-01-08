# Set the minimum version of CMake that can be used
# To find the cmake version run
# $ cmake --version
#
cmake_minimum_required (VERSION 3.8)

# Set the project name
project(TemplateMeta)

# Create a sources variable with a link to all cpp files to compile
set(MAIN
	main/main.cpp
)


# create group
set(TEMPLATEMETA
	template/TemplateMeta.h
	template/TemplateMeta.cpp
)
set(UNIT
	unit/test/test.h
	unit/test/test.cpp
)

source_group(main FILES ${MAIN})
source_group(template FILES ${TEMPLATEMETA})
source_group(unit FILES ${UNIT})
source_group(unit\\test FILES ${UNIT})

# Add an executable with the above sources
add_executable(${PROJECT_NAME} ${MAIN} ${TEMPLATEMETA} ${UNIT})

add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E echo compile finish
                    VERBATIM
)

# Install directories
install(TARGETS ${PROJECT_NAME} 
		RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/bin
		)

# Set the directories that should be included in the build command for this target
# when running g++ these will be included as -I/directory/path/
target_include_directories(${PROJECT_NAME}
	PRIVATE
		./
)

# Config 
install (FILES config/config.json 
		DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/bin/etc
		)
