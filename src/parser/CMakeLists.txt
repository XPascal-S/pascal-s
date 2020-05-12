
cmake_minimum_required(VERSION 3.15)
project(pascal-s)

add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test pascal-s-local)