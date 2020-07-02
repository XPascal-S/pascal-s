//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>

LLVMBuilder::Function *LLVMBuilder::code_gen_procedure(const ast::Subprogram *pSubprogram) {
    Function *fn = modules.getFunction(pSubprogram->subhead->name->content);

    // create function proto llvm_func
    if (!fn) {
        llvm::Type *llvm_ret_type = nullptr;
        if (pSubprogram->subhead->ret_type == nullptr) {
            llvm_ret_type = llvm::Type::getVoidTy(ctx);
        } else {
            llvm_ret_type = create_type(pSubprogram->subhead->ret_type);
        }

        std::vector<llvm::Type *> args_proto;

        if (pSubprogram->subhead->decls != nullptr) {
            int args_proto_size = 0;

            for (auto arg_spec : pSubprogram->subhead->decls->params) {
                args_proto_size += arg_spec->id_list->idents.size();
            }
            args_proto.reserve(args_proto_size);

            for (auto arg_spec : pSubprogram->subhead->decls->params) {
                llvm::Type *llvm_arg_type = create_type(arg_spec->spec);

                if (arg_spec->keyword_var != nullptr) {
                    llvm_arg_type = llvm_arg_type->getPointerTo();
                }

                for (auto ident: arg_spec->id_list->idents) {
                    args_proto.push_back(llvm_arg_type);
                }
            }
        }

        auto *prototype = llvm::FunctionType::get(
                llvm_ret_type, args_proto, false);

        fn = Function::Create(prototype, Function::ExternalLinkage,
                              pSubprogram->subhead->name->content, modules);

        if (pSubprogram->subhead->decls != nullptr) {
            int arg_cursor = 0;
            for (auto arg_spec : pSubprogram->subhead->decls->params) {
                for (auto ident: arg_spec->id_list->idents) {
                    fn->getArg(arg_cursor++)->setName(ident->content);
                }
            }
        }
    } else {
//            for (int i = 0; i < fn->arg_size(); i++) {
//                const auto &arg = fn->getArg(i);
//
//            }
        //todo action fn existed
    }

    // out_code('entry:')
    llvm::BasicBlock *body = llvm::BasicBlock::Create(ctx, "entry", fn);
    ir_builder.SetInsertPoint(body);

    // create local variable map this.ctx
    std::map<std::string, pascal_s::ArrayInfo *> program_array_infos;
    std::map<std::string, llvm::Value *> program_this;
    insert_var_decls(fn, program_array_infos, program_this, pSubprogram->subbody->vardecls);
    // create local const map this.const_ctx
    std::map<std::string, Value *> program_const_this;
    insert_const_decls(program_const_this, pSubprogram->subbody->constdecls);
    insert_param_decls(fn, program_this, program_const_this);

    // push 'this' into scope stack
    auto link = LinkedContext{scope_stack, &program_array_infos, &program_this, &program_const_this};
    scope_stack = &link;

    // out_code( define variable ret_type: %procedure.name )
    llvm::IRBuilder<> dfn_block(&fn->getEntryBlock(), fn->getEntryBlock().begin());
    if (!fn->getReturnType()->isVoidTy())
        program_this[pSubprogram->subhead->name->content] = dfn_block.CreateAlloca(
                fn->getReturnType(), nullptr, pSubprogram->subhead->name->content);

    // generate body
    if (pSubprogram->subbody->compound->state->statement.empty() ||
        code_gen_statement(pSubprogram->subbody->compound)) {
        // if body generated
        if (fn->getReturnType()->isVoidTy()) {
            // out_code( ret void )
            ir_builder.CreateRetVoid();
        } else {
            // out_code( %ret_tmp = load ret_type from %procedure.name )
            // out_code( ret ret_type: %ret_tmp )
            ir_builder.CreateRet(
                    ir_builder.CreateLoad(program_this[pSubprogram->subhead->name->content], "ret_tmp"));
        }
        llvm::verifyFunction(*fn);
        fn_pass_manager.run(*fn);

        // pop 'this' from scope stack
        scope_stack = link.last;
        return fn;
    }

    fn->eraseFromParent();
    // pop 'this' from scope stack
    scope_stack = link.last;
    return nullptr;
}
