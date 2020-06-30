//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>


LLVMBuilder::Value *LLVMBuilder::code_gen_if_else_statement(const ast::IfElseStatement *if_else_stmt) {

    Value *cond = code_gen(if_else_stmt->expression);
    if (!cond) {
        return nullptr;
    }

    switch (cond->getType()->getTypeID()) {
        case llvm::Type::TypeID::IntegerTyID:
            cond = ir_builder.CreateICmpNE(
                    cond, llvm::Constant::getIntegerValue(
                            cond->getType(), llvm::APInt(cond->getType()->getIntegerBitWidth(), 0)), "if_cond");
            break;
        case llvm::Type::TypeID::DoubleTyID:
            cond = ir_builder.CreateFCmpONE(
                    cond, llvm::ConstantFP::get(cond->getType(), llvm::APFloat(double(0))), "if_cond");
            break;
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "if else statement type error"));
            assert(false);
            return nullptr;
    }


    Function *cur_function = ir_builder.GetInsertBlock()->getParent();
    llvm::BasicBlock *then_block = llvm::BasicBlock::Create(ctx, "then", cur_function);
    llvm::BasicBlock *else_block = llvm::BasicBlock::Create(ctx, "else");
    llvm::BasicBlock *merge_block = llvm::BasicBlock::Create(ctx, "follow_ie");

    // link before if to -> cond ? then_block : else_block
    ir_builder.CreateCondBr(cond, then_block, else_block);

    // already pushed then block
    // build then block
    ir_builder.SetInsertPoint(then_block);
    Value *then_value = code_gen_statement(if_else_stmt->if_part);
    ir_builder.CreateBr(merge_block);
    then_block = ir_builder.GetInsertBlock();

    // push else block
    cur_function->getBasicBlockList().push_back(else_block);
    // build else block
    ir_builder.SetInsertPoint(else_block);
    Value *else_value = code_gen_statement(if_else_stmt->else_part);
    ir_builder.CreateBr(merge_block);
    else_block = ir_builder.GetInsertBlock();

    // push merge block
    cur_function->getBasicBlockList().push_back(merge_block);
    ir_builder.SetInsertPoint(merge_block);

    if (!(then_value && else_value))
        return nullptr;

    if (then_value->getType()->getTypeID() == else_value->getType()->getTypeID()) {
        //assuming equal

        llvm::PHINode *merged_value = ir_builder.CreatePHI(
                then_value->getType(), 2, "ieb_eval");

        merged_value->addIncoming(then_value, then_block);
        merged_value->addIncoming(else_value, else_block);
        return merged_value;
    }

    return llvm::UndefValue::get(llvm::Type::getVoidTy(ctx));
}

void LLVMBuilder::insert_const_decls(std::map<std::string, llvm::Value *> &map, const ast::ConstDecls *pDecls) {
    if (pDecls != nullptr) {
        for (auto decl : pDecls->decls) {
            map[decl->ident->content] = code_gen(decl->rhs);
        }
    }
}
