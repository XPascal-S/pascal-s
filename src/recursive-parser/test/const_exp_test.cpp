
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


//struct ConstExpTest : public ParserTest {};
//
//PARSER_SUB_BASIC_TEST_P(ConstExpTest, parse_program_head)
//
//
//INSTANTIATE_TEST_SUITE_P(Simple, ConstExpTest, testing::Values( /* NOLINT */
//        ParserTestCase{
//                {
//                        new Keyword(KeywordType::Program),
//                        new Identifier("main"),
//                }
//        }
//));


struct ConstFacTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(ConstFacTest, parse_const_fac)


INSTANTIATE_TEST_SUITE_P(Simple, ConstFacTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new ConstantInteger(1),
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
        },
        ParserTestCase{
                {
                        new ConstantReal("1.", 1.),
                }
        }
));
