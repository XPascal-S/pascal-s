//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::Procedure *Parser<Lexer>::parse_function_head() {
    // keyword procedure or function
    auto fn_def = reinterpret_cast<const Keyword *>(current_token);

    // id
    auto ident = reinterpret_cast<const Identifier *>(next_token());
    expected_type(TokenType::Identifier);
    next_token();

    // share common struct type Procedure
    auto proc = new ast::Procedure(fn_def, ident);

    // param list
    if (predicate::is_lparen(current_token)) {
        proc->params = parse_param_list_with_paren();
        if (proc->params == nullptr) {
            delete proc;
            return nullptr;
        }
    }

    return proc;
}

