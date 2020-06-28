
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct IdentListTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(IdentListTest, parse_param_list)


INSTANTIATE_TEST_SUITE_P(Simple, IdentListTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::Var),
                        new Identifier("a"),
                        new Marker(MarkerType::Colon),
                        new Keyword(KeywordType::Integer),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Var),
                        new Identifier("a"),
                        new Marker(MarkerType::Comma),
                        new Identifier("a"),
                        new Marker(MarkerType::Colon),
                        new Keyword(KeywordType::Real),
                        new Marker(MarkerType::Semicolon),
                        new Identifier("a"),
                        new Marker(MarkerType::Colon),
                        new Keyword(KeywordType::Boolean),
                }
        }
));
