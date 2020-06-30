//
// Created by kamiyoru on 2020/5/8.
//

#ifndef PASCAL_S_LLVM_H
#define PASCAL_S_LLVM_H

#include "llvm/ADT/APFloat.h"
#include "llvm/ADT/STLExtras.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/IRBuilder.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Type.h"
#include "llvm/IR/Verifier.h"
#include <pascal-s/lib/libstdps.h>
#include <stdexcept>
#include <pascal-s/llvm-ast.h>
#include <iostream>
#include "llvm/IR/LegacyPassManager.h"
#include <pascal-s/exception.h>

extern const char *pascal_main_function_name;

namespace pascal_s {
    struct ArrayInfo {
        const ast::ArrayTypeSpec *spec;
    };
}

// 用于生成目标中间代码LLVM-IR
struct LLVMBuilder {
    using LLVMContext = llvm::LLVMContext;
    using Module = llvm::Module;
    using Value = llvm::Value;
    using Function = llvm::Function;

    LLVMContext ctx;
    llvm::IRBuilder<> ir_builder;
    llvm::legacy::FunctionPassManager fn_pass_manager;
    Module modules;
    std::vector<PascalSSemanticError *> errors;

    struct LinkedContext {
        LinkedContext *last;
        std::map<std::string, pascal_s::ArrayInfo *> *array_infos;
        std::map<std::string, llvm::AllocaInst *> *ctx;
        std::map<std::string, Value *> *const_ctx;

        ~LinkedContext() {
            deconstruct();
        }

        void deconstruct() const {
            for (auto &ai: *array_infos) {
                delete ai.second;
            }
        }
    };

    LinkedContext *scope_stack;

    LLVMBuilder() :
            ir_builder(ctx), modules("llvm-pascal-s", ctx), fn_pass_manager(&modules), scope_stack(nullptr) {
        prepend_lib_standard_pascal_s();
    }

    ~LLVMBuilder() {
        for (auto e: errors) {
            delete e;
        }
    }

    bool doInitialization() {
        return fn_pass_manager.doInitialization();
    }

    void prepend_lib_standard_pascal_s();

    void insert_var_decls(Function *cur_func, std::map<std::string, pascal_s::ArrayInfo *> &array_infos,
                          std::map<std::string, llvm::AllocaInst *> &map, const ast::VarDecls *pDecls);

    void insert_const_decls(std::map<std::string, llvm::Value *> &map, const ast::ConstDecls *pDecls);

    int64_t calc_periods_size(const ast::ArrayTypeSpec *spec);

    llvm::Type *create_type(const ast::TypeSpec *spec);

    llvm::Type *create_basic_type(const ast::BasicTypeSpec *spec);

    llvm::Type *create_basic_type_from_keyword(KeywordType spec);

    Function *code_gen_program(const ast::Program *pProgram);

    Function *rename_program_to_pascal_s_native(Function *f);

    static void insert_param_decls(Function *fn,
                                   std::map<std::string, llvm::AllocaInst *> &map,
                                   std::map<std::string, llvm::Value *> &const_map);

