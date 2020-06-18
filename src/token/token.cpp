#include <cstdlib>
#include <cstring>
#include <fmt/core.h>
#include <pascal-s/token.h>
#include <string>


char *copy_string(const char *content, int length) {
    char *ns = new char[length + 1];
    strcpy(ns, content);
    return ns;
}

char *copy_string(const char *content) {
    return copy_string(content, strlen(content));
}


std::string convertToString(const Token *pToken) {
    switch (pToken->type) {
        case TokenType::Keyword:
            return fmt::format("{{ .type = Keyword .key_type = {} }}",
                               get_keyword_type_reversed(
                                       reinterpret_cast<const Keyword *>(pToken)->key_type));
        case TokenType::Marker:
            return fmt::format(
                    "{{ .type = Marker .marker_type = {} }}",
                    get_marker_type_reversed(
                            reinterpret_cast<const Marker *>(pToken)->marker_type));
        case TokenType::ConstantString:
            return fmt::format(
                    "{{ .type = ConstantString .attr = {} }}",
                    reinterpret_cast<const ConstantString *>(pToken)->attr);
        case TokenType::ConstantReal:
            return fmt::format(
                    "{{ .type = ConstantReal .attr = {}, .raw = {} }}",
                    reinterpret_cast<const ConstantReal *>(pToken)->attr,
                    reinterpret_cast<const ConstantReal *>(pToken)->content);
        case TokenType::ConstantInteger:
            return fmt::format(
                    "{{ .type = ConstantInteger .attr = {} }}",
                    reinterpret_cast<const ConstantInteger *>(pToken)->attr);
        case TokenType::ConstantChar:
            return fmt::format(
                    "{{ .type = ConstantChar .attr = {} }}",
                    reinterpret_cast<const ConstantChar *>(pToken)->attr);
        case TokenType::Identifier:
            return fmt::format(
                    "{{ .type = Identifier .content = {} }}",
                    reinterpret_cast<const Identifier *>(pToken)->content);
        default:
            throw RuntimeReinterpretTokenException(pToken);
    }
    assert(false);
}

Keyword::Keyword(KeywordType key_type) : Token(), key_type(key_type) {
    this->type = TokenType::Keyword;
}


ErrorToken::ErrorToken(const char *content, const char *hint)
        : Token() {
    this->type = TokenType::ErrorToken;
    this->content = copy_string(content);
    this->hint = nullptr;
    if (hint != nullptr) this->hint = copy_string(hint);
}

ErrorToken::ErrorToken(const char *content, const char *&&hint)
        : Token() {
    this->type = TokenType::ErrorToken;
    this->content = copy_string(content);
    this->hint = hint;
}

ErrorToken::~ErrorToken() {
    delete[] this->content;
    this->content = nullptr;
    delete[] this->hint;
    this->hint = nullptr;
}

ConstantReal::ConstantReal(const char *content, double attr) : Token() {
    this->type = TokenType::ConstantReal;
    this->content = copy_string(content);
    this->attr = attr;
}

ConstantReal::~ConstantReal() {
    delete[] this->content;
    this->content = nullptr;
}

ConstantInteger::ConstantInteger(pascal_s_integer_t attr) : Token() {
    this->type = TokenType::ConstantInteger;
    this->attr = attr;
}

ConstantInteger::~ConstantInteger() = default;

ConstantChar::ConstantChar(char ch) : Token() {
    this->type = TokenType::ConstantChar;
    this->attr = ch;
}

ConstantChar::~ConstantChar() = default;

Identifier::Identifier(const char *content) : Token() {
    this->type = TokenType::Identifier;
    this->content = copy_string(content);
}

Identifier::~Identifier() {
    delete[]content;
}

ConstantBoolean::ConstantBoolean(bool attr) : Token() {
    this->type = TokenType::ConstantBoolean;
    this->attr = attr;
}

ConstantBoolean::~ConstantBoolean() = default;


Marker::Marker(MarkerType marker_type)
        : Token(), marker_type(marker_type) {
    this->type = TokenType::Marker;
}

