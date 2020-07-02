//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::Program *Parser<Lexer>::parse_program() {

    auto program = new ast::Program(nullptr, nullptr);

    // program head
    program->programHead = parse_program_head();
    if (program->programHead == nullptr) {
        return program;
    }

    // ;
    expected_enum_type_r(predicate::is_semicolon, predicate::marker_semicolon, program);
    program->semicolon = reinterpret_cast<const Marker *>(current_token);
    next_token();

    // program body
    program->programBody = parse_program_body();
    if (program->programBody == nullptr) {
        return program;
    }

    return program;
}
