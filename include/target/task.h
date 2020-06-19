//
// Created by kamiyoru on 2020/5/9.
//

#ifndef PASCAL_S_TARGET_TASK_H
#define PASCAL_S_TARGET_TASK_H

#include <string>

struct CompilerTargetTask {
//    ast::Node *source;
    std::string target;
    bool out_ir;
};

#endif //PASCAL_S_TARGET_TASK_H
