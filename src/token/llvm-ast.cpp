//
// Created by kamiyoru on 2020/5/8.
//

#include <pascal-s/exception.h>
#include <pascal-s/llvm-ast.h>
#include <cassert>

void ast::deleteAST(Node *node) {
    if (node == nullptr) {
        return;
    }
    switch (node->type) {
        default:
        case Type::Unknown:
            throw RuntimeReinterpretASTException(node);
        case Type::Program:
            delete reinterpret_cast<Program *>(node);
            break;
        case Type::ProgramHead:
            delete reinterpret_cast<ProgramHead *>(node);
            break;
        case Type::ProgramBody:
            delete reinterpret_cast<ProgramBody *>(node);
            break;
        case Type::Procedure:
            delete reinterpret_cast<Procedure *>(node);
            break;
        case Type::ParamSpec:
            delete reinterpret_cast<ParamSpec *>(node);
            break;
        case Type::Function:
            delete reinterpret_cast<Function *>(node);
            break;
//        case Type::StatementBlock:
//            delete reinterpret_cast<StatementBlock *>(node);
//            break;
        case Type::ExpCall:
            delete reinterpret_cast<ExpCall *>(node);
            break;
        case Type::ExecStatement:
            delete reinterpret_cast<ExecStatement *>(node);
            break;
        case Type::IfElseStatement:
            delete reinterpret_cast<IfElseStatement *>(node);
            break;
        case Type::ForStatement:
            delete reinterpret_cast<ForStatement *>(node);
            break;
        case Type::CompoundStatement:
            delete reinterpret_cast<CompoundStatement *>(node);
            break;
        case Type::Ident:
            delete reinterpret_cast<Ident *>(node);
            break;
        case Type::ParamList:
            delete reinterpret_cast<ParamList *>(node);
            break;
        case Type::Variabele:
            delete reinterpret_cast<Variable *>(node);
            break;
        case Type::ExpressionList:
            delete reinterpret_cast<ExpressionList *>(node);
            break;
        case Type::VariableList:
            delete reinterpret_cast<VariableList *>(node);
            break;
        case Type::IdentList:
            delete reinterpret_cast<IdentList *>(node);
            break;
        case Type::ConstDecl:
            delete reinterpret_cast<ConstDecl *>(node);
            break;
        case Type::ConstDecls:
            delete reinterpret_cast<ConstDecls *>(node);
            break;
        case Type::VarDecl:
            delete reinterpret_cast<VarDecl *>(node);
            break;
        case Type::VarDecls:
            delete reinterpret_cast<VarDecls *>(node);
            break;
        case Type::FunctionDecls:
            delete reinterpret_cast<FunctionDecls *>(node);
            break;
        case Type::ExpAssign:
            delete reinterpret_cast<ExpAssign *>(node);
            break;
        case Type::UnExp:
            delete reinterpret_cast<UnExp *>(node);
            break;
        case Type::BiExp:
            delete reinterpret_cast<BiExp *>(node);
            break;
        case Type::ExpConstantBoolean:
            delete reinterpret_cast<ExpConstantBoolean *>(node);
            break;
        case Type::ExpKeyword:
            delete reinterpret_cast<ExpKeyword *>(node);
            break;
        case Type::ExpConstantChar:
            delete reinterpret_cast<ExpConstantChar *>(node);
            break;
        case Type::ExpConstantInteger:
            delete reinterpret_cast<ExpConstantInteger *>(node);
            break;
        case Type::ExpConstantString:
            delete reinterpret_cast<ExpConstantString *>(node);
            break;
        case Type::ExpConstantReal:
            delete reinterpret_cast<ExpConstantReal *>(node);
            break;
        case Type::BasicTypeSpec:
            delete reinterpret_cast<BasicTypeSpec *>(node);
            break;
        case Type::ArrayTypeSpec:
            delete reinterpret_cast<ArrayTypeSpec *>(node);
            break;
    }
}


