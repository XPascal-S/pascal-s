
//
// Created by kamiyoru on 2020/6/30.
//


template<typename Lexer>
ast::CompoundStatement *Parser<Lexer>::parse_compound_statement(std::set<const Token *> *till) {
    expected_enum_type(predicate::is_begin, predicate::keyword_begin);
    return _parse_compound_statement(till);
}

template<typename Lexer>
ast::CompoundStatement *Parser<Lexer>::_parse_compound_statement(std::set<const Token *> *till) {
    auto begin_tok = reinterpret_cast<const Keyword *>(current_token);
    next_token();

    std::vector<ast::Statement *> stmts;
    auto sl = new ast::StatementList;
    auto block = new ast::CompoundStatement(sl/*begin_tok, end_tok*/);

    // end
    ast::Statement *stmt;
    while (!predicate::is_end(current_token)) {
        if (current_token == nullptr) {
            sl->statement.swap(stmts);
            return fall_expect_v(&predicate::keyword_end), block;
        }

        // statement
        if (till == nullptr) {
            std::set<const Token *> m_till;
            m_till.insert(reinterpret_cast<const Token *>(&predicate::keyword_end));
            m_till.insert(reinterpret_cast<const Token *>(&predicate::marker_semicolon));
            stmt = parse_statement(&m_till);
        } else {
            bool no_end = !till->count(&predicate::keyword_end), no_semi = !till->count(
                    &predicate::marker_semicolon);
            if (no_end) {
                till->insert(&predicate::keyword_end);
            }
            if (no_semi) {
                till->insert(&predicate::marker_semicolon);
            }
            stmt = parse_statement(till);
            if (no_end) {
                till->erase(&predicate::keyword_end);
            }
            if (no_semi) {
                till->erase(&predicate::marker_semicolon);
            }
        }

        if (stmt != nullptr) {
            stmts.push_back(stmt);
        }

        for (;;) {
            if (current_token == nullptr) {
                sl->statement.swap(stmts);
                return fall_expect_s("keyword 'end' or marker ';'"), block;
            }
            // look ahead

            maybe_recover_keyword(KeywordType::End)
            if (predicate::is_semicolon(current_token)) {
                break;
            }

            skip_any_but_eof_token_s("keyword 'end' or marker ';'");
            sl->statement.swap(stmts);
            return fall_expect_s("keyword 'end' or marker ';'"), block;
        }

        if (predicate::is_end(current_token)) {
            continue;
        }

        // eat ; if possible

        if (!predicate::is_semicolon(current_token)) {
            return fall_expect_v(&predicate::marker_semicolon), block;
        }
        next_token();
    }

    // end
    auto end_tok = reinterpret_cast<const Keyword *>(current_token);
    next_token();
    sl->statement.swap(stmts);
    if (sl->statement.empty()) {
        ast::copy_pos_with_check(sl, begin_tok);
    } else {
        ast::copy_pos_between_tokens(sl, begin_tok, sl->statement.back());
    }
    ast::copy_pos_with_check(block, sl);
    return block;
}
