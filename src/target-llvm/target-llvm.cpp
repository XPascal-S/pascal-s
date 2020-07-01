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

int64_t LLVMBuilder::calc_periods_size(const ast::ArrayTypeSpec *spec) {
    int64_t ret = 1;
    for (const auto &p : spec->periods) {
        if (p.second < p.first) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "calc periods size error"));
            assert(false);
        }
        ret *= (p.second - p.first);
    }
    return ret;
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

llvm::Type *LLVMBuilder::create_basic_type(const ast::BasicTypeSpec *spec) {
    return create_basic_type_from_keyword(spec->keyword->key_type);
}

LLVMBuilder::Function *LLVMBuilder::code_gen_program(const ast::Program *pProgram) {

    Function *program = modules.getFunction(pProgram->programHead->id->ident->content);

    // gen function proto
    if (!program) {
        auto *prototype = llvm::FunctionType::get(
                llvm::Type::getInt32Ty(ctx), false);

        program = Function::Create(prototype, Function::ExternalLinkage,
                                   pProgram->programHead->id->ident->content, modules);
    } else {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "main function redeclared"));
        assert(false);
    }

    // out_code('entry:')
    llvm::BasicBlock *body = llvm::BasicBlock::Create(ctx, "entry", program);
    ir_builder.SetInsertPoint(body);

    // create local variable map this.ctx
    std::map<std::string, pascal_s::ArrayInfo *> program_array_infos;
    std::map<std::string, llvm::Value *> program_this;
    insert_var_decls(program, program_array_infos, program_this, pProgram->programBody->vardecls);
    // create local variable map this.const_ctx
    std::map<std::string, Value *> program_const_this;
    insert_const_decls(program_const_this, pProgram->programBody->constdecls);

    // push this into scope stack
    auto link = LinkedContext{scope_stack, &program_array_infos, &program_this, &program_const_this};
    scope_stack = &link;

    // out_code( define variable i32: %program.name )
    llvm::IRBuilder<> dfn_block(&program->getEntryBlock(),
                                program->getEntryBlock().begin());
    auto ptr = dfn_block.CreateAlloca(llvm::Type::getInt32Ty(
            ctx), nullptr, pProgram->programHead->id->ident->content);
    program_this[pProgram->programHead->id->ident->content] = ptr;
    ir_builder.CreateStore(llvm::Constant::getIntegerValue(llvm::Type::getInt32Ty(
            ctx), llvm::APInt(32, 0)), ptr);

    if (pProgram->programBody->subprogram != nullptr) {
        for (auto fn_decl : pProgram->programBody->subprogram->subprogram) {
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

LLVMBuilder::Function *LLVMBuilder::rename_program_to_pascal_s_native(LLVMBuilder::Function *f) {
    Function *maybe_conflict = modules.getFunction(pascal_main_function_name);
    if (maybe_conflict) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "llvm natie main function redeclared"));
        assert(false);
        return nullptr;
    }

    f->setName(pascal_main_function_name);
    return f;
}

void LLVMBuilder::insert_param_decls(LLVMBuilder::Function *fn, std::map<std::string, llvm::Value *> &map,
                                     std::map<std::string, llvm::Value *> &const_map) {
    for (size_t i = 0; i < fn->arg_size(); i++) {
        auto arg = fn->getArg(i);
        if (arg->getType()->isPointerTy()) {
            map[arg->getName().str()] = arg;// llvm::dyn_cast<llvm::AllocaInst>(arg);
        } else {
            const_map[arg->getName().str()] = arg;
        }
    }
}

