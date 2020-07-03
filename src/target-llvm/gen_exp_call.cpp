//
// Created by kamiyoru on 2020/5/10.
//

#include <target/llvm.h>


LLVMBuilder::Value *LLVMBuilder::code_gen_exp_call(const ast::ExpCall *pCall) {
    // get function proto llvm_func
    Function *calleeFunc = modules.getFunction(pCall->fn->content);
    if (!calleeFunc) {
        llvm_pascal_s_report_semantic_error_n(pCall->fn, "get callee error");
        return nullptr;
    }
    if (calleeFunc->arg_size() != pCall->params->explist.size()) {
        llvm_pascal_s_report_semantic_error_n(pCall->params, "callee func param size does not match exp list size");
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
            llvm_pascal_s_report_semantic_error_n(pCall->params->explist[i], "gen exp failed");
            gen_exp_failed = true;
        } else if (argument_proto->getType()->getTypeID() != argument_value->getType()->getTypeID()) {
            // todo: implicit type conversion feature
            llvm_pascal_s_report_semantic_warning_n(pCall->params->explist[i], "callee func gen exp type conflicted");
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
