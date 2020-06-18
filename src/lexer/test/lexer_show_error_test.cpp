
#include <gtest/gtest.h>
#include <pascal-s/lexer.h>
#include <pascal-s/features.h>

struct ShowErrorTestCase {
    const char *input;
    const char *expected;
};

class GoodShowErrorTest : public testing::TestWithParam<ShowErrorTestCase> {
};

class CFile {
    FILE *f;

public:
    explicit CFile(FILE *f) : f(f) {}
};

class CPPStreamFile {
    std::istream &f;

public:
    explicit CPPStreamFile(std::istream &f) : f(f) {}

    pascal_errno seek(size_t offset) {
        f.seekg(offset);
    }

    pascal_errno read(char *buf, size_t len) {
        f.read(buf, len);
    }
};

TEST_P(GoodShowErrorTest, WillNotThrowException) /* NOLINT */
{
    auto &param = GetParam();
    std::stringstream in(param.input);
    FullInMemoryLexer lexer(&in);

    lexer.get_all_tokens();
    ASSERT_TRUE(lexer.has_error());

    CPPStreamFile fin(in);
    FileProxy<CPPStreamFile> fp(fin);
    WriterProxy<std::ostream> os(std::cout);

    for (auto e : lexer.get_all_errors()) {
        feature::format_line_column_error(fp, ErrorProxy<ErrorToken>(*e), os);
    }
}

INSTANTIATE_TEST_SUITE_P(TestIdentifiers, GoodShowErrorTest, testing::Values( /* NOLINT */
        ShowErrorTestCase{"1a"},
        ShowErrorTestCase{"     1a"},
        ShowErrorTestCase{"     1a      "},
        ShowErrorTestCase{"     'xx'      "}
));
