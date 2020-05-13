//
// Created by kamiyoru on 2020/5/12.
//

#ifndef PASCAL_S_TARGET_C_H
#define PASCAL_S_TARGET_C_H

#include <pascal-s/AST.h>
#include <fmt/core.h>
#include <vector>
#include <string>

namespace target_c {
    class Buffer {

        std::ostream &os;
    public:
        Buffer(std::ostream &s) : os(s) {
        }

        Buffer &write(const std::string &s) {
            os << s;
            return *this;
        }

        Buffer &writeln(const std::string &s) {
            os << s << '\n';
            return *this;
        }
    };

    struct LinkedContext {
        LinkedContext *last;
        std::map<std::string, std::string> *content;
    };

    struct CBuilder {

        enum TranslateCode {
            OK,
            TranslateFailed,
        };
        std::vector<std::string> include_files;
        Buffer &buf;
        LinkedContext *current_linkedCtx;

        CBuilder(std::vector<std::string> &include_files,
                 Buffer &buf) : include_files(std::move(include_files)), buf(buf) {}

        CBuilder(std::vector<std::string> &&include_files,
                 Buffer &buf) : include_files(std::move(include_files)), buf(buf) {}

        int code_gen(const Node *node){
            for (const auto &f : include_files) {
                buf.writeln(fmt::format("#include <{}>", f));
            }

            if (node->type != Type::Program) {
                assert(false);
                return TranslateFailed;
            }

            int code = code_gen_node(node);
            buf
                    .writeln("int main(){")
                    .writeln(fmt::format("return {}();", (reinterpret_cast<const Program *>(node))->name->content))
                    .writeln("}");
            return code;
        }

        int code_gen_node(const Node *node){
            switch (node->type) {
                default:
                    assert(false);
                    return TranslateFailed;
                case Type::Unknown:
                    assert(false);
                    return TranslateFailed;
                case Type::Program:
                    return code_gen_program(
                            reinterpret_cast<const Program *>(node));
//                case Type::Procedure:
//                    return code_gen_procedure(
//                            reinterpret_cast<const Procedure *>(node));
//                case Type::Function:
//                    return code_gen_function(
//                            reinterpret_cast<const Function *>(node));
//                case Type::StatementBlock:
//                    return code_gen_statement_block(
//                            reinterpret_cast<const StatementBlock *>(node));
//                case Type::ExpCall:
//                    return code_gen_exp_call(
//                            reinterpret_cast<const ExpCall *>(node));
//                case Type::ExecStatement:
//                    return code_gen_exec_statement(
//                            reinterpret_cast<const ExecStatement *>(node));
//                case Type::IfElseStatement:
//                    return code_gen_if_else_statement(
//                            reinterpret_cast<const IfElseStatement *>(node));
//                case Type::ForStatement:
//                    return code_gen_for_statement(
//                            reinterpret_cast<const ForStatement *>(node));
//                case Type::ExpConstantInteger:
//                    return code_gen_exp_constant_integer(
//                            reinterpret_cast<const ExpConstantInteger *>(node));
//                case Type::ExpConstantChar:
//                    return code_gen_exp_constant_char(
//                            reinterpret_cast<const ExpConstantChar *>(node));
//                case Type::ExpConstantBoolean:
//                    return code_gen_exp_constant_boolean(
//                            reinterpret_cast<const ExpConstantBoolean *>(node));
//                case Type::ExpConstantString:
//                    return code_gen_exp_constant_string(
//                            reinterpret_cast<const ExpConstantString *>(node));
//                case Type::ExpConstantReal:
//                    return code_gen_exp_constant_real(
//                            reinterpret_cast<const ExpConstantReal *>(node));
//                case Type::Ident:
//                    return code_gen_ident(
//                            reinterpret_cast<const Ident *>(node));
//            case Type::ParamList:
//                return code_gen_param_list(
//                        reinterpret_cast<const ParamList *>(node));
//            case Type::VariableList:
//                return code_gen_variable_list(
//                        reinterpret_cast<const VariableList *>(node));
//            case Type::IdentList:
//                return code_gen_ident_list(
//                        reinterpret_cast<const IdentList *>(node));
//                case Type::ConstDecl:
//                    return code_gen_const_decl(
//                            reinterpret_cast<const ConstDecl *>(node));
//            case Type::ConstDecls:
//                return code_gen_const_decls(
//                        reinterpret_cast<const ConstDecls *>(node));
//            case Type::VarDecl:
//                return code_gen_var_decl(
//                        reinterpret_cast<const VarDecl *>(node));
//            case Type::VarDecls:
//                return code_gen_var_decls(
//                        reinterpret_cast<const VarDecls *>(node));
//            case Type::FunctionDecls:
//                return code_gen_function_decls(
//                        reinterpret_cast<const FunctionDecls *>(node));
//                case Type::ExpAssign:
//                    return code_gen_exp_assign(
//                            reinterpret_cast<const ExpAssign *>(node));
//                case Type::UnExp:
//                    return code_gen_unary_exp(
//                            reinterpret_cast<const UnExp *>(node));
//                case Type::BiExp:
//                    return code_gen_binary_exp(
//                            reinterpret_cast<const BiExp *>(node));
//            case Type::BasicTypeSpec:
//                return code_gen_BasicTypeSpec(
//                        reinterpret_cast<const BasicTypeSpec*>(node))
//                case Type::ArrayTypeSpec:
//                    return code_gen_ArrayTypeSpec(
//                            reinterpret_cast<const ArrayTypeSpec *>(node));
            }
        }

