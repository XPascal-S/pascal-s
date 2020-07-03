//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_unary_exp(const ast::UnExp *pExp) {
    auto lhs = code_gen(pExp->lhs);
    if (lhs == nullptr) {
        llvm_pascal_s_report_semantic_error_n(pExp->lhs, "gen exp error");
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
                    llvm_pascal_s_report_semantic_error_n(pExp->lhs, "llvm type error");
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
                    llvm_pascal_s_report_semantic_error_n(pExp->lhs, "llvm type error");
                    return nullptr;
            }
        default:
            llvm_pascal_s_report_semantic_error_n(pExp->marker, "marker type error");
            return nullptr;
    }
}
