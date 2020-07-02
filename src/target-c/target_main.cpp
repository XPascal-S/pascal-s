//
// Created by kamiyoru on 2020/5/12.
//

#include <target/task.h>


[[maybe_unused]] int target_compile(int, const char **, CompilerTargetTask *) {
    printf("target c main function invoked");
    return 0;
}


