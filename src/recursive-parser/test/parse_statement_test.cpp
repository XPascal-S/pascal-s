
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct StatementTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(StatementTest, parse_statement)


INSTANTIATE_TEST_SUITE_P(Expression, StatementTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                }
        }
));


INSTANTIATE_TEST_SUITE_P(CompoundStatement, StatementTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::Begin),
                        new Identifier("a"),
                        new Keyword(KeywordType::End),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::Begin),
                        new Identifier("a"),
                        new Marker(MarkerType::Semicolon),
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                        new Marker(MarkerType::Semicolon),
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                        new Marker(MarkerType::LParen),
                        new Marker(MarkerType::RParen),
                        new Marker(MarkerType::Semicolon),
                        new Identifier("a"),
                        new Keyword(KeywordType::End),
                }
        }
));


INSTANTIATE_TEST_SUITE_P(ForStatement, StatementTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::For),
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                        new Keyword(KeywordType::To),
                        new Identifier("a"),
                        new Keyword(KeywordType::Do),
                        new Identifier("a"),
                }
        }
));


INSTANTIATE_TEST_SUITE_P(IfElseStatement, StatementTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Keyword(KeywordType::If),
                        new Identifier("a"),
                        new Keyword(KeywordType::Then),
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Keyword(KeywordType::If),
                        new Identifier("a"),
                        new Keyword(KeywordType::Then),
                        new Keyword(KeywordType::For),
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                        new Keyword(KeywordType::To),
                        new Identifier("a"),
                        new Keyword(KeywordType::Do),
                        new Identifier("a"),
                        new Keyword(KeywordType::Else),
                        new Identifier("a"),
                }
        }
));
