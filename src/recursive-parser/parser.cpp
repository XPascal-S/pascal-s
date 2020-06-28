//
// Created by kamiyoru on 2020/5/8.
//

#include <pascal-s/mock.h>
#include <pascal-s/parser.h>
#include <set>
#include <fmt/core.h>

#ifdef WITH_MOCK
template
struct Parser<MockLexer>;
#endif

#ifdef WITH_PASCAL_LEXER_FILES
#include <pascal-s/lexer.h>
template
struct Parser<FullInMemoryLexer>;
#endif

#define expected_enum_type(predicator, indicate) do {if (!predicator(current_token)) {\
    errors.push_back(new PascalSParseExpectGotError(__FUNCTION__, &indicate, current_token));\
    return nullptr;\
}}while(0)

#define expected_enum_type_r(predicator, indicate, rvalue) do {if (!predicator(current_token)) {\
    errors.push_back(new PascalSParseExpectGotError(__FUNCTION__, &indicate, current_token));\
    return rvalue;\
}}while(0)

#define expected_type_r(tok_type, rvalue) do {if (current_token == nullptr || current_token->type != tok_type) {\
    errors.push_back(new PascalSParseExpectTGotError(__FUNCTION__, tok_type, current_token));\
    return rvalue;\
}}while(0)

#define expected_type(tok_type) expected_type_r(tok_type, nullptr)

namespace predicate {
    struct _parserPredicateContainer {
        const std::set<const Token *> rParenContainer;
        const std::set<const Token *> semicolonContainer;
        const std::vector<Token *> thenContainer;
        const std::vector<Token *> elseContainer;
        const std::vector<Token *> endOrSemicolonContainer;
        const std::set<const Token *> commaOrRParenContainer;
        const std::vector<Token *> endOrSemicolonOrElseContainer;


        explicit _parserPredicateContainer() noexcept:
                rParenContainer(
                        {
                                reinterpret_cast<const Token *>(&predicate::marker_rparen)
                        }),
                semicolonContainer(
                        {
                                reinterpret_cast<const Token *>(&predicate::marker_semicolon)
                        }),
                thenContainer(
                        {
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::keyword_then))
                        }),
                elseContainer(
                        {
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::keyword_else))
                        }),
                endOrSemicolonContainer(
                        {
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::marker_semicolon)),
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::keyword_end)),
                        }),
                commaOrRParenContainer(
                        {
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::marker_comma)),
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::marker_rparen)),
                        }),
                endOrSemicolonOrElseContainer(
                        {
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::marker_comma)),
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::marker_rparen)),
                                const_cast<Token *>(reinterpret_cast<const Token *>(&predicate::keyword_else)),
                        }) {
        }
    } predicateContainers;
}

template<typename Lexer>
Parser<Lexer>::Parser(LexerProxy <Lexer> lexer) : lexer(std::move(lexer)) {}

template<typename Lexer>
const Token *Parser<Lexer>::next_token() {
    current_token = lexer.next_token();
    return current_token;
}

template<typename Lexer>
ast::Node *Parser<Lexer>::parse() {
    next_token();
    return parse_program();
}


#include "parse_program.cc"
#include "parse_program_head.cc"
#include "parse_program_body.cc"

//#include "parse_subprogram.cc"
//#include "parse_subprogram_head.cc"
//#include "parse_subprogram_body.cc"

#include "parse_const_decls.cc"
#include "parse_var_decls.cc"

#include "parse_id_list.cc"
#include "parse_expression_list.cc"
#include "parse_param_list.cc"
#include "parse_type.cc"
#include "parse_const_exp.cc"
#include "parse_exp.cc"
#include "parse_statement.cc"

#undef expected_keyword
#undef expected_enum_type
#undef expected_enum_type_r
#undef expected_type_r
#undef expected_type