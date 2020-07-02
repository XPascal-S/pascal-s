

#ifndef PASCAL_S_TOKEN
#define PASCAL_S_TOKEN

#include <vector>
#include "exception.h"
#include "lib/stdtype.h"
#include <string>
#include <set>
#include <cassert>

enum class TokenType : pascal_s::token_type_underlying_type {
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
    ConstRangeL = ConstantString,
    ConstRangeR = ConstantBoolean,
};


enum class KeywordType : pascal_s::keyword_type_underlying_type {
    Program,
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

enum class MarkerType : pascal_s::marker_type_underlying_type {
    Range = 0x00, // ..

    LogicAnd = 0x01, // and
    LogicOr = 0x02, // or
    LogicNot = 0x03, // not

    NEQ = 0x11, // <>
    LE = 0x12, // <=
    GE = 0x13, // >=
    LT = 0x14, // <
    EQ = 0x15, // =
    GT = 0x16, // >

    Add = 0x20, // +
    Sub = 0x21, // -

    Mul = 0x30, // *
    Div = 0x31, // /
    Mod = 0x32, // mod

    LParen = 0x40, // (
    RParen = 0x41, // )
    LBracket = 0x50, // [
    RBracket = 0x51, // ]

    Assign = 0x60, // :=
    Comma = 0x61, // ,
    Dot = 0x62, // .
    Semicolon = 0x63, // ;
    Colon = 0x64, // :
};

struct Token {
    // 0 ~ 8字节
    TokenType type;
    pascal_s::line_t line;
    // 8 ~ 16字节
    pascal_s::column_t column;
    pascal_s::length_t length;
    // 16 ~ 24字节
    pascal_s::offset_t offset;

    virtual ~Token()=default;
};


struct ErrorToken : public Token {
    const char *content;
    const char *hint;

    explicit ErrorToken(const char *content, const char *hint = nullptr);

    explicit ErrorToken(const char *content, int len, const char *hint = nullptr);

    static ErrorToken *copy_in(const char *content, const char *hint = nullptr);

    ~ErrorToken();
};

struct Keyword : public Token {
    KeywordType key_type;

    explicit Keyword(KeywordType key_type);
};

struct ConstantString : public Token {
    const char *attr;
};

struct ConstantReal : public Token {
    const char *content;
    pascal_s::pascal_s_real_t attr;

    ConstantReal(const char *content, double attr);

    ~ConstantReal();
};

struct ConstantInteger : public Token {
    pascal_s::pascal_s_integer_t attr;

    explicit ConstantInteger(pascal_s::pascal_s_integer_t attr);

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

};

void deleteToken(Token *pToken);

std::string convertToString(const Token *pToken);

const char *convertToString(TokenType tt);

KeywordType get_keyword_type(const std::string &kt);

const std::string &get_keyword_type_reversed(KeywordType kt);

pascal_s::marker_type_underlying_type get_marker_pri(MarkerType);

MarkerType get_marker_type(const std::string &mt);

const std::string &get_marker_type_reversed(MarkerType mt);

namespace predicate {
    bool is_const_token(TokenType tt);

    bool is_binary_sign(MarkerType mt);

    bool is_binary_sign(const Token *t);

#define pascal_s_predicator(cls, cls_lower, lower, upper) bool is_ ## lower(const Token *tok);\
extern const cls cls_lower ##_## lower;

    pascal_s_predicator(Marker, marker, logic_not, LogicNot)

    pascal_s_predicator(Marker, marker, logic_and, LogicAnd)

    pascal_s_predicator(Marker, marker, logic_or, LogicOr)

    pascal_s_predicator(Marker, marker, neq, NEQ)

    pascal_s_predicator(Marker, marker, le, LE)

    pascal_s_predicator(Marker, marker, ge, GE)

    pascal_s_predicator(Marker, marker, lt, LT)

    pascal_s_predicator(Marker, marker, eq, EQ)

    pascal_s_predicator(Marker, marker, gt, GT)

    pascal_s_predicator(Marker, marker, range, Range)

    pascal_s_predicator(Marker, marker, assgin, Assign)

    pascal_s_predicator(Marker, marker, add, Add)

    pascal_s_predicator(Marker, marker, sub, Sub)

    pascal_s_predicator(Marker, marker, mul, Mul)

    pascal_s_predicator(Marker, marker, div, Div)

    pascal_s_predicator(Marker, marker, mod, Mod)

    pascal_s_predicator(Marker, marker, lparen, LParen)

    pascal_s_predicator(Marker, marker, rparen, RParen)

    pascal_s_predicator(Marker, marker, lbracket, LBracket)

    pascal_s_predicator(Marker, marker, rbracket, RBracket)

    pascal_s_predicator(Marker, marker, comma, Comma)

    pascal_s_predicator(Marker, marker, dot, Dot)

    pascal_s_predicator(Marker, marker, semicolon, Semicolon)

    pascal_s_predicator(Marker, marker, colon, Colon)

    pascal_s_predicator(Keyword, keyword, program, Program)

    pascal_s_predicator(Keyword, keyword, const, Const)

    pascal_s_predicator(Keyword, keyword, var, Var)

    pascal_s_predicator(Keyword, keyword, procedure, Procedure)

    pascal_s_predicator(Keyword, keyword, function, Function)

    pascal_s_predicator(Keyword, keyword, begin, Begin)

    pascal_s_predicator(Keyword, keyword, end, End)

    pascal_s_predicator(Keyword, keyword, array, Array)

    pascal_s_predicator(Keyword, keyword, integer, Integer)

    pascal_s_predicator(Keyword, keyword, real, Real)

    pascal_s_predicator(Keyword, keyword, boolean, Boolean)

    pascal_s_predicator(Keyword, keyword, char, Char)

    pascal_s_predicator(Keyword, keyword, if, If)

    pascal_s_predicator(Keyword, keyword, then, Then)

    pascal_s_predicator(Keyword, keyword, else, Else)

    pascal_s_predicator(Keyword, keyword, for, For)

    pascal_s_predicator(Keyword, keyword, to, To)

    pascal_s_predicator(Keyword, keyword, do, Do)

    pascal_s_predicator(Keyword, keyword, of, Of)

#undef pascal_s_predicator


    bool token_equal(const Token *lhs, const Token *rhs);

    bool token_equal(const Token *lhs, const std::vector<Token *> *rhs);

    bool token_equal(const Token *lhs, const std::set<const Token *> *rhs);

}


#endif
