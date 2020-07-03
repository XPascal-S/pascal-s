//
// Created by kamiyoru on 2020/6/27.
//


#include <pascal-s/parser_recursive.h>

template<typename Lexer>
ast::ProgramHead *RecursiveParser<Lexer>::parse_program_head() {

    // program id
    auto program = reinterpret_cast<const Keyword *>(current_token);
    expected_enum_type(predicate::is_program, predicate::keyword_program);
    auto ident = reinterpret_cast<const Identifier *>(next_token());
    expected_type(TokenType::Identifier);
    next_token();

    // maybe ( id list )
    ast::IdentList *il = nullptr;
    if (predicate::is_lparen(current_token)) {
        il = parse_id_list_with_paren();
    }

    return new ast::ProgramHead(new ast::ExpKeyword(program), new ast::Ident(ident), il);
}