LLVMBuilder::Value *LLVMBuilder::code_gen_statement_block(const ast::StatementList *pBlock) {
    Value *block_value = nullptr;
    bool collapsed = false;
    for (auto stmt : pBlock->statement) {
        block_value = code_gen_statement(stmt);
        if (block_value == nullptr) {
            collapsed = true;
        }
    }

    return collapsed ? nullptr : block_value;
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_call(const ast::ExpCall *pCall) {
    // get function proto llvm_func
    Function *calleeFunc = modules.getFunction(pCall->fn->content);
    if (!calleeFunc) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "get callee error"));
        assert(false);
        return nullptr;
    }
    if (calleeFunc->arg_size() != pCall->params->explist.size()) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                  "callee func param size does not match exp list size"));
        assert(false);
        return nullptr;
    }
    std::vector<Value *> args;

    bool gen_exp_failed = false;

    // for
    for (int i = 0; i < calleeFunc->arg_size(); i++) {
        auto *argument_proto = calleeFunc->getArg(i);
        Value *argument_value = nullptr;
        if (argument_proto->getType()->isPointerTy()) {
            argument_value = get_lvalue_pointer(pCall->params->explist[i]);
        } else {
            argument_value = code_gen(pCall->params->explist[i]);
        }
        if (argument_value == nullptr) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                      "callee func gen exp failed"));
            assert(false);
            gen_exp_failed = true;
        } else if (argument_proto->getType()->getTypeID() != argument_value->getType()->getTypeID()) {
            // todo: type conversion
            errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                      "callee func gen exp type conflicted"));
            assert(false);
            gen_exp_failed = true;
        }
        args.push_back(argument_value);
    }

    if (gen_exp_failed) {
        return nullptr;
    }

    // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
    if (calleeFunc->getReturnType()->isVoidTy()) {
        return ir_builder.CreateCall(calleeFunc, args);
    } else {
        return ir_builder.CreateCall(calleeFunc, args, pCall->fn->content);
    }
}

LLVMBuilder::Value *LLVMBuilder::code_gen_for_statement(const ast::ForStatement *for_stmt) {
    Function *cur_function = ir_builder.GetInsertBlock()->getParent();

    llvm::IRBuilder<> dfn_block(&cur_function->getEntryBlock(),
                                cur_function->getEntryBlock().begin());

    Value *from_value = code_gen(for_stmt->express1);
    Value *to_value = code_gen(for_stmt->express2);

    if (from_value == nullptr || to_value == nullptr) {
        return nullptr;
    }

    if (from_value->getType()->getTypeID() != to_value->getType()->getTypeID()) {
        // todo: type conversion
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "from statement loop type error"));
        assert(false);
        return nullptr;
    }

    llvm::AllocaInst *loop_var = dfn_block.CreateAlloca(from_value->getType(), nullptr,
                                                        for_stmt->id->content);
    Value *step_value = nullptr;
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
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "unknown loop type error"));
            assert(false);
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
            // todo: signed
            first_loop_cond = ir_builder.CreateICmpSLE(
                    from_value, to_value, "loop_cond");
            break;
        case llvm::Type::DoubleTyID:
            // todo: OLE?
            first_loop_cond = ir_builder.CreateFCmpOLE(
                    from_value, to_value, "loop_cond");
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "loop unknown compare type error"));
            assert(false);
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
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "loop store next compare type error"));
            assert(false);
            return nullptr;
    }
    if (si == nullptr)
        return nullptr;

    Value *loop_cond = nullptr;
    switch (from_value->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            // todo: signed
            loop_cond = ir_builder.CreateICmpSLE(
                    ir_builder.CreateLoad(loop_var), to_value, "loop_cond");
            break;
        case llvm::Type::DoubleTyID:
            // todo: OLE?
            loop_cond = ir_builder.CreateFCmpOLE(
                    ir_builder.CreateLoad(loop_var), to_value, "loop_cond");
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "loop unknown compare type error 2"));
            assert(false);
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

