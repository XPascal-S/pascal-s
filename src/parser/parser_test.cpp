
#include <cstdio>
#include <pascal-s/interface.h>

#include <pascal-s/AST.h>
#define YYDEBUG 1
#include "parser.example.h"
#include <pascal-s/mock.h>
#include <vector>
#include <string>
#include <iostream>

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
    Node * ast_root;

    std::deque<Node *> astTreeStack;

private:
    int yylex(void ** current_token) override {
        auto token = lexer.next_token();
        (*current_token) = (void *)(token);
        if ((*current_token) == nullptr) {
            return 0;
        }

        return static_cast<int>(token->type);
    }

    // void access_ast(void * ast) override {
    //     parsed_result = (Node*)ast;
    // }
    void access_ast(void *leaf_node) override {
      astTreeStack.push_back((Node *)leaf_node);
    }
    // void ast_insert_leaf_node(void * leaf_node) {
    //   astTreeStack.push_back((Node *)leaf_node);
    // }

    void ast_reduce_nodes(int k, Type type) override {
      printf("size: %d k %d\n", astTreeStack.size(), k);
      if( astTreeStack.size()<k ){
        throw RuntimeReinterpretASTException(astTreeStack.back());
      }
      Node *par_node = new Node(type);
      for(int i=0;i<k;++i){
        Node* n = astTreeStack.back(); astTreeStack.pop_back();
        par_node->children.push_front(n);
      }
      astTreeStack.push_back(par_node);
      ast_root = par_node;
      printf("size: %d k %d\n", astTreeStack.size(), k);
    }


};

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
                                      new Identifier("i"),
                                      new Marker(MarkerType::Add),
                                      new Identifier("i"),
                                      new Marker(MarkerType::Sub),
                                      new ConstantInteger("1")
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

  for (auto tok : lexer.token_stream) {
    deleteToken(tok);
    }

    printf("parsed result: ");
    // printAST(parser.parsed_result);
    // deleteAST(parser.parsed_result);
    printAST(parser.ast_root);
    // deleteAST(parser.ast_root);
    return res;
}
