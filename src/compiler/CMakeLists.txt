
cmake_minimum_required(VERSION 3.15)
project(pascal-s)

add_definitions(-D__STDC_VERSION__=199901L)

function(add_compiler compiler-suffix)
    add_executable(nothing-pascal-s${compiler-suffix} ${ARGN})
    target_link_libraries(nothing-pascal-s${compiler-suffix} fmt debug target-nothing)

    add_executable(c-pascal-s${compiler-suffix} ${ARGN})
    target_link_libraries(c-pascal-s${compiler-suffix} fmt debug target-c)

    add_executable(llvm-pascal-s${compiler-suffix} ${ARGN})
    target_link_libraries(llvm-pascal-s${compiler-suffix} fmt debug target-llvm)
endfunction()

add_compiler(-r compiler.cpp ${PASCAL_S_COMPILER_SOURCE_FILES})