LLVMBuilder::Value *LLVMBuilder::code_gen_binary_exp(const ast::BiExp *pExp) {
    auto lhs = code_gen(pExp->lhs);
    auto rhs = code_gen(pExp->rhs);
    if (lhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp eval lhs error"));
        assert(false);
        return nullptr;
    }
    if (rhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp eval rhs error"));
        assert(false);
        return nullptr;
    }

    if (lhs->getType()->getTypeID() != rhs->getType()->getTypeID()) {
        // todo : type convert
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary type conflict error"));
        assert(false);
        return nullptr;
    }
    switch (lhs->getType()->getTypeID()) {
        case llvm::Type::IntegerTyID:
            switch (pExp->marker->marker_type) {
                case MarkerType::LogicAnd:
                    return ir_builder.CreateAnd(
                            ir_builder.CreateICmpNE(
                                    lhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            ir_builder.CreateICmpNE(
                                    rhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            "and_tmp");
                case MarkerType::LogicOr:
                    return ir_builder.CreateOr(
                            ir_builder.CreateICmpNE(
                                    lhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            ir_builder.CreateICmpNE(
                                    rhs, llvm::Constant::getIntegerValue(
                                            lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))),
                            "or_tmp");

                case MarkerType::Add:
                    return ir_builder.CreateAdd(lhs, rhs, "add_tmp");
                case MarkerType::Sub:
                    return ir_builder.CreateSub(lhs, rhs, "sub_tmp");
                case MarkerType::Mul:
                    return ir_builder.CreateMul(lhs, rhs, "mul_tmp");
                case MarkerType::Div:
                    return ir_builder.CreateSDiv(lhs, rhs, "div_tmp");
                case MarkerType::Mod:
                    return ir_builder.CreateSRem(lhs, rhs, "mod_tmp");

                case MarkerType::LT:
                    return ir_builder.CreateICmpSLT(lhs, rhs, "lt_tmp");
                case MarkerType::LE:
                    return ir_builder.CreateICmpSLE(lhs, rhs, "le_tmp");
                case MarkerType::GT:
                    return ir_builder.CreateICmpSGT(lhs, rhs, "gt_tmp");
                case MarkerType::GE:
                    return ir_builder.CreateICmpSGE(lhs, rhs, "ge_tmp");
                case MarkerType::EQ:
                    return ir_builder.CreateICmpEQ(lhs, rhs, "eq_tmp");
                case MarkerType::NEQ:
                    return ir_builder.CreateICmpNE(lhs, rhs, "neq_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp error"));
                    assert(false);
                    return nullptr;
            }
        case llvm::Type::DoubleTyID:
            switch (pExp->marker->marker_type) {
                case MarkerType::LogicAnd:
                    return ir_builder.CreateAnd(
                            ir_builder.CreateFCmpONE(
                                    lhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            ir_builder.CreateFCmpONE(
                                    rhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            "and_tmp");
                case MarkerType::LogicOr:
                    return ir_builder.CreateOr(
                            ir_builder.CreateFCmpONE(
                                    lhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            ir_builder.CreateFCmpONE(
                                    rhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))),
                            "or_tmp");

                case MarkerType::Add:
                    return ir_builder.CreateFAdd(lhs, rhs, "add_f_tmp");
                case MarkerType::Sub:
                    return ir_builder.CreateFSub(lhs, rhs, "sub_f_tmp");
                case MarkerType::Mul:
                    return ir_builder.CreateFMul(lhs, rhs, "mul_f_tmp");
                case MarkerType::Div:
                    return ir_builder.CreateFDiv(lhs, rhs, "div_f_tmp");
                case MarkerType::Mod:
                    return ir_builder.CreateFRem(lhs, rhs, "mod_f_tmp");

                case MarkerType::LT:
                    return ir_builder.CreateFCmpOLT(lhs, rhs, "lt_f_tmp");
                case MarkerType::LE:
                    return ir_builder.CreateFCmpOLE(lhs, rhs, "le_f_tmp");
                case MarkerType::GT:
                    return ir_builder.CreateFCmpOGT(lhs, rhs, "gt_f_tmp");
                case MarkerType::GE:
                    return ir_builder.CreateFCmpOGE(lhs, rhs, "ge_f_tmp");
                case MarkerType::EQ:
                    return ir_builder.CreateFCmpOEQ(lhs, rhs, "eq_f_tmp");
                case MarkerType::NEQ:
                    return ir_builder.CreateFCmpONE(lhs, rhs, "neq_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp error"));
                    assert(false);
                    return nullptr;
            }
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "binary exp error"));
            assert(false);
            return nullptr;
    }
}

