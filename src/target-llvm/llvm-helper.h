//
// Created by kamiyoru on 2020/7/3.
//

#ifndef PASCAL_S_LLVM_HELPER_H
#define PASCAL_S_LLVM_HELPER_H

inline llvm::Value *create_int64_literal(llvm::LLVMContext &ctx, int64_t literal) {
    return llvm::Constant::getIntegerValue(
            llvm::IntegerType::get(ctx, 64), llvm::APInt(64, literal, true));
}

inline const char *format_type(llvm::Type *t) {
    switch (t->getTypeID()) {
        case llvm::Type::IntegerTyID:
            switch (t->getIntegerBitWidth()) {
                case 1:
                    return "boolean";
                case 8:
                    return "char";
                case 64:
                    return "integer";
                default:
                    std::cerr << "format llvm type error type id: " << t->getTypeID();
                    assert(false);
                    return "";
            }
        case llvm::Type::DoubleTyID:
            return "real";
        default:
            std::cerr << "format llvm type error type id: " << t->getTypeID();
            assert(false);
            return "";
    }
}

#endif //PASCAL_S_LLVM_HELPER_H
