//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::SubprogramHead *Parser<Lexer>::parse_subprogram_head() {

    // keyword procedure or function
    if (!predicate::is_procedure(current_token) || !predicate::is_function(current_token)) {
        errors.push_back(new PascalSParseExpectTGotError(__FUNCTION__, TokenType::Function, current_token));
        return nullptr;
    }
    auto fn_def = reinterpret_cast<const Keyword *>(current_token);
    next_token();

    // id
    auto ident = reinterpret_cast<const Identifier *>(current_token);
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

    // function should with type
    if (predicate::is_function(fn_def)) {

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


    return proc;
}

