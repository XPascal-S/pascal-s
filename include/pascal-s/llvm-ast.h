//
// Created by kamiyoru on 2020/5/10.
//

#ifndef LLVM_PASCAL_S_AST_H
#define LLVM_PASCAL_S_AST_H

#include <cstdint>
#include <vector>
#include <deque>
#include "token.h"
#include <pascal-s/lib/stdtype.h>

namespace ast {

    template<typename T, typename F>
    void copy_pos_with_check(T *node, F *tok) {
        assert(node != nullptr);
        if (tok == nullptr) {
            return;
        }
        pascal_s::copy_pos_any(node, tok);
    }

    template<typename P, typename F, typename T>
    void copy_pos_between_tokens(P *target, F *fr, T *to) {
        assert(target != nullptr);
        if (fr == nullptr || to == nullptr) {
            return;
        }
        assert(fr->offset <= to->offset);

        pascal_s::copy_pos_any(target, fr);
        target->length = to->offset + to->length - fr->offset;
    }

    enum class Type : uint16_t {

        Unknown,

        Program, // program struct

        ProgramHead, // program head

        ProgramBody, // program body

        IdentList, // id list

        ConstDecls, // const declarations

        ConstDecl, // const declaration

        ExpConst, // const value

        VarDecl, // var declarations

        VarDecls, // var declaration

        TypeSpec, // type

        BasicTypeSpec, // basic type

        ArrayTypeSpec, // array type

        Period, // Period

        SubprogramDecls, // subprogram declarations

        Subprogram, // subprogram

        SubprogramHead, // subprogram head

        SubprogramBody, // subprogram body

        CompoundStatement, // compound_statement

        FormalParameter, // formal parameter

        ParamSpec,//child of parameter list

        ParamList, // parameter list

        StatementList, // statement list

        Statement,

        ElsePart, // else part

        VariableList, // variable list

        Variable, // variable

        IdVarpart, // id varpart

        ExpressionList, // expression list

        Expression, // expression

        SimpleExpression, // simple expression

        Procedure,

        Function,

        ExecStatement,

        //StatementBlock,

        Read,

        Write,

        ExpCall,

        IfElseStatement,

        ForStatement,

        ExpConstantInteger,

        ExpConstantChar,

        ExpConstantBoolean,

        ExpConstantString,

        ExpConstantReal,

        Ident,

        FunctionDecl,

        FunctionDecls,

        ExpAssign,

        Exp,

        UnExp,

        BiExp,

        ExpMarker,

        ExpKeyword,

        ExpVoid,
    };

    struct Node;

    void deleteAST(Node *node);

    void printAST(const Node *node, int dep = 0);


    struct Node : pascal_s::Pos {

        Type type;

        std::deque<Node *> children;

        explicit Node(Type type) : type(type) {}

        char *GetTokenSymbol();

        pascal_s::Pos *visit_pos() {
            return reinterpret_cast<pascal_s::Pos *>(this);
        }

        [[nodiscard]] const pascal_s::Pos *visit_pos() const {
            return reinterpret_cast<const pascal_s::Pos *>(this);
        }

    };


    struct Exp : public Node {

        explicit Exp(Type type) : Node(type) {}

    };


    struct Function : public Node {


        explicit Function(Type type) : Node(type) {}

    };


    struct TypeSpec : public Node {

        explicit TypeSpec(Type type) : Node(type) {}

    };


    struct Period : public TypeSpec {

        std::vector<std::pair<ast::Exp *, ast::Exp *>> periods;

        explicit Period() : TypeSpec(Type::Period) {}

    };


    struct BasicTypeSpec : public TypeSpec {

        const Keyword *keyword;

        explicit BasicTypeSpec(const Keyword *keyword) : TypeSpec(Type::BasicTypeSpec), keyword(keyword) {
            copy_pos_with_check(this, keyword);
        }

    };


    struct ArrayTypeSpec : public TypeSpec {

        const Keyword *keyword;

        // todo: check period
        std::vector<std::pair<int64_t, int64_t>> periods;

        explicit ArrayTypeSpec(const Keyword *keyword) : TypeSpec(Type::ArrayTypeSpec), keyword(keyword) {}


    };


    struct IdentList : public Node {

        std::vector<const Identifier *> idents;


        IdentList() : Node(Type::IdentList) {}

    };


    struct ParamSpec : public Node {

        const Keyword *keyword_var = nullptr;

        IdentList *id_list;

        TypeSpec *spec;

        ParamSpec(const Keyword *keyword_var, IdentList *id_list, TypeSpec *spec) : Node(Type::ParamSpec),
                                                                                    keyword_var(keyword_var),
                                                                                    id_list(id_list), spec(spec) {
            if (keyword_var) {
                copy_pos_between_tokens(this,
                                        keyword_var, spec);
            } else {
                copy_pos_between_tokens(this,
                                        id_list, spec);
            }
        }

