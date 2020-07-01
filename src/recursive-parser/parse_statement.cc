//
// Created by kamiyoru on 2020/6/27.
//



template<typename Lexer>
ast::Statement *Parser<Lexer>::parse_statement(std::set<const Token *> *till) {
    for (;;) {
        if (current_token == nullptr) {
            return fall_expect_s("exp call or complex statement keywords");
        }
        if (predicate::is_semicolon(current_token)) {
            return fall_expect_s("exp call or complex statement keywords");
        }
        if (predicate::is_end(current_token)) {
            return fall_expect_s("exp call or complex statement keywords");
        }
        if (current_token->type == TokenType::Identifier) {
            break;
        }
        maybe_recover_keyword(KeywordType::Begin)
        maybe_recover_keyword(KeywordType::For)
        maybe_recover_keyword(KeywordType::If)
        maybe_recover_keyword(KeywordType::Read)
        maybe_recover_keyword(KeywordType::Write)
        skip_error_token_s("exp call or complex statement keywords")
        return fall_expect_s("exp call or complex statement keywords");
    }

    // assign op or func call
    if (current_token->type == TokenType::Identifier) {
        // we extend the prod of statement to reduce work
        ast::Exp *exp = parse_exp(till);

        if (exp == nullptr) {
            return nullptr;
        } else {
            return new ast::ExecStatement(exp);
        }
    }

    if (current_token->type == TokenType::Keyword) {
        switch (reinterpret_cast<const Keyword *>(current_token)->key_type) {
            case KeywordType::Begin:
                return _parse_compound_statement();
            case KeywordType::For:
                return parse_for_statement(till);
            case KeywordType::If:
                return parse_if_else_statement(till);
            case KeywordType::Read:
                return parse_read_statement(till);
            case KeywordType::Write:
                return parse_write_statement(till);
            default:
                assert(false);
                return nullptr;
        }
    }


    // epsilon
    return nullptr;
}

template<typename Lexer>
ast::Statement *Parser<Lexer>::parse_read_statement(std::set<const Token *> *till) {
    assert(predicate::is_read(current_token));
    next_token();

    auto stmt = new ast::Read();
    stmt->var_list = parse_variable_list_with_paren();
    return stmt;
}

template<typename Lexer>
ast::Statement *Parser<Lexer>::parse_write_statement(std::set<const Token *> *till) {
    assert(predicate::is_write(current_token));
    next_token();

    auto stmt = new ast::Write();
    stmt->exp_list = parse_expression_list_with_paren();
    return stmt;
}
