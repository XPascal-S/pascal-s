#include <cstring>
#include <iostream>
#include <pascal-s/interface.h>

#include <pascal-s/llvm-ast.h>
#include <pascal-s/yacc_parser.h>
#include <pascal-s/mock.h>

template<typename Lexer>
Parser *parser_factory(Lexer &lexer) {
    return new YaccParser<Lexer>(LexerProxy<Lexer>(lexer));
}

#ifdef WITH_MOCK
#include <pascal-s/lexer_mock.h>
template
struct YaccParser<MockLexer>;

template Parser* parser_factory(MockLexer& lexer);
#endif

#ifdef WITH_PASCAL_LEXER_FILES

#include <pascal-s/lexer.h>

// #include <pascal-s/lexer_full_in_memory.h>
template
struct YaccParser<FullInMemoryLexer>;

template Parser *parser_factory(FullInMemoryLexer &lexer);

template<typename Lexer>
YaccParser<Lexer>::~YaccParser() {
    for (auto e: yyparser.errors) {
        delete e;
    }
}


#endif
