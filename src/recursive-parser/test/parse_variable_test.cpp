
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct VariableTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(VariableTest, parse_variable)


INSTANTIATE_TEST_SUITE_P(Simple, VariableTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::LBracket),
                        new Identifier("a"),
                        new Marker(MarkerType::RBracket),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::LBracket),
                        new Identifier("a"),
                        new Marker(MarkerType::Comma),
                        new Identifier("a"),
                        new Marker(MarkerType::LBracket),
                        new Identifier("a"),
                        new Marker(MarkerType::RBracket),
                        new Marker(MarkerType::RBracket),
                }
        }
));
