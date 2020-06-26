//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::Procedure *Parser<Lexer>::parse_function_body(ast::Procedure *proc) {

    // const declarations
    ast::ConstDecls *const_decls = nullptr;
    if (predicate::is_const(current_token)) {
        proc->const_decls = parse_const_decls();
    }

    // var declarations
    if (predicate::is_var(current_token)) {
        proc->var_decls = parse_var_decls();
    }

    // statement
    proc->body = parse_statement();
    return proc;
}
