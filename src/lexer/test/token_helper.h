//
// Created by kamiyoru on 2020/4/30.
//

#ifndef PASCAL_S_TOKEN_HELPER_H
#define PASCAL_S_TOKEN_HELPER_H

#include <pascal-s/token.h>
#include <gtest/gtest.h>
#include <fmt/core.h>

#define ASSERT_TOKEN_EQUAL(val1, val2)\
    ASSERT_PRED_FORMAT2(CompareToken, val1, val2)
//
//ASSERT_EQ(tok->type, TokenType::Identifier);
//ASSERT_STREQ(reinterpret_cast<const Identifier*>(tok)->content, param.expected);


testing::Message &operator<<(testing::Message &msg, const Token *tok) {
    return msg << convertToString(tok);
}

#define equal_field(val1, val2) do{if (val1 != val2) {\
    return internal::CmpHelperEQFailure(lhs_expression, rhs_expression, lhs, rhs);\
}}while(0)

#define str_equal_field(val1, val2) do{if (std::string(val1) != val2) {\
    return internal::CmpHelperEQFailure(lhs_expression, rhs_expression, lhs, rhs);\
}}while(0)

static testing::AssertionResult CompareIdentifier(const char *lhs_expression,
                                                  const char *rhs_expression, const Identifier *lhs,
                                                  const Identifier *rhs) {
    using namespace testing;

    str_equal_field(lhs->content, rhs->content);

    return AssertionSuccess();
}


static testing::AssertionResult
CompareMarker(const char *lhs_expression, const char *rhs_expression, const Marker *lhs, const Marker *rhs) {
    using namespace testing;

    str_equal_field(lhs->content, lhs->content);

    return AssertionSuccess();
}

static testing::AssertionResult CompareToken(const char *lhs_expression,
                                             const char *rhs_expression, const Token *lhs,
                                             const Token *rhs) {
    using namespace testing;
    equal_field(lhs->type, rhs->type);
    switch (lhs->type) {
        case TokenType::Identifier:
            return CompareIdentifier(lhs_expression, rhs_expression,
                                     reinterpret_cast<const Identifier *>(lhs),
                                     reinterpret_cast<const Identifier *>(rhs));
        case TokenType::Marker:
            return CompareMarker(lhs_expression, rhs_expression,
                                     reinterpret_cast<const Marker *>(lhs),
                                     reinterpret_cast<const Marker *>(rhs));
        default:
            return AssertionFailure() << fmt::format("unknown token type {}", lhs->type);
    }
    assert(false);
}


#undef equal_field

#endif //PASCAL_S_TOKEN_HELPER_H