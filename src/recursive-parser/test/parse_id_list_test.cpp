
//
// Created by kamiyoru on 2020/6/27.
//


#include "parser_test_helper.h"


struct IdentListTest : public ParserTest {
};

PARSER_SUB_BASIC_TEST_P(IdentListTest, parse_id_list)


INSTANTIATE_TEST_SUITE_P(Simple, IdentListTest, testing::Values( /* NOLINT */
        ParserTestCase{
                {
                        new Identifier("a"),
                }
        },
        ParserTestCase{
                {
                        new Identifier("a"),
                        new Marker(MarkerType::Comma),
                        new Identifier("a"),
                }
        }
));
