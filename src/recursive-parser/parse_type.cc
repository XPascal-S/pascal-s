//
// Created by kamiyoru on 2020/6/27.
//


template<typename Lexer>
ast::TypeSpec *Parser<Lexer>::parse_type() {
    // next token == array | basic_type, all belong to keyword
    if (current_token == nullptr || current_token->type != TokenType::Keyword) {
        errors.push_back(new PascalSParseExpectSGotError(__FUNCTION__, "type spec", current_token));
        return nullptr;
    }


    auto array_or_basic = reinterpret_cast<const Keyword *>(current_token);

    // array
    if (array_or_basic->key_type == KeywordType::Array) {
        next_token();
        return parse_array_type(array_or_basic);
    } else if (
        // basic type
            array_or_basic->key_type == KeywordType::Integer ||
            array_or_basic->key_type == KeywordType::Real ||
            array_or_basic->key_type == KeywordType::Char ||
            array_or_basic->key_type == KeywordType::Boolean
            ) {
        next_token();
        return new ast::BasicTypeSpec(array_or_basic);
    }
    errors.push_back(new PascalSParseExpectSGotError(__FUNCTION__, "basic type spec", array_or_basic));
    return nullptr;
}

template<typename Lexer>
ast::ArrayTypeSpec *Parser<Lexer>::parse_array_type(const Keyword *keyword_array) {
    auto arr_type_spec = new ast::ArrayTypeSpec(keyword_array);

    // [
    expected_enum_type_r(predicate::is_lbracket, predicate::marker_lbracket, arr_type_spec);
    next_token();


    // digit
    for (;;) {

        // digit
        expected_type_r(TokenType::ConstantInteger, arr_type_spec);
        auto l_range = reinterpret_cast<const ConstantInteger *>(current_token);
        next_token();

        // ..
        expected_enum_type_r(predicate::is_range, predicate::marker_range, arr_type_spec);
        next_token();

        // digit
        expected_type_r(TokenType::ConstantInteger, arr_type_spec);
        arr_type_spec->periods.emplace_back(
                int64_t(l_range->attr),
                int64_t(reinterpret_cast<const ConstantInteger *>(current_token)->attr));
        next_token();

        // ,
        if (!predicate::is_comma(current_token)) {
            break;
        }
        next_token();
    }

    // ]
    expected_enum_type_r(predicate::is_rbracket, predicate::marker_rbracket, arr_type_spec);
    next_token();

    // of
    expected_enum_type_r(predicate::is_of, predicate::keyword_of, arr_type_spec);
    next_token();

    // basic_type
    auto basic = reinterpret_cast<const Keyword *>(current_token);
    if (
            basic->key_type == KeywordType::Integer ||
            basic->key_type == KeywordType::Real ||
            basic->key_type == KeywordType::Char ||
            basic->key_type == KeywordType::Boolean
            ) {
        next_token();
        arr_type_spec->keyword = basic;
        return arr_type_spec;
    }

    errors.push_back(new PascalSParseExpectSGotError(__FUNCTION__, "basic type spec", basic));
    return nullptr;
}
