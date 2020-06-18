

#ifndef PASCAL_S_TOKEN
#define PASCAL_S_TOKEN

#include <map>
#include <cassert>
#include "exception.h"

using pascal_s_integer_t = int64_t;

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
    Nullptr = 9,
    ErrorToken = 10,
    Length = 11,
};

using line_t = uint64_t;
using column_t = uint64_t;
using length_t = uint64_t;

struct Token {
    TokenType type;
    //todo: add line, column info
    line_t line;
    column_t column;
    length_t length;
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

    Div,
    Mod,
    And,
    Or,
    Not,
    Read,
    Write,
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

using marker_type_underlying_type = uint8_t ;


struct Keyword : public Token {
    KeywordType key_type;

    explicit Keyword(KeywordType key_type);
};


struct ErrorToken : public Token {
    const char *content;
    const char *hint;

    explicit ErrorToken(const char *content, const char *hint = nullptr);

    explicit ErrorToken(const char *content, const char *&&hint);

    ~ErrorToken();
};

struct ConstantString : public Token {
    const char *attr;
};

struct ConstantReal : public Token {
    const char *content;
    double attr;

    ConstantReal(const char *content, double attr);

    ~ConstantReal();
};

struct ConstantInteger : public Token {
    pascal_s_integer_t attr;

    explicit ConstantInteger(pascal_s_integer_t attr);

    ~ConstantInteger();
};

struct ConstantChar : public Token {
    char attr;

    explicit ConstantChar(char ch);

    ~ConstantChar();
};

struct Identifier : public Token {
    const char *content;

    explicit Identifier(const char *content);

    ~Identifier();
};

struct ConstantBoolean : public Token {
    bool attr;

    explicit ConstantBoolean(bool attr);

    ~ConstantBoolean();
};

struct Marker : public Token {
    MarkerType marker_type;

    explicit Marker(MarkerType marker_type);

    ~Marker();
};

void deleteToken(Token *pToken);

std::string convertToString(const Token *pToken);

#include <map>
#include <string>

using keyword_mapping = std::map<std::string, KeywordType>;
using reverse_keyword_mapping = std::map<KeywordType, const char *>;
using marker_mapping = std::map<std::string, MarkerType>;
using reverse_marker_mapping = std::map<MarkerType, const char*>;
extern keyword_mapping key_map;
extern reverse_keyword_mapping reverse_key_map;
extern marker_mapping marker_map;
extern reverse_marker_mapping  reverse_marker_map;

const char *get_keyword_type_reversed(KeywordType kt);

marker_type_underlying_type get_marker_pri(MarkerType);


const char *get_marker_type_reversed(MarkerType mt);

#endif
