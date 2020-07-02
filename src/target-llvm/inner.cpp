//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>


LLVMBuilder::Function *LLVMBuilder::rename_program_to_pascal_s_native(LLVMBuilder::Function *f) {
    Function *maybe_conflict = modules.getFunction(pascal_main_function_name);
    if (maybe_conflict) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "llvm native main function redeclared"));
        assert(false);
        return nullptr;
    }

    f->setName(pascal_main_function_name);
    return f;
}


LLVMBuilder::Value *LLVMBuilder::assign_lvalue(LLVMBuilder::Value *ptr, LLVMBuilder::Value *rhs) {
    llvm::Type *elemType = nullptr;
    if (ptr->getType()->isPointerTy()) {
        elemType = ptr->getType()->getPointerElementType();
    } else if (ptr->getType()->isArrayTy()) {
        elemType = ptr->getType()->getArrayElementType();
    }

    if (rhs->getType()->getTypeID() != elemType->getTypeID()) {
        // todo: implicit type conversion feature
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_named_value error"));
        assert(false);
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
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_named_value error"));
        assert(false);
        return nullptr;
    }

    ir_builder.CreateStore(rhs, ptr);
    return rhs;
}
