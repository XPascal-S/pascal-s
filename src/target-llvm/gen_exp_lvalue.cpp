//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>


llvm::Value *LLVMBuilder::get_lvalue_pointer(const ast::Exp *lvalue) {

    const char *content = nullptr;
    const ast::ExpressionList *exp_list = nullptr;
    switch (lvalue->type) {
        case ast::Type::Ident:
            content = reinterpret_cast<const ast::Ident *>(lvalue)->ident->content;
            break;
        case ast::Type::Variabele:
            content = reinterpret_cast<const ast::Variable *>(lvalue)->id->content;
            exp_list = reinterpret_cast<const ast::Variable *>(lvalue)->id_var;
            break;
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer error"));
            assert(false);
            return nullptr;
    }

    std::vector<Value *> offset;

    for (auto resolving_ctx = scope_stack;
         resolving_ctx; resolving_ctx = resolving_ctx->last) {
        auto &value_ctx = resolving_ctx->ctx;
        if (value_ctx->count(content)) {
            if (resolving_ctx->array_infos->count(content)) {
                if (exp_list != nullptr) {
                    offset.push_back(llvm::ConstantInt::get(ctx, llvm::APInt(64, 0, true)));
                    code_gen_offset(offset, resolving_ctx->array_infos->at(content), exp_list);
                } else {
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer error 2"));
                    assert(false);
                    return nullptr;
                }
            }

            auto ptr = (*value_ctx).at(content);

            if (offset.empty()) {
                return ptr;
            } else {
                return ir_builder.CreateGEP(ptr, offset, "gep_tmp");
            }
        }
        auto &const_ctx = resolving_ctx->const_ctx;
        if (const_ctx->count(content)) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer const error 3"));
            assert(false);
            return nullptr;
        }
    }
    errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer not found error"));
    assert(false);
    return nullptr;
}

