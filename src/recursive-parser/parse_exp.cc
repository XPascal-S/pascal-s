//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::Exp *Parser<Lexer>::parse_exp(const std::set<const Token *> *till) {

    // lhs
    auto maybe_lhs = parse_fac();
    if (predicate::token_equal(current_token, till)) {
        return maybe_lhs;
    }

    if (current_token->type == TokenType::Marker) {
        auto marker = reinterpret_cast<const Marker *>(current_token);
        switch (marker->marker_type) {

            // a + b
            case MarkerType::Add:

                // a - b
            case MarkerType::Sub:

                // a * b
            case MarkerType::Mul:

                // a / b
            case MarkerType::Div:

                // a % b
            case MarkerType::Mod:

                // a < b
            case MarkerType::LT:

                // a <= b
            case MarkerType::LE:

                // a > b
            case MarkerType::GT:

                // a >= b
            case MarkerType::GE:

                // a = b
            case MarkerType::EQ:

                // a <> b
            case MarkerType::NEQ:

                // todo: a % b
//            case MarkerType::Mod:
                next_token();
                return parse_binary_exp(maybe_lhs, marker, get_marker_pri(marker->marker_type), till);

                // fix follow markers
            case MarkerType::Dot:
            case MarkerType::RParen:
                return maybe_lhs;

                // a := b
            case MarkerType::Assign:
                next_token();
                return new ast::ExpAssign(maybe_lhs, parse_exp(till));
            default:
                assert(false);
                return nullptr;
        }
    } else {
        throw std::runtime_error(
                std::string("want marker, got ") + fmt::format("{}",
                                                               convertToString(current_token))
        );
    }

}

template<typename Lexer>
ast::Exp *Parser<Lexer>::parse_fac() {
    if (current_token == nullptr) {
        throw std::runtime_error("expected fac, got nullptr");
    }

    // const factors
    ast::Exp *e = nullptr;
    switch (current_token->type) {
        case TokenType::ConstantInteger:
            e = new ast::ExpConstantInteger(
                    reinterpret_cast<const ConstantInteger *>(current_token));
            break;
        case TokenType::ConstantChar:
            e = new ast::ExpConstantChar(
                    reinterpret_cast<const ConstantChar *>(current_token));
            break;
        case TokenType::ConstantReal:
            e = new ast::ExpConstantReal(
                    reinterpret_cast<const ConstantReal *>(current_token));
            break;
        case TokenType::ConstantString:
            e = new ast::ExpConstantString(
                    reinterpret_cast<const ConstantString *>(current_token));
            break;
        case TokenType::ConstantBoolean:
            e = new ast::ExpConstantBoolean(
                    reinterpret_cast<const ConstantBoolean *>(current_token));
            break;
    }

    if (e != nullptr) {
        return e;
    }


    // unary expression or paren
    if (current_token->type == TokenType::Marker) {
        auto marker = reinterpret_cast<const Marker *>(current_token);
        switch (marker->marker_type) {
            default:
                throw std::runtime_error("expected +/-/(");

                // + exp
            case MarkerType::Add:

                // - exp
            case MarkerType::Sub:
                next_token();
                return new ast::UnExp(marker, parse_exp());

                // (  )
            case MarkerType::LParen:
                next_token();

                auto exp = parse_exp(&predicate::predicateContainers.rParenContainer);
                expected_enum_type_r(predicate::is_rparen, predicate::marker_rparen, exp);
                next_token();
                return exp;
        }

        // function call or array index or identifier exp
        // ident
    } else if (current_token->type == TokenType::Identifier) {
        auto ident = reinterpret_cast<const Identifier *>(current_token);
        next_token();

        // ( or [
        if (current_token != nullptr && current_token->type == TokenType::Marker) {
            auto marker = reinterpret_cast<const Marker *>(current_token);
            if (marker->marker_type == MarkerType::LParen) {

                // will not eat (, just parse ( variable list )
                return new ast::ExpCall(
                        ident, parse_variable_list_with_paren());
                // [
            } else if (marker->marker_type == MarkerType::LBracket) {
                //todo
                throw std::runtime_error("todo");
            }
        }

        // otherwise just a identifier exp
        return new ast::Ident(ident);
    }
    throw std::runtime_error("expected fac");
}

template<typename Lexer>
ast::Exp *
Parser<Lexer>::parse_binary_exp(ast::Exp *lhs, const Marker *marker, marker_type_underlying_type current_marker_pri,
                                const std::set<const Token *> *till) {

    auto rhs = parse_fac();
    if (predicate::token_equal(current_token, till)) {
        return new ast::BiExp(lhs, marker, rhs);
    }
    if (current_token->type != TokenType::Marker) {
        throw std::runtime_error("expected marker");
    }
    auto pri = get_marker_pri(reinterpret_cast<const Marker *>(current_token)->marker_type);
    auto next_marker = reinterpret_cast<const Marker *>(current_token);
    next_token();
    if (current_marker_pri >= pri) {
        return parse_binary_exp(new ast::BiExp(lhs, marker, rhs),
                                next_marker, pri, till);
    }
    return new ast::BiExp(lhs, marker, parse_binary_exp(rhs, next_marker, pri, till));
}
