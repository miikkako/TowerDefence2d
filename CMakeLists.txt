cmake_minimum_required(VERSION 3.2)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# @TODO: add versioning: project minor and major that #include to the program
set(EXECUTABLE_NAME td)
project(2dGame CXX)

# Set compiling flags, use debug build (-g) every time for now
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -Wall -Wextra -pedantic")

# Set source files, could also be done with "set(SOURCES file.cpp...)"
file(GLOB SOURCES "engine/src/*.cpp" "src/*.cpp")

# Main program
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Set the path to findSFML.cmake-file, which is needed by find_package()
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")

# Find SFML and its modules. Require version 2.3
find_package(SFML 2.3 REQUIRED system window graphics network audio)

if(SFML_FOUND)
    # Bring the project and SFML header files into the project
    include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src/include\ 
                        ${CMAKE_CURRENT_SOURCE_DIR}/engine/src/include\ 
                        ${SFML_INCLUDE_DIR})
    # Link SFML
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
else()
    message(SEND_ERROR "SFML not found")
endif()
