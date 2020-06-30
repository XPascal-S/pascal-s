//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::ProgramHead *Parser<Lexer>::parse_program_head() {

    // program id
    auto program = reinterpret_cast<const Keyword *>(current_token);
    expected_enum_type(predicate::is_program, predicate::keyword_program);
    auto ident = reinterpret_cast<const Identifier *>(next_token());
    expected_type(TokenType::Identifier);
    next_token();

    ast::ProgramHead *hd = new ast::ProgramHead(new ast::ExpKeyword(program), new ast::Ident(ident), nullptr);

    // maybe ( id list )
    if (predicate::is_lparen(current_token)) {
        hd->idlist = parse_id_list_with_paren();
    }

    return hd;
}
