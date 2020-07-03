
cmake_minimum_required(VERSION 3.15)
project(pascal-s)


if (ENABLE_TESTING)
  add_executable(parser_main_test parser_test/parser_test.cpp)
  target_link_libraries(parser_main_test pascal-s-local)
endif (ENABLE_TESTING)

add_library(pascal-s-parser ${PASCAL_S_PARSER_SOURCE_FILES})
link_pascal_s_local(pascal-s-parser)
# target_link_libraries(parser-s-parser pascal-s-local)


if (UNIX)
  add_custom_target(
          bison_build
          COMMAND ${CMAKE_CURRENT_SOURCE_DIR}/build.sh
  )
  add_dependencies(pascal-s-parser bison_build)
endif (UNIX)

# pybind11_add_module(py_ast py_ast.cpp)
# target_link_libraries(py_ast PRIVATE pybind11::module)
# target_link_libraries(py_ast PRIVATE pascal-s-local)
# set_target_properties(py_ast PROPERTIES SUFFIX ".so")
