//
// Created by kamiyoru on 2020/5/8.
//

#ifndef PASCAL_S_PARSER_H
#define PASCAL_S_PARSER_H

#include <vector>
#include "interface.h"
#include "llvm-ast.h"
#include "exception.h"
#include <set>

template<typename Lexer>
class Parser {
    LexerProxy<Lexer> lexer;
    const Token *current_token;

public:
    std::vector<PascalSError *> errors;

    explicit Parser(LexerProxy<Lexer> lexer);

    ast::Node *parse();

    const Token *next_token();

    ast::Program *parse_program();

    ast::ProgramHead *parse_program_head();

    ast::ProgramBody *parse_program_body();

    ast::IdentList *parse_id_list_with_paren();

    ast::ParamList *parse_param_list_with_paren();

    ast::ExpressionList *parse_expression_list_with_paren();

    ast::IdentList *parse_id_list();

    ast::ParamList *parse_param_list();

    ast::ExpressionList *parse_expression_list();

    ast::ParamSpec *parse_param();

    ast::ConstDecls *parse_const_decls();

    ast::ConstDecl *parse_const_decl();

    ast::VarDecls *parse_var_decls();

    ast::VarDecl *parse_var_decl();

    ast::FunctionDecls *parse_function_decls();

    ast::SubprogramHead * parse_subprogram_head();

    ast::Procedure *parse_function_body(ast::Procedure *);

    ast::TypeSpec *parse_type();

    ast::ArrayTypeSpec *parse_array_type(const Keyword *keyword_array);

    ast::Statement *parse_statement(std::set<const Token *> *till = nullptr);

    ast::CompoundStatement *parse_compound_statement(std::set<const Token *> *till = nullptr);

    ast::Statement *parse_for_statement(std::set<const Token *> *till = nullptr);

    ast::Statement *parse_if_else_statement(std::set<const Token *> *till = nullptr);

    ast::Exp *parse_const_exp(const std::set<const Token *> *till = nullptr);

    ast::Exp *parse_const_fac(const std::set<const Token *> *till = nullptr);

    ast::Exp *parse_exp(const std::set<const Token *> *till = nullptr);

    ast::Exp *parse_binary_exp(ast::Exp *lhs, const Marker *marker, marker_type_underlying_type current_marker_pri,
                               const std::set<const Token *> *till = nullptr);

    ast::Exp *parse_fac();

    virtual bool has_error();

private:
    ast::IdentList *_parse_id_list(ast::IdentList *);

    ast::ParamList *_parse_param_list(ast::ParamList *params);

    ast::ConstDecls *_parse_const_decls(ast::ConstDecls *);

    ast::VarDecls *_parse_var_decls(ast::VarDecls *);

    ast::FunctionDecls *_parse_function_decls(ast::FunctionDecls *decls);

    ast::CompoundStatement *_parse_compound_statement(std::set<const Token *> *till = nullptr);
};


#endif //PASCAL_S_PARSER_H
