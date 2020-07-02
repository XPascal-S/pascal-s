//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>


llvm::Type *LLVMBuilder::create_type(const ast::TypeSpec *spec) {
    if (spec->type == ast::Type::BasicTypeSpec) {
        return create_basic_type(reinterpret_cast<const ast::BasicTypeSpec *>(spec));
    } else if (spec->type == ast::Type::ArrayTypeSpec) {
        auto sz = calc_periods_size(reinterpret_cast<const ast::ArrayTypeSpec *>(spec));

        if (sz <= 0) {
            return nullptr;
        }

        return llvm::ArrayType::get(create_basic_type_from_keyword(
                reinterpret_cast<const ast::ArrayTypeSpec *>(spec)->keyword->key_type), sz);
//        return create_basic_type_from_keyword(
//                reinterpret_cast<const ast::ArrayTypeSpec *>(spec)->keyword->key_type);
    } else {
        assert(false);
        return nullptr;
    }
}

llvm::Type *LLVMBuilder::create_basic_type(const ast::BasicTypeSpec *spec) {
    return create_basic_type_from_keyword(spec->keyword->key_type);
}

llvm::Type *LLVMBuilder::create_basic_type_from_keyword(KeywordType spec) {
    switch (spec) {
        case KeywordType::Char:
            return llvm::Type::getInt8Ty(ctx);
        case KeywordType::Integer:

            return llvm::Type::getInt64Ty(ctx);
        case KeywordType::Real:
            return llvm::Type::getDoubleTy(ctx);
        case KeywordType::Boolean:
            return llvm::Type::getInt1Ty(ctx);
//            case KeywordType::String:
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get keyword spec type error"));
            assert(false);
            return nullptr;
    }
}
