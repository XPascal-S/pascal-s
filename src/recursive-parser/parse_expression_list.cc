//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::ExpressionList *Parser<Lexer>::parse_expression_list_with_paren() {

    // (
    expected_enum_type(predicate::is_lparen, predicate::marker_lparen);
    next_token();

    // expression list
    auto exp_list = parse_expression_list();
    if (exp_list == nullptr) {
        return nullptr;
    }

    // )
    if (!predicate::is_rparen(current_token)) {
        delete exp_list;
        errors.push_back(new PascalSParseExpectVGotError(__FUNCTION__, &predicate::marker_rparen, current_token));
        return nullptr;
    }
    next_token();

    return exp_list;
}

template<typename Lexer>
ast::ExpressionList *Parser<Lexer>::parse_expression_list_with_bracket() {

    // [
    expected_enum_type(predicate::is_lbracket, predicate::marker_lbracket);
    next_token();

    // expression list
    auto exp_list = parse_expression_list();
    if (exp_list == nullptr) {
        return nullptr;
    }

    // ]
    if (!predicate::is_rbracket(current_token)) {
        delete exp_list;
        errors.push_back(new PascalSParseExpectVGotError(__FUNCTION__, &predicate::marker_rbracket, current_token));
        return nullptr;
    }
    next_token();

    return exp_list;
}

template<typename Lexer>
ast::ExpressionList *Parser<Lexer>::parse_expression_list() {
    auto *ret = new ast::ExpressionList;
    for (;;) {

        // look ahead
        if (predicate::is_rparen(current_token)) {
            return ret;
        }

        // extend production
        ret->explist.push_back(parse_exp(&predicate::predicateContainers.commaOrRParenContainer));

        // eat , if possible
        if (predicate::is_comma(current_token)) {
            next_token();

            // want FOLLOW(variable) = {)}
        } else if (!predicate::is_rparen(current_token)) {
            delete ret;
            throw std::runtime_error("expected ,/)");
            return nullptr;
        }
    }
    return nullptr;
}

