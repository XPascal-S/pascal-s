//
// Created by kamiyoru on 2020/6/27.
//



template<typename Lexer>
ast::ConstDecls *Parser<Lexer>::parse_const_decls() {

    // const
    expected_enum_type_r_e(predicate::is_const, predicate::keyword_const, nullptr,
                           || predicate::is_var(current_token));
    next_token();

    // declarations
    return _parse_const_decls(new ast::ConstDecls);
}

template<typename Lexer>
ast::ConstDecls *Parser<Lexer>::_parse_const_decls(ast::ConstDecls *decls) {

    for (;;) {
        // declaration
        auto decl = parse_const_decl();
        if (decl == nullptr) {
            return decls;
        }
        decls->decls.push_back(decl);

        // look ahead
        if (current_token == nullptr || predicate::is_var(current_token)) {
            return decls;
        }
    }
}

template<typename Lexer>
ast::ConstDecl *Parser<Lexer>::parse_const_decl() {
    // id
    expected_type_r(TokenType::Identifier, nullptr);
    auto ident = reinterpret_cast<const Identifier *>(current_token);
    next_token();

    // =
    expected_enum_type_r_e(predicate::is_eq, predicate::marker_eq, nullptr,
                           || predicate::is_var(current_token));
    next_token();

    // const exp
    auto decl = new ast::ConstDecl(ident, parse_const_exp(&predicate::predicateContainers.semicolonOrVarContainer));

    // ;
    expected_enum_type_r_e(predicate::is_semicolon, predicate::marker_semicolon, decl,
                           || predicate::is_var(current_token));
    next_token();

    return decl;
}