        ~ParamSpec() {
            deleteAST(id_list);
            deleteAST(spec);
        }

    };

    struct ParamList : public Node {

        std::vector<ParamSpec *> params;


        ParamList() : Node(Type::ParamList) {}


        ~ParamList() {

            for (auto exp : params) {

                deleteAST(exp);

            }

        }

    };


    struct ExpressionList : public Node {
        std::vector<Exp *> explist;

        explicit ExpressionList() : Node(Type::ExpressionList) {}

        ~ExpressionList() {

            for (auto exp : explist) {

                deleteAST(exp);

            }

        }
    };


    struct Variable : public Exp {

        const Identifier *id = nullptr;

        ExpressionList *id_var = nullptr;

        explicit Variable() : Exp(Type::Variable) {}

        explicit Variable(Identifier *id, ExpressionList *id_var) : Exp(Type::Variable), id(id), id_var(id_var) {}

        ~Variable() {
            deleteAST(id_var);
        }
    };


    struct VariableList : public Node {

        std::vector<Variable *> params;


        VariableList() : Node(Type::VariableList) {}


        ~VariableList() {

            for (auto exp : params) {

                deleteAST(exp);

            }

        }

    };


    struct ConstDecl : public Node {

        const Identifier *ident;

        Exp *rhs;


        ConstDecl(const Identifier *ident, Exp *rhs) : Node(Type::ConstDecl), ident(ident), rhs(rhs) {
            copy_pos_between_tokens(this, ident, rhs);
        }

        ~ConstDecl() {
            deleteAST(rhs);
        }
    };


    struct ConstDecls : public Node {

        std::vector<ConstDecl *> decls;

        ConstDecls() : Node(Type::ConstDecls) {}


        ~ConstDecls() {

            for (auto exp : decls) {

                deleteAST(exp);

            }

        }

    };


    struct VarDecl : public Node {

        TypeSpec *type_spec;

        IdentList *idents;


        VarDecl(IdentList *idents, TypeSpec *type_spec) : Node(Type::VarDecl),

                                                          type_spec(type_spec), idents(idents) {
            copy_pos_between_tokens(this, idents, type_spec);
        }

        ~VarDecl() {
            deleteAST(type_spec);
            deleteAST(idents);
        }
    };


    struct VarDecls : public Node {

        std::vector<VarDecl *> decls;

        VarDecls() : Node(Type::VarDecls) {}


        ~VarDecls() {

            for (auto exp : decls) {

                deleteAST(exp);

            }

        }

    };


    struct Ident : public Exp {

        const Identifier *ident;


        explicit Ident(const Identifier *ident) : Exp(Type::Ident), ident(ident) {
            copy_pos_with_check(this, ident);
        }

    };


    struct ExpAssign : public Exp {

        Exp *lhs, *rhs;


        ExpAssign(Exp *lhs, Exp *rhs) : Exp(Type::ExpAssign), lhs(lhs), rhs(rhs) {
            copy_pos_between_tokens(this, lhs, rhs);
        }

        ~ExpAssign() {
            deleteAST(lhs);
            deleteAST(rhs);
        }
    };


    struct UnExp : public Exp {

        Exp *lhs;

        const Marker *marker;


        explicit UnExp(const Marker *marker, Exp *lhs) : Exp(Type::UnExp), lhs(lhs), marker(marker) {
            copy_pos_between_tokens(this, marker, lhs);
        }

        ~UnExp() {

            deleteAST(lhs);

        };

    };


    struct BiExp : public Exp {

        Exp *lhs, *rhs;

        const Marker *marker;


        explicit BiExp(Exp *lhs, const Marker *marker, Exp *rhs) : Exp(Type::BiExp), lhs(lhs), rhs(rhs),
                                                                   marker(marker) {
            copy_pos_between_tokens(this, lhs, rhs);
        }

        ~BiExp() {

            deleteAST(lhs);

            deleteAST(rhs);

        };

    };


    struct ExpCall : public Exp {

        const Identifier *fn;

        ExpressionList *params;


        explicit ExpCall(const Identifier *fn, ExpressionList *params) : Exp(Type::ExpCall), fn(fn), params(params) {
            copy_pos_between_tokens(this, fn, params);
        }

        ~ExpCall() {

            deleteAST(params);

        };

    };


    struct Statement : public Exp {

        explicit Statement(Type type) : Exp(type) {}

    };


    struct ExecStatement : public Statement {
        Exp *exp;