LLVMBuilder::Value *LLVMBuilder::code_gen_unary_exp(const ast::UnExp *pExp) {
    auto lhs = code_gen(pExp->lhs);
    if (lhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
        assert(false);
        return nullptr;
    }

    switch (pExp->marker->marker_type) {
        case MarkerType::LogicNot:
            switch (lhs->getType()->getTypeID()) {
                case llvm::Type::IntegerTyID:
                    return ir_builder.CreateNot(ir_builder.CreateICmpNE(
                            lhs, llvm::Constant::getIntegerValue(
                                    lhs->getType(), llvm::APInt(lhs->getType()->getIntegerBitWidth(), 0))), "neg_tmp");
                case llvm::Type::DoubleTyID:
                    return ir_builder.CreateNot(ir_builder.CreateFCmpONE(
                            lhs, llvm::ConstantFP::get(lhs->getType(), llvm::APFloat(0.))), "neg_f_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
                    assert(false);
                    return nullptr;
            }
        case MarkerType::Add:
            return lhs;
        case MarkerType::Sub:
            switch (lhs->getType()->getTypeID()) {
                case llvm::Type::IntegerTyID:
                    return ir_builder.CreateNeg(lhs, "neg_tmp");
                case llvm::Type::DoubleTyID:
                    return ir_builder.CreateFNeg(lhs, "neg_f_tmp");
                default:
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
                    assert(false);
                    return nullptr;
            }
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "unary exp error"));
            assert(false);
            return nullptr;
    }
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_assign(const ast::ExpAssign *pAssign) {
    auto rhs = code_gen(pAssign->rhs);
    if (rhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "code_gen_exp_assign error"));
        assert(false);
        return nullptr;
    }
    return assign_lvalue(pAssign->lhs, rhs);
}

LLVMBuilder::Value *LLVMBuilder::assign_lvalue(const ast::Exp *lvalue, LLVMBuilder::Value *rhs) {
    auto ptr = get_lvalue_pointer(lvalue);
    if (rhs == nullptr) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
        assert(false);
        return nullptr;
    }
    llvm::Type *elemType = nullptr;
    if (ptr->getType()->isPointerTy()) {
        elemType = ptr->getType()->getPointerElementType();
    } else if (ptr->getType()->isArrayTy()) {
        elemType = ptr->getType()->getArrayElementType();
    }

    if (rhs->getType()->getTypeID() != elemType->getTypeID()) {
        // todo: type conversion
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_named_value error"));
        assert(false);
        return nullptr;
    }

    if (elemType->getTypeID() == llvm::Type::IntegerTyID) {
        // todo signed
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

llvm::Value *LLVMBuilder::get_lvalue_pointer(const ast::Exp *lvalue) {

    const char *content = nullptr;
    const ast::ExpressionList *exp_list = nullptr;
    switch (lvalue->type) {
        case ast::Type::Ident:
            content = reinterpret_cast<const ast::Ident *>(lvalue)->ident->content;
            break;
        case ast::Type::Variabele:
            content = reinterpret_cast<const ast::Variable *>(lvalue)->id->content;
            exp_list = reinterpret_cast<const ast::Variable *>(lvalue)->id_var;
            break;
        default:
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer error"));
            assert(false);
            return nullptr;
    }

    std::vector<Value *> offset;

    for (auto resolving_ctx = scope_stack;
         resolving_ctx; resolving_ctx = resolving_ctx->last) {
        auto &value_ctx = resolving_ctx->ctx;
        if (value_ctx->count(content)) {
            if (resolving_ctx->array_infos->count(content)) {
                if (exp_list != nullptr) {
                    offset.push_back(llvm::ConstantInt::get(ctx, llvm::APInt(64, 0, true)));
                    code_gen_offset(offset, resolving_ctx->array_infos->at(content), exp_list);
                } else {
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer error 2"));
                    assert(false);
                    return nullptr;
                }
            }

            auto ptr = (*value_ctx).at(content);

            if (offset.empty()) {
                return ptr;
            } else {
                return ir_builder.CreateGEP(ptr, offset, "gep_tmp");
            }
        }
        auto &const_ctx = resolving_ctx->const_ctx;
        if (const_ctx->count(content)) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer const error 3"));
            assert(false);
            return nullptr;
        }
    }
    errors.push_back(new PascalSSemanticError(__FUNCTION__, "get_lvalue_pointer not found error"));
    assert(false);
    return nullptr;
}
//
//LLVMBuilder::Value *LLVMBuilder::get_named_value_pointer(const char *name) {
//    for (auto resolving_ctx = scope_stack;
//         resolving_ctx; resolving_ctx = resolving_ctx->last) {
//        auto &value_ctx = resolving_ctx->ctx;
//        if (value_ctx->count(name)) {
//            if (resolving_ctx->array_infos->count((name))) {
//                errors.push_back(new PascalSSemanticError(__FUNCTION__,
//                                                          "get_named_value_pointer 1"));
//                assert(false);
//                return nullptr;
//            }
//            return value_ctx->at(name);
//        }
//        auto &const_ctx = resolving_ctx->const_ctx;
//        if (const_ctx->count(name)) {
//            errors.push_back(new PascalSSemanticError(__FUNCTION__,
//                                                      "get_named_value_pointer 2"));
//            assert(false);
//            return nullptr;
//        }
//    }
//    return nullptr;
//}

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

