//
// Created by kamiyoru on 2020/5/12.
//

#ifndef PASCAL_S_TARGET_C_H
#define PASCAL_S_TARGET_C_H

#include <pascal-s/AST.h>
#include <fmt/core.h>
#include <vector>
#include <string>

namespace target_c {
    class Buffer {

        std::ostream &os;
    public:
        Buffer(std::ostream &s) : os(s) {
        }

        Buffer &write(const std::string &s) {
            os << s;
            return *this;
        }

        Buffer &writeln(const std::string &s) {
            os << s << '\n';
            return *this;
        }
    };

    struct LinkedContext {
        LinkedContext *last;
        std::map<std::string, std::string> *content;
    };


    struct CBuilder {

        enum TranslateCode {
            OK,
            TranslateFailed,
        };

        std::vector<std::string> include_files;
        Buffer &buf;

        CBuilder(std::vector<std::string> &include_files,
                 Buffer &buf) : include_files(std::move(include_files)), buf(buf) {}

        CBuilder(std::vector<std::string> &&include_files,
                 Buffer &buf) : include_files(std::move(include_files)), buf(buf) {}

        int code_gen(const Node *node);

        int code_gen_node(const Node *node);

        int code_gen_program(const Program *node);

        int code_gen_ArrayTypeSpec(const ArrayTypeSpec *node);

        int code_gen_exp_assign(const ExpAssign *node);
    };
}


#endif //PASCAL_S_TARGET_C_H
