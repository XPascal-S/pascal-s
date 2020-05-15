#ifndef PASCAL_S_AST_H

#define PASCAL_S_AST_H



#include "token.h"

#include <vector>
#include <utility>
#include <deque>



enum class Type : uint16_t {

    Unknown,

    Program,

    Procedure,

    Function,

    StatementBlock,

    ExpCall,

    IfElseStatement,

    ForStatement,

    ExpConstantInteger,

    ExpConstantChar,

    ExpConstantBoolean,

    ExpConstantString,

    ExpConstantReal,

    Ident,

    ParamList,

    VariableList,

    IdentList,

    ConstDecl,

    ConstDecls,

    VarDecl,

    VarDecls,

    FunctionDecl,

    FunctionDecls,

    ExpAssign,

    UnExp,

    BiExp,

    BasicTypeSpec,

    ArrayTypeSpec,

    ExpKeyword,

    ExpMarker,
};



struct Node;

void deleteAST(Node* node);

void printAST(Node *node, int dep=0);



struct Node {//�ڵ����

    Type type;

    std::deque<Node *> children;

    explicit Node(Type type) : type(type) {}

};



struct Exp : public Node {//���ʽ����

    explicit Exp(Type type) : Node(type) {}

};



struct Function : public Node {//�����͹��̻���



    explicit Function(Type type) : Node(type) {}

};



struct TypeSpec : public Node {//������������

    explicit TypeSpec(Type type) : Node(type) {}

};



struct BasicTypeSpec : public TypeSpec {//������������ e.g.integer

    const Keyword* keyword;

    explicit BasicTypeSpec(const Keyword* keyword) : TypeSpec(Type::BasicTypeSpec), keyword(keyword) {}

};



struct ArrayTypeSpec : public TypeSpec {//������������  e.g.Array

    const Keyword* keyword;

    std::vector<std::pair<int64_t, int64_t>> periods;

    explicit ArrayTypeSpec(const Keyword* keyword) : TypeSpec(Type::ArrayTypeSpec), keyword(keyword) {}

};



struct ParamList : public Node {//�βα�

    std::vector<Exp*> params;



    ParamList() : Node(Type::ParamList) {}



    ~ParamList() {

        for (auto exp : params) {

            deleteAST(exp);

        }

    }

};



struct VariableList : public Node {//�����Ĳ�����

    std::vector<Exp*> params;



    VariableList() : Node(Type::VariableList) {}



    ~VariableList() {

        for (auto exp : params) {

            deleteAST(exp);

        }

    }

};



struct IdentList : public Node {//id list  program���id

    std::vector<const Identifier*> idents;



    IdentList() : Node(Type::IdentList) {}

};



struct ConstDecl : public Node {//��������ֵ

    const Identifier* ident;

    const Exp* rhs;



    ConstDecl(const Identifier* ident, Exp* rhs) : Node(Type::ConstDecl), ident(ident), rhs(rhs) {}

};



struct ConstDecls : public Node {

    std::vector<ConstDecl*> decls;

    ConstDecls() : Node(Type::ConstDecls) {}



    ~ConstDecls() {

        for (auto exp : decls) {

            deleteAST(exp);

        }

    }

};



struct VarDecl : public Node {//�������ͺ�ֵ

    TypeSpec* type_spec;

    IdentList* idents;

    VarDecl(IdentList* idents, TypeSpec* type_spec) : Node(Type::VarDecl),

        type_spec(type_spec), idents(idents) {}

    ~VarDecl() {

        deleteAST(idents);

    }

};



struct VarDecls : public Node {

    std::vector<VarDecl*> decls;

    VarDecls() : Node(Type::VarDecls) {}



    ~VarDecls() {

        for (auto exp : decls) {

            deleteAST(exp);

        }

    }

};



struct FunctionDecl : public Node {

    const Identifier* name;

    VarDecls* decls;

    FunctionDecl(Identifier* name, VarDecls* decls) : Node(Type::FunctionDecl), name(name), decls(decls) {}