Marker::~Marker() = default;


keyword_mapping key_map = {
        keyword_mapping::value_type{"to", KeywordType::To},
        keyword_mapping::value_type{"do", KeywordType::Do},
        keyword_mapping::value_type{"of", KeywordType::Of},
        keyword_mapping::value_type{"for", KeywordType::For},
        keyword_mapping::value_type{"else", KeywordType::Else},
        keyword_mapping::value_type{"if", KeywordType::If},
        keyword_mapping::value_type{"then", KeywordType::Then},
        keyword_mapping::value_type{"char", KeywordType::Char},
        keyword_mapping::value_type{"boolean", KeywordType::Boolean},
        keyword_mapping::value_type{"real", KeywordType::Real},
        keyword_mapping::value_type{"integer", KeywordType::Integer},
        keyword_mapping::value_type{"array", KeywordType::Array},
        keyword_mapping::value_type{"end", KeywordType::End},
        keyword_mapping::value_type{"begin", KeywordType::Begin},
        keyword_mapping::value_type{"function", KeywordType::Function},
        keyword_mapping::value_type{"procedure", KeywordType::Procedure},
        keyword_mapping::value_type{"program", KeywordType::Program},
        keyword_mapping::value_type{"var", KeywordType::Var},
        keyword_mapping::value_type{"const", KeywordType::Const},
        keyword_mapping::value_type{"div", KeywordType::Div},
        keyword_mapping::value_type{"mod", KeywordType::Mod},
        keyword_mapping::value_type{"and", KeywordType::And},
        keyword_mapping::value_type{"or", KeywordType::Or},
        keyword_mapping::value_type{"not", KeywordType::Not},
        keyword_mapping::value_type{"read", KeywordType::Read},
        keyword_mapping::value_type{"write", KeywordType::Write}
};

marker_mapping marker_map = {
        marker_mapping::value_type{"<>", MarkerType::NEQ},
        marker_mapping::value_type{"<=", MarkerType::LE},
        marker_mapping::value_type{">=", MarkerType::GE},
        marker_mapping::value_type{"<", MarkerType::LT},
        marker_mapping::value_type{"=", MarkerType::EQ},
        marker_mapping::value_type{">", MarkerType::GT},
        marker_mapping::value_type{"..", MarkerType::Range},

        marker_mapping::value_type{":=", MarkerType::Assign},
        marker_mapping::value_type{"+", MarkerType::Add},
        marker_mapping::value_type{"-", MarkerType::Sub},
        marker_mapping::value_type{"*", MarkerType::Mul},
        marker_mapping::value_type{"/", MarkerType::Div},

        marker_mapping::value_type{"(", MarkerType::LParen},
        marker_mapping::value_type{")", MarkerType::RParen},
        marker_mapping::value_type{"[", MarkerType::LBracket},
        marker_mapping::value_type{"]", MarkerType::RBracket},

        marker_mapping::value_type{",", MarkerType::Comma},
        marker_mapping::value_type{".", MarkerType::Dot},
        marker_mapping::value_type{";", MarkerType::Semicolon},
        marker_mapping::value_type{":", MarkerType::Colon}
};

reverse_keyword_mapping reverse_key_map;

const char *get_keyword_type_reversed(KeywordType kt) {
    if (reverse_key_map.empty()) {
        for (auto &kv: key_map) {
            reverse_key_map[kv.second] = kv.first.c_str();
        }
    }
    return reverse_key_map.at(kt);
}

marker_type_underlying_type get_marker_pri(MarkerType marker_type) {
    return static_cast<marker_type_underlying_type>(marker_type)
            >> 0x4U;
}

reverse_marker_mapping reverse_marker_map;

const char *get_marker_type_reversed(MarkerType mt) {
    if (reverse_marker_map.empty()) {
        for (auto &mv : marker_map) {
            reverse_marker_map[mv.second] = mv.first.c_str();
        }
    }
    return reverse_marker_map.at(mt);
}

