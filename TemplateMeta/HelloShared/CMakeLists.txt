# CMAKE VERSION
cmake_minimum_required (VERSION 3.8)

# PROJECT NAME
project(hello_shared)

# CREATE SHARED LIBRARY
add_library(hello_shared SHARED
	src/helloShared.cpp
)

target_include_directories(hello_shared
    PUBLIC 
        ./include
)

# INSTALL include
install(DIRECTORY ./include/ 
	DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/include
)

# INSTALL library
install(TARGETS hello_shared
	DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/lib
)


#******************************************************
# using library create exe
#******************************************************
# PREDEFINE MACRO
Add_Definitions(-EXPORT_DLL)

# CREATE TARGET BY LIBRARY
add_executable(hello_shared_demo
	src/main.cpp
)

add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E echo compile finish
                    VERBATIM
)

# LINCK LIBRARY
target_link_libraries(hello_shared_demo
	PRIVATE
		hello_shared
)

# INSTALL TARGET
install(TARGETS hello_shared_demo 
	RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/bin
)