//
// Created by kamiyoru on 2020/4/29.
//

#ifndef PASCAL_S_LEXER_H
#define PASCAL_S_LEXER_H

#include <FlexLexer.h>
#include "logger.h"
#include "token.h"



class Lexer : public yyFlexLexer {
public:
    using token_container = std::vector<Token *>;
    using error_references = std::vector<ErrorToken *>;

    explicit Lexer(std::istream *in = nullptr, std::ostream *out = nullptr);

    ~Lexer() override;

    virtual void reset_cursor() = 0;

    virtual const Token *next_token() = 0;

    virtual const Token *peek_token() = 0;

    virtual const token_container &get_all_tokens() = 0;

    virtual const error_references &get_all_errors() = 0;

    virtual bool has_error() = 0;

protected:
    int yylex() final;

    Logger logger;
    column_t current_offset = 0, line_offset = 0;

    virtual int addToken(Token *token) = 0;

    virtual void addError(ErrorToken *token) = 0;

private:

    int addIdentifier();

    int addReal();

    int addInteger();

    int addBoolean();

    int addKeyword();

    int addMarker();

    int addChar();

    int recordNewLine();

    int skipErrorString();
};

class FullInMemoryLexer : public Lexer {
    token_container tokens;
    error_references errors;
    int64_t current_token_cursor;
public:
    explicit FullInMemoryLexer(std::istream *in = nullptr, std::ostream *out = nullptr);

    ~FullInMemoryLexer() override;

    void reset_cursor() override;

    const Token *next_token() override;

    const Token *peek_token() override;

    const token_container &get_all_tokens() override;

    const error_references &get_all_errors() override;

    bool has_error() override;

private:
    int addToken(Token *token) override;

    void addError(ErrorToken *token) override;
};

#endif //PASCAL_S_LEXER_H
