//
// Created by kamiyoru on 2020/6/27.
//



#include <pascal-s/parser_recursive.h>

template<typename Lexer>
ast::ConstDecls *RecursiveParser<Lexer>::parse_const_decls() {

    // const
    expected_enum_type_r_e(predicate::is_const, predicate::keyword_const, nullptr,
                           || predicate::is_var(current_token));
    auto const_tok = current_token;
    next_token();

    // declarations
    ast::ConstDecls *decls = _parse_const_decls(new ast::ConstDecls);
    assert(decls != nullptr);
    if (decls->decls.empty()) {
        ast::copy_pos_with_check(decls, const_tok);
    } else {
        ast::copy_pos_between_tokens(decls, const_tok, decls->decls.back());
    }
    return decls;
}

template<typename Lexer>
ast::ConstDecls *RecursiveParser<Lexer>::_parse_const_decls(ast::ConstDecls *decls) {

    for (;;) {
        // declaration
        auto decl = parse_const_decl();
        if (decl == nullptr) {
            return decls;
        }
        decls->decls.push_back(decl);

        // look ahead

        for (;;) {
            if (current_token == nullptr) {
                return decls;
            }

            if (current_token->type == TokenType::Identifier) {
                break;
            }
            maybe_recover_keyword(KeywordType::Var)
            maybe_recover_keyword(KeywordType::Begin)

            skip_any_but_eof_token_s("next const decl or var/begin");
            return fall_expect_s("next const decl or var/begin"), decls;
        }

        if (predicate::is_var(current_token) || predicate::is_begin(current_token)) {
            return decls;
        }
    }
}

template<typename Lexer>
ast::ConstDecl *RecursiveParser<Lexer>::parse_const_decl() {
    // id
    expected_type_r(TokenType::Identifier, nullptr);
    auto ident = reinterpret_cast<const Identifier *>(current_token);
    next_token();

    // =
    expected_enum_type_r_e(predicate::is_eq, predicate::marker_eq, nullptr,
                           || predicate::is_var(current_token));
    next_token();

    // const exp
    auto decl = new ast::ConstDecl(ident, parse_const_exp(&predicate::predicateContainers.semicolonOrVarContainer));

    // ;
    expected_enum_type_r_e(predicate::is_semicolon, predicate::marker_semicolon, decl,
                           || predicate::is_var(current_token));
    next_token();

    return decl;
}