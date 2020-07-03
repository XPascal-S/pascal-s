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
#include <pascal-s/token.h>


namespace target_c {

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
        const struct ast::ArrayTypeSpec *arrayInfo; // 数组信息.
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
        std::vector<std::string> errMsg; //错误信息
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

        int code_gen(const ast::Node *node) {
            if (node->type != ast::Type::Program) {
                assert(false);
                throw std::runtime_error("node type is not program");
                return TranslateFailed;
            }
            int code = code_gen_node(node);
            if (code == TranslateFailed) {
                for (auto msg: errMsg) {
                    outputBuff.writeln(msg);
                }
                return TranslateFailed;
            }

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

        int constType2str(const ast::Node *node, std::string &result) {
            switch (node->type) {
                case ast::Type::ExpConstantInteger:
                    result = "int";
                    return 1;
                case ast::Type::ExpConstantChar:
                    result = "char";
                    return 1;
                case ast::Type::ExpConstantBoolean:
                    result = "int";
                    return 1;
                case ast::Type::ExpConstantReal:
                    result = "double";
                    return 1;
                case ast::Type::ExpConstantString:
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
                default:
                    //assert(false);
                    throw std::runtime_error("semantic error: no marker type match");
                    return TranslateFailed;
            }
        }

        void addErrMsg(const ast::Node *node, const std::string msg) {
            this->errMsg.push_back(fmt::format("{}:{}: semantic error: {}", node->line, node->column + 1, msg));
        }

        void printTab(std::string &buffer) {
            for (int i = 0; i < this->tabNum; i++)
                buffer += '\t';
        }

        int code_gen_node(const ast::Node *node) {
            if(node == NULL)
                return OK;
            switch (node->type) {
                default:
                    addErrMsg(node, "no node type match");
                    assert(false);
                    return TranslateFailed;
                case ast::Type::Unknown:
                    addErrMsg(node, "unknown node type");
                    assert(false);
                    return TranslateFailed;
                case ast::Type::Program:
                    return code_gen_program(
                            reinterpret_cast<const ast::Program *>(node));
                case ast::Type::ProgramHead:
                    return code_gen_programHead(
                            reinterpret_cast<const ast::ProgramHead *>(node));
                case ast::Type::ProgramBody:
                    return code_gen_programBody(
                            reinterpret_cast<const ast::ProgramBody *>(node));
                case ast::Type::SubprogramDecls:
                    return code_gen_SubprogramDecls(
                            reinterpret_cast<const ast::SubprogramDecls *>(node));
                case ast::Type::Subprogram:
                    return code_gen_Subprogram(
                            reinterpret_cast<const ast::Subprogram *>(node));
                case ast::Type::SubprogramHead:
                    return code_gen_SubprogramHead(
                            reinterpret_cast<const ast::SubprogramHead *>(node));
                case ast::Type::SubprogramBody:
                    return code_gen_SubprogramBody(
                            reinterpret_cast<const ast::SubprogramBody *>(node));
            }
        }

        int code_gen_programHead(const ast::ProgramHead *node) {
            // Currently there is no corresponding relation
            // from pascal head to C head
            return OK;
        }

        int code_gen_programBody(const ast::ProgramBody *node) {
            bool check = true;
            check &= code_gen_ConstDecls(node->constdecls, this->mainBuff);
            check &= code_gen_VarDecls(node->vardecls, this->mainBuff);
            check &= code_gen_node(node->subprogram); //SubprogramDecls
            check &= code_gen_CompoundStatement(node->compound, this->mainBuff); //CompoundStatement
            return check;
        }

        int code_gen_program(const ast::Program *node) {
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

        int code_gen_ConstDecls(const ast::ConstDecls *node, std::string &buffer) {
            if (node == NULL)
                return OK;
            bool check = true;
            for (auto x : node->decls) {
                check &= code_gen_ConstDecl(x, buffer);
            }
            return check;
        }

        int code_gen_ConstDecl(const ast::ConstDecl *node, std::string &buffer) {
            std::string lhs = node->ident->content;
            struct SymbolEntry se;
            se.varType = ISCONSTANT;
            //se.newName = lhs + "_" + this->nowST_pointer->tableName;
            switch (node->rhs->type) {
                case ast::Type::ExpConstantInteger:
                    se.typeDecl = "int";
                    se.value = std::to_string(reinterpret_cast<const ast::ExpConstantInteger *>(node->rhs)->value->attr);
                    break;
                case ast::Type::ExpConstantString:
                    se.typeDecl = "char*";
                    se.value = reinterpret_cast<const ast::ExpConstantString *>(node->rhs)->value->attr;
                    break;
                case ast::Type::ExpConstantReal:
                    se.typeDecl = "double";
                    se.value = std::to_string(reinterpret_cast<const ast::ExpConstantReal *>(node->rhs)->value->attr);
                    break;
                case ast::Type::ExpConstantChar:
                    se.typeDecl = "char";
                    se.value = ("'" + std::string(1, reinterpret_cast<const ast::ExpConstantChar *>(node->rhs)->value->attr) +
                                "'");
                    break;
                case ast::Type::ExpConstantBoolean:
                    se.typeDecl = "int";
                    se.value = std::to_string(reinterpret_cast<const ast::ExpConstantBoolean *>(node->rhs)->value->attr);
                    break;
                default:
                    assert(false);
                    addErrMsg(node, "no constant type match");
                    return TranslateFailed;
            }

            if(se.typeDecl == "char*"){
                auto *arrayType = new ast::ArrayTypeSpec(new Keyword(KeywordType::Char));
                arrayType->periods.push_back(std::pair<int, int>(0, se.value.size()));
                se.arrayInfo = arrayType;
            }
            this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(lhs, se));
            printTab(buffer);
            buffer += fmt::format("const {0} {1} = {2};\n", se.typeDecl, lhs, se.value);
            return OK;
        }

        int code_gen_VarDecls(const ast::VarDecls *node, std::string &buffer) {
            if(node == NULL)
                return OK;
            bool check = true;
            for (auto x : node->decls) {
                check &= code_gen_VarDecl(x, buffer);
            }
            return check;
        }

        int code_gen_VarDecl(const ast::VarDecl *node, std::string &buffer) {
            for (auto x : node->idents->idents) {
                std::string name = x->content;
                struct SymbolEntry se;
                //se.newName = name + "_" + this->nowST_pointer->tableName;
                if (node->type_spec->type == ast::Type::BasicTypeSpec) {
                    keyword2str(reinterpret_cast<const ast::BasicTypeSpec *>(node->type_spec)->keyword->key_type, se.typeDecl);
                    se.varType = ISBASIC;
                    printTab(buffer);
                    buffer += fmt::format("{0} {1};\n", se.typeDecl, name);
                } else if (node->type_spec->type == ast::Type::ArrayTypeSpec) {
                    se.arrayInfo = reinterpret_cast<const ast::ArrayTypeSpec *>(node->type_spec);
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

        int code_gen_SubprogramDecls(const ast::SubprogramDecls *node) {
            bool check = true;
            for (auto x : node->subprogram) {
                check &= code_gen_node(x);
            }
            return check;
        }

        int code_gen_Subprogram(const ast::Subprogram *node) {
            //符号表的初始化，在subprogram_head中完成
            bool check = true;
            check &= code_gen_node(node->subhead);
            check &= code_gen_node(node->subbody);
            this->nowST_pointer = this->nowST_pointer->prev; // 回到上层符号表，subprogram生成完毕
            return check;
        }

        int code_gen_SubprogramHead(const ast::SubprogramHead *node) {
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
            check &= keyword2str(node->ret_type->keyword->key_type, functionInfo.returnType);
            for (const auto param : node->decls->params){
                for(const auto id : param->id_list->idents){
                    struct SymbolEntry se;
                    if (param->spec->type == ast::Type::BasicTypeSpec) {
                        check &= keyword2str(reinterpret_cast<const ast::BasicTypeSpec *>(param->spec)->keyword->key_type, se.typeDecl);
                        functionInfo.paraType.push_back(se.typeDecl);
                        se.varType = ISBASIC;
                    } else if (param->spec->type == ast::Type::ArrayTypeSpec) {
                        check &= keyword2str(reinterpret_cast<const ast::ArrayTypeSpec *>(param->spec)->keyword->key_type, se.typeDecl);
                        for(int i=0; i<reinterpret_cast<const ast::ArrayTypeSpec *>(param->spec)->periods.size(); i++){
                            se.typeDecl += "*"; //数组类型
                        }
                        functionInfo.paraType.push_back(se.typeDecl);
                        se.varType = ISARRAY;
                        se.arrayInfo = reinterpret_cast<const ast::ArrayTypeSpec *>(param->spec);
                    } else {
                        addErrMsg(node, "no var type match");
                        assert(false);
                        return TranslateFailed;
                    }

                    st_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(id->content, se));
                    functionInfo.formalPara += se.typeDecl + " " + id->content + ", ";
                }
            }
            this->functionBuff.insert(std::pair<std::string, struct FuncInfo>(funcName, functionInfo));
            this->nowST_pointer->nextTable.insert(
                    std::pair<std::string, struct SymbolTable *>(funcName, st_pointer));
            this->nowST_pointer = st_pointer;
            //check &= code_gen_node(node->func);
            return check;
        }

        /*
        int code_gen_headerDecl_helper(const std::vector<VarDecl *> &decls, struct FuncInfo &nowFuncInfo) {
            bool check = true;
            for (const auto x : decls) {
                //本来函数形参表的node表示，应该是文法里的formal_parameter
                //但是实际ast实现里，形参还是用varDecls表示的
                //形参的varDecls，和变量定义的varDecls需要区分开来。
                //故这里不调用code_gen_node
                for (const auto y : x->idents->idents) {
                    struct SymbolEntry se;
                    if (x->type_spec->type == Type::BasicTypeSpec) {
                        check &= keyword2str(reinterpret_cast<const BasicTypeSpec *>(x->type_spec)->keyword->key_type, se.typeDecl);
                        nowFuncInfo.paraType.push_back(se.typeDecl);
                        se.varType = ISBASIC;
                    } else if (x->type_spec->type == Type::ArrayTypeSpec) {
                        check &= keyword2str(reinterpret_cast<const ArrayTypeSpec *>(x->type_spec)->keyword->key_type, se.typeDecl);
                        for(int i=0; i<reinterpret_cast<const ArrayTypeSpec *>(x)->periods.size(); i++){
                            se.typeDecl += "*"; //数组类型
                        }
                        nowFuncInfo.paraType.push_back(se.typeDecl);
                        se.varType = ISARRAY;
                        se.arrayInfo = reinterpret_cast<const ArrayTypeSpec *>(x->type_spec);
                    } else {
                        assert(false);
                        throw std::runtime_error("semantic error: no var type match");
                        return TranslateFailed;
                    }

                    this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(y->content, se));
                    nowFuncInfo.formalPara += se.typeDecl + " " + y->content + ", ";
                }
            }
            return check;
        };

        int code_gen_FunctionDecl(const FunctionDecl *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                assert(false); //未找到函数
                throw std::runtime_error("semantic error: func not found in functionBuff");
                return TranslateFailed;
            }
            bool check = true;
            struct FuncInfo &nowFuncInfo = iter->second;
            check &= keyword2str(node->basic->keyword->key_type, nowFuncInfo.returnType);
            check &= code_gen_headerDecl_helper(node->decls->decls, nowFuncInfo);
            return check;
        }

        int code_gen_Procedure(const Procedure *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                assert(false); //未找到函数
                throw std::runtime_error("semantic error: proc not found in functionBuff");
                return TranslateFailed;
            }
            bool check = true;
            struct FuncInfo &nowFuncInfo = iter->second;
            nowFuncInfo.returnType = "void";
            check &= code_gen_headerDecl_helper(node->decls->decls, nowFuncInfo);
            return check;
        }
         */

        int code_gen_SubprogramBody(const ast::SubprogramBody *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                addErrMsg(node, "func or proc not found in functionBuff");
                assert(false); //未找到函数
                return TranslateFailed;
            }
            bool check = true;
            struct FuncInfo &nowFuncInfo = iter->second;
            check &= code_gen_ConstDecls(node->constdecls, nowFuncInfo.funcBody);
            check &= code_gen_VarDecls(node->vardecls, nowFuncInfo.funcBody);
            check &= code_gen_CompoundStatement(node->compound, nowFuncInfo.funcBody);
            return check;
        }

        int code_gen_CompoundStatement(const ast::CompoundStatement *node, std::string &buffer) {
            bool check = true;
            for (auto x : node->state->statement) {
                if(x->type != ast::Type::IfElseStatement && x->type != ast::Type::ForStatement)
                    printTab(buffer);
                check &= code_gen_Statement(x, buffer);
                if(x->type != ast::Type::IfElseStatement && x->type != ast::Type::ForStatement)
                    buffer += ";\n";
            }
            return check;
        }

        int code_gen_exp(const ast::Exp *node, std::string &buffer, std::string &expType) {
            switch (node->type) {
                case ast::Type::BiExp:
                    return code_gen_BiExp(reinterpret_cast<const ast::BiExp *>(node), buffer, expType);
                case ast::Type::UnExp:
                    return code_gen_UnExp(reinterpret_cast<const ast::UnExp *>(node), buffer, expType);
                case ast::Type::Read:
                    return code_gen_Read(reinterpret_cast<const ast::Read *>(node), buffer);
                case ast::Type::Write:
                    return code_gen_Write(reinterpret_cast<const ast::Write *>(node), buffer);
                case ast::Type::ExpCall:
                    return code_gen_ExpCall(reinterpret_cast<const ast::ExpCall *>(node), buffer, expType);
                case ast::Type::ExpAssign:
                    return code_gen_ExpAssign(reinterpret_cast<const ast::ExpAssign *>(node), buffer, expType);
                case ast::Type::Variable:
                    return code_gen_Variable(reinterpret_cast<const ast::Variable *>(node), buffer, expType);
                case ast::Type::ExpConstantBoolean:
                    return code_gen_ExpConstantBoolean(reinterpret_cast<const ast::ExpConstantBoolean *>(node), buffer,
                                                       expType);
                case ast::Type::ExpConstantChar:
                    return code_gen_ExpConstantChar(reinterpret_cast<const ast::ExpConstantChar *>(node), buffer, expType);
                case ast::Type::ExpConstantReal:
                    return code_gen_ExpConstantReal(reinterpret_cast<const ast::ExpConstantReal *>(node), buffer, expType);
                case ast::Type::ExpConstantInteger:
                    return code_gen_ExpConstantInteger(reinterpret_cast<const ast::ExpConstantInteger *>(node), buffer,
                                                       expType);
                case ast::Type::ExpConstantString:
                    return code_gen_ExpConstantString(reinterpret_cast<const ast::ExpConstantString *>(node), buffer,
                                                      expType);
                default:
                    assert(false);
                    return TranslateFailed;
            }
            return OK;
        }

        int code_gen_Statement(const ast::Statement *node, std::string &buffer) {
            // 该函数负责statement的生成。
            std::string tempString;
            bool check = true;
            switch (node->type) {
                case ast::Type::ExecStatement:
                    check &= code_gen_exp(reinterpret_cast<const ast::ExecStatement *>(node)->exp, buffer, tempString);
                    return check;
                case ast::Type::IfElseStatement:
                    return code_gen_IfElseStatement(reinterpret_cast<const ast::IfElseStatement *>(node), buffer);
                case ast::Type::ForStatement:
                    return code_gen_ForStatement(reinterpret_cast<const ast::ForStatement *>(node), buffer);
                case ast::Type::CompoundStatement:
                    return code_gen_CompoundStatement(reinterpret_cast<const ast::CompoundStatement *>(node), buffer);
                default:
                    addErrMsg(node, "no statement type match");
                    assert(false);
                    return TranslateFailed;
            }
        }

        int code_gen_BiExp(const ast::BiExp *node, std::string &buffer, std::string &expType) {
            bool check = true;
            std::string lhsType;
            std::string rhsType;
            check &= code_gen_exp(node->lhs, buffer, lhsType);
            std::string markerStr;
            check &= marker2str(node->marker->marker_type, markerStr);
            buffer += " " + markerStr + " ";
            check &= code_gen_exp(node->rhs, buffer, rhsType);
            //buffer += ";\n";
            if (check) {
                if (lhsType == rhsType) {
                    expType = lhsType;
                }
                else {
                    check = false;
                    addErrMsg(node, "left type does not match right type");
                    assert(false);
                }
            }
            return check;
        }

        int code_gen_ExpCall(const ast::ExpCall *node, std::string &buffer, std::string &expType) {
            auto iter = this->functionBuff.find(node->fn->content);
            //TODO

            if (iter == this->functionBuff.end()) {
                addErrMsg(node, "no func or proc found in functionBuff");
                assert(false); //未找到函数
                return TranslateFailed;
            }

            bool check = true;
            const struct FuncInfo callInfo = iter->second;
            buffer += node->fn->content;
            buffer += "(";
            for (int i = 0; i < node->params->explist.size(); i++) {
                auto x = node->params->explist[i];
                check &= code_gen_exp(x, buffer, expType);
                if (expType != callInfo.paraType[i]) {
                    check = false;
                    addErrMsg(node, "type of parameter passed in does not match the formal parameter");
                    return TranslateFailed;
                }
                buffer += ", ";
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

        int code_gen_Variable(const ast::Variable *node, std::string &buffer, std::string &expType) {
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
                        if(expType.find("*") == std::string::npos) {
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
                    auto *arraySubInt = new ConstantInteger(0);
                    auto *arraySubIntExp = new ast::ExpConstantInteger(arraySubInt);
                    auto *subMarker = new Marker(MarkerType::Sub);
                    auto *tempExp = new ast::BiExp(nullptr,
                                              subMarker, nullptr);

                    for(int i=0; i<node->id_var->explist.size(); i++){
                        expType.pop_back(); // int* --> int
                        buffer += "[";
                        arraySubInt->attr = iterTable->second.arrayInfo->periods[i].first;
                        arraySubIntExp->value = arraySubInt;
                        tempExp->lhs = node->id_var->explist.at(i);
                        tempExp->rhs = arraySubIntExp;
                        check &= code_gen_exp(tempExp, buffer, periodType);
                        if(periodType != "int"){
                            addErrMsg(node, "array range must be int");
                            check = false;
                            assert(false);
                        }
                        buffer += "]";
                        delete tempExp; // delete tempExp会删除lhs和rhs
                        delete subMarker;
                    }
                }
            } else {
                addErrMsg(node, "var not found in current symbol table and its parent");
                check = false;
            }
            return check;
        }

        int code_gen_ExpAssign(const ast::ExpAssign *node, std::string &buffer, std::string &expType) {
            //类型检查
            bool check = true;
            std::string lhsType;
            std::string rhsType;
            if (node->lhs->type == ast::Type::Variable) {
                //处理函数返回值的问题
                std::string varName = reinterpret_cast<const ast::Variable *>(node->lhs)->id->content;
                if (varName == this->nowST_pointer->tableName) {
                    buffer += "return ";
                    code_gen_exp(node->rhs, buffer, rhsType);
                    //buffer += ";\n";
                    auto funcIter = this->functionBuff.find(this->nowST_pointer->tableName);
                    if (funcIter->second.returnType != rhsType) {
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
            code_gen_exp(node->lhs, buffer, lhsType);
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

        int code_gen_UnExp(const ast::UnExp *node, std::string &buffer, std::string &expType) {
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

        int code_gen_Read(const ast::Read *node, std::string &buffer) {
            buffer += "scanf(\"";
            std::string readBuffer;
            for (auto x: node->var_list->params) {
                auto var_type = this->nowST_pointer->content[x->id->content].typeDecl;
                std::string io_type;
                if (typeStr2ioStr(var_type, io_type)) {
                    buffer += io_type;
                    readBuffer += ", ";
                    if (io_type != "%s") {
                        readBuffer += "&";
                    }
                    readBuffer += x->id->content;
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

        int code_gen_Write(const ast::Write *node, std::string &buffer) {
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

        int code_gen_IfElseStatement(const ast::IfElseStatement *node, std::string &buffer) {
            bool check = true;
            std::string ifType;
            printTab(buffer);
            buffer += "if (";
            check &= code_gen_exp(node->expression, buffer, ifType);
            buffer += ") {\n";

            this->tabNum += 1;
            if (node->if_part->type != ast::Type::CompoundStatement)
                printTab(buffer);
            check &= code_gen_Statement(node->if_part, buffer);
            if (node->if_part->type != ast::Type::CompoundStatement)
                buffer += ";\n";
            this->tabNum -= 1;
            printTab(buffer);
            buffer += "}\n";

            if (node->else_part != nullptr) {
                printTab(buffer);
                buffer += "else {\n";
                this->tabNum += 1;
                if (node->else_part->type != ast::Type::CompoundStatement)
                    printTab(buffer);
                code_gen_Statement(node->else_part, buffer);
                if (node->else_part->type != ast::Type::CompoundStatement)
                    buffer += ";\n";
                this->tabNum -= 1;
                printTab(buffer);
                buffer += "}\n";
            }
            return check;
        }

        int code_gen_ForStatement(const ast::ForStatement *node, std::string &buffer) {
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
            if (node->type != ast::Type::CompoundStatement)
                printTab(buffer);
            check &= code_gen_Statement(node->for_stmt, buffer);
            if (node->type != ast::Type::CompoundStatement)
                buffer += ";\n";
            this->tabNum -= 1;
            printTab(buffer);
            buffer += "}\n";
            this->nowST_pointer->content.erase(node->id->content);
            return check;
        }

        int code_gen_ExpConstantBoolean(const ast::ExpConstantBoolean *node, std::string &buffer, std::string &expType) {
            buffer += std::to_string(node->value->attr);
            return constType2str(node, expType);
        }

        int code_gen_ExpConstantChar(const ast::ExpConstantChar *node, std::string &buffer, std::string &expType) {
            buffer += "'";
            buffer += node->value->attr;
            buffer += "'";
            return constType2str(node, expType);
        }

        int code_gen_ExpConstantReal(const ast::ExpConstantReal *node, std::string &buffer, std::string &expType) {
            buffer += node->value->content;
            return constType2str(node, expType);
        }

        int code_gen_ExpConstantInteger(const ast::ExpConstantInteger *node, std::string &buffer, std::string &expType) {
            buffer += std::to_string(node->value->attr);
            return constType2str(node, expType);
        }

        int code_gen_ExpConstantString(const ast::ExpConstantString *node, std::string &buffer, std::string &expType) {
            buffer += "\"";
            buffer += node->value->attr;
            buffer += "\"";
            return constType2str(node, expType);
        }
    };
}
#endif //PASCAL_S_TARGET_C_H