    ~FunctionDecl(){

        deleteAST(decls);

    }

};



struct FunctionDecls : public Node {

    std::vector<FunctionDecl*> decls;

    FunctionDecls() : Node(Type::FunctionDecls) {}



    ~FunctionDecls() {

        for (auto exp : decls) {

            deleteAST(exp);

        }

    }

};



struct Program : public Function {

    Node fn_type;

    const Keyword* program;

    const Identifier* name;

    ConstDecls* decls;



    explicit Program(const Keyword *program, const Identifier *name, ConstDecls *decls)

            : Function(Type::Program), fn_type(Type::Program), program(program), name(name), decls(decls) {}



    ~Program() {

        deleteAST(decls);

    }

};



struct Procedure : public Function {

    Node fn_type;



    Procedure() : Function(Type::Procedure), fn_type(Type::Procedure) {}

};



struct Ident : public Exp {

    const Identifier* ident;



    explicit Ident(const Identifier* ident) : Exp(Type::Ident), ident(ident) {}

};



struct ExpAssign : public Exp {   //:=

    ExpAssign() : Exp(Type::ExpAssign) {}

};



struct UnExp : public Exp {    //һԪ���� lhs�ǲ��� marker�Ƿ���

    Exp* lhs;

    const Marker* marker;



    explicit UnExp(const Marker* marker, Exp* lhs) : Exp(Type::UnExp), lhs(lhs), marker(marker) {}

    ~UnExp() {

        deleteAST(lhs);

    };

};



struct BiExp : public Exp { //��Ԫ����

    Exp* lhs, * rhs;//���Ҳ���

    const Marker* marker;



    explicit BiExp(Exp* lhs, const Marker* marker, Exp* rhs) : Exp(Type::BiExp), lhs(lhs), rhs(rhs), marker(marker) {}

    ~BiExp() {

        deleteAST(lhs);

        deleteAST(rhs);

    };

};



struct ExpCall : public Exp {

    const Identifier* fn;

    VariableList* params;



    explicit ExpCall(const Identifier* fn, VariableList* params) : Exp(Type::ExpCall), fn(fn), params(params) {}

    ~ExpCall() {

        deleteAST(params);

    };

};



struct Statement : public Exp {

    explicit Statement(Type type) : Exp(type) {}

};



struct StatementBlock : public Statement {

    StatementBlock() : Statement(Type::StatementBlock) {}

};



struct IfElseStatement : public Statement {

    IfElseStatement() : Statement(Type::IfElseStatement) {}

};



struct ForStatement : public Statement {

    ForStatement() : Statement(Type::ForStatement) {}

};



struct ExpConstantInteger : public Exp {

    const ConstantInteger* value;



    explicit ExpConstantInteger(const ConstantInteger* value) : Exp(Type::ExpConstantInteger), value(value) {}

};



struct ExpConstantChar : public Exp {

    const ConstantChar* value;



    explicit ExpConstantChar(const ConstantChar* value) : Exp(Type::ExpConstantChar), value(value) {}

};



struct ExpConstantBoolean : public Exp {

    const ConstantBoolean* value;



    explicit ExpConstantBoolean(const ConstantBoolean* value) : Exp(Type::ExpConstantBoolean), value(value) {}

};



struct ExpConstantString : public Exp {

    const ConstantString* value;



    explicit ExpConstantString(const ConstantString* value) : Exp(Type::ExpConstantString), value(value) {}

};



struct ExpConstantReal : public Exp {

    const ConstantReal* value;



    explicit ExpConstantReal(const ConstantReal* value) : Exp(Type::ExpConstantReal), value(value) {}

};


struct ExpMarker : public Exp {
  const Marker* value;


  explicit ExpMarker(const Marker* value) : Exp(Type::ExpMarker), value(value) {}
};

struct ExpKeyword : public Node{
  const Keyword* value;

  explicit ExpKeyword(const Keyword *value) : Node(Type::ExpKeyword), value(value) {}
};

#endif
