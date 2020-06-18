

#include <pascal-s/token.h>


void deleteToken(Token *pToken) {
    switch (pToken->type) {
        case TokenType::Keyword:
            delete reinterpret_cast<Keyword *>(pToken);
            break;
        case TokenType::Marker:
            delete reinterpret_cast<Marker *>(pToken);
            break;
        case TokenType::ConstantString:
            delete reinterpret_cast<ConstantString *>(pToken);
            break;
        case TokenType::ConstantReal:
            delete reinterpret_cast<ConstantReal *>(pToken);
            break;
        case TokenType::ConstantInteger:
            delete reinterpret_cast<ConstantInteger *>(pToken);
            break;
        case TokenType::ConstantChar:
            delete reinterpret_cast<ConstantChar *>(pToken);
            break;
        case TokenType::ConstantBoolean:
            delete reinterpret_cast<ConstantBoolean *>(pToken);
            break;
        case TokenType::Identifier:
            delete reinterpret_cast<Identifier *>(pToken);
            break;
        case TokenType::ErrorToken:
            delete reinterpret_cast<ErrorToken *>(pToken);
            break;
        default:
            throw RuntimeReinterpretTokenException(pToken);
    }
}
