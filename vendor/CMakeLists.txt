
cmake_minimum_required(VERSION 3.15)
project(pascal-s)

# GTest Begin
if (${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    set(LIBRARIES ${LIBRARIES} " " pthread)
else ()
    message("!!! warning: not using pthread " "(host: " ${CMAKE_SYSTEM_NAME} ")!!!")
endif ()

add_subdirectory(googletest)
# GTest End

# LLVM Begin
# 需要提前build好，该目录为LLVMConfig.cmake所在目录
function(add_llvm_dependency)
    set(LLVM_DIR C:/work/cpp/llvm-tutorial/lib/build-llvm/lib/cmake/llvm)
    find_package(LLVM REQUIRED CONFIG)

    message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
    message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

    include_directories(${LLVM_INCLUDE_DIRS})
    add_definitions(${LLVM_DEFINITIONS})
endfunction()
# LLVM End

#fmt
add_subdirectory(fmt)
include_directories(fmt/include)

#flex
function(target_include_flex target_name)
    target_include_directories(${target_name} PUBLIC BEFORE SYSTEM ${CMAKE_SOURCE_DIR}/vendor/flex/src)
endfunction()

#pybind11
add_subdirectory(pybind11)
include_directories(pybind11/include)
include_directories(/usr/include/python3.6)
