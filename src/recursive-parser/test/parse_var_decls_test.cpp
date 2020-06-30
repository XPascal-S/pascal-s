
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct VarDeclsTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(VarDeclsTest, parse_var_decls)


INSTANTIATE_TEST_SUITE_P(Simple, VarDeclsTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::Var),
                        new Identifier("a"),
                        new Marker(MarkerType::Colon),
                        new Keyword(KeywordType::Integer),
                        new Marker(MarkerType::Semicolon),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Var),
                        new Identifier("a"),
                        new Marker(MarkerType::Comma),
                        new Identifier("b"),
                        new Marker(MarkerType::Colon),
                        new Keyword(KeywordType::Integer),
                        new Marker(MarkerType::Semicolon),
                        new Identifier("c"),
                        new Marker(MarkerType::Colon),
                        new Keyword(KeywordType::Integer),
                        new Marker(MarkerType::Semicolon),
                }
        }
));