        explicit ExecStatement(Exp *exp) : Statement(Type::ExecStatement), exp(exp) {
            copy_pos_with_check(this, exp);
        }

        ~ExecStatement() {
            deleteAST(exp);
        }
    };

    struct StatementList : public Node {

        std::vector<Statement *> statement;

        explicit StatementList() : Node(Type::StatementList) {}

        ~StatementList() {
            for (auto stm : statement) {

                deleteAST(stm);

            }
        }
    };


    struct Read : public Statement {
        VariableList *var_list = nullptr;

        explicit Read() : Statement(Type::Read) {}

        explicit Read(VariableList *var_list) : Statement(Type::Read), var_list(var_list) {}

        ~Read() {
            deleteAST(var_list);
        }
    };


    struct Write : public Statement {
        ExpressionList *exp_list = nullptr;

        explicit Write() : Statement(Type::Write) {}

        explicit Write(ExpressionList *exp_list) : Statement(Type::Write), exp_list(exp_list) {}

        ~Write() {
            deleteAST(exp_list);
        }
    };


//struct StatementBlock : public Statement {
//
//  StatementBlock() : Statement(Type::StatementBlock) {}
//
//};



    struct IfElseStatement : public Statement {

        Exp *expression = nullptr;

        Statement *if_part = nullptr;

        Statement *else_part = nullptr;

        IfElseStatement() : Statement(Type::IfElseStatement) {}

        IfElseStatement(Exp *expression, Statement *if_part, Statement *else_part) : Statement(Type::IfElseStatement),
                                                                                     expression(expression),
                                                                                     if_part(if_part),
                                                                                     else_part(else_part) {}

        ~IfElseStatement() {
            deleteAST(expression);
            deleteAST(if_part);
            deleteAST(else_part);
        }
    };


    struct ForStatement : public Statement {

        const Identifier *id = nullptr;

        Exp *express1 = nullptr;

        Exp *express2 = nullptr;

        Statement *for_stmt = nullptr;

        ForStatement() : Statement(Type::ForStatement) {}

        ForStatement(const Identifier *id, Exp *express1, Exp *express2, Statement *for_stmt) : Statement(
                Type::ForStatement), id(id), express1(express1), express2(express2), for_stmt(for_stmt) {}

        ~ForStatement() {
            deleteAST(express1);
            deleteAST(express2);
            deleteAST(for_stmt);
        }
    };


    struct ExpConstantInteger : public Exp {

        const ConstantInteger *value;


        explicit ExpConstantInteger(const ConstantInteger *value) : Exp(Type::ExpConstantInteger), value(value) {
            copy_pos_with_check(this, value);
        }

    };


    struct ExpConstantChar : public Exp {

        const ConstantChar *value;


        explicit ExpConstantChar(const ConstantChar *value) : Exp(Type::ExpConstantChar), value(value) {
            copy_pos_with_check(this, value);
        }

    };


    struct ExpConstantBoolean : public Exp {

        const ConstantBoolean *value;


        explicit ExpConstantBoolean(const ConstantBoolean *value) : Exp(Type::ExpConstantBoolean), value(value) {
            copy_pos_with_check(this, value);
        }

    };


    struct ExpConstantString : public Exp {

        const ConstantString *value;


        explicit ExpConstantString(const ConstantString *value) : Exp(Type::ExpConstantString), value(value) {
            copy_pos_with_check(this, value);
        }

    };


    struct ExpConstantReal : public Exp {

        const ConstantReal *value;


        explicit ExpConstantReal(const ConstantReal *value) : Exp(Type::ExpConstantReal), value(value) {
            copy_pos_with_check(this, value);
        }

    };


    struct ExpMarker : public Exp {
        const Marker *value;


        explicit ExpMarker(const Marker *value) : Exp(Type::ExpMarker), value(value) {
            copy_pos_with_check(this, value);
        }

    };

    struct ExpKeyword : public Exp {
        const Keyword *value;

        explicit ExpKeyword(const Keyword *value)
                : Exp(Type::ExpKeyword), value(value) {
            copy_pos_with_check(this, value);
        }

    };


    struct ExpVoid : public Exp {

        explicit ExpVoid() : Exp(Type::ExpVoid) {}

    };


    struct CompoundStatement : public Statement {

        StatementList *state = nullptr;

        explicit CompoundStatement() : Statement(Type::CompoundStatement) {}

        explicit CompoundStatement(StatementList *state) : Statement(Type::CompoundStatement), state(state) {
            copy_pos_with_check(this, state);
        }

        ~CompoundStatement() {
            deleteAST(state);
        }
    };


    struct SubprogramHead : public Node { // subprogram head

        const Keyword *fn_def = nullptr;

        const Identifier *name = nullptr;

