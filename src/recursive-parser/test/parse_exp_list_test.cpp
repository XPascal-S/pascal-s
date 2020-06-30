
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct ExpressionListWithParenTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(ExpressionListWithParenTest, parse_expression_list_with_paren)


INSTANTIATE_TEST_SUITE_P(Simple, ExpressionListWithParenTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Marker(MarkerType::LParen),
                        new ConstantChar('h'),
                        new Marker(MarkerType::RParen),
                }
        },
        ParserTestCase{
                {
                        new Marker(MarkerType::LParen),
                        new ConstantChar('h'),
                        new Marker(MarkerType::Comma),
                        new ConstantChar('h'),
                        new Marker(MarkerType::RParen),
                }
        },
        ParserTestCase{
                {
                        new Marker(MarkerType::LParen),
                        new ConstantChar('h'),
                        new Marker(MarkerType::Add),
                        new ConstantChar('h'),
                        new Marker(MarkerType::Comma),
                        new ConstantChar('h'),
                        new Marker(MarkerType::RParen),
                }
        }
));
