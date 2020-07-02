//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_integer(const ast::ExpConstantInteger *pInteger) {
    return llvm::Constant::getIntegerValue(
            llvm::Type::getInt64Ty(ctx), llvm::APInt(64, pInteger->value->attr));
}


LLVMBuilder::Value *LLVMBuilder::code_gen_ident(const ast::Ident *pIdent) {
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
    if (calleeFunc->getReturnType()->isVoidTy()) {
        return ir_builder.CreateCall(calleeFunc, args);
    } else {
        return ir_builder.CreateCall(calleeFunc, args, pIdent->ident->content);
    }
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_string(const ast::ExpConstantString *) {
    errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                              "code_gen_exp_constant_string 2"));
    assert(false);
    return nullptr;
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_boolean(const ast::ExpConstantBoolean *pBoolean) {
    return llvm::Constant::getIntegerValue(
            llvm::Type::getInt1Ty(ctx), llvm::APInt(8, pBoolean->value->attr));
}

LLVMBuilder::Value *LLVMBuilder::code_gen_variable(const ast::Variable *node) {
    auto ptr = get_lvalue_pointer(node);
    if (ptr == nullptr) {
        assert(false);
        return nullptr;
    }
    return ir_builder.CreateLoad(ptr, "arr_load");
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_char(const ast::ExpConstantChar *pChar) {
    return llvm::Constant::getIntegerValue(
            llvm::Type::getInt8Ty(ctx), llvm::APInt(8, pChar->value->attr));
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_real(const ast::ExpConstantReal *pReal) {
    return llvm::ConstantFP::get(
            llvm::Type::getDoubleTy(ctx), llvm::APFloat(pReal->value->attr));
}
