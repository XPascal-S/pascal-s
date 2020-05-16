
#include <cstdio>
#include <pascal-s/interface.h>

#include <pascal-s/AST.h>
#include "parser.h"
#include <pascal-s/mock.h>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

//  protected:
//      virtual int yylex(const Token**) = 0;

void simple_printAST(Node * n, int d){
  printf("ast node type %d %d\n",n->type, d);
  for (Node *c : n->children) {
    simple_printAST(c, d +1);
  }
}

int main() {
  // std::vector<Token*> mocking_stream{new ConstantInteger("1")};

  // const char c = 't';
  // std::vector<Token *> mocking_stream{new ConstantChar(&c)};
  // std::vector<Token *> mocking_stream{new ConstantReal("1.0")};
  std::vector<Token *> mocking_stream{
                                      new Keyword("If",KeywordType::If),
                                      new Identifier("i"),
                                      new Marker("=", MarkerType::EQ),
                                      new ConstantInteger("1"),
                                      new Keyword("Then", KeywordType::Then),
                                      new Identifier("i"),
                                      new Marker("=", MarkerType::EQ),
                                      new Identifier("i"),
                                      new Marker("*", MarkerType::Mul),
                                      new Identifier("i"),
                                      new Marker("-", MarkerType::Sub),
                                      new ConstantInteger("1"),
                                      new Keyword("Else", KeywordType::Else),
                                      new Identifier("i"),
                                      new Marker("=", MarkerType::EQ),
                                      new ConstantInteger("-1")
                                      // new Identifier("="),
                                      // new ConstantInteger("1"),
                                      // new Identifier("i"),
                                      // new Keyword(KeywordType::Length)
  };

  MockLexer lexer(mocking_stream);
  LexerProxy<MockLexer> lexer_proxy(lexer);

  YACCParser<MockLexer> parser(lexer_proxy);

  parser.set_debug_level(1);

  auto res = parser.parse();


  printf("parsed result: ");
  // printAST(parser.parsed_result);
  // deleteAST(parser.parsed_result);
  // printf("parser stack: %d\n", parser.astTreeStack.size());
  printAST(parser.ast_root);

  for (auto tok : lexer.token_stream) {
    deleteToken(tok);
  }
  // deleteAST(parser.ast_root);
  return res;
}
