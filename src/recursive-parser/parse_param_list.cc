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
        errors.push_back(new PascalSParseExpectVGotError(__FUNCTION__, &predicate::marker_rparen, current_token));
        return nullptr;
    }
    next_token();

    return param_list;
}

template<typename Lexer>
ast::ParamList *Parser<Lexer>::parse_param_list() {
    //look ahead
    return _parse_param_list(new ast::ParamList);
}


template<typename Lexer>
ast::ParamList *Parser<Lexer>::_parse_param_list(ast::ParamList *params) {
    for (;;) {
        auto spec = parse_param();
        if (spec != nullptr) {
            params->params.push_back(spec);
        }


        //look ahead
        // ;
        for (;;) {
            if (current_token == nullptr || predicate::is_rparen(current_token)) {
                return params;
            }
            if (predicate::is_semicolon(current_token)) {
                break;
            }
            skip_any_but_eof_token_s("param list sep marker ';' or ')'");
            return fall_expect_s("param list sep marker ';' or ')'"), params;
        }
        next_token();
    }
}

template<typename Lexer>
ast::ParamSpec *Parser<Lexer>::parse_param() {

    for (;;) {
        if (current_token == nullptr) {
            return fall_expect_s("keyword var or id list");
        }
        if (predicate::is_rparen(current_token)) {
            return nullptr;
        }
        // todo: allow empty?
//        if (predicate::is_rparen(current_token)) {
//            return fall_expect_s("keyword var or id list");
//        }
        if (predicate::is_semicolon(current_token)) {
            return fall_expect_s("keyword var or id list");
        }
        if (predicate::is_var(current_token)) {
            break;
        }
        if (current_token->type == TokenType::Identifier) {
            break;
        }

        skip_any_but_eof_token_s("keyword var or id list");
        return fall_expect_s("keyword var or id list");
    }


    auto keyword_var = reinterpret_cast<const Keyword *>(current_token);
    if (keyword_var->type != TokenType::Keyword ||
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


    if (current_token == nullptr || current_token->type != TokenType::Keyword) {
        for (;;) {
            if (current_token == nullptr) {
                return fall_expect_s("basic type spec"), new ast::ParamSpec(keyword_var, id_list, nullptr);
            }
            if (predicate::is_rparen(current_token)) {
                return fall_expect_s("basic type spec"), new ast::ParamSpec(keyword_var, id_list, nullptr);
            }
            if (predicate::is_semicolon(current_token)) {
                return fall_expect_s("basic type spec"), new ast::ParamSpec(keyword_var, id_list, nullptr);
            }
            maybe_recover_keyword(KeywordType::Boolean)
            maybe_recover_keyword(KeywordType::Integer)
            maybe_recover_keyword(KeywordType::Char)
            maybe_recover_keyword(KeywordType::Real)
            skip_error_token_s("basic type spec")
            return fall_expect_s("basic type spec"), new ast::ParamSpec(keyword_var, id_list, nullptr);
        }
    }

    auto basic = reinterpret_cast<const Keyword *>(current_token);
    auto spec = new ast::BasicTypeSpec(basic);
    next_token();

    return new ast::ParamSpec(keyword_var, id_list, spec);
}
