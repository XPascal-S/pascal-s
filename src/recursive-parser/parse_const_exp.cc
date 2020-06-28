//
// Created by kamiyoru on 2020/6/27.
//


#include <pascal-s/parser.h>

template<typename Lexer>
ast::Exp *Parser<Lexer>::parse_const_exp(const std::set<const Token *> *till) {

    auto *maybe_lhs = parse_const_fac(till);
    if (maybe_lhs == nullptr) {
        return nullptr;
    }

    if (predicate::token_equal(current_token, till)) {
        return maybe_lhs;
    }

    assert(false);
    // todo: parse recursive const exp
    return nullptr;
}

template<typename Lexer>
ast::Exp *Parser<Lexer>::parse_const_fac(const std::set<const Token *> *till) {
    if (current_token == nullptr) {
        errors.push_back(new PascalSParseExpectSGotError(__FUNCTION__, "const value", current_token));
        return nullptr;
    }

    if (current_token->type == TokenType::Marker) {
        auto marker = reinterpret_cast<const Marker *>(current_token);
        switch (marker->marker_type) {
            case MarkerType::Add:
            case MarkerType::Sub:
                next_token();
                return new ast::UnExp(marker, parse_const_exp(till));
            case MarkerType::LParen:
                next_token();
                return parse_const_exp(&predicate::predicateContainers.rParenContainer);
            default:
                throw std::runtime_error("expected +/-/(");
        }
    }

    // parse const fac
    ast::Exp *fac = nullptr;

    switch (current_token->type) {

        case TokenType::ConstantInteger:
            fac = new ast::ExpConstantInteger(
                    reinterpret_cast<const ConstantInteger *>(current_token));
            break;
        case TokenType::ConstantChar:
            fac = new ast::ExpConstantChar(
                    reinterpret_cast<const ConstantChar *>(current_token));
            break;
        case TokenType::ConstantString:
            fac = new ast::ExpConstantString(
                    reinterpret_cast<const ConstantString *>(current_token));
            break;
        case TokenType::ConstantReal:
            fac = new ast::ExpConstantReal(
                    reinterpret_cast<const ConstantReal *>(current_token));
            break;
        case TokenType::ConstantBoolean:
            fac = new ast::ExpConstantBoolean(
                    reinterpret_cast<const ConstantBoolean *>(current_token));
            break;
        default:
            return nullptr;
    }
    next_token();
    return fac;
}

template<typename Lexer>
bool Parser<Lexer>::has_error() {
    return !errors.empty();
}
