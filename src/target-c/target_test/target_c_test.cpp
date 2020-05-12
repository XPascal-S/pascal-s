
#include <gtest/gtest.h>
#include <target/c.h>


struct TranslateTestCase {
    const char *input;
    const char *expected;
};

class GoodTranslateTest : public testing::TestWithParam<TranslateTestCase> {
};

TEST_P(GoodTranslateTest, WillNotThrowException) /* NOLINT */
{
    std::vector<std::string> files{"cstdio"};
    target_c::CBuilder builder(files);
    target_c::Buffer buf(std::cout);
    builder.code_gen(nullptr, buf);
}

INSTANTIATE_TEST_SUITE_P(TestIdentifiers, GoodTranslateTest, testing::Values( /* NOLINT */
        TranslateTestCase{"a {a}", "a"}
));
