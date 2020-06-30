
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

# vendor files (external libraries)
add_subdirectory(vendor)

set(LLVM_DIR C:/work/cpp/llvm-tutorial/lib/build-llvm/lib/cmake/llvm)
find_package(LLVM REQUIRED CONFIG)

message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "llvm include dir ${LLVM_INCLUDE_DIRS}")

add_definitions(${LLVM_DEFINITIONS})
include_directories(${LLVM_INCLUDE_DIRS})
#set_property(GLOBAL PROPERTY _target_llvm_include_directory_property ${LLVM_INCLUDE_DIRS})

# lib files (internal libraries)
add_subdirectory(lib)

# source files (implementations)
add_subdirectory(src)
