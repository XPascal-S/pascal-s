
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct TypeTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(TypeTest, parse_type)


INSTANTIATE_TEST_SUITE_P(Simple, TypeTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::Integer),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Real),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Char),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Boolean),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Array),
                        new Marker(MarkerType::LBracket),
                        new ConstantInteger(0),
                        new Marker(MarkerType::Range),
                        new ConstantInteger(1),
                        new Marker(MarkerType::RBracket),
                        new Keyword(KeywordType::Of),
                        new Keyword(KeywordType::Integer),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Array),
                        new Marker(MarkerType::LBracket),
                        new ConstantInteger(0),
                        new Marker(MarkerType::Range),
                        new ConstantInteger(1),
                        new Marker(MarkerType::Comma),
                        new ConstantInteger(0),
                        new Marker(MarkerType::Range),
                        new ConstantInteger(1),
                        new Marker(MarkerType::RBracket),
                        new Keyword(KeywordType::Of),
                        new Keyword(KeywordType::Integer),
                }
        }
));
