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
    } else {
        assert(false);
        return nullptr;
    }
}

int64_t LLVMBuilder::calc_periods_size(const ast::ArrayTypeSpec *spec) {
    int64_t ret = 1;
    for (const auto &p : spec->periods) {
        if (p.second >= p.first) {
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
            return llvm::Type::getInt8Ty(ctx);
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
    std::map<std::string, llvm::AllocaInst *> program_this;
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
    program_this[pProgram->programHead->id->ident->content] = dfn_block.CreateAlloca(llvm::Type::getInt32Ty(
            ctx), nullptr, pProgram->programHead->id->ident->content);

    if (pProgram->programBody->subprogram != nullptr) {
        for (auto fn_decl : pProgram->programBody->subprogram->subprogram) {
            code_gen_procedure(fn_decl);
        }
    }

    // reset insert point
    ir_builder.SetInsertPoint(body);

    // generate body
    if (code_gen_statement(pProgram->programBody->compound)) {
        // if body generated
        // out_code( %ret_tmp = load i32 from %program.name )
        // out_code( ret i32: %ret_tmp )
        ir_builder.CreateRet(
                ir_builder.CreateLoad(program_this[pProgram->programHead->id->ident->content], "ret_tmp"));

        llvm::verifyFunction(*program);
        fn_pass_manager.run(*program);

        // pop 'this' from scope stack
        scope_stack->deconstruct();
        scope_stack = link.last;
        return rename_program_to_pascal_s_native(program);
    }
    program->eraseFromParent();

    // pop 'this' from scope stack
    scope_stack->deconstruct();
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

void LLVMBuilder::insert_param_decls(LLVMBuilder::Function *fn, std::map<std::string, llvm::AllocaInst *> &map,
                                     std::map<std::string, llvm::Value *> &const_map) {
    for (size_t i = 0; i < fn->arg_size(); i++) {
        auto arg = fn->getArg(i);
        if (arg->getType()->isPointerTy()) {
            map[arg->getName().str()] = llvm::dyn_cast<llvm::AllocaInst>(arg);
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
    return ir_builder.CreateCall(calleeFunc, args, pCall->fn->content);
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

    llvm::AllocaInst *old_var = nullptr;
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
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
            assert(false);
            return nullptr;
    }

    Value *offset = nullptr;
    int64_t mp = 1;

    for (auto resolving_ctx = scope_stack;
         resolving_ctx; resolving_ctx = resolving_ctx->last) {
        auto &value_ctx = resolving_ctx->ctx;
        if (value_ctx->count(content)) {
            if (resolving_ctx->array_infos->count(content)) {
                if (exp_list != nullptr) {
                    auto ai = resolving_ctx->array_infos->at(content);

                    if (ai->spec->periods.size() != exp_list->explist.size()) {
                        errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
                        assert(false);
                        return nullptr;
                    }

                    Value *e = nullptr;
                    llvm::Type *llvm_i64 = llvm::IntegerType::get(ctx, 64);

                    offset = llvm::Constant::getIntegerValue(
                            llvm_i64, llvm::APInt(64, 0));

                    for (int i = ai->spec->periods.size() - 1; i >= 0; i--) {
                        auto &pd = ai->spec->periods[i];
                        e = code_gen(exp_list->explist[i]);
                        if (e->getType()->isIntegerTy()) {
                            if (e->getType()->getIntegerBitWidth() < 64) {
                                ir_builder.CreateSExt(e, llvm_i64, "exp_ext_tmp");
                            }
                        } else {
                            errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_lvalue error"));
                            assert(false);
                            return nullptr;
                        }

                        offset = ir_builder.CreateAdd(
                                offset, ir_builder.CreateMul(e, llvm::Constant::getIntegerValue(
                                        llvm::IntegerType::get(ctx, 64), llvm::APInt(64, mp))));
                        mp *= pd.second - pd.first;
                    }
                    assert(false);
                } else {
                    errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_named_value error"));
                    assert(false);
                    return nullptr;
                }
            }

            auto ptr = (*value_ctx)[content];
            auto elemType = ptr->getType()->getElementType();
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

            if (offset != nullptr) {
                ir_builder.CreateStore(rhs, ir_builder.CreateGEP(ptr, offset, "gep_tmp"));
            } else {
                ir_builder.CreateStore(rhs, ptr);
            }
            return rhs;
        }
        auto &const_ctx = resolving_ctx->const_ctx;
        if (const_ctx->count(content)) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_named_value const error"));
            assert(false);
            return nullptr;
        }
    }
    errors.push_back(new PascalSSemanticError(__FUNCTION__, "assign_named_value not found error"));
    assert(false);
    return nullptr;
}

LLVMBuilder::Value *LLVMBuilder::get_lvalue_pointer(const ast::Exp *lvalue) {
    switch (lvalue->type) {
        case ast::Type::Ident:
            return get_named_value_pointer(
                    reinterpret_cast<const ast::Ident *>(lvalue)->ident->content);
        default:
            assert(false);
            return nullptr;
    }
}

LLVMBuilder::Value *LLVMBuilder::get_named_value_pointer(const char *name) {
    for (auto resolving_ctx = scope_stack;
         resolving_ctx; resolving_ctx = resolving_ctx->last) {
        auto &value_ctx = resolving_ctx->ctx;
        if (value_ctx->count(name)) {
            if (resolving_ctx->array_infos->count((name))) {
                errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                          "get_named_value_pointer 1"));
                assert(false);
                return nullptr;
            }
            auto ptr = ir_builder.CreateLoad((*value_ctx).at(name));
            return ptr->getPointerOperand();
        }
        auto &const_ctx = resolving_ctx->const_ctx;
        if (const_ctx->count(name)) {
            errors.push_back(new PascalSSemanticError(__FUNCTION__,
                                                      "get_named_value_pointer 2"));
            assert(false);
            return nullptr;
        }
    }
    return nullptr;
}
