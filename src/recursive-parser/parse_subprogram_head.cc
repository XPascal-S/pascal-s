//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::SubprogramHead *Parser<Lexer>::parse_subprogram_head() {

    // program id
    auto fn_def = reinterpret_cast<const Keyword *>(current_token);
    next_token();
    assert(fn_def->key_type == KeywordType::Procedure || fn_def->key_type == KeywordType::Function);

    auto ident = reinterpret_cast<const Identifier *>(current_token);
    expected_type(TokenType::Identifier);
    next_token();

    // maybe param list
    ast::ParamList *pl = nullptr;
    if (predicate::is_lparen(current_token)) {
        pl = parse_param_list_with_paren();
    }

    // function should with type
    ast::BasicTypeSpec *rt = nullptr;
    if (predicate::is_function(fn_def)) {

        // :
        expected_enum_type_r(predicate::is_colon, predicate::marker_colon, new ast::SubprogramHead(fn_def, ident, pl,
                                                                                                   nullptr));
        next_token();

        if (current_token == nullptr || current_token->type != TokenType::Keyword) {
            for (;;) {
                if (current_token == nullptr) {
                    return fall_expect_s("basic type spec"), new ast::SubprogramHead(fn_def, ident, pl, nullptr);
                }
                if (predicate::is_rparen(current_token)) {
                    return fall_expect_s("basic type spec"), new ast::SubprogramHead(fn_def, ident, pl, nullptr);
                }
                if (predicate::is_semicolon(current_token)) {
                    return fall_expect_s("basic type spec"), new ast::SubprogramHead(fn_def, ident, pl, nullptr);
                }
                maybe_recover_keyword(KeywordType::Boolean)
                maybe_recover_keyword(KeywordType::Integer)
                maybe_recover_keyword(KeywordType::Char)
                maybe_recover_keyword(KeywordType::Real)
                skip_error_token_s("basic type spec")

                return fall_expect_s("basic type spec"), new ast::SubprogramHead(fn_def, ident, pl, nullptr);
            }
        }

        auto basic = reinterpret_cast<const Keyword *>(current_token);
        rt = new ast::BasicTypeSpec(basic);
        next_token();
    }

    // share common struct type SubprogramHead
    return new ast::SubprogramHead(fn_def, ident, pl, rt);
}

