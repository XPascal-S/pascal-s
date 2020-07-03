//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>
#include <fmt/core.h>


LLVMBuilder::Value *LLVMBuilder::code_gen_read_statement(const ast::Read *stmt) {
    Value *ret_value = llvm::Constant::getIntegerValue(
            llvm::IntegerType::get(ctx, 32), llvm::APInt(32, 0));

    for (auto ptr_proto: stmt->var_list->params) {
        auto res = get_lvalue_pointer(ptr_proto);
        if (res == nullptr) {
            ret_value = nullptr;
            continue;
        }

        // get function proto llvm_func
        Function *calleeFunc = nullptr;
        switch (res->getType()->getPointerElementType()->getTypeID()) {
            default:
                llvm_pascal_s_report_semantic_error_n(
                        ptr_proto,
                        fmt::format("could not read a variable with type {}",
                                    format_type(res->getType())));
                ret_value = nullptr;
                break;
            case llvm::Type::DoubleTyID:
                calleeFunc = modules.getFunction("read_real");
                break;
            case llvm::Type::IntegerTyID:
                auto bw = res->getType()->getPointerElementType()->getIntegerBitWidth();
                if (bw == 64) {
                    calleeFunc = modules.getFunction("read_int64");
                } else if (bw == 32) {
                    calleeFunc = modules.getFunction("read_int32");
                } else if (bw == 8) {
                    calleeFunc = modules.getFunction("read_char");
                } else if (bw == 1) {
                    calleeFunc = modules.getFunction("read_bool");
                }
                break;
        }
        if (!calleeFunc) {
            llvm_pascal_s_report_semantic_error_n(
                    ptr_proto,
                    fmt::format("could not read a variable with type {}, read callee not found",
                                format_type(res->getType())));
            ret_value = nullptr;
            continue;
        }
        assert(calleeFunc->arg_size() == 1);
        std::vector<Value *> args;
        auto *argument_proto = calleeFunc->getArg(0);
        assert(argument_proto->getType()->getTypeID() == res->getType()->getTypeID());
        args.push_back(res);

        // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
        if (ret_value)
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
            ret_value = nullptr;
            continue;
        }

        // get function proto llvm_func
        Function *calleeFunc = nullptr;
        switch (res->getType()->getTypeID()) {
            case llvm::Type::IntegerTyID:
                if (res->getType()->getIntegerBitWidth() == 64) {
                    calleeFunc = modules.getFunction("write_int64");
                } else if (res->getType()->getIntegerBitWidth() == 32) {
                    calleeFunc = modules.getFunction("write_int32");
                } else if (res->getType()->getIntegerBitWidth() == 8) {
                    calleeFunc = modules.getFunction("write_char");
                } else if (res->getType()->getIntegerBitWidth() == 1) {
                    calleeFunc = modules.getFunction("write_bool");
                }
                break;
            case llvm::Type::DoubleTyID:
                calleeFunc = modules.getFunction("write_real");
                break;
            default:
                llvm_pascal_s_report_semantic_error_n(
                        exp_proto,
                        fmt::format("could not write a variable with type {}",
                                    format_type(res->getType())));
                ret_value = nullptr;
                break;
        }
        if (!calleeFunc) {
            llvm_pascal_s_report_semantic_error_n(
                    exp_proto,
                    fmt::format("could not write a variable with type {}, write callee not found",
                                format_type(res->getType())));
            ret_value = nullptr;
            continue;
        }
        assert(calleeFunc->arg_size() == 1);
        std::vector<Value *> args;
        auto *argument_proto = calleeFunc->getArg(0);
        assert(argument_proto->getType()->getTypeID() == res->getType()->getTypeID());
        args.push_back(res);

        // out_code(%call_stmt.name = call ret_type @call_stmt.name(args))
        if (ret_value)
            ret_value = ir_builder.CreateAdd(ret_value, ir_builder.CreateCall(calleeFunc, args, "write_tmp"));
    }
    return ret_value;
}