        ParamList *decls = nullptr;

        BasicTypeSpec *ret_type = nullptr;

        SubprogramHead() : Node(Type::SubprogramHead) {}

        SubprogramHead(const Keyword *fn_def, const Identifier *name, ParamList *decls, BasicTypeSpec *ret_type) :
                Node(Type::SubprogramHead), fn_def(fn_def), name(name), decls(decls), ret_type(ret_type) {
            if (ret_type != nullptr) {
                copy_pos_between_tokens(this, fn_def, ret_type);
            } else if (decls != nullptr) {
                copy_pos_between_tokens(this, fn_def, decls);
            } else {
                copy_pos_between_tokens(this, fn_def, name);
            }
        }

        ~SubprogramHead() {
            deleteAST(decls);
            deleteAST(ret_type);
        }
    };

    struct SubprogramBody : public Node { // subprogram body

        ConstDecls *constdecls = nullptr;

        VarDecls *vardecls = nullptr;

        CompoundStatement *compound = nullptr;

        explicit SubprogramBody() : Node(Type::SubprogramBody) {}

        explicit SubprogramBody(ConstDecls *constdecls, VarDecls *vardecls, CompoundStatement *compound) :
                Node(Type::SubprogramBody), constdecls(constdecls), vardecls(vardecls), compound(compound) {
            Node *l = constdecls;
            if (l == nullptr) l = vardecls;
            if (l == nullptr) l = compound;

            copy_pos_between_tokens(this, l, compound);
        }

        ~SubprogramBody() {
            deleteAST(constdecls);
            deleteAST(vardecls);
            deleteAST(compound);
        }
    };


    struct Subprogram : public Function { // subprogram

        SubprogramHead *subhead;

        const Marker *semicolon = nullptr;

        SubprogramBody *subbody;

        explicit Subprogram(SubprogramHead *subhead, SubprogramBody *subbody) : Function(Type::Subprogram),
                                                                                subhead(subhead), subbody(subbody) {}

        ~Subprogram() {
            deleteAST(subhead);
            deleteAST(subbody);
        }
    };


    struct SubprogramDecls : public Node { // subprogram declarations

        std::vector<Subprogram *> subprogram;

        explicit SubprogramDecls() : Node(Type::SubprogramDecls) {}

        ~SubprogramDecls() {
            for (auto subp : subprogram) {
                deleteAST(subp);
            }
        }
    };


    struct ProgramHead : public Node {

        const ExpKeyword *programKeyword;

        Ident *id;

        IdentList *idlist;

        explicit ProgramHead(const ExpKeyword *programKeyword, Ident *id, IdentList *idlist) : Node(Type::ProgramHead),
                                                                                               programKeyword(
                                                                                                       programKeyword),
                                                                                               id(id), idlist(idlist) {
            if (idlist) copy_pos_between_tokens(this, programKeyword, idlist);
            else copy_pos_between_tokens(this, programKeyword, id);
        }

        explicit ProgramHead(const ExpKeyword *programKeyword, Ident *id) :
                Node(Type::ProgramHead), programKeyword(programKeyword), id(id), idlist(nullptr) {}

        ~ProgramHead() {
            deleteAST(id);
            deleteAST(idlist);
        }
    };


    struct ProgramBody : public Node {

        ConstDecls *constdecls;

        VarDecls *vardecls;

        SubprogramDecls *subprogram;

        CompoundStatement *compound;

        explicit ProgramBody(ConstDecls *constdecls, VarDecls *vardecls, SubprogramDecls *subprogram,
                             CompoundStatement *compound) :
                Node(Type::ProgramBody), constdecls(constdecls), vardecls(vardecls), subprogram(subprogram),
                compound(compound) {
            Node *l = constdecls;
            if (l == nullptr) l = vardecls;
            if (l == nullptr) l = subprogram;
            if (l == nullptr) l = compound;

            copy_pos_between_tokens(this, l, compound);
        }

        ~ProgramBody() {
            deleteAST(constdecls);
            deleteAST(vardecls);
            deleteAST(subprogram);
            deleteAST(compound);
        }
    };


    struct Program : public Function {

        Node fn_type;

        ProgramHead *programHead;

        const Marker *semicolon;

        ProgramBody *programBody;

        const Marker *dot = nullptr;


        explicit Program(ProgramHead *programHead, ProgramBody *programBody)

                : Function(Type::Program), fn_type(Type::Program), programHead(programHead), programBody(programBody) {

            copy_pos_between_tokens(this, programHead, programBody);
        }


        ~Program() {
            deleteAST(programHead);
            deleteAST(programBody);
        }
    };
}

#endif //LLVM_PASCAL_S_AST_H
