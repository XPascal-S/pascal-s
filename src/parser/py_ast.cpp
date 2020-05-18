#include <cstdlib>
#include <pascal-s/AST.h>
#include <pascal-s/mock.h>
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <vector>

#include "parser.h"

extern "C" {
  Node *ParseToken() {
    std::vector<Token *> mocking_stream{
                                        new Keyword("program", KeywordType::Program),
                                        new Identifier("test"),
                                        new Marker(";", MarkerType::Semicolon),
                                        new Keyword("const", KeywordType::Const),
                                        new Identifier("a"),
                                        new Marker("=", MarkerType::EQ),
                                        new ConstantInteger("2"),
                                        new Marker(";", MarkerType::Semicolon),
                                        new Keyword("var", KeywordType::Var),
                                        new Identifier("b"),
                                        new Marker(":", MarkerType::Colon),
                                        new Keyword("integer", KeywordType::Integer),
                                        new Marker(";", MarkerType::Semicolon),
                                        new Keyword("begin", KeywordType::Begin),
                                        new Keyword("end", KeywordType::End),
                                        new Marker(".", MarkerType::Dot)
    };

    MockLexer lexer(mocking_stream);
    LexerProxy<MockLexer> lexer_proxy(lexer);

    YACCParser<MockLexer> parser(lexer_proxy);

    parser.set_debug_level(1);

    auto res = parser.parse();
    if (res)
      return NULL;
    else
      return parser.ast_root;
  }
}

PYBIND11_MODULE(py_ast, m) {
  m.doc() = "pybind11 example plugin"; // optional module docstring

  m.def("ParseToken", &ParseToken, "Get AST root from token stream");
  // m.def("GetTokenSymbol", &GetTokenSymbol, "Get token symbok from an AST node");

  pybind11::enum_<Type>(m, "Type")
    .value("Unknown", Type::Unknown)
    .value("Program", Type::Program)
    .value("Procedure", Type::Procedure)
    .value("Function", Type::Function)
    .value("StatementBlock", Type::StatementBlock)
    .value("Statement", Type::Statement)
    .value("ExpCall", Type::ExpCall)
    .value("IfElseStatement", Type::IfElseStatement)
    .value("ForStatement", Type::ForStatement)
    .value("ExpConstantInteger", Type::ExpConstantInteger)
    .value("ExpConstantChar", Type::ExpConstantChar)
    .value("ExpConstantBoolean", Type::ExpConstantBoolean)
    .value("ExpConstantString", Type::ExpConstantString)
    .value("ExpConstantReal", Type::ExpConstantReal)
    .value("Ident", Type::Ident)
    .value("ParamList", Type::ParamList)
    .value("VariableList", Type::VariableList)
    .value("IdentList", Type::IdentList)
    .value("ConstDecl", Type::ConstDecl)
    .value("ConstDecls", Type::ConstDecls)
    .value("VarDecl", Type::VarDecl)
    .value("VarDecls", Type::VarDecls)
    .value("FunctionDecl", Type::FunctionDecl)
    .value("FunctionDecls", Type::FunctionDecls)
    .value("ExpAssign", Type::ExpAssign)
    .value("Exp", Type::Exp)
    .value("TypeSpec", Type::TypeSpec)
    .value("UnExp", Type::UnExp)
    .value("BiExp", Type::BiExp)
    .value("BasicTypeSpec", Type::BasicTypeSpec)
    .value("ArrayTypeSpec", Type::ArrayTypeSpec)
    .value("ExpKeyword", Type::ExpKeyword)
    .value("ExpMarker", Type::ExpMarker)
    .value("ExpVoid", Type::ExpVoid)
    .export_values();

  pybind11::class_<Node>(m, "Node")
    .def(pybind11::init<Type>())
    .def_readonly("type", &Node::type)
    .def_readonly("children", &Node::children)
    .def("GetTokenSymbol", &Node::GetTokenSymbol);
}
