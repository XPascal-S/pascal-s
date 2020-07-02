//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

inline llvm::Value *create_int64_literal(llvm::LLVMContext &ctx, int64_t literal) {
    return llvm::Constant::getIntegerValue(
            llvm::IntegerType::get(ctx, 64), llvm::APInt(64, literal, true));
}

int64_t LLVMBuilder::calc_periods_size(const ast::ArrayTypeSpec *spec) {
    int64_t ret = 1;
    for (const auto &p : spec->periods) {
        if (p.second < p.first) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "calc periods size error"));
            assert(false);
        }
        ret *= (p.second - p.first + 1);
    }
    return ret;
}

void LLVMBuilder::code_gen_offset(std::vector<llvm::Value *> &offset, const pascal_s::ArrayInfo *ai,
                                  const ast::ExpressionList *exp_list) {
    if (ai->spec->periods.size() != exp_list->explist.size()) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
        assert(false);
        offset.clear();
        return;
    }

    Value *e, *value_offset = create_int64_literal(ctx, 0);
    llvm::Type *llvm_i64 = llvm::IntegerType::get(ctx, 64);
    int64_t mp = 1;
    llvm::ConstantInt *constant_index;

    for (int64_t i = ai->spec->periods.size() - 1; i >= 0; i--) {
        auto &pd = ai->spec->periods[i];
        e = code_gen(exp_list->explist[i]);
        if (e->getType()->isIntegerTy()) {
            if (e->getType()->getIntegerBitWidth() < 64) {
                e = ir_builder.CreateSExt(e, llvm_i64, "exp_ext_tmp");
            }
        } else {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
            assert(false);
            offset.clear();
            return;
        }

        constant_index = llvm::dyn_cast<llvm::ConstantInt>(e);
        if (constant_index) {
            if (constant_index->getValue().getSExtValue() < pd.first) {
                errors.push_back(new PascalSSemanticError(__FUNCTION__, "constant array index underflow error"));
                assert(false);
                offset.clear();
                return;
            }
            // todo >= pd.second
            if (constant_index->getValue().getSExtValue() > pd.second) {
                errors.push_back(new PascalSSemanticError(__FUNCTION__, "constant array index overflow error"));
                assert(false);
                offset.clear();
                return;
            }
        }

        value_offset = ir_builder.CreateAdd(
                value_offset,
                ir_builder.CreateMul(
                        ir_builder.CreateSub(
                                e,
                                create_int64_literal(ctx, pd.first)
                        ),
                        create_int64_literal(ctx, mp)
                )
        );
        mp *= (pd.second - pd.first + 1);
    }
    offset.push_back(value_offset);
}
