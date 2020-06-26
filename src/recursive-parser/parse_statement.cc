//
// Created by kamiyoru on 2020/6/27.
//



template<typename Lexer>
ast::Statement *Parser<Lexer>::parse_statement(std::set<const Token *> *till) {

    // begin
    if (predicate::is_begin(current_token)) {
        auto begin_tok = reinterpret_cast<const Keyword *>(current_token);
        next_token();

        std::vector < ast::Statement * > stmts;

        // end
        ast::Statement *stmt;
        while (!predicate::is_end(current_token)) {
            if (current_token == nullptr) {
                throw std::invalid_argument("bad ... eof");
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

            // eat ; if possible
            if (predicate::is_semicolon(current_token)) {
                next_token();
            } else if (stmt == nullptr) {
                assert(false);
            }
        }

        // end
        auto end_tok = reinterpret_cast<const Keyword *>(current_token);
        next_token();

        auto block = new ast::StatementBlock(begin_tok, end_tok);
        block->stmts.swap(stmts);
        return block;

        // assign op or func call
    } else if (current_token != nullptr && (current_token->type == TokenType::Identifier)) {

        // we extend the prod of statement to reduce work
        ast::Exp *exp = parse_exp(till);

        if (exp == nullptr) {
            return nullptr;
        } else {
            return new ast::ExecStatement(exp);
        }
    } else if (predicate::is_for(current_token)) {
        auto *for_stmt = new ast::ForStatement();

        // for
        expected_enum_type_r(predicate::is_for, predicate::keyword_for, for_stmt);
        next_token();

        // id
        expected_type_r(TokenType::Identifier, for_stmt);
        for_stmt->loop_var = reinterpret_cast<const Identifier *>(current_token);
        next_token();

        // :=
        expected_enum_type_r(predicate::is_assgin, predicate::marker_assgin, for_stmt);
        next_token();

        // from exp
        if (till == nullptr) {
            std::set<const Token *> m_till;
            m_till.insert(reinterpret_cast<const Token *>(&predicate::keyword_to));
            for_stmt->from_exp = parse_exp(&m_till);
        } else {
            bool no_to = !till->count(&predicate::keyword_to);
            if (no_to) {
                till->insert(&predicate::keyword_to);
            }
            for_stmt->from_exp = parse_exp(till);
            if (no_to) {
                till->erase(&predicate::keyword_to);
            }
        }

        // to
        expected_enum_type_r(predicate::is_to, predicate::keyword_to, for_stmt);
        next_token();

        // to exp
        if (till == nullptr) {
            std::set<const Token *> m_till;
            m_till.insert(reinterpret_cast<const Token *>(&predicate::keyword_do));
            for_stmt->to_exp = parse_exp(&m_till);
        } else {
            bool no_do = !till->count(&predicate::keyword_do);
            if (no_do) {
                till->insert(&predicate::keyword_do);
            }
            for_stmt->to_exp = parse_exp(till);
            if (no_do) {
                till->erase(&predicate::keyword_do);
            }
        }

        // do
        expected_enum_type_r(predicate::is_do, predicate::keyword_do, for_stmt);
        next_token();


        // for statement body
        for_stmt->for_stmt = parse_statement(till);


        return for_stmt;
    } else if (predicate::is_if(current_token)) {
        auto *if_else = new ast::IfElseStatement();

        // if
        expected_enum_type_r(predicate::is_if, predicate::keyword_if, if_else);
        next_token();

        // if cond
        if (till == nullptr) {
            std::set<const Token *> m_till;
            m_till.insert(reinterpret_cast<const Token *>(&predicate::keyword_then));
            if_else->cond = parse_exp(&m_till);
        } else {
            bool no_then = !till->count(&predicate::keyword_then);
            if (no_then) {
                till->insert(&predicate::keyword_then);
            }
            if_else->cond = parse_exp(till);
            if (no_then) {
                till->erase(&predicate::keyword_then);
            }
        }

        // then
        expected_enum_type_r(predicate::is_then, predicate::keyword_then, if_else);
        next_token();

        // if stmt
        if (till == nullptr) {
            std::set<const Token *> m_till;
            m_till.insert(reinterpret_cast<const Token *>(&predicate::keyword_else));
            if_else->if_stmt = parse_statement(&m_till);
        } else {
            bool no_else = !till->count(&predicate::keyword_else);
            if (no_else) {
                till->insert(&predicate::keyword_else);
            }
            if_else->if_stmt = parse_statement(till);
            if (no_else) {
                till->erase(&predicate::keyword_else);
            }
        }

        // else part
        if (predicate::is_else(current_token)) {
            next_token();

            // else stmt
            if_else->else_stmt = parse_statement(till);
        }

        return if_else;
    }

    // epsilon
    return nullptr;
}
