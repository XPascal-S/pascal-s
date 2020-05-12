
cmake_minimum_required(VERSION 3.15)
project(pascal-s)


function(add_parser_test test_name)
    add_gtest(${test_name})
    target_link_libraries(${test_name} pascal-s-local)
endfunction()

add_parser_test(target_c_test)