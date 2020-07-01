//
// Created by kamiyoru on 2020/6/30.
//

#include <target/llvm.h>

void LLVMBuilder::insert_var_decls(LLVMBuilder::Function *cur_func,
                                   std::map<std::string, pascal_s::ArrayInfo *> &array_infos,
                                   std::map<std::string, llvm::AllocaInst *> &map,
                                   const ast::VarDecls *pDecls) {

    if (pDecls != nullptr) {
        llvm::IRBuilder<> dfn_block(&cur_func->getEntryBlock(),
                                    cur_func->getEntryBlock().begin());

        for (auto decl : pDecls->decls) {
            llvm::Type *value = create_type(decl->type_spec);
            if (value == nullptr) {
                continue;
            }

            if (decl->type_spec->type == ast::Type::ArrayTypeSpec) {
//                auto array_info = new pascal_s::ArrayInfo{reinterpret_cast<const ast::ArrayTypeSpec *>(decl->type_spec)};
                for (auto ident : decl->idents->idents) {
                    map[ident->content] = dfn_block.CreateAlloca(value, nullptr, ident->content);
                    array_infos[ident->content] = new pascal_s::ArrayInfo{
                            reinterpret_cast<const ast::ArrayTypeSpec *>(decl->type_spec)};
                }
            } else {
                for (auto ident : decl->idents->idents) {
                    map[ident->content] = dfn_block.CreateAlloca(value, nullptr, ident->content);
                }
            }
        }
    }
}