        int code_gen_program(const Program *node){
            // in fmt::format {{ = {, }} = }
            buf.writeln(fmt::format("int {}(){{", node->name->content));
            buf.writeln("printf(\"hello world\");");
            buf.writeln("}");
            return OK;
        }

        int code_gen_ArrayTypeSpec(const ArrayTypeSpec *node);

        int code_gen_exp_assign(const ExpAssign *node);

        int search_for_symbol(const std::string &symbol, std::string &value){
            LinkedContext *now_ctx = current_linkedCtx;
            while(now_ctx != NULL){
                if(now_ctx->content->count(symbol) > 0){
                    value = now_ctx->content->find(symbol)->second ;
                    return OK;
                }else{
                    now_ctx = current_linkedCtx->last;
                }
            }
            throw std::runtime_error(fmt::format("symbol {} not found", symbol));
            return TranslateFailed;
        }

        void insert_const_decls(std::map<std::string, std::string> &map, ConstDecls *pDecls){
            if (pDecls != nullptr){
                for (auto decl : pDecls->decls){
                }
            }
        }

        int convert_exp_to_str(const Exp *expression, std::string &result){
            switch(expression->type) {
                case Type::UnExp:
                    result +=  reinterpret_cast<const UnExp *>(expression)->marker->content;
                    return convert_exp_to_str( reinterpret_cast<const UnExp *>(expression)->lhs,result);
                case Type::BiExp:
                    convert_exp_to_str(reinterpret_cast<const BiExp *>(expression)->lhs, result);
                    result += std::string(" ") + reinterpret_cast<const BiExp *>(expression)->marker->content + std::string(" ");
                    return convert_exp_to_str(reinterpret_cast<const BiExp *>(expression)->rhs, result);
                case Type::ExpConstantInteger:
                    result += reinterpret_cast<const ExpConstantInteger *>(expression)->value->content;
                    return OK;
                case Type::ExpConstantChar:
                    result += reinterpret_cast<const ExpConstantChar *>(expression)->value->content;
                    return OK;
                case Type::ExpConstantBoolean:
                    if(reinterpret_cast<const ExpConstantBoolean *>(expression)->value->attr == 1)
                        result += "1";
                    else if(reinterpret_cast<const ExpConstantBoolean *>(expression)->value->attr == 0)
                        result += "0";
                    else
                        return TranslateFailed;
                    return OK;
                case Type::ExpConstantString:
                    result += reinterpret_cast<const ExpConstantString *>(expression)->value->content;
                    return OK;
                case Type::ExpConstantReal:
                    result += reinterpret_cast<const ExpConstantString *>(expression)->value->content;
                    return OK;
                default:
                    throw std::runtime_error("expression_to_str error");
            }
        }
    };
}


#endif //PASCAL_S_TARGET_C_H

