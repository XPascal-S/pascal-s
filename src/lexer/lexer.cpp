
#include <iostream>
#include <string_view>
#include <cstdarg>
#include <cstring>
#include <pascal-s/logger.h>
#include <pascal-s/token.h>
#include <pascal-s/lexer.h>

Lexer::Lexer(std::istream *in, std::ostream *out)
        : yyFlexLexer(in, out) {}


Lexer::~Lexer() {
}


int Lexer::addIdentifier() {
    std::string str_temp = std::string(yytext);
    std::transform(str_temp.begin(),str_temp.end(),str_temp.begin(),tolower);
    auto tok = new Identifier(str_temp.c_str());
    return addToken(tok);
}

int Lexer::addReal() {
    auto tok = new ConstantReal(yytext);
    return addToken(tok);
}

int Lexer::addInteger() {
    auto tok = new ConstantInteger(yytext);
    return addToken(tok);
}

int Lexer::addBoolean() {
    auto tok = new ConstantBoolean(yytext);
    return addToken(tok);
}


int Lexer::addKeyword() {
    std::string str_temp = std::string(yytext);
    std::transform(str_temp.begin(),str_temp.end(),str_temp.begin(),tolower);
    auto tok = new Keyword(key_map.at(str_temp));
    return addToken(tok);
}

int Lexer::addMarker() {
    auto tok = new Marker(marker_map.at(yytext));
    return addToken(tok);
}

int Lexer::addChar() {
    auto tok = new ConstantChar(yytext);
    return addToken(tok);
}

int Lexer::recordNewLine() {
    line_offset = current_offset;
    return 1;
}

int Lexer::skipErrorString() {
    auto tok = new ErrorToken(yytext);
    addError(tok);
    return addToken(tok);
}

