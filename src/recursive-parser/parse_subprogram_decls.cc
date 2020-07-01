//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::SubprogramDecls *Parser<Lexer>::parse_subprogram_decls() {
    return _parse_subprogram_decls(new ast::SubprogramDecls);
}

template<typename Lexer>
ast::SubprogramDecls *Parser<Lexer>::_parse_subprogram_decls(ast::SubprogramDecls *decls) {

    // function head

    auto subprogram = new ast::Subprogram(nullptr, nullptr);
    decls->subprogram.push_back(subprogram);

    // subprogram head
    subprogram->subhead = parse_subprogram_head();
    if (subprogram->subhead == nullptr) {
        return decls;
    }

    // ;
    expected_enum_type_r(predicate::is_semicolon, predicate::marker_semicolon, decls);
    subprogram->semicolon = reinterpret_cast<const Marker *>(current_token);
    next_token();

    // subprogram body
    subprogram->subbody = parse_subprogram_body();
    if (subprogram->subbody == nullptr) {
        return decls;
    }

    // look ahead
    if (predicate::is_function(current_token) || predicate::is_procedure(current_token)) {
        return _parse_subprogram_decls(decls);
    }

    return decls;
}
