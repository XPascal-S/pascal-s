cmake_minimum_required(VERSION 3.15)
project(pascal-s)

#add_executable(target-c_test target_test.cpp)

add_executable(target_main target_main.cpp)
link_pascal_s_local(target_main)
add_subdirectory(target_test)