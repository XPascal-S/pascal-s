//
// Created by kamiyoru on 2020/5/12.
//
#include <target/c.h>

int target_c::CBuilder::code_gen(const Node *node){
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

int target_c::CBuilder::code_gen_node(const Node *node) {
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
//            case Type::ConstDecl:
//                return code_gen_const_decl(
//                        reinterpret_cast<const ConstDecl *>(node));
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
//                        reinterpret_cast<const BasicTypeSpec*>(node));
//            case Type::ArrayTypeSpec:
//                return code_gen_ArrayTypeSpec(
//                        reinterpret_cast<const ArrayTypeSpec*>(node));
    }
}

int target_c::CBuilder::code_gen_program(const Program *node) {
    // in fmt::format {{ = {, }} = }
    buf.writeln(fmt::format("int {}(){{", node->name->content));
    buf.writeln("printf(\"hello world\");");
    buf.writeln("}");
    return OK;
}



