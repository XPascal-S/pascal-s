//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_binary_exp(const ast::BiExp *pExp) {
    auto lhs = code_gen(pExp->lhs);
    auto rhs = code_gen(pExp->rhs);
    if (lhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp eval lhs error"));
        assert(false);
        return nullptr;
    }
    if (rhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp eval rhs error"));
        assert(false);
        return nullptr;
    }

    if (lhs->getType()->getTypeID() != rhs->getType()->getTypeID()) {
        // todo: signed/unsigned integer type feature
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary type conflict error"));
        assert(false);
        return nullptr;
    }
    switch (lhs->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            switch (pExp->marker->marker_type) {
                case MarkerType::LogicAnd:
                    return ir_builder.CreateAnd(
                            ir_builder.CreateICmpNE(
                                    lhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            ir_builder.CreateICmpNE(
                                    rhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            "and_tmp");
                case MarkerType::LogicOr:
                    return ir_builder.CreateOr(
                            ir_builder.CreateICmpNE(
                                    lhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            ir_builder.CreateICmpNE(
                                    rhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            "or_tmp");

                case MarkerType::Add:
                    return ir_builder.CreateAdd(lhs, rhs, "add_tmp");
                case MarkerType::Sub:
                    return ir_builder.CreateSub(lhs, rhs, "sub_tmp");
                case MarkerType::Mul:
                    return ir_builder.CreateMul(lhs, rhs, "mul_tmp");
                case MarkerType::Div:
                    return ir_builder.CreateSDiv(lhs, rhs, "div_tmp");
                case MarkerType::Mod:
                    return ir_builder.CreateSRem(lhs, rhs, "mod_tmp");

                case MarkerType::LT:
                    return ir_builder.CreateICmpSLT(lhs, rhs, "lt_tmp");
                case MarkerType::LE:
                    return ir_builder.CreateICmpSLE(lhs, rhs, "le_tmp");
                case MarkerType::GT:
                    return ir_builder.CreateICmpSGT(lhs, rhs, "gt_tmp");
                case MarkerType::GE:
                    return ir_builder.CreateICmpSGE(lhs, rhs, "ge_tmp");
                case MarkerType::EQ:
                    return ir_builder.CreateICmpEQ(lhs, rhs, "eq_tmp");
                case MarkerType::NEQ:
                    return ir_builder.CreateICmpNE(lhs, rhs, "neq_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp error"));
                    assert(false);
                    return nullptr;
            }
        case llvm::Type::DoubleTyID:
            switch (pExp->marker->marker_type) {
                case MarkerType::LogicAnd:
                    return ir_builder.CreateAnd(
                            ir_builder.CreateFCmpONE(
                                    lhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            ir_builder.CreateFCmpONE(
                                    rhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            "and_tmp");
                case MarkerType::LogicOr:
                    return ir_builder.CreateOr(
                            ir_builder.CreateFCmpONE(
                                    lhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            ir_builder.CreateFCmpONE(
                                    rhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            "or_tmp");

                case MarkerType::Add:
                    return ir_builder.CreateFAdd(lhs, rhs, "add_f_tmp");
                case MarkerType::Sub:
                    return ir_builder.CreateFSub(lhs, rhs, "sub_f_tmp");
                case MarkerType::Mul:
                    return ir_builder.CreateFMul(lhs, rhs, "mul_f_tmp");
                case MarkerType::Div:
                    return ir_builder.CreateFDiv(lhs, rhs, "div_f_tmp");
                case MarkerType::Mod:
                    return ir_builder.CreateFRem(lhs, rhs, "mod_f_tmp");

                case MarkerType::LT:
                    return ir_builder.CreateFCmpOLT(lhs, rhs, "lt_f_tmp");
                case MarkerType::LE:
                    return ir_builder.CreateFCmpOLE(lhs, rhs, "le_f_tmp");
                case MarkerType::GT:
                    return ir_builder.CreateFCmpOGT(lhs, rhs, "gt_f_tmp");
                case MarkerType::GE:
                    return ir_builder.CreateFCmpOGE(lhs, rhs, "ge_f_tmp");
                case MarkerType::EQ:
                    return ir_builder.CreateFCmpOEQ(lhs, rhs, "eq_f_tmp");
                case MarkerType::NEQ:
                    return ir_builder.CreateFCmpONE(lhs, rhs, "neq_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp error"));
                    assert(false);
                    return nullptr;
            }
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp error"));
            assert(false);
            return nullptr;
    }
}