LLVMBuilder::Value *LLVMBuilder::code_gen_read_statement(const ast::Read *stmt) {
    Value *ret_value = llvm::Constant::getIntegerValue(
            llvm::IntegerType::get(ctx, 32), llvm::APInt(32, 0));

    for (auto ptr_proto: stmt->var_list->params) {
        auto res = get_lvalue_pointer(ptr_proto);
        if (res == nullptr) {
            return nullptr;
        }

        // get function proto llvm_func
        Function *calleeFunc = nullptr;
        switch (res->getType()->getPointerElementType()->getTypeID()) {
            case llvm::Type::DoubleTyID:
                calleeFunc = modules.getFunction("read_real");
                break;
            default:
                assert(false);
                return nullptr;
            case llvm::Type::IntegerTyID:
                auto bw = res->getType()->getPointerElementType()->getIntegerBitWidth();
                if (bw == 64) {
                    calleeFunc = modules.getFunction("read_int64");
                } else if (bw == 8) {
                    calleeFunc = modules.getFunction("read_char");
                } else if (bw == 1) {
                    calleeFunc = modules.getFunction("read_bool");
                    // todo: read bool
                    assert(false);
                }
                break;
        }
        if (!calleeFunc) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get callee error"));
            assert(false);
            return nullptr;
        }
        assert(calleeFunc->arg_size() == 1);
        std::vector<Value *> args;
        auto *argument_proto = calleeFunc->getArg(0);
        assert(argument_proto->getType()->getTypeID() == res->getType()->getTypeID());
        args.push_back(res);

        // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
        ret_value = ir_builder.CreateAdd(ret_value, ir_builder.CreateCall(calleeFunc, args, "read_tmp"));
    }
    return ret_value;
}

LLVMBuilder::Value *LLVMBuilder::code_gen_write_statement(const ast::Write *stmt) {
    Value *ret_value = llvm::Constant::getIntegerValue(
            llvm::IntegerType::get(ctx, 32), llvm::APInt(32, 0));

    for (auto exp_proto: stmt->exp_list->explist) {
        auto res = code_gen(exp_proto);
        if (res == nullptr) {
            return nullptr;
        }

        // get function proto llvm_func
        Function *calleeFunc = nullptr;
        switch (res->getType()->getTypeID()) {
            case llvm::Type::IntegerTyID:
                if (res->getType()->getIntegerBitWidth() == 64) {
                    calleeFunc = modules.getFunction("write_int64");
                } else if (res->getType()->getIntegerBitWidth() == 8) {
                    calleeFunc = modules.getFunction("write_char");
                } else if (res->getType()->getIntegerBitWidth() == 1) {
                    calleeFunc = modules.getFunction("write_bool");
                    // todo: write bool
                    assert(false);
                }
                break;
            case llvm::Type::DoubleTyID:
                calleeFunc = modules.getFunction("write_real");
                break;
            default:
                assert(false);
                return nullptr;
        }
        if (!calleeFunc) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "get callee error"));
            assert(false);
            return nullptr;
        }
        assert(calleeFunc->arg_size() == 1);
        std::vector<Value *> args;
        auto *argument_proto = calleeFunc->getArg(0);
        assert(argument_proto->getType()->getTypeID() == res->getType()->getTypeID());
        args.push_back(res);

        // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
        ret_value = ir_builder.CreateAdd(ret_value, ir_builder.CreateCall(calleeFunc, args, "write_tmp"));
    }
    return ret_value;
}

