
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct ConstDeclsTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(ConstDeclsTest, parse_const_decls)


INSTANTIATE_TEST_SUITE_P(Simple, ConstDeclsTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::Const),
                        new Identifier("a"),
                        new Marker(MarkerType::EQ),
                        new ConstantInteger(1),
                        new Marker(MarkerType::Semicolon),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Const),
                        new Identifier("a"),
                        new Marker(MarkerType::EQ),
                        new ConstantInteger(1),
                        new Marker(MarkerType::Semicolon),
                        new Identifier("a"),
                        new Marker(MarkerType::EQ),
                        new ConstantInteger(2),
                        new Marker(MarkerType::Semicolon),
                }
        }
));
