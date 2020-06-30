//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::IdentList *Parser<Lexer>::parse_id_list_with_paren() {

    // lparen
    expected_enum_type(predicate::is_lparen, predicate::marker_lparen);
    next_token();

    // id list
    auto ident_list = parse_id_list();
    if (ident_list == nullptr) {
        return nullptr;
    }

    // rparen
    expected_enum_type(predicate::is_rparen, predicate::marker_rparen);
    next_token();

    return ident_list;
}

template<typename Lexer>
ast::IdentList *Parser<Lexer>::parse_id_list() {
    // allocate
    return _parse_id_list(new ast::IdentList);
}

template<typename Lexer>
ast::IdentList *Parser<Lexer>::_parse_id_list(ast::IdentList *params) {

    for (;;) {
        if (predicate::is_rparen(current_token)) {
            return params;
        }
        if (predicate::is_colon(current_token)) {
            return params;
        }
        if (current_token != nullptr && current_token->type == TokenType::Identifier) {
            break;
        }
        skip_any_but_eof_token_s("variable list sep marker ')' or ':'");
        return fall_expect_s("variable list sep marker ')' or ':'"), params;
    }

    // id
    expected_type_r(TokenType::Identifier, params);
    params->idents.push_back(reinterpret_cast<const Identifier *>(current_token));
    next_token();

    for (;;) {
        if (predicate::token_equal(current_token, &predicate::predicateContainers.commaOrRParenContainer)) {
            break;
        }
        if (predicate::is_colon(current_token)) {
            break;
        }
        skip_any_but_eof_token_s("variable list sep marker ',', ':' or ')'");
        return fall_expect_s("variable list sep marker ',', ':' or ')'"), params;
    }

    // ,
    if (predicate::is_comma(current_token)) {
        next_token();

        // id list
        _parse_id_list(params);
    }
    return params;
}