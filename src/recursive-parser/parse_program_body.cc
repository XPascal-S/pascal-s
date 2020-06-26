//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::ProgramBody *Parser<Lexer>::parse_program_body() {

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
//
//    // function declarations
//    ast::FunctionDecls *fn_decls = nullptr;
//    if (predicate::is_function(current_token) || predicate::is_procedure(current_token)) {
//        fn_decls = parse_function_decls();
//    }
//
//    std::set<const Token *> till;
//    till.insert(reinterpret_cast<const Token *>(&predicate::marker_semicolon));
//    // program statement
//    return new ast::Program(
//            program, ident, ident_list,
//            const_decls, var_decls, fn_decls, parse_statement(&till));

    return new ast::ProgramBody(const_decls, nullptr, nullptr, nullptr);
}