LLVMBuilder::Value *LLVMBuilder::code_gen_ident(const ast::Ident *pIdent) {
    for (auto resolving_ctx = scope_stack;
         resolving_ctx; resolving_ctx = resolving_ctx->last) {
        auto &value_ctx = resolving_ctx->ctx;
        if (value_ctx->count(pIdent->ident->content)) {
            return ir_builder.CreateLoad(value_ctx->at(pIdent->ident->content), "load_tmp");
        }
        auto &const_ctx = resolving_ctx->const_ctx;
        if (const_ctx->count(pIdent->ident->content)) {
            return const_ctx->at(pIdent->ident->content);
        }
    }
    // get function proto llvm_func
    Function *calleeFunc = modules.getFunction(pIdent->ident->content);
    if (!calleeFunc) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "get callee error"));
        assert(false);
        return nullptr;
    }
    if (calleeFunc->arg_size() != 0) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                  "callee func param size does not match exp list size"));
        assert(false);
        return nullptr;
    }
    std::vector<Value *> args;


    // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
    if (calleeFunc->getReturnType()->isVoidTy()) {
        return ir_builder.CreateCall(calleeFunc, args);
    } else {
        return ir_builder.CreateCall(calleeFunc, args, pIdent->ident->content);
    }
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_string(const ast::ExpConstantString *) {
    errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                              "code_gen_exp_constant_string 2"));
    assert(false);
    return nullptr;
}

LLVMBuilder::Value *LLVMBuilder::code_gen_exp_constant_boolean(const ast::ExpConstantBoolean *pBoolean) {
    return llvm::Constant::getIntegerValue(
            llvm::Type::getInt1Ty(ctx), llvm::APInt(8, pBoolean->value->attr));
}

LLVMBuilder::Value *LLVMBuilder::code_gen_variable(const ast::Variable *node) {
    auto ptr = get_lvalue_pointer(node);
    if (ptr == nullptr) {
        assert(false);
        return nullptr;
    }
    return ir_builder.CreateLoad(ptr, "arr_load");
}

void
LLVMBuilder::code_gen_offset(std::vector<llvm::Value *> &offset, const pascal_s::ArrayInfo *ai,
                             const ast::ExpressionList *exp_list) {
    if (ai->spec->periods.size() != exp_list->explist.size()) {
        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
        assert(false);
        offset.clear();
        return;
    }

    Value *e;
    llvm::Type *llvm_i64 = llvm::IntegerType::get(ctx, 64);
    int64_t mp = 1;

    for (int64_t i = 0; i < ai->spec->periods.size(); i++) {
        auto &pd = ai->spec->periods[i];
        e = code_gen(exp_list->explist[i]);
        if (e->getType()->isIntegerTy()) {
            if (e->getType()->getIntegerBitWidth() < 64) {
                ir_builder.CreateSExt(e, llvm_i64, "exp_ext_tmp");
            }
        } else {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
            assert(false);
            offset.clear();
            return;
        }

        offset.push_back(ir_builder.CreateSub(
                e, llvm::Constant::getIntegerValue(
                        llvm::IntegerType::get(ctx, 64), llvm::APInt(64, pd.first))));
//            mp *= pd.second - pd.first;
    }
}
