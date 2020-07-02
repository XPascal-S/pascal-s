
cmake_minimum_required(VERSION 3.15)
project(pascal-s)

add_executable(parser parser_test.cpp)
target_link_libraries(parser pascal-s-local)

if (UNIX)
add_custom_target(
  bison_build
  COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build.sh
  )
add_dependencies(parser bison_build)
endif (UNIX)

# pybind11_add_module(py_ast py_ast.cpp)
# target_link_libraries(py_ast PRIVATE pybind11::module)
# target_link_libraries(py_ast PRIVATE pascal-s-local)
# set_target_properties(py_ast PROPERTIES SUFFIX ".so")
