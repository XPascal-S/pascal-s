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

    struct CBuilder {

        std::vector<std::string> include_files;

        explicit CBuilder(std::vector<std::string> &include_files) : include_files(std::move(include_files)) {}

        explicit CBuilder(std::vector<std::string> &&include_files) : include_files(std::move(include_files)) {}

        int code_gen(Node *node, Buffer &buf) {
            for (const auto &f : include_files) {
                buf.writeln(fmt::format("#include <{}>", f));
            }

            buf
                    .writeln("int main(){");
            code_gen_program(node, buf);
            buf
                    .writeln("return 0;")
                    .writeln("}");
            return 0;
        }

        static int code_gen_program(Node *node, Buffer &buf) {
            buf.writeln("printf(\"hello world\");");
            return 0;
        }
    };
}


#endif //PASCAL_S_TARGET_C_H
