//
// Created by kamiyoru on 2020/5/5.
//

#include <dep/opt.h>
#include <iostream>
#include <fstream>
#include <pascal-s/interface.h>
#include <pascal-s/features.h>
#include <pascal-s/lexer.h>
#include <pascal-s/lib/stream_file.h>
//#include <pascal-s/parser.h>
//#include <target/llvm.h>
#include <target/task.h>
#include <functional>
#include <utility>
#include <pascal-s/parser.h>
#include <pascal-s/exception.h>


#define VERSION "v0.1.0"

string_view_return basename(string_view s) {
    for (size_t i = s.length() - 1; i >= 0; i--) {
        if (s[i] == '\\' || s[i] == '/') {
            return s.substr(i + 1);
        }
    }
    return s;
}

static const char *cat_default = "";
static const char *cat_compile_options = "compile options";

extern int target_compile(int argc, const char **pString, CompilerTargetTask *task);

struct CompilerOptions {
    bool help = false;
    bool version = false;
    bool env = false;
    std::string wk_dir;
    std::string source_path;
    std::string out_path;
    std::string out_with_ir;
    std::string out_with_ast;
    std::string out_with_token;

    explicit CompilerOptions(dep::OptParser &parser) {
        parser.addOpts("help", &help, "Print help message", cat_default, false, "h");
        parser.addOpts("version", &version, "Print Version", cat_default, false, "");
        parser.addOpts("env", &env, "Print the environment of pascal", cat_default, false, "");
        parser.addOpts("work-dir", &wk_dir, "Working directory",
                       cat_compile_options, ".", "wd");
        parser.addOpts("src", &source_path,
                       "Source path",
                       cat_compile_options, ".", "i");
        parser.addOpts("out", &out_path,
                       "Output path",
                       cat_compile_options, "main.o", "o");
        parser.addOpts("out-ir", &out_with_ir,
                       "Output IR code, enum of {, json, yml, fmt, binary, console}",
                       cat_compile_options, "", "f");
        parser.addOpts("out-token", &out_with_token,
                       "Output tokens, enum of {, json, yml, fmt, binary, console}",
                       cat_compile_options, "", "tf");
        parser.addOpts("out-ast", &out_with_ast,
                       "Output asts, enum of {, json, yml, fmt, binary, console}",
                       cat_compile_options, "", "af");
    }

    ~CompilerOptions() {
        for (auto &file : files) {
            delete file;
        }
    }

    std::vector<std::fstream *> files;

    std::fstream *source_file = nullptr;
    std::istream &get_source() {
        if (source_path == "stdin") {
            return std::cin;
        } else {
            if (source_file != nullptr) {
                return *source_file;
            }

            auto fs = new std::fstream(source_path);
            if (fs->fail()) {
                delete fs;
                std::cout << "Open Source File Error: " << strerror(errno) << ": " << source_path;
                exit(errno);
            }

            files.push_back(fs);
            source_file = fs;
            return *fs;
        }
    }
};

template<>
struct ErrorProxy<const PascalSError *> {
    DefaultProxyConstructor(ErrorProxy, PascalSError*, err)

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

template<typename Lexer, typename Parser>
struct Compiler {
    CompilerOptions &options;
    std::function<void(int code)> _exit;
    LexerProxy<Lexer> lexer;
    ParserProxy<Parser> parser;

    Compiler(
            LexerProxy<Lexer> lexer,
            ParserProxy<Parser> parser,
            CompilerOptions &options, std::function<void(int)> _exit)
            :
            lexer(std::move(lexer)), parser(std::move(parser)),
            options(options), _exit(std::move(_exit)) {}

    int work(int &argc, const char *argv[]) {
        reset();
        work_help(argc, argv);
        work_version(argc, argv);
        work_out_tokens(argc, argv);
        work_out_ast(argc, argv);
        work_compile(argc, argv);

        return _code;
    }

    void reset() {
        exited = false;
    }

private:
    void work_help(int, const char *argv[]) {
        if (exited) return;
        if (options.help) {
            std::cout << "usage: " << basename(argv[0]) << " [--version] [-h | --help]\n\n";

            std::cout << dep::print_helps();
            exit(0);
        }
    }

    void work_version(int, const char *[]) {
        if (exited) return;
        if (options.version) {
            std::cout << "Pascal-S Compiler, version " VERSION "\n";
            exit(0);
        }
    }

    void work_out_tokens(int, const char *[]) {
        if (exited) return;
        if (!options.out_with_token.empty()) {
            WriterProxy<std::ostream> os(std::cout);
            feature::output_tokens(lexer.get_all_tokens(), os);
            lexer.reset_cursor();
            fflush(stdout);
        }
    }

    void work_out_ast(int, const char *[]) {
        if (exited) return;
        if (!options.out_with_ast.empty()) {
            ast::printAST(get_ast());
            fflush(stdout);
        }
    }

    void work_compile(int argc, const char *argv[]) {
        if (exited) return;

        CompilerTargetTask task;

        task.target = options.out_path;
        task.source = get_ast();

        if (lexer.has_error() || parser.has_error()) {
            exit(1);
        }

        task.out_ir = !options.out_with_ir.empty();

        exit(target_compile(argc, argv, &task));
    }


    ast::Node *_cached_ast = nullptr;

    ast::Node *get_ast() {
        if (_cached_ast) return _cached_ast;

        _cached_ast = parser.parse();

        if (lexer.has_error()) {

            pascal_s::CPPStreamFile fin(options.get_source());
            FileProxy<pascal_s::CPPStreamFile> fp(fin);
            WriterProxy<std::ostream> os(std::cout);

            for (auto e : lexer.get_all_errors()) {
                feature::format_line_column_error(fp, ErrorProxy<ErrorToken>(*e), os, options.source_path.c_str());
            }
        }

        if (parser.has_error()) {

            pascal_s::CPPStreamFile fin(options.get_source());
            FileProxy<pascal_s::CPPStreamFile> fp(fin);
            WriterProxy<std::ostream> os(std::cout);

            for (auto e : parser.get_all_errors()) {
                feature::format_line_column_error(fp, ErrorProxy<const PascalSError *>(e), os,
                                                  options.source_path.c_str());
            }
        }

        return _cached_ast;
    }

    void exit(int code) {
        exited = true;
        _exit(_code = code);
    }

    bool exited = false;
    int _code = 0;
};

int main(int argc, const char *argv[]) {

    CompilerOptions options(dep::_global);
    dep::parseOpts(argc, argv);
    std::istream *is = nullptr;

    if (!options.help) {
        is = &options.get_source();
    }
    FullInMemoryLexer lexer(is, &std::cout);
    LexerProxy<FullInMemoryLexer> lexer_proxy(lexer);
    Parser<FullInMemoryLexer> parser(lexer_proxy);
    ParserProxy<Parser<FullInMemoryLexer>> parser_proxy(parser);

    Compiler<FullInMemoryLexer, Parser<FullInMemoryLexer>> compiler(
            lexer_proxy, parser_proxy,
            options, exit);

    return compiler.work(argc, argv);
}
