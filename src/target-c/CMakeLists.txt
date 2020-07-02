cmake_minimum_required(VERSION 3.15)
project(pascal-s)

add_subdirectory(target_test)

file(GLOB PASCAL_S_TARGET_C_SOURCE_FILES **.cpp)

add_library(target-c ${PASCAL_S_TARGET_C_SOURCE_FILES})
target_include_fmt(target-c)