namespace ast {
    void put_tab(int dep) {
        for (int i = -dep; i < dep; i++) putchar(' ');
    }
}

void ast::printAST(ast::Node *node, int dep) {
    if (node == nullptr) {
        put_tab(dep);
        printf("nullptr\n");
        return;
    }
    switch (node->type) {
        default:
        case Type::Unknown:
            throw RuntimeReinterpretASTException(node);
        case Type::Program:
#define cur_node (reinterpret_cast<ast::Program*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = Program\n");
            put_tab(dep + 1);
            printf("name = %s\n", convertToString(cur_node->programHead->id->ident).c_str());
            // todo: remove const cast
            put_tab(dep + 1);
            printf("param(ids) = \n");
            printAST(const_cast<IdentList *>(cur_node->programHead->idlist), dep + 1);
            put_tab(dep + 1);
            printf("const decls = \n");
            printAST(const_cast<ConstDecls *>(cur_node->programBody->constdecls), dep + 1);
            put_tab(dep + 1);
            printf("var decls = \n");
            printAST(const_cast<VarDecls *>(cur_node->programBody->vardecls), dep + 1);
//            printAST(const_cast<SubprogramDecls*>(cur_node->programBody->subprogram), dep+1);
            put_tab(dep + 1);
            printf("body = \n");
            printAST(const_cast<CompoundStatement *>(cur_node->programBody->compound), dep + 1);

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ParamSpec:
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ParamSpec\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::Procedure:
#define cur_node (reinterpret_cast<ast::Procedure*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = Procedure\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::Function:
            throw std::exception("todo function block");
//#define cur_node (reinterpret_cast<ast::Function*>(node))
//            put_tab(dep);
//            printf("{\n");
//            if (cur_node->fn_def->key_type == KeywordType::Program) {
//#undef  cur_node
//#define cur_node (reinterpret_cast<Program*>(node))
//                put_tab(dep + 1);
//                printf("type = Program\n");
//                put_tab(dep + 1);
//                printf("%s", convertToString(cur_node->name).c_str());
//                put_tab(dep + 1);
//                printf("body = \n");
//                printAST(cur_node->body, dep + 1);
//#undef  cur_node
//            } else {
//                assert(false);
//            }
//            put_tab(dep);
//            printf("}\n");
//            break;
        case Type::CompoundStatement:
#define cur_node (reinterpret_cast<ast::CompoundStatement*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = CompoundStatement\n");
            put_tab(dep + 1);
            printf("inner = \n");
            printAST(const_cast<StatementList *>(cur_node->state), dep + 1);
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::StatementList:
#define cur_node (reinterpret_cast<ast::StatementList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = StatementList\n");
            for (auto &stmt: cur_node->statement) {
                printAST(stmt, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpCall:
#define cur_node (reinterpret_cast<ast::ExpCall*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpCall\n");
            put_tab(dep + 1);
            printf("invoke_target = %s\n", convertToString(cur_node->fn).c_str());
            put_tab(dep + 1);
            printf("invoke_params = \n");

            for (auto exp: cur_node->params->explist) {
                printAST(exp, dep + 1);
            }


            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExecStatement:
#define cur_node (reinterpret_cast<ast::ExecStatement*>(node))
//            printf("{\n");
            printAST(cur_node->exp, dep);
//            put_tab(dep);  printf("}\n");
#undef  cur_node
            break;
        case Type::IfElseStatement:
#define cur_node (reinterpret_cast<ast::IfElseStatement*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = IfElseStatement\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ForStatement:
#define cur_node (reinterpret_cast<ast::ForStatement*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ForStatement\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::Ident:
#define cur_node (reinterpret_cast<ast::Ident*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = Ident\n");
            put_tab(dep + 1);
            printf("value = %s\n", convertToString(cur_node->ident).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ParamList:
#define cur_node (reinterpret_cast<ast::ParamList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ParamList\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::VariableList:
#define cur_node (reinterpret_cast<ast::VariableList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = VariableList\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::IdentList:
#define cur_node (reinterpret_cast<ast::IdentList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = IdentList\n");
            for (auto ident: cur_node->idents) {
                put_tab(dep + 2);
                printf("%s\n", convertToString(ident).c_str());
            }

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ConstDecl:
#define cur_node (reinterpret_cast<ast::ConstDecl*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ConstDecl\n");
            put_tab(dep + 1);
            printf("lhs  = %s\n", convertToString(cur_node->ident).c_str());
            put_tab(dep + 1);
            printf("rhs = \n");
            printAST(const_cast<Exp *>(cur_node->rhs), dep + 1);

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ConstDecls:
#define cur_node (reinterpret_cast<ast::ConstDecls*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ConstDecls\n");
            for (auto c: cur_node->decls) {
                printAST(c, dep + 1);
            }

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::VarDecl:
#define cur_node (reinterpret_cast<ast::VarDecl*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = VarDecl\n");
            put_tab(dep + 1);
            printf("idents = \n");
            printAST(cur_node->idents, dep + 1);
            put_tab(dep + 1);
            printf("type_spec = \n");
            printAST(cur_node->type_spec, dep + 1);


            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::VarDecls:
#define cur_node (reinterpret_cast<ast::VarDecls*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = VarDecls\n");
            for (auto c: cur_node->decls) {
                printAST(c, dep + 1);
            }

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::FunctionDecls:
#define cur_node (reinterpret_cast<ast::FunctionDecls*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = FunctionDecls\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpAssign:
#define cur_node (reinterpret_cast<ast::ExpAssign*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpAssign\n");
            put_tab(dep + 1);
            printf("lhs = \n");
            printAST(cur_node->lhs, dep + 1);
            put_tab(dep + 1);
            printf("rhs = \n");
            printAST(cur_node->rhs, dep + 1);

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::UnExp:
#define cur_node (reinterpret_cast<ast::UnExp*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = UnExp\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::BiExp:
#define cur_node (reinterpret_cast<ast::BiExp*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = BiExp\n");

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantBoolean:
#define cur_node (reinterpret_cast<ast::ExpConstantBoolean*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantBoolean\n");
            put_tab(dep + 1);
            printf("value = %s\n", convertToString(cur_node->value).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantChar:
#define cur_node (reinterpret_cast<ast::ExpConstantChar*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantChar\n");
            put_tab(dep + 1);
            printf("value = %s\n", convertToString(cur_node->value).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantInteger:
#define cur_node (reinterpret_cast<ast::ExpConstantInteger*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantInteger\n");
            put_tab(dep + 1);
            printf("value = %s\n", convertToString(cur_node->value).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantString:
#define cur_node (reinterpret_cast<ast::ExpConstantString*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantString\n");
            put_tab(dep + 1);
            printf("value = %s\n", convertToString(cur_node->value).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantReal:
#define cur_node (reinterpret_cast<ast::ExpConstantReal*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantReal\n");
            put_tab(dep + 1);
            printf("value = %s\n", convertToString(cur_node->value).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::BasicTypeSpec:
#define cur_node (reinterpret_cast<ast::BasicTypeSpec*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = BasicTypeSpec\n");
            printf("key_type = %s\n", convertToString(cur_node->keyword).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ArrayTypeSpec:
#define cur_node (reinterpret_cast<ast::ArrayTypeSpec*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ArrayTypeSpec\n");
            put_tab(dep + 1);
            printf("range = \n");
            for (auto &pr: cur_node->periods) {
                put_tab(dep + 2);
                printf("[%lld, %lld]\n", pr.first, pr.second);
            }
            put_tab(dep + 1);
            printf("key_type = %s\n", convertToString(cur_node->keyword).c_str());

            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
    }
}