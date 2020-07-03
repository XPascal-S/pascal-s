//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_assign(const ast::ExpAssign *pAssign) {
    auto rhs = code_gen(pAssign->rhs);
    auto ptr = get_lvalue_pointer(pAssign->lhs);
    if (ptr == nullptr || rhs == nullptr) {
        return nullptr;
    }

    return assign_lvalue(pAssign->lhs->visit_pos(), ptr, rhs);
}
