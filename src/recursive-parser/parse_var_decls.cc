//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::VarDecls *Parser<Lexer>::parse_var_decls() {

    //var
    expected_enum_type(predicate::is_var, predicate::keyword_var);
    next_token();

    // look ahead
    expected_type_r(TokenType::Identifier, nullptr);
    return _parse_var_decls(new ast::VarDecls);
}

template<typename Lexer>
ast::VarDecls *Parser<Lexer>::_parse_var_decls(ast::VarDecls *decls) {

    // declaration
    auto decl = parse_var_decl();
    if (decl == nullptr) {
        return decls;
    }
    decls->decls.push_back(decl);

    // look ahead
    if (current_token == nullptr || current_token->type != TokenType::Identifier) {
        return decls;
    }
    return _parse_var_decls(decls);
}

template<typename Lexer>
ast::VarDecl *Parser<Lexer>::parse_var_decl() {

    // id list
    auto id_list = parse_id_list();
    if (id_list == nullptr) {
        return nullptr;
    }

    // :
    expected_enum_type(predicate::is_colon, predicate::marker_colon);
    next_token();

    // type
    auto type = parse_type();
    if (type == nullptr) {
        return nullptr;
    }

    // ;
    expected_enum_type(predicate::is_semicolon, predicate::marker_semicolon);
    next_token();


    return new ast::VarDecl(id_list, type);
}
