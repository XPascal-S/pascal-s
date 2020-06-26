//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::FunctionDecls *Parser<Lexer>::parse_function_decls() {

    // look ahead
    if (predicate::is_function(current_token) || predicate::is_procedure(current_token)) {

        // procedure or function
        return _parse_function_decls(new ast::FunctionDecls);
    }
    return nullptr;
}

template<typename Lexer>
ast::FunctionDecls *Parser<Lexer>::_parse_function_decls(ast::FunctionDecls *decls) {

    // function head
    ast::Procedure *proc = parse_function_head();
    if (proc == nullptr) {
        return decls;
    }

    // function should with type
    if (predicate::is_function(proc->fn_def)) {

        // :
        expected_enum_type_r(predicate::is_colon, predicate::marker_colon, decls);
        next_token();

        // basic type
        auto basic = reinterpret_cast<const Keyword *>(current_token);
        if (
                basic->key_type == KeywordType::Integer ||
                basic->key_type == KeywordType::Real ||
                basic->key_type == KeywordType::Char ||
                basic->key_type == KeywordType::Boolean
                ) {
            next_token();
            proc->return_type = new ast::BasicTypeSpec(basic);
        } else {
            errors.push_back(new PascalSParseExpectSGotError(__FUNCTION__, "basic type spec", basic));
            delete proc;
            return decls;
        }
    }

    // ;
    expected_enum_type_r(predicate::is_semicolon, predicate::marker_semicolon, decls);
    next_token();

    // function body
    proc = parse_function_body(proc);
    if (proc != nullptr) {
        decls->decls.push_back(proc);
    }

    // look ahead
    if (predicate::is_function(current_token) || predicate::is_procedure(current_token)) {
        return _parse_function_decls(decls);
    }

    return decls;
}