    static Function *code_gen_procedure(const ast::Subprogram *pProcedure) {
        throw std::exception("todo code gen procedure");
//        Function *fn = modules.getFunction(pProcedure->subhead->ident->content);
//
//        // create function proto llvm_func
//        if (!fn) {
//            llvm::Type *llvm_ret_type = nullptr;
//            if (pProcedure->return_type == nullptr) {
//                llvm_ret_type = llvm::Type::getVoidTy(ctx);
//            } else {
//                llvm_ret_type = create_type(pProcedure->return_type);
//            }
//
//            int args_proto_size = 0;
//
//            for (auto arg_spec : pProcedure->params->params) {
//                args_proto_size += arg_spec->id_list->idents.size();
//            }
//
//            std::vector<llvm::Type *> args_proto;
//            args_proto.reserve(args_proto_size);
//
//            for (auto arg_spec : pProcedure->params->params) {
//                llvm::Type *llvm_arg_type = create_type(arg_spec->spec);
//
//                if (arg_spec->keyword_var != nullptr) {
//                    llvm_arg_type = llvm_arg_type->getPointerTo();
//                }
//
//                for (auto ident: arg_spec->id_list->idents) {
//                    args_proto.push_back(llvm_arg_type);
//                }
//            }
//
//            auto *prototype = llvm::FunctionType::get(
//                    llvm_ret_type, args_proto, false);
//
//            fn = Function::Create(prototype, Function::ExternalLinkage,
//                                  pProcedure->subhead->ident->content, modules);
//
//            int arg_cursor = 0;
//            for (auto arg_spec : pProcedure->params->params) {
//                for (auto ident: arg_spec->id_list->idents) {
//                    fn->getArg(arg_cursor++)->setName(ident->content);
//                }
//            }
//        } else {
//            for (int i = 0; i < program->arg_size(); i++) {
//                const auto &arg = program->getArg(i);
//            }
//            //todo action fn existed
//        }
//
//        // out_code('entry:')
//        llvm::BasicBlock *body = llvm::BasicBlock::Create(ctx, "entry", fn);
//        ir_builder.SetInsertPoint(body);
//
//        // create local variable map this.ctx
//        std::map<std::string, llvm::AllocaInst *> program_this;
//        insert_var_decls(fn, program_this, pProcedure->var_decls);
//        // create local const map this.const_ctx
//        std::map<std::string, Value *> program_const_this;
//        insert_const_decls(program_const_this, pProcedure->const_decls);
//        insert_param_decls(fn, program_this, program_const_this);
//
//        // push 'this' into scope stack
//        auto link = LinkedContext{scope_stack, &program_this, &program_const_this};
//        scope_stack = &link;
//
//        // out_code( define variable ret_type: %procedure.name )
//        llvm::IRBuilder<> dfn_block(&fn->getEntryBlock(), fn->getEntryBlock().begin());
//        program_this[pProcedure->subhead->ident->content] = dfn_block.CreateAlloca(
//                fn->getReturnType(), nullptr, pProcedure->subhead->ident->content);
//
//        // generate body
//        if (code_gen_statement(pProcedure->body)) {
//            // if body generated
//            // out_code( %ret_tmp = load ret_type from %procedure.name )
//            // out_code( ret ret_type: %ret_tmp )
//            ir_builder.CreateRet(
//                    ir_builder.CreateLoad(program_this[pProcedure->subhead->ident->content], "ret_tmp"));
//
//            llvm::verifyFunction(*fn);
//            fn_pass_manager.run(*fn);
//
//            // pop 'this' from scope stack
//        scope_stack->deconstruct();
//            scope_stack = link.last;
//            return fn;
//        }
//
//        fn->eraseFromParent();
//        // pop 'this' from scope stack
//        scope_stack->deconstruct();
//        scope_stack = link.last;
        return nullptr;
    }

    Value *code_gen_statement_block(const ast::StatementList *pBlock);

    Value *code_gen_exp_call(const ast::ExpCall *pCall);

    Value *code_gen_exec_statement(const ast::ExecStatement *pStatement) {
        return code_gen(pStatement->exp);
    }

    Value *code_gen_if_else_statement(const ast::IfElseStatement *if_else_stmt);

    Value *code_gen_for_statement(const ast::ForStatement *for_stmt);

    Value *code_gen_binary_exp(const ast::BiExp *pExp);

    Value *code_gen_unary_exp(const ast::UnExp *pExp);

    Value *code_gen_exp_assign(const ast::ExpAssign *pAssign);

    Value *assign_lvalue(const ast::Exp *lvalue, Value *rhs);

    Value *get_lvalue_pointer(const ast::Exp *lvalue);

    Value *get_named_value_pointer(const char *name);

    Value *code_gen_exp_constant_integer(const ast::ExpConstantInteger *pInteger) {
        return llvm::Constant::getIntegerValue(
                llvm::Type::getInt64Ty(ctx), llvm::APInt(64, pInteger->value->attr));
    }

    Value *code_gen_exp_constant_char(const ast::ExpConstantChar *pChar) {
        return llvm::Constant::getIntegerValue(
                llvm::Type::getInt8Ty(ctx), llvm::APInt(8, pChar->value->attr));
    }

