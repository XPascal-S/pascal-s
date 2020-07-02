//
// Created by kamiyoru on 2020/5/25.
//

#include <target/llvm.h>

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

