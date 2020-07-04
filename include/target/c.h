//
// Created by kamiyoru on 2020/5/12.
//

#ifndef PASCAL_S_TARGET_C_H
#define PASCAL_S_TARGET_C_H

#define ISCONSTANT 1
#define ISBASIC 2
#define ISARRAY 3

#include <pascal-s/llvm-ast.h>
#include <fmt/include/fmt/core.h>
#include <vector>
#include <string>
#include <deque>

using namespace ast;
using namespace std::string_literals;

namespace target_c {

    std::map<char, std::string> escapeTable = {
            {'\0', "\\0"},
            {'\1', "\\1"},
            {'\2', "\\2"},
            {'\3', "\\3"},
            {'\4', "\\4"},
            {'\5', "\\5"},
            {'\6', "\\6"},
            {'\7', "\\7"},
            {'\8', "\\8"},
            {'\9', "\\9"},
            {'\10', "\\10"},
            {'\11', "\\11"},
            {'\12', "\\12"},
            {'\13', "\\13"},
            {'\14', "\\14"},
            {'\15', "\\15"},
            {'\16', "\\16"},
            {'\17', "\\17"},
            {'\18', "\\18"},
            {'\19', "\\19"},
            {'\20', "\\20"},
            {'\21', "\\21"},
            {'\22', "\\22"},
            {'\23', "\\23"},
            {'\24', "\\24"},
            {'\25', "\\25"},
            {'\26', "\\26"},
            {'\27', "\\27"},
            {'\28', "\\28"},
            {'\29', "\\29"},
            {'\30', "\\30"},
            {'\31', "\\31"},
            {'\32', "\\32"},
    };

    class Buffer {
        std::ostream &os;
    public:
        Buffer(std::ostream &s) : os(s) {}

        Buffer &write(const std::string &s) {
            os << s;
            return *this;
        }

        Buffer &writeln(const std::string &s) {
            os << s + '\n';
            return *this;
        }
    };

    //符号表表项
    struct SymbolEntry {
        std::string typeDecl;//变量定义类型
        std::string value; //变量值 在常数定义语境下是常量值。
        const struct ArrayTypeSpec *arrayInfo; // 数组信息.
        char varType; //变量类型 (常数定义，基本类型定义，数组定义。)
    };

    //符号表
    struct SymbolTable {
        std::string tableName;  //表示当前符号表的作用域。（以函数名称作为区分）
        SymbolTable *prev; //指向上层符号表
        std::map<std::string, struct SymbolTable *> nextTable; //Hash。函数名->符号表的映射
        std::map<std::string, struct SymbolEntry> content; //Hash。原始变量名->变量属性的映射
        //original_string --> new_string
    };

    struct FuncInfo {
        std::string funcName; //函数名
        std::string returnType; //函数返回类型
        std::vector<std::string> paraType; //函数形参类型表
        std::string formalPara; // 函数定义字符串 int a, int b,
        std::string additionPara; // 函数形参追加表 (用以传入不在函数内定义的变量) c, d
        std::string funcBody; // 函数体
        //formalPara, 用于最终函数定义时字符串输出。包含原始形参表和追加形参表的字符串内容
        //additionPara 不是形参定义表。只是在调用函数时，需要追加在调用参数后面。
    };

    struct CBuilder {

        enum TranslateCode {
            TranslateFailed,
            OK
        };

        std::vector<std::string> include_files;
        Buffer &outputBuff; //输出buffer
        std::map<std::string, struct FuncInfo> functionBuff; //函数定义字符串
        std::string mainBuff; // 主函数字符串
        std::vector<std::string> callRecordBuff; //记录函数调用顺序，用于debug
        struct SymbolTable *startST_pointer; //符号表入口指针
        struct SymbolTable *nowST_pointer; //当前符号表指针
        std::vector<PascalSSemanticError *> errors; //错误信息
        int tabNum = 0;

        CBuilder(std::vector<std::string> &include_files,
                 Buffer &buf) : include_files(std::move(include_files)), outputBuff(buf) {
            this->startST_pointer = new SymbolTable;
            this->nowST_pointer = this->startST_pointer;
            this->nowST_pointer->prev = NULL;
            this->nowST_pointer->tableName = "main";
            struct FuncInfo functionInfo;
            functionInfo.funcName = "main";
            functionInfo.returnType = "int";
            functionInfo.funcBody = "";
            functionInfo.formalPara = "";
            functionInfo.additionPara = "";
            this->functionBuff.insert(std::pair<std::string, struct FuncInfo>(this->nowST_pointer->tableName, functionInfo));
        }

        ~CBuilder() {
            std::deque<struct SymbolTable *> st_deque;
            st_deque.push_back(this->startST_pointer);
            while (!st_deque.empty()) {
                struct SymbolTable *now_pointer = st_deque.front();
                st_deque.pop_front();
                for (auto x : now_pointer->nextTable) {
                    st_deque.push_back(x.second);
                }
                delete now_pointer;
            }
        }