    Value *code_gen_exp_constant_real(const ast::ExpConstantReal *pReal) {
        return llvm::ConstantFP::get(
                llvm::Type::getDoubleTy(ctx), llvm::APFloat(pReal->value->attr));
    }

    Value *code_gen_exp_constant_boolean(const ast::ExpConstantBoolean *pBoolean) {
        return llvm::Constant::getIntegerValue(
                llvm::Type::getInt8Ty(ctx), llvm::APInt(8, pBoolean->value->attr));
    }

    Value *code_gen_exp_constant_string(const ast::ExpConstantString *) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                  "code_gen_exp_constant_string 2"));
        assert(false);
        return nullptr;
    }

    Value *code_gen_ident(const ast::Ident *pIdent) {
        for (auto resolving_ctx = scope_stack;
             resolving_ctx; resolving_ctx = resolving_ctx->last) {
            auto &value_ctx = resolving_ctx->ctx;
            if (value_ctx->count(pIdent->ident->content)) {
                return ir_builder.CreateLoad(value_ctx->at(pIdent->ident->content), "load_tmp");
            }
            auto &const_ctx = resolving_ctx->const_ctx;
            if (const_ctx->count(pIdent->ident->content)) {
                return const_ctx->at(pIdent->ident->content);
            }
        }
        // get function proto llvm_func
        Function *calleeFunc = modules.getFunction(pIdent->ident->content);
        if (!calleeFunc) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get callee error"));
            assert(false);
            return nullptr;
        }
        if (calleeFunc->arg_size() != 0) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                      "callee func param size does not match exp list size"));
            assert(false);
            return nullptr;
        }
        std::vector<Value *> args;


        // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
        return ir_builder.CreateCall(calleeFunc, args, pIdent->ident->content);
    }

