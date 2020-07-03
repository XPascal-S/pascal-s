//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

static pascal_s::Pos static_pos{0, 0, 1, 1};

LLVMBuilder::Function *LLVMBuilder::rename_program_to_pascal_s_native(LLVMBuilder::Function *f) {
    Function *maybe_conflict = modules.getFunction(pascal_main_function_name);
    if (maybe_conflict) {
        llvm_pascal_s_report_semantic_error(&static_pos, "rename function error");
        return nullptr;
    }

    f->setName(pascal_main_function_name);
    return f;
}


llvm::Value *LLVMBuilder::assign_lvalue(const pascal_s::Pos *lvalue_pos, Value *ptr, Value *rhs) {
    llvm::Type *elemType = nullptr;
    if (ptr->getType()->isPointerTy()) {
        elemType = ptr->getType()->getPointerElementType();
    } else if (ptr->getType()->isArrayTy()) {
        elemType = ptr->getType()->getArrayElementType();
    }

    if (rhs->getType()->getTypeID() != elemType->getTypeID()) {
        // todo: implicit type conversion feature
        llvm_pascal_s_report_semantic_error(lvalue_pos, "lvalue type incompatible error");
        return nullptr;
    }

    if (elemType->getTypeID() == llvm::Type::IntegerTyID) {
        // todo: signed/unsigned integer type feature
        auto rhs_bit_width = rhs->getType()->getIntegerBitWidth();
        auto elem_type_bit_width = elemType->getIntegerBitWidth();
        if (rhs_bit_width > elem_type_bit_width) {
            rhs = ir_builder.CreateTrunc(rhs, elemType, "");
        } else if (rhs_bit_width < elem_type_bit_width) {
            rhs = ir_builder.CreateSExt(rhs, elemType, "");
        }
    } else if (elemType->getTypeID() != llvm::Type::DoubleTyID) {
        llvm_pascal_s_report_semantic_error(lvalue_pos, "lvalue llvm type error");
        return nullptr;
    }

    ir_builder.CreateStore(rhs, ptr);
    return rhs;
}
