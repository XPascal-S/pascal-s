

#include <pascal-s/exception.h>
#include <pascal-s/token.h>
#include <pascal-s/llvm-ast.h>
#include <fmt/core.h>
#include <pascal-s/interface.h>


RuntimeReinterpretTokenException::RuntimeReinterpretTokenException(const Token *token)
        : token(token), msg(fmt::format("runtime reinterpret token error: unknown type: {}", token->type)) {
}

const char *RuntimeReinterpretTokenException::what() const noexcept {
    return msg.c_str();
}

RuntimeReinterpretASTException::RuntimeReinterpretASTException(const ast::Node *node)
        : node(node), msg(fmt::format("runtime reinterpret node error: unknown type: {}", node->type)) {

}

const char *RuntimeReinterpretASTException::what() const noexcept {
    return msg.c_str();
}

PascalSParseExpectVGotError::PascalSParseExpectVGotError(char *fn, const Token *expected, const Token *got,
                                                         std::string msg) :
        PascalSParseError(fn, fmt::format("{} parse failed: "
                                          "expected: {}, "
                                          "got: {}", fn, convertToString(expected), convertToString(got)),
                          PascalSErrno::ParseExpectVGotError), expected(expected), got(got) {
    if (!msg.empty()) {
        this->msg += ":" + msg;
    }
    this->length = got->length;
    this->offset = got->offset;
    this->line = got->line;
    this->column = got->column;
}

PascalSParseExpectTGotError::PascalSParseExpectTGotError(
        char *fn, TokenType expected, const Token *got, std::string msg) :
        PascalSParseError(fn,
                          fmt::format("{} parse failed: "
                                      "expected type: {}, "
                                      "got: {}", fn, convertToString(expected), convertToString(got)),
                          PascalSErrno::ParseExpectTGotError),
        expected(static_cast<pascal_s::token_type_underlying_type>(expected)), got(got) {
    if (!msg.empty()) {
        this->msg += ":" + msg;
    }
    this->length = got->length;
    this->offset = got->offset;
    this->line = got->line;
    this->column = got->column;
}

PascalSParseExpectSGotError::PascalSParseExpectSGotError(
        char *fn, const char *expected, const Token *got, std::string msg) :
        PascalSParseError(fn, "",
                          PascalSErrno::ParseExpectSGotError), expected(expected), got(got) {
    this->msg = fmt::format("{} parse failed: "
                            "expected: {}, "
                            "got: {}", fn, expected, convertToString(got));
    if (!msg.empty()) {
        this->msg += ":" + msg;
    }
    this->length = got->length;
    this->offset = got->offset;
    this->line = got->line;
    this->column = got->column;
}