        int code_gen(const Node *node) {
            if (node->type != Type::Program) {
                assert(false);
                throw std::runtime_error("node type is not program");
                return TranslateFailed;
            }
            int code = code_gen_node(node);

            this->tabNum = 0;
            //输出头文件
            for (const auto &f : include_files) {
                outputBuff.writeln(fmt::format("#include <{}>", f));
//                outputBuff.writeTab(this->tabNum);
            }

            //输出全局变量定义
            /*
            for(auto const& x : startST_pointer->content){
                if(x.second.varType == ISCONSTANT){
                    outputBuff.writeln(fmt::format("const {0} {1} = {2};",
                            x.second.typeDecl, x.first, x.second.value));
                }else if(x.second.varType == ISBASIC){
                    outputBuff.writeln(fmt::format("{0} {1};",
                            x.second.typeDecl, x.first));
                }else if(x.second.varType == ISARRAY){
                    std::string tempArray = "";
                    tempArray += x.second.typeDecl + " ";
                    tempArray += x.first;
                    for(auto x : x.second.arrayInfo->periods){
                        tempArray += "[" + std::to_string(x.second) + "]";
                    }
                    outputBuff.writeln(tempArray);
                }else{
                    assert(false);
                    return TranslateFailed;
                }
            }
             */

            //输出函数定义
            for (auto x : this->functionBuff) {
                if(x.first == "main")
                    continue;
                x.second.formalPara.pop_back();
                x.second.formalPara.pop_back();
                this->outputBuff.writeln(
                        x.second.returnType + " " + x.second.funcName + "("
                        + x.second.formalPara + ") {"
                );
                this->outputBuff.write(x.second.funcBody);
//                this->outputBuff.writeTab(this->tabNum);
                this->outputBuff.writeln("}");
//                this->outputBuff.writeTab(this->tabNum);
                this->outputBuff.writeln("");
            }

            //输出主函数内容
            outputBuff.writeln("int main() {").write(fmt::format("{}", this->mainBuff));
//            this->outputBuff.writeTab(this->tabNum);
            outputBuff.writeln("}");
            return code;
        }

        int constType2str(const Node *node, std::string &result) {
            switch (node->type) {
                case Type::ExpConstantInteger:
                    result = "int";
                    return 1;
                case Type::ExpConstantChar:
                    result = "char";
                    return 1;
                case Type::ExpConstantBoolean:
                    result = "int";
                    return 1;
                case Type::ExpConstantReal:
                    result = "double";
                    return 1;
                case Type::ExpConstantString:
                    result = "char*";
                    return 1;
                default:
                    addErrMsg(node, "no const type match");
                    assert(false);
                    return 0;
            }
        }

        int keyword2str(const KeywordType kt, std::string &result) {
            switch (kt) {
                case KeywordType::Boolean:
                    result = "int";
                    return 1;
                case KeywordType::Integer:
                    result = "int";
                    return 1;
                case KeywordType::Char:
                    result = "char";
                    return 1;
                case KeywordType::Real:
                    result = "double";
                    return 1;
                case KeywordType::Mod:
                    result = "%";
                    return 1;
                case KeywordType::And:
                    result = "&&";
                    return 1;
                case KeywordType::Or:
                    result = "||";
                    return 1;
                case KeywordType::Not:
                    result = "!";
                    return 1;
                default:
                    assert(false);
                    throw std::runtime_error("semantic error: no keyword type match");
                    return 0;
            }
        }

        int marker2str(const MarkerType mt, std::string &result) {
            switch (mt) {
                case MarkerType::NEQ:
                    result = "!=";
                    return OK;
                case MarkerType::LE:
                    result = "<=";
                    return OK;
                case MarkerType::GE:
                    result = ">=";
                    return OK;
                case MarkerType::LT:
                    result = "<";
                    return OK;
                case MarkerType::EQ:
                    result = "==";
                    return OK;
                case MarkerType::GT:
                    result = ">";
                    return OK;
                case MarkerType::Add:
                    result = "+";
                    return OK;
                case MarkerType::Sub:
                    result = "-";
                    return OK;
                case MarkerType::Mul:
                    result = "*";
                    return OK;
                case MarkerType::Div:
                    result = "/";
                    return OK;
                case MarkerType::LParen:
                    result = "(";
                    return OK;
                case MarkerType::RParen:
                    result = ")";
                    return OK;
                case MarkerType::LBracket:
                    result = "[";
                    return OK;
                case MarkerType::RBracket:
                    result = "]";
                    return OK;
                case MarkerType::Assign:
                    result = "=";
                    return OK;
                case MarkerType::Comma:
                    result = ",";
                    return OK;
                case MarkerType::Dot:
                    result = ".";
                    return OK;
                case MarkerType::Semicolon:
                    result = ";";
                    return OK;
                case MarkerType::Colon:
                    result = ":";
                    return OK;
                case MarkerType::Mod:
                    result = "%";
                    return OK;
                case MarkerType::LogicAnd:
                    result = "&&";
                    return OK;
                case MarkerType::LogicNot:
                    result = "!";
                    return OK;
                case MarkerType::LogicOr:
                    result = "||";
                    return OK;
                default:
                    //assert(false);
                    throw std::runtime_error("semantic error: no marker type match");
                    return TranslateFailed;
            }
        }

