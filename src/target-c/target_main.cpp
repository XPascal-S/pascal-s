//
// Created by kamiyoru on 2020/5/12.
//
#include <target/c.h>
#include <iostream>
#include <target/task.h>
#include "pascal-s/features.h"

using namespace ast;

template<>
struct ErrorProxy<PascalSSemanticError *> {
    DefaultProxyConstructor(ErrorProxy, PascalSSemanticError*, err)

    [[maybe_unused]] [[nodiscard]] pascal_s::line_t visit_line() const {
        return err->line;
    }

    [[maybe_unused]] [[nodiscard]] pascal_s::column_t visit_column() const {
        return err->column;
    }

    [[maybe_unused]] [[nodiscard]] pascal_s::length_t visit_length() const {
        return err->length;
    }

    [[maybe_unused]] [[nodiscard]] pascal_s::offset_t visit_offset() const {
        return err->offset;
    }

    // 如果没有hint，为nullptr
    [[maybe_unused]] [[nodiscard]] const char *visit_hint() const {
        return err->msg.c_str();
    }
};

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


