//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_assign(const ast::ExpAssign *pAssign) {
    auto rhs = code_gen(pAssign->rhs);
    if (rhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "code_gen_exp_assign rhs error"));
        assert(false);
        return nullptr;
    }
    auto ptr = get_lvalue_pointer(pAssign->lhs);
    if (ptr == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "code_gen_exp_assign lhs error"));
        assert(false);
        return nullptr;
    }

    return assign_lvalue(ptr, rhs);
}
