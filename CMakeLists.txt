
cmake_minimum_required(VERSION 3.15)
project(pascal-s)

message(${CMAKE_SYSTEM_NAME} " " ${CMAKE_SYSTEM_PROCESSOR} " " ${CMAKE_SYSTEM_VERSION})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_definitions(-DYY_NO_UNISTD_H)
endif ()

# include files (header, configuration, and others can include)
include_directories(include)
include_directories(vendor)

# vendor files (external libraries)
add_subdirectory(vendor)

# lib files (internal libraries)
add_subdirectory(lib)

# source files (implementations)
add_subdirectory(src)
