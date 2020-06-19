
cmake_minimum_required(VERSION 3.15)
project(pascal-s)

add_definitions(-D__STDC_VERSION__=199901L)

add_executable(nothing-pascal-s compiler.cpp ${PASCAL_S_COMPILER_SOURCE_FILES})
target_link_libraries(nothing-pascal-s fmt debug target-nothing)

add_executable(c-pascal-s compiler.cpp ${PASCAL_S_COMPILER_SOURCE_FILES})
target_link_libraries(c-pascal-s fmt debug target-c)

add_executable(llvm-pascal-s compiler.cpp ${PASCAL_S_COMPILER_SOURCE_FILES})
target_link_libraries(llvm-pascal-s fmt debug target-llvm)
