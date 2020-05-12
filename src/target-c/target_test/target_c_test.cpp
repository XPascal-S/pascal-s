
#include <gtest/gtest.h>
#include <target/c.h>


struct TranslateTestCase {
    const Node *node;
    const char *expected;
};

class GoodTranslateTest : public testing::TestWithParam<TranslateTestCase> {

    void TearDown() override {

        delete GetParam().node;
    }
};

TEST_P(GoodTranslateTest, WillNotThrowException) /* NOLINT */
{
    auto &param = GetParam();
    std::vector<std::string> files{"cstdio"};
    std::stringstream str_buf;
    target_c::Buffer buf(str_buf);
    target_c::CBuilder builder(files, buf);

    builder.code_gen(param.node);

    ASSERT_STREQ(param.expected, str_buf.str().c_str());
}

INSTANTIATE_TEST_SUITE_P(TestIdentifiers, GoodTranslateTest, testing::Values( /* NOLINT */
        TranslateTestCase{new Program(nullptr, new Identifier("my_program"), nullptr),
                          "#include <cstdio>\n"
                          "int my_program(){\n"
                          "printf(\"hello world\");\n"
                          "}\n"
                          "int main(){\n"
                          "return my_program();\n"
                          "}\n"}
));
