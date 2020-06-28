
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct FacTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(FacTest, parse_fac)


INSTANTIATE_TEST_SUITE_P(ConstFac, FacTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new ConstantInteger(1),
                }
        },
        ParserTestCase{
                {
                        new ConstantReal("1.", 1.),
                }
        },
        ParserTestCase{
                {
                        new ConstantBoolean(true),
                }
        },
        ParserTestCase{
                {
                        new ConstantChar('a'),
                }
        }
));

INSTANTIATE_TEST_SUITE_P(Simple, FacTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::LParen),
                        new Marker(MarkerType::RParen),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::LParen),
                        new Identifier("a"),
                        new Marker(MarkerType::RParen),
                }
        },
        ParserTestCase{
                {
                        new Marker(MarkerType::LParen),
                        new Identifier("a"),
                        new Marker(MarkerType::RParen),
                }
        }
));


INSTANTIATE_TEST_SUITE_P(Variable, FacTest, testing::Values( /* NOLINT */
// todo: id [ expression_list ]
        ParserTestCase{
                {
                        new Identifier("a"),
                }
        }
));


struct ExpTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(ExpTest, parse_exp)

INSTANTIATE_TEST_SUITE_P(Assign, ExpTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Add),
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                        new Marker(MarkerType::Add),
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Assign),
                        new Identifier("a"),
                        new Marker(MarkerType::Add),
                        new Identifier("a"),
                }
        }
));

INSTANTIATE_TEST_SUITE_P(Arithmetic, ExpTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Add),
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Mul),
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Add),
                        new Identifier("a"),
                        new Marker(MarkerType::LE),
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::LE),
                        new Identifier("a"),
                        new Marker(MarkerType::Add),
                        new Identifier("a"),
                }
        }
));

