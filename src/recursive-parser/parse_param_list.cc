//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::ParamList *Parser<Lexer>::parse_param_list_with_paren() {

    // (
    expected_enum_type(predicate::is_lparen, predicate::marker_lparen);
    next_token();

    // param list
    auto param_list = parse_param_list();
    if (param_list == nullptr) {
        return nullptr;
    }

    // )
    if (!predicate::is_rparen(current_token)) {
        delete param_list;
        errors.push_back(new PascalSParseExpectGotError(__FUNCTION__, &predicate::marker_rparen, current_token));
        return nullptr;
    }
    next_token();

    return param_list;
}

template<typename Lexer>
ast::ParamList *Parser<Lexer>::parse_param_list() {
    //look ahead
    if (current_token == nullptr || current_token->type != TokenType::Identifier) {
        return nullptr;
    }
    return _parse_param_list(new ast::ParamList);
}


template<typename Lexer>
ast::ParamList *Parser<Lexer>::_parse_param_list(ast::ParamList *params) {
    auto spec = parse_param();
    if (spec == nullptr) {
        return params;
    }
    params->params.push_back(spec);

    //look ahead
    // ;
    if (predicate::is_semicolon(current_token)) {
        next_token();

        // param list
        _parse_param_list(params);
    }
    return params;
}

template<typename Lexer>
ast::ParamSpec *Parser<Lexer>::parse_param() {
    auto keyword_var = reinterpret_cast<const Keyword *>(current_token);
    if (current_token == nullptr ||
        keyword_var->type != TokenType::Keyword ||
        keyword_var->key_type != KeywordType::Var) {

        keyword_var = nullptr;
    } else {
        next_token();
    }

    // id list
    auto id_list = parse_id_list();
    if (id_list == nullptr) {
        return nullptr;
    }

    // :
    expected_enum_type(predicate::is_colon, predicate::marker_colon);
    next_token();

    auto basic = reinterpret_cast<const Keyword *>(current_token);
    if (basic == nullptr || basic->type != TokenType::Keyword) {
        return nullptr;
    }
    if (
        // basic type
            basic->key_type != KeywordType::Integer &&
            basic->key_type != KeywordType::Real &&
            basic->key_type != KeywordType::Char &&
            basic->key_type != KeywordType::Boolean
            ) {
        errors.push_back(new PascalSParseExpectSGotError(__FUNCTION__, "basic type spec", basic));
        return nullptr;
    }
    auto spec = new ast::BasicTypeSpec(basic);
    next_token();

    return new ast::ParamSpec(keyword_var, id_list, spec);
}
