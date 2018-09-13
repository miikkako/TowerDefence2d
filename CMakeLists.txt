# @TODO coverage build

cmake_minimum_required(VERSION 3.2)

# Enable debug symbols by default, must be done before project() statement
set(IS_DEBUG_ON 0)
if(NOT CMAKE_BUILD_TYPE OR CMAKE_BUILD_TYPE MATCHES Debug)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose the type of build (Debug or Release)" FORCE)
    set(IS_DEBUG_ON 1)
    message(STATUS "Using debug build")
elseif(CMAKE_BUILD_TYPE MATCHES Release)
    message(STATUS "Using release build")
else()
    message(FATAL_ERROR "CMAKE_BUILD_TYPE not recognized. Use '-DCMAKE_BUILD_TYPE=[Release|Debug]'. Default is Debug.")
endif()
if(SFML_STATIC_LIBRARIES)
    message(STATUS "Linking SFML statically")
else()
    message(STATUS "Linking SFML dynamically")
endif()

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# This is how SFML could be automatically built as a subdirectory (Then find_package(SFML) must not be invoked)
#set(SFML_INCLUDE_DIR "extlibs/SFML/include")
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/extlibs/SFML ${PROJECT_BINARY_DIR})
#set(SFML_LIBRARIES "sfml-system sfml-network sfml-graphics sfml-window sfml-audio")

# Set project name, language, and version info
project(2dGame LANGUAGES CXX VERSION 0.2)

# Set version information in a config.h file
set(ADDITIONAL_INCLUDES ${PROJECT_BINARY_DIR}/additional_include)
file(MAKE_DIRECTORY ${ADDITIONAL_INCLUDES})
configure_file(
        "${PROJECT_SOURCE_DIR}/config.h.in"
        "${ADDITIONAL_INCLUDES}/config.hpp"
)

# Set extra compiling flags
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -stdlib=libc++ -Wall -Wextra -pedantic")

# Set the path to findSFML.cmake-file, which is needed by find_package(). Then Find SFML and its modules
if(NOT CMAKE_MODULE_PATH) # Can be manually set when invoking cmake
    set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake_modules")
endif()
find_package(SFML 2.4 COMPONENTS system window graphics network audio REQUIRED)
#message(STATUS "SFML_LIBRARIES:${SFML_LIBRARIES}, SFML_INCLUDE_DIR:${SFML_INCLUDE_DIR}")

# Set source files
#file(GLOB SOURCES "engine/src/*.cpp" "src/*.cpp")
set(SOURCES
        ${PROJECT_SOURCE_DIR}/engine/src/gameobject.cpp
        ${PROJECT_SOURCE_DIR}/engine/src/scene.cpp
        ${PROJECT_SOURCE_DIR}/engine/src/scenehandler.cpp
        ${PROJECT_SOURCE_DIR}/engine/src/soundhandler.cpp
        ${PROJECT_SOURCE_DIR}/engine/src/usereventhandler.cpp
        ${PROJECT_SOURCE_DIR}/src/main.cpp
        ${PROJECT_SOURCE_DIR}/src/tdusereventhandler.cpp
        ${PROJECT_SOURCE_DIR}/src/towerdefencescene.cpp
        ${PROJECT_SOURCE_DIR}/src/map.cpp
        ${PROJECT_SOURCE_DIR}/src/enemy.cpp)

# Main program
set(EXECUTABLE_NAME ${PROJECT_NAME})
add_executable(${EXECUTABLE_NAME} ${SOURCES})

# Bring the project and SFML header files into the project
include_directories(${ADDITIONAL_INCLUDES}
                    ${PROJECT_SOURCE_DIR}/src/include
                    ${PROJECT_SOURCE_DIR}/engine/src/include
                    ${SFML_INCLUDE_DIR})

target_link_libraries(${EXECUTABLE_NAME} ${SFML_LIBRARIES})
if(SFML_STATIC_LIBRARIES)
    target_link_libraries(${EXECUTABLE_NAME} ${SFML_DEPENDENCIES})
endif()
