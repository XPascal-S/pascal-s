//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>
#include <fmt/core.h>

LLVMBuilder::Function *LLVMBuilder::code_gen_program(const ast::Program *pProgram) {

    Function *program = modules.getFunction(pProgram->programHead->id->ident->content);

    // gen function proto
    if (!program) {
        auto *prototype = llvm::FunctionType::get(
                llvm::Type::getInt32Ty(ctx), false);

        program = Function::Create(prototype, Function::ExternalLinkage,
                                   pProgram->programHead->id->ident->content, modules);
    } else {
        llvm_pascal_s_report_semantic_error_n(pProgram, "main function redeclared");
        return nullptr;
    }

    // out_code('entry:')
    llvm::BasicBlock *body = llvm::BasicBlock::Create(ctx, "entry", program);
    ir_builder.SetInsertPoint(body);

    // create local variable map this.const_ctx
    std::map<std::string, Value *> program_const_this;
    insert_const_decls(program_const_this, pProgram->programBody->constdecls);
    // create local variable map this.ctx
    std::map<std::string, pascal_s::ArrayInfo *> program_array_infos;
    std::map<std::string, llvm::Value *> program_this;
    insert_var_decls(program, program_array_infos, program_this, pProgram->programBody->vardecls);

    if (pProgram->programBody->constdecls != nullptr) {
        for (auto d : pProgram->programBody->constdecls->decls) {
            if (program_this.count(d->ident->content)) {
                llvm_pascal_s_report_semantic_error_n(
                        d->ident, fmt::format("ident redeclared"));
            }
        }
    }

    // push this into scope stack
    auto link = LinkedContext{scope_stack, &program_array_infos, &program_this, &program_const_this};
    scope_stack = &link;

    // out_code( define variable i32: %program.name )
    llvm::IRBuilder<> dfn_block(&program->getEntryBlock(),
                                program->getEntryBlock().begin());
    auto ptr = dfn_block.CreateAlloca(llvm::Type::getInt32Ty(
            ctx), nullptr, pProgram->programHead->id->ident->content);

    if (program_this.count(pProgram->programHead->id->ident->content) ||
        program_const_this.count(pProgram->programHead->id->ident->content)) {
        llvm_pascal_s_report_semantic_error_n(
                pProgram->programHead->id->ident, fmt::format("ident redeclared"));
    }

    program_this[pProgram->programHead->id->ident->content] = ptr;
    ir_builder.CreateStore(llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(
            ctx), llvm::APInt(32, 0)), ptr);

    if (pProgram->programBody->subprogram != nullptr) {
        for (auto fn_decl : pProgram->programBody->subprogram->subprogram) {
            if (program_this.count(fn_decl->subhead->name->content) ||
                program_const_this.count(fn_decl->subhead->name->content)) {
                llvm_pascal_s_report_semantic_error_n(
                        fn_decl->subhead->name,
                        fmt::format("function redeclared, another variable is in this context"));
            }
            code_gen_procedure(fn_decl);
        }
    }

    // reset insert point
    ir_builder.SetInsertPoint(body);

    // generate body
    if (pProgram->programBody->compound->state->statement.empty() ||
        code_gen_statement(pProgram->programBody->compound)) {
        // if body generated
        // out_code( %ret_tmp = load i32 from %program.name )
        // out_code( ret i32: %ret_tmp )
        ir_builder.CreateRet(
                ir_builder.CreateLoad(program_this[pProgram->programHead->id->ident->content], "ret_tmp"));

        llvm::verifyFunction(*program);
        fn_pass_manager.run(*program);

        // pop 'this' from scope stack
        scope_stack = link.last;
        return rename_program_to_pascal_s_native(program);
    }
    program->eraseFromParent();

    // pop 'this' from scope stack
    scope_stack = link.last;
    return nullptr;
}
