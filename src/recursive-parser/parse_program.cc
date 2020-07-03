//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::Program *Parser<Lexer>::parse_program() {

    // program head
    auto ph = parse_program_head();
    if (ph == nullptr) {
        return nullptr;
    }

    // ;
    expected_enum_type_r(predicate::is_semicolon, predicate::marker_semicolon,
                         new ast::Program(ph, nullptr));
    auto semicolon = reinterpret_cast<const Marker *>(current_token);
    next_token();

    // program body
    auto program = new ast::Program(ph, parse_program_body());
    program->semicolon = semicolon;

    // ;
    expected_enum_type_r(predicate::is_dot, predicate::marker_dot, program);
    program->dot = reinterpret_cast<const Marker *>(current_token);
    next_token();

    return program;
}
