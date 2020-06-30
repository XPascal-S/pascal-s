//
// Created by kamiyoru on 2020/6/27.
//

template<typename Lexer>
ast::Variable *Parser<Lexer>::parse_variable(const std::set<const Token *> *till) {
    if (current_token == nullptr || current_token->type != TokenType::Identifier) {
        for (;;) {
            if (current_token == nullptr) {
                return fall_expect_t(TokenType::Identifier);
            }

            if (current_token->type == TokenType::Identifier) {
                break;
            }

            if (predicate::is_rparen(current_token)) {
                return fall_expect_t(TokenType::Identifier);
            }
            if (predicate::is_rbracket(current_token)) {
                return fall_expect_t(TokenType::Identifier);
            }
            if (predicate::is_semicolon(current_token)) {
                return fall_expect_t(TokenType::Identifier);
            }
            if (predicate::is_comma(current_token)) {
                return fall_expect_t(TokenType::Identifier);
            }
            if (predicate::is_end(current_token)) {
                return fall_expect_t(TokenType::Identifier);
            }
            skip_any_but_eof_token_t(TokenType::Identifier)
            return fall_expect_t(TokenType::Identifier);
        }
    }

    auto ident = reinterpret_cast<const Identifier *>(current_token);
    next_token();

    auto variable = new ast::Variable();
    variable->id = ident;

    if (!predicate::is_lbracket(current_token)) {
        for (;;) {
            if (current_token == nullptr) {
                return fall_expect_v(&predicate::marker_lbracket), variable;
            }
            if (predicate::token_equal(current_token, till)) {
                return variable;
            }
            if (predicate::is_lbracket(current_token)) {
                break;
            }

            if (predicate::is_rparen(current_token)) {
                return fall_expect_v(&predicate::marker_lbracket), variable;
            }
            if (predicate::is_rbracket(current_token)) {
                return fall_expect_v(&predicate::marker_lbracket), variable;
            }
            if (predicate::is_semicolon(current_token)) {
                return fall_expect_v(&predicate::marker_lbracket), variable;
            }
            if (predicate::is_comma(current_token)) {
                return fall_expect_v(&predicate::marker_lbracket), variable;
            }
            if (predicate::is_end(current_token)) {
                return fall_expect_v(&predicate::marker_lbracket), variable;
            }
            skip_any_but_eof_token_v(&predicate::marker_lbracket)
            return fall_expect_v(&predicate::marker_lbracket), variable;
        }
    }

    variable->id_var = parse_expression_list_with_bracket();
    return variable;
}
