#ifndef YACC_PARSER_H
#define YACC_PARSER_H

#define YYDEBUG 1

#include <pascal-s/llvm-ast.h>
#include <pascal-s/parser.h>
#include <pascal-s/yacc_bison.h>
#include <cstdio>
#include <pascal-s/interface.h>
#include <pascal-s/mock.h>
#include <vector>
#include <string>
#include <iostream>

#define KEYWORDTYPE(type) (0x100 | (int)type)
#define MARKERTYPE(type) (0x200 | (int)type)

void yy::parser::error(const std::string &msg) {
    std::cout << msg << std::endl;
}

template<typename Lexer>
class YaccParser_yy : public yy::parser {
    LexerProxy<Lexer> lexer;
    //    const Token* current_token;
public:
    explicit YaccParser_yy(LexerProxy<Lexer> lexer) : lexer(lexer) {}

    ast::Node *parsed_result;
    // Node *ast_root;

    std::vector<ast::Node *> astTreeStack;

private:
    int yylex(void **current_token) override {
        auto token = lexer.next_token();
        (*current_token) = (void *) (token);
        if ((*current_token) == nullptr) {
            return 0;
        }
        switch (token->type) {
            case TokenType::Keyword: {
                const Keyword *keyword_token = reinterpret_cast<const Keyword *>(token);
                // printf("\ntoken keyword: %x %s\n",
                //        static_cast<int>(KEYWORDTYPE(keyword_token->key_type)), convertToString(keyword_token).c_str());
                return static_cast<int>(KEYWORDTYPE(keyword_token->key_type));
            }
            case TokenType::Marker: {
                const Marker *marker_token = reinterpret_cast<const Marker *>(token);
                // printf("\ntoken marker: %x %s\n",
                //        static_cast<int>(MARKERTYPE(marker_token->marker_type)), convertToString(marker_token).c_str());
                return static_cast<int>(MARKERTYPE(marker_token->marker_type));
            }
            default:
                // printf("\ndefault token: %d %s\n", token->type, convertToString(token).c_str());
                return static_cast<int>(token->type);
        }
        return static_cast<int>(token->type);
    }

    void access_ast(void *ast) override {
        // parsed_result = (ast::Program *) ast;
        parsed_result = reinterpret_cast<ast::Node*>(ast);
    }
};

template<typename Lexer>
class YaccParser : public Parser {
    YaccParser_yy<Lexer> yyparser;
public:
    std::vector<PascalSError *> errors;

    explicit YaccParser(LexerProxy<Lexer> lexer) : yyparser(lexer) {}

    virtual ~YaccParser() override;

    ast::Node *parse() {
      // assert(yyparser.parse() == 0);
      if( yyparser.parse() != 0 ){
        yyparser.parsed_result = nullptr;
      }
      return yyparser.parsed_result;
    }

    bool has_error() {
        return !errors.empty();
    }

    const std::vector<PascalSError *> &get_all_errors() {
        return errors;
    }
};

#endif
