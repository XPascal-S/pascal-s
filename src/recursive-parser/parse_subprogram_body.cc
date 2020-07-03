//
// Created by kamiyoru on 2020/6/27.
//


#include <pascal-s/parser_recursive.h>

template<typename Lexer>
ast::SubprogramBody *RecursiveParser<Lexer>::parse_subprogram_body() {

    // const declarations
    ast::ConstDecls *const_decls = nullptr;
    if (predicate::is_const(current_token)) {
        const_decls = parse_const_decls();
    }

    // var declarations
    ast::VarDecls *var_decls = nullptr;
    if (predicate::is_var(current_token)) {
        var_decls = parse_var_decls();
    }

    // compound statement
    return new ast::SubprogramBody(const_decls, var_decls, parse_compound_statement());
}
