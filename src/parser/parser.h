#ifndef PARSER_H
#define PARSER_H

#define YYDEBUG 1
#include "parser.example.h"
#include <cstdio>
#include <pascal-s/interface.h>
#include <pascal-s/mock.h>
#include <vector>
#include <string>
#include <iostream>

#define KEYWORDTYPE(type) (0x100 | (int)type)
#define MARKERTYPE(type) (0x200 | (int)type)

void yy::parser::error(const std::string & msg) {
    std::cout << msg << std::endl;
}

template <typename Lexer> class YACCParser : public yy::parser {
  LexerProxy<Lexer> lexer;
  //    const Token* current_token;
public:
  explicit YACCParser(LexerProxy<Lexer> lexer) : lexer(lexer) {}

  Node *parsed_result;
  // Node *ast_root;

  std::vector<Node *> astTreeStack;

private:
  int yylex(void **current_token) override {
    auto token = lexer.next_token();
    (*current_token) = (void *)(token);
    if ((*current_token) == nullptr) {
      return 0;
    }
    switch (token->type) {
    case TokenType::Keyword: {
      const Keyword* keyword_token = reinterpret_cast<const Keyword *>(token);
      printf("\ntoken keyword: %x\n",
             static_cast<int>(KEYWORDTYPE(keyword_token->key_type)));
      return static_cast<int>(KEYWORDTYPE(keyword_token->key_type));
    }
    case TokenType::Marker: {
      const Marker* marker_token = reinterpret_cast<const Marker *>(token);
        printf("\ntoken marker: %x\n",
               static_cast<int>(MARKERTYPE(marker_token->marker_type)));
        return static_cast<int>(MARKERTYPE(marker_token->marker_type));
    }
        default:
            return static_cast<int>(token->type);
    }
      return static_cast<int>(token->type);
  }

    void access_ast(void *ast) override {
        parsed_result = (Node *) ast;
    }

    Node *ast_reduce_nodes(int k, Type type) override {
        // if (astTreeStack.size() < k) {
        //   // Node* errNode = astTreeStack.back();
        //   // throw RuntimeReinterpretASTException(*errNode);
        // }
        // Node *par_node = new Node(type);
        // for (int i = 0; i < k; ++i) {
        //   Node *n = astTreeStack.back();
    //   astTreeStack.pop_back();
    //   par_node->children.push_back(n);
    // }
    // reverse(par_node->children.begin(), par_node->children.end());
    // astTreeStack.push_back(par_node);
    // ast_root = par_node;
    // // printAST(ast_root);
    // return par_node;
  }
};

#endif
