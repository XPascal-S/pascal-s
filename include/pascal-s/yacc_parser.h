#ifndef YACC_PARSER_H
#define YACC_PARSER_H

#define YYDEBUG 1
#include <pascal-s/yacc_ast.h>
#include <pascal-s/yacc_bison.h>
#include <pascal-s/parser.h>
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

void yy::parser::access_ast(void *ast) {
  parsed_result = (Node*)ast;
}



template <typename Lexer> class YACCParser {
  LexerProxy<Lexer> lexer;
  //    const Token* current_token;

  yy::parser yyparser;
public:
  explicit YACCParser(LexerProxy<Lexer> lexer) : lexer(lexer) {
    yyparser = yy::parser();
  }

  Node *parsed_result = nullptr;
  // Node *ast_root;

  std::vector<Node *> astTreeStack;

  std::vector<PascalSError *> errors;
  bool has_error(){
      return !errors.empty();
  }

  [[maybe_unused]] const std::vector<PascalSError *> &get_all_errors() {
    return errors;
  }


  int yy::parser::yylex(void **current_token) {
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

  Node* parse(){
    yyparser.parse();
    return parsed_result;
  }

// private:
//   Node* ast_reduce_nodes(int k, Type type) override {
//     if (astTreeStack.size() < k) {
//       // Node* errNode = astTreeStack.back();
//       // throw RuntimeReinterpretASTException(*errNode);
//     }
//     Node *par_node = new Node(type);
//     for (int i = 0; i < k; ++i) {
//       Node *n = astTreeStack.back();
//       astTreeStack.pop_back();
//       par_node->children.push_back(n);
//     }
//     reverse(par_node->children.begin(), par_node->children.end());
//     astTreeStack.push_back(par_node);
//     ast_root = par_node;
//     // printAST(ast_root);
//     return par_node;
//   }
};

#endif
