//
// Created by kamiyoru on 2020/5/12.
//
#include <target/c.h>
#include <iostream>
#include <target/task.h>
#include "pascal-s/features.h"
#include <iostream>

using namespace ast;



/*
program main;
begin
    write_char('h');
    write_char('e');
    write_char('l');
    write_char('l');
    write_char('o');
main := 0;
end

 */

/*
int main(){
    auto *mainProgram = test_gcd();
    target_c::Buffer tempBuffer(std::cout);
    std::vector<std::string> include_files;
    target_c::CBuilder theBuilder(include_files, tempBuffer);
    theBuilder.code_gen(mainProgram);
    printf("target c main function invoked");
}
*/

[[maybe_unused]] int target_compile(int, const char **, CompilerTargetTask * task) {
    target_c::Buffer tempBuffer(std::cout);
    std::vector<std::string> include_files;
    target_c::CBuilder theBuilder(include_files, tempBuffer);
    theBuilder.code_gen(task->source);

    if (!theBuilder.errors.empty()) {
        for (auto e : theBuilder.errors) {
            feature::format_line_column_error(
                    task->f, ErrorProxy<PascalSSemanticError *>(e), task->os, task->file_path);
        }
        return 252;
    }

    return 0;
}


