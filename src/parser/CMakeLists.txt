
cmake_minimum_required(VERSION 3.15)
project(pascal-s)


add_executable(parser_test parser_test.cpp)
target_link_libraries(parser_test pascal-s-local)

pybind11_add_module(py_ast py_ast.cpp)
target_link_libraries(py_ast PRIVATE pascal-s-local)
