
#include <cstdio>
#include <pascal-s/interface.h>

#include <pascal-s/AST.h>
#define YYDEBUG 1
#include "parser.example.h"
#include <pascal-s/mock.h>
#include <vector>

void yy::parser::error(const std::string & msg) {
    std::cout << msg << std::endl;
}

template<typename Lexer>
class YACCParser : public yy::parser {
    LexerProxy<Lexer> lexer;

//    const Token* current_token;
public:
    explicit YACCParser(LexerProxy<Lexer> lexer) : lexer(lexer) {}

    Node * parsed_result;

private:
    int yylex(void ** current_token) override {
        auto token = lexer.next_token();
        (*current_token) = (void *)(token);
        if ((*current_token) == nullptr) {
            return 0;
        }

        return static_cast<int>(token->type);
    }

    void access_ast(void * ast) override {
        parsed_result = (Node*)ast;
    }
};

//  protected:
//      virtual int yylex(const Token**) = 0;
int main() {

    std::vector<Token*> mocking_stream{new ConstantInteger("1")};
    MockLexer lexer(mocking_stream);
    LexerProxy<MockLexer> lexer_proxy(lexer);

    YACCParser<MockLexer>  parser(lexer_proxy);

    parser.set_debug_level(1);

    auto res = parser.parse();

    for (auto tok :lexer.token_stream) {
        deleteToken(tok);
    }

    printf("parsed result: ");
    printAST(parser.parsed_result);
    deleteAST(parser.parsed_result);

    return res;
}


