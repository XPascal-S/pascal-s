//
// Created by kamiyoru on 2020/5/8.
//

#include <pascal-s/AST.h>
#include <pascal-s/exception.h>
#include <cstdio>

void deleteAST(Node *node) {
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
        case Type::Procedure:
            delete reinterpret_cast<Procedure *>(node);
            break;
//        case Type::ParamSpec:
//            delete reinterpret_cast<ParamSpec *>(node);
//            break;
        case Type::Function:
            delete reinterpret_cast<Function *>(node);
            break;
        case Type::StatementBlock:
            delete reinterpret_cast<StatementBlock *>(node);
            break;
        case Type::ExpCall:
            delete reinterpret_cast<ExpCall *>(node);
            break;
//        case Type::ExecStatement:
//            delete reinterpret_cast<ExecStatement *>(node);
//            break;
        case Type::IfElseStatement:
            delete reinterpret_cast<IfElseStatement *>(node);
            break;
        case Type::ForStatement:
            delete reinterpret_cast<ForStatement *>(node);
            break;
        case Type::Ident:
            delete reinterpret_cast<Ident *>(node);
            break;
        case Type::ParamList:
            delete reinterpret_cast<ParamList *>(node);
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


//namespace ast {
    void put_tab(int dep) {
        for (int i = -dep; i < dep; i++) putchar(' ');
    }
//}

void printAST(Node *node, int dep) {
    if (node == nullptr) {
        printf("nullptr\n");
        return;
    }
    switch (node->type) {
        default:
        case Type::Unknown:
          throw RuntimeReinterpretASTException(node);
        case Type::Program:
#define cur_node (reinterpret_cast<Procedure*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = Program\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
//        case Type::ParamSpec:
//            put_tab(dep);
//            printf("{\n");
//            put_tab(dep + 1);
//            printf("type = ParamSpec\n");
//
//            put_tab(dep);
//            printf("}\n");
#undef cur_node
            break;
  case Type::Procedure:
#define cur_node (reinterpret_cast<Procedure*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = Procedure\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::Function:
#define cur_node (reinterpret_cast<Function*>(node))
            put_tab(dep);
            printf("{\n");
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
            put_tab(dep);
            printf("}\n");
            break;
        case Type::StatementBlock:
#define cur_node (reinterpret_cast<StatementBlock*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = StatementBlock\n");
//            for (auto &stmt: cur_node->stmts) {
//                printAST(stmt, dep + 1);
//            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpCall:
#define cur_node (reinterpret_cast<ExpCall*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpCall\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
//        case Type::ExecStatement:
//#define cur_node (reinterpret_cast<ExecStatement*>(node))
////            printf("{\n");
//            printAST(cur_node->exp, dep);
////            put_tab(dep);  printf("}\n");
//#undef  cur_node
//            break;
        case Type::IfElseStatement:
#define cur_node (reinterpret_cast<IfElseStatement*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = IfElseStatement\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ForStatement:
#define cur_node (reinterpret_cast<ForStatement*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ForStatement\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::Ident:
#define cur_node (reinterpret_cast<Ident*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = Ident\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ParamList:
#define cur_node (reinterpret_cast<ParamList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ParamList\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::VariableList:
#define cur_node (reinterpret_cast<VariableList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = VariableList\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::IdentList:
#define cur_node (reinterpret_cast<IdentList*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = IdentList\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ConstDecl:
#define cur_node (reinterpret_cast<ConstDecl*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ConstDecl\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ConstDecls:
#define cur_node (reinterpret_cast<ConstDecls*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ConstDecls\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::VarDecl:
#define cur_node (reinterpret_cast<VarDecl*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = VarDecl\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::VarDecls:
#define cur_node (reinterpret_cast<VarDecls*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = VarDecls\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::FunctionDecls:
#define cur_node (reinterpret_cast<FunctionDecls*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = FunctionDecls\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpAssign:
#define cur_node (reinterpret_cast<ExpAssign*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpAssign\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep+1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::UnExp:
#define cur_node (reinterpret_cast<UnExp*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = UnExp\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::BiExp:
#define cur_node (reinterpret_cast<BiExp*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = BiExp\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantBoolean:
#define cur_node (reinterpret_cast<ExpConstantBoolean*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantBoolean\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantChar:
#define cur_node (reinterpret_cast<ExpConstantChar*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantChar\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantInteger:
#define cur_node (reinterpret_cast<ExpConstantInteger*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantInteger\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantString:
#define cur_node (reinterpret_cast<ExpConstantString*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantString\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpConstantReal:
#define cur_node (reinterpret_cast<ExpConstantReal*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ExpConstantReal\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::BasicTypeSpec:
#define cur_node (reinterpret_cast<BasicTypeSpec*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = BasicTypeSpec\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ArrayTypeSpec:
#define cur_node (reinterpret_cast<ArrayTypeSpec*>(node))
            put_tab(dep);
            printf("{\n");
            put_tab(dep + 1);
            printf("type = ArrayTypeSpec\n");
            for (Node *c : cur_node->children) {
              printAST(c, dep + 1);
            }
            put_tab(dep);
            printf("}\n");
#undef  cur_node
            break;
        case Type::ExpMarker : put_tab(dep);
#define cur_node (reinterpret_cast<ExpMarker *>(node))
            printf("{\n");
            put_tab(dep + 1);
            printf("type = marker %s\n", cur_node->value->content);
            put_tab(dep);
            printf("}\n");
#undef cur_node
            break;
    }
}
