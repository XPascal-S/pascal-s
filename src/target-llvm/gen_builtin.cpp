//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>


void LLVMBuilder::prepend_lib_standard_pascal_s() {
    auto *prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getInt8PtrTy(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "read_char", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getInt1PtrTy(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "read_bool", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getInt64PtrTy(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "read_int64", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getDoublePtrTy(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "read_real", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getInt8Ty(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "write_char", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getInt1Ty(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "write_bool", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getInt64Ty(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "write_int64", modules);

    prototype = llvm::FunctionType::get(
            llvm::Type::getInt32Ty(ctx), {
                    llvm::Type::getDoubleTy(ctx),
            }, false);
    Function::Create(prototype, Function::ExternalLinkage,
                     "write_real", modules);
}

void LLVMBuilder::LinkedContext::deconstruct() const {
    for (auto &ai: *array_infos) {
        delete ai.second;
        ai.second = nullptr;
    }
    array_infos->clear();
    ctx->clear();
    const_ctx->clear();
}
