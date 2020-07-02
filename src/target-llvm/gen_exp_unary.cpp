//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_unary_exp(const ast::UnExp *pExp) {
    auto lhs = code_gen(pExp->lhs);
    if (lhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
        assert(false);
        return nullptr;
    }

    switch (pExp->marker->marker_type) {
        case MarkerType::LogicNot:
            switch (lhs->getType()->getTypeID()) {
                case llvm::Type::IntegerTyID:
                    return ir_builder.CreateNot(ir_builder.CreateICmpNE(
                            lhs, llvm::Constant::getIntegerValue(
                                    lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))), "neg_tmp");
                case llvm::Type::DoubleTyID:
                    return ir_builder.CreateNot(ir_builder.CreateFCmpONE(
                            lhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))), "neg_f_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
                    assert(false);
                    return nullptr;
            }
        case MarkerType::Add:
            return lhs;
        case MarkerType::Sub:
            switch (lhs->getType()->getTypeID()) {
                case llvm::Type::IntegerTyID:
                    return ir_builder.CreateNeg(lhs, "neg_tmp");
                case llvm::Type::DoubleTyID:
                    return ir_builder.CreateFNeg(lhs, "neg_f_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
                    assert(false);
                    return nullptr;
            }
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
            assert(false);
            return nullptr;
    }
}
