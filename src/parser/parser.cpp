#include <cstring>
#include <iostream>
#include <pascal-s/interface.h>

#include <pascal-s/yacc_ast.h>
#include <pascal-s/yacc_parser.h>
#include <pascal-s/mock.h>


// int TestExample() {
//   // std::vector<Token*> mocking_stream{new ConstantInteger("1")};

//   // const char c = 't';
//   // std::vector<Token *> mocking_stream{new ConstantChar(&c)};
//   // std::vector<Token *> mocking_stream{new ConstantReal("1.0")};
//   std::vector<Token *> mocking_stream{
//                                       new Keyword(KeywordType::Program),
//                                       new Identifier("test"),
//                                       new Marker(MarkerType::Semicolon),
//                                       new Keyword(KeywordType::Const),
//                                       new Identifier("a"),
//                                       new Marker(MarkerType::EQ),
//                                       new ConstantInteger(2),
//                                       new Marker(MarkerType::Semicolon),
//                                       new Keyword(KeywordType::Var),
//                                       new Identifier("b"),
//                                       new Marker(MarkerType::Colon),
//                                       new Keyword(KeywordType::Integer),
//                                       new Marker(MarkerType::Semicolon),
//                                       new Keyword(KeywordType::Begin),
//                                       new Keyword(KeywordType::End),
//                                       new Marker(MarkerType::Dot)
//   };

//   MockLexer lexer(mocking_stream);
//   LexerProxy<MockLexer> lexer_proxy(lexer);

//   YACCParser<MockLexer> parser(lexer_proxy);

//   parser.set_debug_level(1);

//   auto res = parser.parse();

//   printf("parsed result: ");
//   // printAST(parser.parsed_result);
//   // deleteAST(parser.parsed_result);
//   // printf("parser stack: %d\n", parser.astTreeStack.size());
//   // printAST(parser.ast_root);

//   for (auto tok : lexer.token_stream) {
//     deleteToken(tok);
//   }
//   // deleteAST(parser.ast_root);
//   return res;
// }