        void addWarningMsg(const Node *node, const std::string msg){
            auto fn = __FUNCTION__ ;
            this->errors.push_back(new PascalSSemanticError(fn, node->visit_pos(),
                    "semantic Warning: at function" + (fn + (": " + msg))));
        }

        void addErrMsg(const Node *node, const std::string msg) {
            auto fn = __FUNCTION__ ;
            this->errors.push_back(new PascalSSemanticError(fn, node->visit_pos(),
                                                            "semantic error: at function" + (fn + (": " + msg))));
        }

        void printTab(std::string &buffer) {
            for (int i = 0; i < this->tabNum; i++)
                buffer += '\t';
        }

        int code_gen_node(const Node *node) {
            if(node == NULL)
                return OK;
            switch (node->type) {
                default:
                    addErrMsg(node, "no node type match");
                    assert(false);
                    return TranslateFailed;
                case Type::Unknown:
                    addErrMsg(node, "unknown node type");
                    assert(false);
                    return TranslateFailed;
                case Type::Program:
                    return code_gen_program(
                            reinterpret_cast<const Program *>(node));
                case Type::ProgramHead:
                    return code_gen_programHead(
                            reinterpret_cast<const ProgramHead *>(node));
                case Type::ProgramBody:
                    return code_gen_programBody(
                            reinterpret_cast<const ProgramBody *>(node));
                case Type::SubprogramDecls:
                    return code_gen_SubprogramDecls(
                            reinterpret_cast<const SubprogramDecls *>(node));
                case Type::Subprogram:
                    return code_gen_Subprogram(
                            reinterpret_cast<const Subprogram *>(node));
                case Type::SubprogramHead:
                    return code_gen_SubprogramHead(
                            reinterpret_cast<const SubprogramHead *>(node));
                case Type::SubprogramBody:
                    return code_gen_SubprogramBody(
                            reinterpret_cast<const SubprogramBody *>(node));
            }
        }

        int code_gen_programHead(const ProgramHead *node) {
            // Currently there is no corresponding relation
            // from pascal head to C head
            return OK;
        }

        int code_gen_programBody(const ProgramBody *node) {
            bool check = true;
            check &= code_gen_ConstDecls(node->constdecls, this->mainBuff);
            check &= code_gen_VarDecls(node->vardecls, this->mainBuff);
            check &= code_gen_node(node->subprogram); //SubprogramDecls
            check &= code_gen_CompoundStatement(node->compound, this->mainBuff); //CompoundStatement
            return check;
        }

        int code_gen_program(const Program *node) {
            // in fmt::format {{ = {, }} = }
            //
            //buf.writeln(fmt::format("int {}(){{", node->name->content));
            //buf.writeln("printf(\"hello world\");");
            //buf.writeln("}");
            bool check = true;
            check &= code_gen_node(node->programHead);
            this->tabNum += 1;
            check &= code_gen_node(node->programBody);
            return check;
        }

        int code_gen_ConstDecls(const ConstDecls *node, std::string &buffer) {
            if (node == NULL)
                return OK;
            bool check = true;
            for (auto x : node->decls) {
                check &= code_gen_ConstDecl(x, buffer);
            }
            return check;
        }

        int code_gen_ConstDecl(const ConstDecl *node, std::string &buffer) {
            std::string lhs = node->ident->content;
            struct SymbolEntry se;
            se.varType = ISCONSTANT;
            std::string constStringValue = "";
            //se.newName = lhs + "_" + this->nowST_pointer->tableName;
            switch (node->rhs->type) {
                case Type::ExpConstantInteger:
                    se.typeDecl = "int";
                    se.value = std::to_string(reinterpret_cast<const ExpConstantInteger *>(node->rhs)->value->attr);
                    break;
                case Type::ExpConstantString:
                    se.typeDecl = "char*";
                    code_gen_String_helper(reinterpret_cast<const ExpConstantString *>(node->rhs)->value->attr, constStringValue);
                    se.value = fmt::format("\"{0}\"", constStringValue);
                    break;
                case Type::ExpConstantReal:
                    se.typeDecl = "double";
                    se.value = std::to_string(reinterpret_cast<const ExpConstantReal *>(node->rhs)->value->attr);
                    break;
                case Type::ExpConstantChar:
                    se.typeDecl = "char";
                    code_gen_Char_helper(reinterpret_cast<const ExpConstantChar *>(node->rhs)->value->attr, constStringValue);
                    se.value = fmt::format("'{0}'", constStringValue);
                    break;
                case Type::ExpConstantBoolean:
                    se.typeDecl = "int";
                    se.value = std::to_string(reinterpret_cast<const ExpConstantBoolean *>(node->rhs)->value->attr);
                    break;
                default:
                    assert(false);
                    addErrMsg(node, "no constant type match");
                    return TranslateFailed;
            }

            if(se.typeDecl == "char*"){
                auto *arrayType = new ArrayTypeSpec(new Keyword(KeywordType::Char));
                arrayType->periods.push_back(std::pair<int, int>(0, se.value.size()));
                se.arrayInfo = arrayType;
            }
            this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(lhs, se));
            printTab(buffer);
            buffer += fmt::format("const {0} {1} = {2};\n", se.typeDecl, lhs, se.value);
            return OK;
        }

