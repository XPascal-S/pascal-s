
cmake_minimum_required(VERSION 3.15)
project(pascal-s)


function(add_recursive_parser_test test_name)
    add_gtest(${test_name} ${PASCAL_S_RECURSIVE_PARSER_SOURCE_FILES})
    target_link_libraries(${test_name} pascal-s-local)
endfunction()


add_definitions(-DWITH_MOCK)

add_recursive_parser_test(parser_test)
add_recursive_parser_test(program_head_test)
add_recursive_parser_test(program_body_test)
add_recursive_parser_test(const_decls_test)
add_recursive_parser_test(parse_var_decls_test)
add_recursive_parser_test(parse_id_list_test)
add_recursive_parser_test(parse_param_list_test)
add_recursive_parser_test(parse_exp_test)
add_recursive_parser_test(parse_statement_test)
add_recursive_parser_test(const_exp_test)
add_recursive_parser_test(type_test)