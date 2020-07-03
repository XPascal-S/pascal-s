//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>
#include <fmt/core.h>

LLVMBuilder::Value *LLVMBuilder::code_gen_for_statement(const ast::ForStatement *for_stmt) {
    Function *cur_function = ir_builder.GetInsertBlock()->getParent();

    llvm::IRBuilder<> dfn_block(&cur_function->getEntryBlock(),
                                cur_function->getEntryBlock().begin());

    Value *from_value = code_gen(for_stmt->express1);
    Value *to_value = code_gen(for_stmt->express2);

    if (from_value == nullptr || to_value == nullptr) {
        return nullptr;
    }

    if (from_value->getType() != to_value->getType() && !check_extend_type(
            for_stmt->express1, from_value, to_value, true)) {
        return nullptr;
    }

    llvm::AllocaInst *loop_var = dfn_block.CreateAlloca(from_value->getType(), nullptr,
                                                        for_stmt->id->content);
    Value *step_value;
    switch (from_value->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            step_value = llvm::Constant::getIntegerValue(
                    from_value->getType(), llvm::APInt(from_value->getType()->getIntegerBitWidth(), 1));
            break;
        case llvm::Type::DoubleTyID:
            step_value = llvm::ConstantFP::get(
                    from_value->getType(), llvm::APFloat(1.0));
            break;
        default:
            llvm_pascal_s_report_semantic_error_n(for_stmt->id,
                                                  fmt::format("iter type invalid error, from-to-exp type = {}",
                                                              format_type(from_value->getType())));
            return nullptr;
    }

    llvm::Value *old_var = nullptr;
    if (scope_stack->ctx->count(for_stmt->id->content)) {
        old_var = scope_stack->ctx->at(for_stmt->id->content);
    }
    (*scope_stack->ctx)[for_stmt->id->content] = loop_var;

    auto si = ir_builder.CreateStore(from_value, loop_var);


    llvm::BasicBlock *loop_block = llvm::BasicBlock::Create(ctx, "loop", cur_function);
    llvm::BasicBlock *loop_after_block =
            llvm::BasicBlock::Create(ctx, "follow_lp");

    Value *first_loop_cond = nullptr;
    switch (from_value->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            // todo: signed/unsigned integer type feature
            first_loop_cond = ir_builder.CreateICmpSLE(
                    from_value, to_value, "loop_cond");
            break;
        case llvm::Type::DoubleTyID:
            // todo: ordered or unordered
            first_loop_cond = ir_builder.CreateFCmpOLE(
                    from_value, to_value, "loop_cond");
            break;
        default:
            llvm_pascal_s_report_semantic_error_n(
                    for_stmt->express1,
                    fmt::format("could not perform binary calc <= on lhs and rhs, lhs type = {}, rhs type = {}",
                                format_type(from_value->getType()), format_type(to_value->getType())));
            return nullptr;
    }

    ir_builder.CreateCondBr(first_loop_cond, loop_block, loop_after_block);
    ir_builder.SetInsertPoint(loop_block);

    Value *loop_body = code_gen_statement(for_stmt->for_stmt);
    if (si == nullptr || loop_body == nullptr)
        return nullptr;


    Value *cur_value = ir_builder.CreateLoad(loop_var, for_stmt->id->content);
    switch (from_value->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            si = ir_builder.CreateStore(
                    ir_builder.CreateAdd(cur_value, step_value, "next_tmp"), loop_var);
            break;
        case llvm::Type::DoubleTyID:
            si = ir_builder.CreateStore(
                    ir_builder.CreateFAdd(cur_value, step_value, "next_tmp_d"), loop_var);
            break;
        default:
            llvm_pascal_s_report_semantic_error_n(
                    for_stmt->id,
                    fmt::format("could not perform binary calc + on lhs and rhs, lhs type = {}, rhs type = {}",
                                format_type(cur_value->getType()), format_type(step_value->getType())));
            return nullptr;
    }
    if (si == nullptr)
        return nullptr;

    Value *loop_cond = ir_builder.CreateLoad(loop_var);
    if (!loop_cond) {
        llvm_pascal_s_report_semantic_error_n(for_stmt->id, "internal load invalid error");
        return nullptr;
    }
    switch (from_value->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            // todo: signed/unsigned integer type feature
            loop_cond = ir_builder.CreateICmpSLE(
                    loop_cond, to_value, "loop_cond");
            break;
        case llvm::Type::DoubleTyID:
            // todo: ordered or unordered
            loop_cond = ir_builder.CreateFCmpOLE(
                    loop_cond, to_value, "loop_cond");
            break;
        default:
            llvm_pascal_s_report_semantic_error_n(
                    for_stmt->id,
                    fmt::format("could not perform binary calc <= on lhs and rhs, lhs type = {}, rhs type = {}",
                                format_type(loop_cond->getType()), format_type(to_value->getType())));
            return nullptr;
    }

    ir_builder.CreateCondBr(loop_cond, loop_block, loop_after_block);

    cur_function->getBasicBlockList().push_back(loop_after_block);
    ir_builder.SetInsertPoint(loop_after_block);

    if (old_var != nullptr) {
        (*scope_stack->ctx)[for_stmt->id->content] = loop_var;
    } else {
        scope_stack->ctx->erase(for_stmt->id->content);
    }

    return loop_body;
}