//    Value *code_gen_variable_list(const ast::VariableList *pList) {
//        return nullptr;
//    }
//
//    Value *code_gen_function_decls(const ast::FunctionDecls *pDecls) {
//        return nullptr;
//    }
//
//    Value *code_gen_param_list(const ast::ParamList *pList) {
//        return nullptr;
//    }
//
//    Value *code_gen_ident_list(const ast::IdentList *pList) {
//        return nullptr;
//    }

    Value *code_gen_function(const ast::Function *pFunction) {
        switch (pFunction->type) {
            // return gen_program() if function.type == program
            case ast::Type::Program:
                return code_gen_program(
                        reinterpret_cast<const ast::Program *>(pFunction));
                // else return gen_procedure() if function.type == procedure(with ret type or without)
            case ast::Type::Subprogram:
                return code_gen_procedure(
                        reinterpret_cast<const ast::Subprogram *>(pFunction));
            default:
                assert(false);
                return nullptr;
        }
    }

    Value *code_gen_statement(const ast::Statement *stmt) {
        switch (stmt->type) {
            case ast::Type::StatementList:
                return code_gen_statement_block(
                        reinterpret_cast<const ast::StatementList *>(stmt));
            case ast::Type::CompoundStatement:
                return code_gen_statement_block(
                        reinterpret_cast<const ast::CompoundStatement *>(stmt)->state);
            case ast::Type::ExecStatement:
                return code_gen_exec_statement(
                        reinterpret_cast<const ast::ExecStatement *>(stmt));
            case ast::Type::IfElseStatement:
                return code_gen_if_else_statement(
                        reinterpret_cast<const ast::IfElseStatement *>(stmt));
            case ast::Type::ForStatement:
                return code_gen_for_statement(
                        reinterpret_cast<const ast::ForStatement *>(stmt));
            default:
                assert(false);
                return nullptr;
        }
    }

    Value *code_gen(const ast::Node *node) {
        switch (node->type) {
            default:
                assert(false);
                return nullptr;
            case ast::Type::Unknown:
                assert(false);
                return nullptr;
            case ast::Type::Program:
                return code_gen_program(
                        reinterpret_cast<const ast::Program *>(node));
            case ast::Type::Subprogram:
                return code_gen_procedure(
                        reinterpret_cast<const ast::Subprogram *>(node));
            case ast::Type::Function:
                return code_gen_function(
                        reinterpret_cast<const ast::Function *>(node));
            case ast::Type::StatementList:
                return code_gen_statement_block(
                        reinterpret_cast<const ast::StatementList *>(node));
            case ast::Type::ExpCall:
                return code_gen_exp_call(
                        reinterpret_cast<const ast::ExpCall *>(node));
            case ast::Type::ExecStatement:
                return code_gen_exec_statement(
                        reinterpret_cast<const ast::ExecStatement *>(node));
            case ast::Type::IfElseStatement:
                return code_gen_if_else_statement(
                        reinterpret_cast<const ast::IfElseStatement *>(node));
            case ast::Type::ForStatement:
                return code_gen_for_statement(
                        reinterpret_cast<const ast::ForStatement *>(node));
            case ast::Type::ExpConstantInteger:
                return code_gen_exp_constant_integer(
                        reinterpret_cast<const ast::ExpConstantInteger *>(node));
            case ast::Type::ExpConstantChar:
                return code_gen_exp_constant_char(
                        reinterpret_cast<const ast::ExpConstantChar *>(node));
            case ast::Type::ExpConstantBoolean:
                return code_gen_exp_constant_boolean(
                        reinterpret_cast<const ast::ExpConstantBoolean *>(node));
            case ast::Type::ExpConstantString:
                return code_gen_exp_constant_string(
                        reinterpret_cast<const ast::ExpConstantString *>(node));
            case ast::Type::ExpConstantReal:
                return code_gen_exp_constant_real(
                        reinterpret_cast<const ast::ExpConstantReal *>(node));
            case ast::Type::Ident:
                return code_gen_ident(
                        reinterpret_cast<const ast::Ident *>(node));
//            case ast::Type::ParamList:
//                return code_gen_param_list(
//                        reinterpret_cast<const ast::ParamList *>(node));
//            case ast::Type::VariableList:
//                return code_gen_variable_list(
//                        reinterpret_cast<const ast::VariableList *>(node));
//            case ast::Type::IdentList:
//                return code_gen_ident_list(
//                        reinterpret_cast<const ast::IdentList *>(node));
//            case ast::Type::ConstDecl:
//                return code_gen_const_decl(
//                        reinterpret_cast<const ast::ConstDecl *>(node));
//            case ast::Type::ConstDecls:
//                return code_gen_const_decls(
//                        reinterpret_cast<const ast::ConstDecls *>(node));
//            case ast::Type::VarDecl:
//                return code_gen_var_decl(
//                        reinterpret_cast<const ast::VarDecl *>(node));
//            case ast::Type::VarDecls:
//                return code_gen_var_decls(
//                        reinterpret_cast<const ast::VarDecls *>(node));
//            case ast::Type::FunctionDecls:
//                return code_gen_function_decls(
//                        reinterpret_cast<const ast::FunctionDecls *>(node));
            case ast::Type::ExpAssign:
                return code_gen_exp_assign(
                        reinterpret_cast<const ast::ExpAssign *>(node));
            case ast::Type::UnExp:
                return code_gen_unary_exp(
                        reinterpret_cast<const ast::UnExp *>(node));
            case ast::Type::BiExp:
                return code_gen_binary_exp(
                        reinterpret_cast<const ast::BiExp *>(node));
//            case ast::Type::BasicTypeSpec:
//                return code_gen_BasicTypeSpec(
//                        reinterpret_cast<const ast::BasicTypeSpec*>(node));
//            case ast::Type::ArrayTypeSpec:
//                return code_gen_ArrayTypeSpec(
//                        reinterpret_cast<const ast::ArrayTypeSpec*>(node));
            case ast::Type::CompoundStatement:
                return code_gen_statement_block(
                        reinterpret_cast<const ast::CompoundStatement *>(node)->state);
            case ast::Type::FormalParameter:
                assert(false);
                break;
            case ast::Type::Variabele:
                assert(false);
                break;
            case ast::Type::Expression:
                assert(false);
                break;
            case ast::Type::SimpleExpression:
                assert(false);
                break;
            case ast::Type::Procedure:
                assert(false);
                break;
            case ast::Type::Exp:
                assert(false);
                break;
        }
    }
};


#endif //PASCAL_S_LLVM_H
