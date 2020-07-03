//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>
#include <fmt/core.h>


llvm::Type *LLVMBuilder::create_type(const ast::TypeSpec *spec) {
    if (spec->type == ast::Type::BasicTypeSpec) {
        return create_basic_type(reinterpret_cast<const ast::BasicTypeSpec *>(spec));
    } else if (spec->type == ast::Type::ArrayTypeSpec) {
        auto sz = calc_periods_size(reinterpret_cast<const ast::ArrayTypeSpec *>(spec));

        if (sz <= 0) {
            return nullptr;
        }

        return llvm::ArrayType::get(create_basic_type_from_keyword(
                reinterpret_cast<const ast::ArrayTypeSpec *>(spec)->keyword), sz);
//        return create_basic_type_from_keyword(
//                reinterpret_cast<const ast::ArrayTypeSpec *>(spec)->keyword->key_type);
    } else {
        llvm_pascal_s_report_semantic_error_n(
                spec,
                fmt::format("type spec {} has no gen function", static_cast<uint16_t>(spec->type)));
        return nullptr;
    }
}

llvm::Type *LLVMBuilder::create_basic_type(const ast::BasicTypeSpec *spec) {
    return create_basic_type_from_keyword(spec->keyword);
}

llvm::Type *LLVMBuilder::create_basic_type_from_keyword(const Keyword *spec) {
    switch (spec->key_type) {
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
            llvm_pascal_s_report_semantic_error_n(
                    spec,
                    fmt::format("basic type spec {} has no gen function",
                                static_cast<uint16_t>(spec->type)));
            return nullptr;
    }
}
