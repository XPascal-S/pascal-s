

#ifndef PASCAL_S_TOKEN
#define PASCAL_S_TOKEN
#define KEYWORD_NUM 19

#include <stdint.h>
#include <map>
#include <cassert>
#include "exception.h"

struct LexerInfo {
    int64_t row, column;
};

enum class TokenType {
    Unknown = 0,
    Keyword = 1,
    ConstantString = 2,
    ConstantChar = 3,
    ConstantReal = 4,
    ConstantInteger = 5,
    ConstantBoolean = 6,
    Identifier = 7,
    Marker = 8,
    Nullptr= 9,
    Length = 10,
};

using line_t = uint64_t;
using column_t = uint64_t;

struct Token {
    TokenType type;
    //todo: add line, column info
    line_t line;
    column_t column;
    virtual ~Token() {};
};

enum class KeywordType {
    Program ,
    Const,
    Var,
    Procedure,
    Function,
    Begin,
    End,

    Array,
    Integer,
    Real,
    Boolean,
    Char,

    If,
    Then,
    Else,
    For,
    To,
    Do,
    Of,

    //todo: keyword type
//    Div,
//    Mod,
//    And,
//    Or,
//    Not,

    Length
};

using marker_type_underlying_type = uint8_t ;
enum class MarkerType :marker_type_underlying_type {
                                                    Range = 0x00, // ..
                                                    NEQ = 0x01, // <>
                                                    LE = 0x02, // <=
                                                    GE = 0x03, // >=
                                                    LT = 0x04, // <
                                                    EQ = 0x05, // =
                                                    GT = 0x06, // >
                                                    Add = 0x10, // +
                                                    Sub = 0x11, // -
                                                    Mul = 0x20, // *
                                                    Div = 0x21, // /

                                                    LParen = 0x30, // (
                                                    RParen = 0x31, // )
                                                    LBracket = 0x40, // [
                                                    RBracket = 0x41, // ]

                                                    Assign = 0x50, // :=
                                                    Comma = 0x51, // ,
                                                    Dot = 0x52, // .
                                                    Semicolon = 0x53, // ;
                                                    Colon = 0x54, // :
};

struct Keyword : public Token {
    KeywordType key_type;
    const char* attr;

    explicit Keyword(const char *attr, KeywordType key_type);

    explicit Keyword(KeywordType key_type) : Token(), key_type(key_type) {
        this->type = TokenType::Keyword;
    }
};

struct ConstantString: public Token {
    const char* content;
    const char* attr;
};

struct ConstantReal: public Token {
    const char* content;
    double attr;

    ConstantReal(const char *content);

    ~ConstantReal();
};

struct ConstantInteger : public Token {
    const char *content;
    int64_t attr;

    ConstantInteger(const char *content);

    ~ConstantInteger();
};

struct ConstantChar : public Token {
    const char *content;
    const char* attr;

    ConstantChar(const char *content);

    ~ConstantChar();
};

struct Identifier : public Token {
    const char *content;
    const char* attr;

    Identifier(const char *content);

    ~Identifier();
};

struct ConstantBoolean : public Token {
    const char *content;
    bool attr;

    ConstantBoolean(const char *content);

    ~ConstantBoolean();
};

struct Marker : public Token {
    const char *content;
    const char *attr;
    MarkerType marker_type;

    Marker(const char *content);

    explicit Marker(MarkerType marker_type);

    explicit Marker(const char *content, MarkerType marker_type);

    ~Marker();
};

void deleteToken(Token *pToken);

std::string convertToString(const Token *pToken);

#include <map>
#include <string>

using keyword_mapping = std::map<std::string, KeywordType>;
using reverse_keyword_mapping = std::map<KeywordType, const char *>;
extern keyword_mapping key_map;
extern reverse_keyword_mapping reverse_key_map;

const char *get_keyword_type_reversed(KeywordType kt);
marker_type_underlying_type get_marker_pri(MarkerType);

#endif