        int code_gen_VarDecls(const VarDecls *node, std::string &buffer) {
            if(node == NULL)
                return OK;
            bool check = true;
            for (auto x : node->decls) {
                check &= code_gen_VarDecl(x, buffer);
            }
            return check;
        }

        int code_gen_VarDecl(const VarDecl *node, std::string &buffer) {
            for (auto x : node->idents->idents) {
                std::string name = x->content;
                struct SymbolEntry se;
                //se.newName = name + "_" + this->nowST_pointer->tableName;
                if (node->type_spec->type == Type::BasicTypeSpec) {
                    keyword2str(reinterpret_cast<const BasicTypeSpec *>(node->type_spec)->keyword->key_type, se.typeDecl);
                    se.varType = ISBASIC;
                    se.arrayInfo = nullptr;
                    printTab(buffer);
                    buffer += fmt::format("{0} {1};\n", se.typeDecl, name);
                } else if (node->type_spec->type == Type::ArrayTypeSpec) {
                    se.arrayInfo = reinterpret_cast<const ArrayTypeSpec *>(node->type_spec);
                    se.varType = ISARRAY;
                    keyword2str(se.arrayInfo->keyword->key_type, se.typeDecl);
                    printTab(buffer);
                    buffer += fmt::format("{0} {1}", se.typeDecl, name);
                    for(int i=0; i<se.arrayInfo->periods.size(); i++){
                        se.typeDecl += "*"; //数组类型 example：char**
                    }
                    for (auto x : se.arrayInfo->periods) {
                        buffer += "[" + std::to_string(x.second - x.first + 1) + "]";
                    }
                    buffer += ";\n";
                } else {
                    addErrMsg(node, "no var type match");
                    assert(false);
                    return TranslateFailed;
                }
                this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(name, se));
            }
            return OK;
        }

        int code_gen_SubprogramDecls(const SubprogramDecls *node) {
            bool check = true;
            for (auto x : node->subprogram) {
                check &= code_gen_node(x);
            }
            return check;
        }

        int code_gen_Subprogram(const Subprogram *node) {
            //符号表的初始化，在subprogram_head中完成
            bool check = true;
            check &= code_gen_node(node->subhead);
            check &= code_gen_node(node->subbody);
            this->nowST_pointer = this->nowST_pointer->prev; // 回到上层符号表，subprogram生成完毕
            return check;
        }

        int code_gen_SubprogramHead(const SubprogramHead *node) {
            bool check = true;
            struct SymbolTable *st_pointer = new struct SymbolTable;
            st_pointer->prev = this->nowST_pointer;
            struct FuncInfo functionInfo;
            functionInfo.funcBody = "";
            functionInfo.formalPara = "";
            functionInfo.additionPara = "";
            std::string funcName = node->name->content;
            st_pointer->tableName = funcName;
            functionInfo.funcName = funcName;
            if(node->ret_type == nullptr){
                functionInfo.returnType = "void";
            }else {
                check &= keyword2str(node->ret_type->keyword->key_type, functionInfo.returnType);
            }
            if(node->decls != nullptr) {
                for (const auto param : node->decls->params) {
                    for (const auto id : param->id_list->idents) {
                        struct SymbolEntry se;
                        if (param->spec->type == Type::BasicTypeSpec) {
                            check &= keyword2str(
                                    reinterpret_cast<const BasicTypeSpec *>(param->spec)->keyword->key_type,
                                    se.typeDecl);
                            functionInfo.paraType.push_back(se.typeDecl);
                            se.varType = ISBASIC;
                        } else if (param->spec->type == Type::ArrayTypeSpec) {
                            check &= keyword2str(
                                    reinterpret_cast<const ArrayTypeSpec *>(param->spec)->keyword->key_type,
                                    se.typeDecl);
                            for (int i = 0;
                                 i < reinterpret_cast<const ArrayTypeSpec *>(param->spec)->periods.size(); i++) {
                                se.typeDecl += "*"; //数组类型
                            }
                            functionInfo.paraType.push_back(se.typeDecl);
                            se.varType = ISARRAY;
                            se.arrayInfo = reinterpret_cast<const ArrayTypeSpec *>(param->spec);
                        } else {
                            addErrMsg(node, "no var type match");
                            assert(false);
                            return TranslateFailed;
                        }

                        st_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(id->content, se));
                        functionInfo.formalPara += se.typeDecl + " " + id->content + ", ";
                    }
                }
            }
            this->functionBuff.insert(std::pair<std::string, struct FuncInfo>(funcName, functionInfo));
            this->nowST_pointer->nextTable.insert(
                    std::pair<std::string, struct SymbolTable *>(funcName, st_pointer));
            this->nowST_pointer = st_pointer;
            //check &= code_gen_node(node->func);
            return check;
        }

        int code_gen_SubprogramBody(const SubprogramBody *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                addErrMsg(node, "func or proc not found in functionBuff");
                return TranslateFailed;
            }
            bool check = true;
            struct FuncInfo &nowFuncInfo = iter->second;
            check &= code_gen_ConstDecls(node->constdecls, nowFuncInfo.funcBody);
            check &= code_gen_VarDecls(node->vardecls, nowFuncInfo.funcBody);
            check &= code_gen_CompoundStatement(node->compound, nowFuncInfo.funcBody);
            return check;
        }

        int code_gen_CompoundStatement(const CompoundStatement *node, std::string &buffer) {
            bool check = true;
            for (auto x : node->state->statement) {
                if(x->type != Type::IfElseStatement && x->type != Type::ForStatement)
                    printTab(buffer);
                check &= code_gen_Statement(x, buffer);
                if(x->type != Type::IfElseStatement && x->type != Type::ForStatement)
                    buffer += ";\n";
            }
            return check;
        }

        int code_gen_exp(const Exp *node, std::string &buffer, std::string &expType) {
            switch (node->type) {
                case Type::BiExp:
                    return code_gen_BiExp(reinterpret_cast<const BiExp *>(node), buffer, expType);
                case Type::UnExp:
                    return code_gen_UnExp(reinterpret_cast<const UnExp *>(node), buffer, expType);
                case Type::Read:
                    return code_gen_Read(reinterpret_cast<const Read *>(node), buffer);
                case Type::Write:
                    return code_gen_Write(reinterpret_cast<const Write *>(node), buffer);
                case Type::ExpCall:
                    return code_gen_ExpCall(reinterpret_cast<const ExpCall *>(node), buffer, expType);
                case Type::ExpAssign:
                    return code_gen_ExpAssign(reinterpret_cast<const ExpAssign *>(node), buffer, expType);
                case Type::Variable: // AST里的Variabele有拼写错误
                    return code_gen_Variable(reinterpret_cast<const Variable *>(node), buffer, expType);
                case Type::ExpConstantBoolean:
                    return code_gen_ExpConstantBoolean(reinterpret_cast<const ExpConstantBoolean *>(node), buffer,
                                                       expType);
                case Type::ExpConstantChar:
                    return code_gen_ExpConstantChar(reinterpret_cast<const ExpConstantChar *>(node), buffer, expType);
                case Type::ExpConstantReal:
                    return code_gen_ExpConstantReal(reinterpret_cast<const ExpConstantReal *>(node), buffer, expType);
                case Type::ExpConstantInteger:
                    return code_gen_ExpConstantInteger(reinterpret_cast<const ExpConstantInteger *>(node), buffer,
                                                       expType);
                case Type::ExpConstantString:
                    return code_gen_ExpConstantString(reinterpret_cast<const ExpConstantString *>(node), buffer,
                                                      expType);
                case Type::Ident:
                    return code_gen_Ident(reinterpret_cast<const Ident *>(node), buffer, expType);
                default:
                    assert(false);
                    return TranslateFailed;
            }
            return OK;
        }

        int code_gen_Ident(const Ident *node, std::string &buffer, std::string &expType){
            // Deal with Ident
            std::string identName = node->ident->content;
            auto funcFinder = this->functionBuff.find(identName);
            if(funcFinder != this->functionBuff.end()){
                //Ident is function call
                auto *tempCall = new ExpCall(node->ident, nullptr);
                delete node;
                return code_gen_ExpCall(tempCall, buffer, expType);
            }else{
                //Take Ident as variable
                auto *tempVariable = new Variable;
                tempVariable->id = node->ident;
                delete node;
                return code_gen_Variable(tempVariable, buffer, expType);
                return OK;
            }
        }

        int code_gen_Statement(const Statement *node, std::string &buffer) {
            // 该函数负责statement的生成。
            std::string tempString;
            bool check = true;
            switch (node->type) {
                case Type::ExecStatement:
                    check &= code_gen_exp(reinterpret_cast<const ExecStatement *>(node)->exp, buffer, tempString);
                    return check;
                case Type::IfElseStatement:
                    return code_gen_IfElseStatement(reinterpret_cast<const IfElseStatement *>(node), buffer);
                case Type::ForStatement:
                    return code_gen_ForStatement(reinterpret_cast<const ForStatement *>(node), buffer);
                case Type::CompoundStatement:
                    return code_gen_CompoundStatement(reinterpret_cast<const CompoundStatement *>(node), buffer);
                case Type::Read:
                    return code_gen_Read(reinterpret_cast<const Read*>(node), buffer);
                case Type::Write:
                    return code_gen_Write(reinterpret_cast<const Write*>(node), buffer);
                default:
                    addErrMsg(node, "no statement type match");
                    return TranslateFailed;
            }
        }

        int type_check(std::string lhs, std::string rhs, const Node *node){
            if(lhs != rhs){
                if(lhs == "int" && rhs == "char"){
                    return OK;
                }else if(lhs == "char" && rhs == "int"){
                    addWarningMsg(node, "truncation from int to char");
                    return OK;
                }else{
                    return TranslateFailed;
                }
            }
            return OK;
        }

        int code_gen_BiExp(const BiExp *node, std::string &buffer, std::string &expType) {
            bool check = true;
            std::string lhsType;
            std::string rhsType;
            buffer += "(";
            check &= code_gen_exp(node->lhs, buffer, lhsType);
            std::string markerStr;
            check &= marker2str(node->marker->marker_type, markerStr);
            buffer += " " + markerStr + " ";
            check &= code_gen_exp(node->rhs, buffer, rhsType);
            //buffer += ";\n";
            if (check) {
                check &= type_check(lhsType, rhsType, node);
                if (check) {
                    expType = lhsType;
                }
                else {
                    addErrMsg(node, "left type does not match right type");
                    assert(false);
                }
            }
            buffer += ")";
            return check;
        }

        int code_gen_ExpCall(const ExpCall *node, std::string &buffer, std::string &expType) {
            auto iter = this->functionBuff.find(node->fn->content);
            if (iter == this->functionBuff.end()) {
                addErrMsg(node, "no func or proc found in functionBuff");
                assert(false); //未找到函数
                return TranslateFailed;
            }

            bool check = true;
            const struct FuncInfo callInfo = iter->second;
            buffer += node->fn->content;
            buffer += "(";
            if(node->params != nullptr) {
                for (int i = 0; i < node->params->explist.size(); i++) {
                    auto x = node->params->explist[i];
                    check &= code_gen_exp(x, buffer, expType);
                    if (!type_check(expType, callInfo.paraType[i], node)) {
                        check = false;
                        addErrMsg(node, "type of parameter passed in does not match the formal parameter");
                        return TranslateFailed;
                    }
                    buffer += ", ";
                }
            }
            expType = callInfo.returnType;
            std::string otherPara = callInfo.additionPara;
            //otherPara.pop_back();
            //otherPara.pop_back();
            buffer += otherPara;
            buffer.pop_back();
            buffer.pop_back();
            buffer += ")";
            return check;
        }

        int code_gen_Variable(const Variable *node, std::string &buffer, std::string &expType) {
            bool varFind = false;

            struct SymbolTable *theTable = this->nowST_pointer;
            auto iterTable = theTable->content.find(node->id->content);
            if (iterTable != theTable->content.end()) {
                expType = iterTable->second.typeDecl;
                varFind = true;
            }
            else {
                theTable = theTable->prev;
                while (theTable != NULL) { //在当前符号表找不到变量。向上层符号表寻找。
                    iterTable = theTable->content.find(node->id->content);
                    if (iterTable != theTable->content.end()) {
                        varFind = true;
                        //对在上层符号表找到的变量，追加函数调用参数。
                        std::string funcName = this->nowST_pointer->tableName; //符号表名称即当前函数名称
                        auto iterFunc = this->functionBuff.find(funcName);
                        if (iterFunc == this->functionBuff.end()) {
                            //没找到函数定义
                            addErrMsg(node, "func or proc not found in functionBuff");
                            assert(false);
                            return TranslateFailed;
                        }
                        expType = iterTable->second.typeDecl;
                        if(iterTable->second.arrayInfo == nullptr) {
                            iterFunc->second.formalPara += fmt::format(
                                    "{0} &{1}, ", iterTable->second.typeDecl, iterTable->first);
                        }else{
                            iterFunc->second.formalPara += fmt::format(
                                    "{0} {1}, ", iterTable->second.typeDecl, iterTable->first);

                        }
                        iterFunc->second.additionPara += fmt::format("{0}, ", iterTable->first);
                        iterFunc->second.paraType.push_back(iterTable->second.typeDecl);
                        //在函数形参表添加完变量之后，在当前符号表内加上该变量的定义。
                        this->nowST_pointer->content.insert(
                                std::pair<std::string, struct SymbolEntry>(iterTable->first, iterTable->second));
                        break;
                    }
                    theTable = theTable->prev;
                }
            }

            bool check = true;
            if (varFind) {
                buffer += fmt::format("{0}", node->id->content);

                if(expType.find("*") != std::string::npos) {
                    std::string periodType;
                    if (iterTable->second.arrayInfo->periods.size() != node->id_var->explist.size()){
                        assert(false); // 定义数组维数与下标不符
                        return TranslateFailed;
                    }

                    /*
                    auto *arraySubInt = new ConstantInteger(0);
                    auto *arraySubIntExp = new ExpConstantInteger(arraySubInt);
                    auto *subMarker = new Marker(MarkerType::Sub);
                    auto *tempExp = new BiExp(nullptr,
                                              subMarker, nullptr);
                    */

                    for(int i=0; i<node->id_var->explist.size(); i++){
                        expType.pop_back(); // int* --> int
                        buffer += "[";
                        /*
                        arraySubInt->attr = iterTable->second.arrayInfo->periods[i].first;
                        arraySubIntExp->value = arraySubInt;
                        tempExp->lhs = node->id_var->explist.at(i);
                        tempExp->rhs = arraySubIntExp;
                         */
                        check &= code_gen_exp(node->id_var->explist.at(i), buffer, periodType);
                        if(periodType != "int"){
                            addErrMsg(node, "array range must be int");
                            check = false;
                            assert(false);
                        }
                        buffer += " - ";
                        buffer += std::to_string(iterTable->second.arrayInfo->periods[i].first);
                        buffer += "]";
                        //delete tempExp; // delete tempExp会删除lhs和rhs
                        //delete subMarker;
                    }
                }
            } else {
                addErrMsg(node, "var not found in current symbol table and its parent");
                check = false;
            }
            return check;
        }

        int code_gen_ExpAssign(const ExpAssign *node, std::string &buffer, std::string &expType) {
            //类型检查
            bool check = true;
            std::string lhsType;
            std::string rhsType;
            if(node->lhs->type == Type::Variable || node->lhs->type == Type::Ident){
                //处理函数返回值的问题
                std::string varName;
                if(node->lhs->type == Type::Variable) {
                    varName = reinterpret_cast<const Variable *>(node->lhs)->id->content;
                }else{
                    varName = reinterpret_cast<const Ident *>(node->lhs)->ident->content;
                }
                if(varName == this->nowST_pointer->tableName){
                    buffer += "return ";
                    code_gen_exp(node->rhs, buffer, rhsType);
                    //buffer += ";\n";
                    auto funcIter = this->functionBuff.find(this->nowST_pointer->tableName);
                    if(funcIter->second.returnType != rhsType){
                        //函数返回值类型不符
                        addErrMsg(node, "type of return value does not match func");
                        assert(false);
                        return TranslateFailed;
                    }
                    expType = rhsType;
                    return OK;
                }
            }
            // 处理正常的表达式赋值
            check &= code_gen_exp(node->lhs, buffer, lhsType);
            buffer += " " + std::string("=") + " ";
            check &= code_gen_exp(node->rhs, buffer, rhsType);
            //buffer += ";\n";
            if (check) {
                if (lhsType == rhsType) {
                    expType = lhsType;
                }
                else {
                    addErrMsg(node, "left type does not match right type in assign");
                    check = false;
                    assert(false);
                }
            }
            return check;
        }

        int code_gen_UnExp(const UnExp *node, std::string &buffer, std::string &expType) {
            bool check = true;
            std::string markerStr;
            check &= marker2str(node->marker->marker_type, markerStr);
            buffer += markerStr + " ";
            check &= code_gen_exp(node->lhs, buffer, expType);
            return check;
        }

        int typeStr2ioStr(const std::string typeStr, std::string &result) {
            if(typeStr == "int"){
                result = "%d";
            }else if(typeStr == "char*"){
                result = "%s";
            }else if(typeStr == "double"){
                result = "%lf";
            }else if(typeStr == "char"){
                result = "%c";
            }else{
                assert(false);
                return TranslateFailed;
            }
            return OK;
        }

        int code_gen_Read(const Read *node, std::string &buffer) {
            buffer += "scanf(\"";
            std::string readBuffer;
            for (auto const x: node->var_list->params) {
                std::string io_type;
                std::string var_type;
                std::string tempVariableBuffer = "";
                code_gen_exp(x, tempVariableBuffer, var_type);
                if (typeStr2ioStr(var_type, io_type)) {
                    buffer += io_type;
                    readBuffer += ", ";
                    if (io_type != "%s") {
                        readBuffer += "&";
                    }
                    readBuffer += tempVariableBuffer;
                }
                else {
                    addErrMsg(node, "no var type match");
                    assert(false);
                    return TranslateFailed;
                }
            }
            buffer += "\"";
            buffer += readBuffer;
            buffer += ")";
            return OK;
        }

        int code_gen_Write(const Write *node, std::string &buffer) {
            buffer += "printf(\"";
            std::string writeBuffer = "";
            bool check = true;
            for (auto x: node->exp_list->explist) {
                writeBuffer += ", ";
                std::string expType, ioType;
                check &= code_gen_exp(x, writeBuffer, expType);
                if (typeStr2ioStr(expType, ioType)) {
                    buffer += ioType;
                }
                else {
                    addErrMsg(node, "no var type match");
                    assert(false);
                    return TranslateFailed;
                }
            }
            buffer += "\"";
            buffer += writeBuffer;
            buffer += ")";
            return check;
        }

        int code_gen_IfElseStatement(const IfElseStatement *node, std::string &buffer) {
            bool check = true;
            std::string ifType;
            printTab(buffer);
            buffer += "if (";
            check &= code_gen_exp(node->expression, buffer, ifType);
            buffer += ") {\n";

            this->tabNum += 1;
            if (node->if_part->type != Type::CompoundStatement)
                printTab(buffer);
            check &= code_gen_Statement(node->if_part, buffer);
            if (node->if_part->type != Type::CompoundStatement)
                buffer += ";\n";
            this->tabNum -= 1;
            printTab(buffer);
            buffer += "}\n";

            if (node->else_part != nullptr) {
                printTab(buffer);
                buffer += "else {\n";
                this->tabNum += 1;
                if (node->else_part->type != Type::CompoundStatement)
                    printTab(buffer);
                code_gen_Statement(node->else_part, buffer);
                if (node->else_part->type != Type::CompoundStatement)
                    buffer += ";\n";
                this->tabNum -= 1;
                printTab(buffer);
                buffer += "}\n";
            }
            return check;
        }

        int code_gen_ForStatement(const ForStatement *node, std::string &buffer) {
            bool check = true;
            printTab(buffer);
            buffer += fmt::format("for (int {} = ", node->id->content);
            std::string expType;
            //将for循环变量i加入符号表。
            SymbolEntry se;
            se.typeDecl = "int";
            se.varType = ISBASIC;
            this->nowST_pointer->content.insert(std::pair<std::string, SymbolEntry>(node->id->content, se));
            check &= code_gen_exp(node->express1, buffer, expType);
            buffer += "; ";
            if (expType != "int") {
                addErrMsg(node, "initial value must be int");
                check = false;
                assert(false);
            }
            buffer += fmt::format("{} <= ", node->id->content);
            check &= code_gen_exp(node->express2, buffer, expType);
            buffer += "; ";
            if (expType != "int") {
                addErrMsg(node, "final value must be int");
                check = false;
                assert(false);
            }
            buffer += fmt::format("{}++", node->id->content);
            buffer += ") {\n";
            this->tabNum += 1;
            if (node->for_stmt->type != Type::CompoundStatement)
                printTab(buffer);
            check &= code_gen_Statement(node->for_stmt, buffer);
            if (node->for_stmt->type != Type::CompoundStatement &&
            node->for_stmt->type != Type::ForStatement && node->for_stmt->type != Type::IfElseStatement)
                buffer += ";\n";
            this->tabNum -= 1;
            printTab(buffer);
            buffer += "}\n";
            this->nowST_pointer->content.erase(node->id->content);
            return check;
        }

        int code_gen_ExpConstantBoolean(const ExpConstantBoolean *node, std::string &buffer, std::string &expType) {
            buffer += std::to_string(node->value->attr);
            return constType2str(node, expType);
        }

        int code_gen_Char_helper(const char target, std::string &buffer){
            std::string tempString;
            if (target < 32) {
                tempString = escapeTable[target];
            }else if(target > 32){
                tempString = std::string(1, target);
            }else{
                tempString = " ";
            }
            buffer += tempString;
            return OK;
        }

        int code_gen_String_helper(std::string target, std::string &buffer){
            for(int i=0; i<target.size(); i++){
                code_gen_Char_helper(target[i], buffer);
            }
            return OK;
        }

        int code_gen_ExpConstantChar(const ExpConstantChar *node, std::string &buffer, std::string &expType) {
            buffer += "'";
            code_gen_Char_helper(node->value->attr, buffer);
            buffer += "'";
            expType = "char";
            return OK;
        }

        int code_gen_ExpConstantReal(const ExpConstantReal *node, std::string &buffer, std::string &expType) {
            buffer += node->value->content;
            return constType2str(node, expType);
        }

        int code_gen_ExpConstantInteger(const ExpConstantInteger *node, std::string &buffer, std::string &expType) {
            buffer += std::to_string(node->value->attr);
            return constType2str(node, expType);
        }

        int code_gen_ExpConstantString(const ExpConstantString *node, std::string &buffer, std::string &expType) {
            std::string tempStr = node->value->attr;
            buffer += "\"";
            code_gen_String_helper(tempStr, buffer);
            buffer += "\"";
            expType = "char*";
        }
    };
}

#endif //PASCAL_S_TARGET_C_H

