
#include <iostream>
#include <string_view>
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

    auto tok = new ConstantReal(yytext, std::strtod(yytext, nullptr));
    return addToken(tok);
}

int Lexer::addInteger() {
    auto tok = new ConstantInteger(std::strtoll(yytext, nullptr, 10));
    return addToken(tok);
}

bool parseBool(const char *literal) {
    if (!strcmp(literal, "true")) {
        return true;
    }
    if (!strcmp(literal, "false")) {
        return false;
    }
    throw std::invalid_argument("convert failed");
}

int Lexer::addBoolean() {
    auto tok = new ConstantBoolean(parseBool(yytext));
    return addToken(tok);
}


int Lexer::addKeyword() {
    std::string str_temp = std::string(yytext);
    std::transform(str_temp.begin(), str_temp.end(), str_temp.begin(), tolower);
    auto tok = new Keyword(key_map.at(str_temp));
    return addToken(tok);
}

int Lexer::addMarker() {
    auto tok = new Marker(marker_map.at(yytext));
    return addToken(tok);
}

namespace char_spec {
    const char invalid = '0';

    static struct _spec_char_map_t {
        char inner[256]{};

        explicit _spec_char_map_t() noexcept {
            for (char &i : inner) {
                i = invalid;
            }

            // \n, \t, \r, \\

            inner['n'] = '\n';
            inner['t'] = '\t';
            inner['r'] = '\r';
            inner['\\'] = '\\';

            // \0 ~ \9
            for (int i = 0; i < 10; i++) {
                inner['0' + i] = char(i);
            }
        }

        char operator[](char a) {
            assert(count(a));
            return inner[a];
        }

        bool count(char a) {
            return inner[a] != invalid;
        }
    } spec_char_map;

    static struct _hex_table_t {
        char inner[256]{};

        explicit _hex_table_t() noexcept {
            for (char &i : inner) {
                i = invalid;
            }
            for (int i = 0; i < 10; i++) {
                inner[i + '0'] = char(i);
            }
            for (int i = 0; i < 6; i++) {
                inner[i + 'a'] = char(10 + i);
                inner[i + 'A'] = char(10 + i);
            }
        }

        char operator[](char a) {
            assert(count(a));
            return inner[a];
        }

        bool count(char a) {
            return inner[a] != invalid;
        }
    } hex_table;


}

int ishex(char n) {
    return char_spec::hex_table.count(n);
}

int Lexer::addASCIIChar() {

    // from this line, yytext.length >= 0, safe index: 0

    //                0
    // case1: any but '
    //        0 1
    // case2: ' $
    if (yytext[0] != '\'' || yytext[1] == '\00') return 0;

    // from this line, yytext.length >= 2, safe index: 0-2

    //        0   1 2 3
    // case3: ' any ' $
    if (yytext[2] == '\'' && yytext[3] == '\00') {
        return addToken(new ConstantChar(yytext[1]));
    }

    // from this line, yytext.length >= 2, safe index: 0-2


    //        0 1
    // case4: ' \

    if (yytext[1] == '\\') {
        // match escape rules with priority

        //                          2 3 4
        // case4.1: valid escape char ' $
        if (char_spec::spec_char_map.count(yytext[2]) && yytext[3] == '\'' && yytext[4] == '\00') {
            return addToken(new ConstantChar(char_spec::spec_char_map[yytext[2]]));
        }

        //          2   3   4 5 6
        // case4.2: x hex hex ' $
        if (yytext[2] == 'x' && ishex(yytext[3]) && ishex(yytext[4]) && yytext[5] == '\'' && yytext[6] == '\00') {
            return addToken(
                    new ConstantChar(char(char_spec::hex_table[yytext[3]] * 16 + char_spec::hex_table[yytext[4]])));
        }

        //            2   3 4 5
        // case4.3: hex hex ' $
        if (ishex(yytext[2]) && ishex(yytext[3]) && yytext[4] == '\'' && yytext[5] == '\00') {
            return addToken(
                    new ConstantChar(char(char_spec::hex_table[yytext[2]] * 16 + char_spec::hex_table[yytext[3]])));
        }
    }

    return 0;
}

int Lexer::addChar() {
    int code = addASCIIChar();
    // unicode rule can be extend
    // code = code ? code : addUnicodeChar();
    if (!code) {
        auto tok = new ErrorToken(yytext);
        return addError(tok), addToken(tok);
    }
    return code;
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

