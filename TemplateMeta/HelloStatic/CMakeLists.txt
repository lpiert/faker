# CMAKE VERSION
cmake_minimum_required (VERSION 3.8)

# PROJECT NAME
project(hello_static)

# CREATE STATIC LIBRARY
add_library(hello_static STATIC
	src/helloStatic.cpp
)

target_include_directories(hello_static
    PUBLIC 
        ./include
)

# INSTALL include
install(DIRECTORY ./include/ 
	DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/include
)

# INSTALL library
install(TARGETS hello_static  
	DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/lib
)



#******************************************************
# using library create exe
#******************************************************
# CREATE TARGET BY LIBRARY
add_executable(hello_static_demo
	src/main.cpp
)

add_custom_command(TARGET ${PROJECT_NAME} 
                    POST_BUILD 
                    COMMAND ${CMAKE_COMMAND} -E echo compile finish
                    VERBATIM
)

# LINCK LIBRARY
target_link_libraries(hello_static_demo
	PRIVATE
		hello_static
)

# INSTALL TARGET
install(TARGETS hello_static_demo 
	RUNTIME DESTINATION ${CMAKE_SOURCE_DIR}/BuildDir/${PROJECT_NAME}/bin
)
