//
// Created by kamiyoru on 2020/5/5.
//

#ifndef PASCAL_S_INTERFACE_H
#define PASCAL_S_INTERFACE_H

#include "token.h"
#include <vector>

// reserve lvalue reference semantics
// ProxyTarget
// 1. rvalue reference: ProxyName& = ProxyTarget&& & = ProxyTarget&
// 1. lvalue reference: ProxyName& = ProxyTarget& & = ProxyTarget&
// 1. origin value: ProxyName& = ProxyTarget & = ProxyTarget&
#define DefaultProxyConstructor(ClassName, ProxyName, proxy_field)\
    ProxyName &proxy_field;\
    explicit ClassName(ProxyName &proxy_field) : proxy_field(proxy_field) {}\
    ClassName(const ClassName &p) : proxy_field(p.proxy_field) {}\
    ClassName(ClassName &&p) noexcept : proxy_field(p.proxy_field) {}\
    ClassName &operator=(const ClassName &p) noexcept {\
        proxy_field = p.proxy_field;\
        return *this; }\
    ClassName &operator=(ClassName &&p)  noexcept {\
        proxy_field = p.proxy_field;\
        return *this; }

// auto generated LexerProxy struct
// you can partially specialize a specified type to change proxy behavior
template<typename Lexer>
struct LexerProxy {
    DefaultProxyConstructor(LexerProxy, Lexer, lexer)

    using token_container = std::vector<Token *>;
    using error_references = std::vector<ErrorToken *>;

    // cursor控制peek_token的值

    // 重置cursor
    [[maybe_unused]] void reset_cursor() { lexer.reset_cursor(); }

    // 返回当前token的值并移动cursor
    [[maybe_unused]] const Token *next_token() { return lexer.next_token(); }

    // 返回当前token的值且不移动cursor
    [[maybe_unused]] const Token *peek_token() { return lexer.peek_token(); }

    // 获取所有的token
    [[maybe_unused]] const token_container &get_all_tokens() { return lexer.get_all_tokens(); }

    // 获取所有的词法错误
    [[maybe_unused]] const error_references &get_all_errors() { return lexer.get_all_errors(); }

    // 判断是否存在词法错误
    [[maybe_unused]] bool has_error() { return lexer.has_error(); }
};

using pascal_errno = int;

// auto generated OStreamProxy struct
// you can partially specialize a specified type to change proxy behavior
template<typename OStream>
struct WriterProxy {
    DefaultProxyConstructor(WriterProxy, OStream, os)

    // 定义一个OStream 为 operator<<(T data)

    // T至少重载一个const char*，其他的可以看心情重载

    // 重置cursor
    template<typename T>
    [[maybe_unused]] WriterProxy &operator<<(T data) {
        os << data;
        return *this;
    }

    [[maybe_unused]] WriterProxy &write_data(const char *data) {
        return operator<<(data);
    }

    [[maybe_unused]] WriterProxy &write_data(char *const data) {
        return operator<<(data);
    }

    [[maybe_unused]] WriterProxy &write_data(const std::string &data) {
        return operator<<(data.c_str());
    }

    template<typename T>
    [[maybe_unused]] WriterProxy &write_data(const T &data) {
        return operator<<(data.c_str());
    }
};

// auto generated OStreamProxy struct
// you can partially specialize a specified type to change proxy behavior
template<typename File>
struct FileProxy {
    DefaultProxyConstructor(FileProxy, File, f)

    [[maybe_unused]] pascal_errno seek(size_t offset) {
        return f.seek(offset);
    }

    [[maybe_unused]] pascal_errno read(char *buf, size_t len) {
        return f.read(buf, len);
    }

    template<typename OStream>
    [[maybe_unused]] pascal_errno read(WriterProxy<OStream> buf, size_t len) {
        return f.read(buf, len);
    }
};

// auto generated ErrorProxy struct
// you can partially specialize a specified type to change proxy behavior
template<typename Error>
struct ErrorProxy {
    DefaultProxyConstructor(ErrorProxy, Error, err)

    [[maybe_unused]] line_t visit_line() {
        return err.line;
    }

    [[maybe_unused]] column_t visit_column() {
        return err.column;
    }

    [[maybe_unused]] length_t visit_length() {
        return err.length;
    }

    [[maybe_unused]] offset_t visit_offset() {
        return err.offset;
    }

    // 如果没有hint，为nullptr
    [[maybe_unused]] const char *visit_hint() {
        return err.hint;
    }
};

template<typename Parser>
struct ParserProxy {
    DefaultProxyConstructor(ParserProxy, Parser, parser)

    // cursor控制peek_token的值

    // 重置cursor
    [[maybe_unused]] ast::Node *parse() { return parser.parse(); }
};

#endif //PASCAL_S_INTERFACE_H
