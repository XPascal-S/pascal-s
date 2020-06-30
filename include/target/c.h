//
// Created by kamiyoru on 2020/5/12.
//

#ifndef PASCAL_S_TARGET_C_H
#define PASCAL_S_TARGET_C_H

#define ISCONSTANT 1
#define ISBASIC 2
#define ISARRAY 3

#include <pascal-s/AST.h>
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
            os << s << '\n';
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
            OK,
            TranslateFailed,
        };

        std::vector<std::string> include_files;
        Buffer &outputBuff; //输出buffer
        std::map<std::string, struct FuncInfo> functionBuff; //函数定义字符串
        std::string mainBuff; // 主函数字符串
        std::vector<std::string> callRecordBuff; //记录函数调用顺序，用于debug
        struct SymbolTable *startST_pointer; //符号表入口指针
        struct SymbolTable *nowST_pointer; //当前符号表指针

        CBuilder(std::vector<std::string> &include_files,
                 Buffer &buf) : include_files(std::move(include_files)), outputBuff(outputBuff) {
            this->startST_pointer = new SymbolTable;
            this->nowST_pointer = this->startST_pointer;
            this->nowST_pointer->prev = NULL;
            this->nowST_pointer->tableName = "main";
        }

        ~CBuilder() {
            std::deque<struct SymbolTable *> st_deque;
            st_deque.push_back(this->startST_pointer);
            while (!st_deque.empty()) {
                struct SymbolTable *now_pointer = st_deque.front();
                for (auto x : now_pointer->nextTable) {
                    st_deque.push_back(x.second);
                }
                delete now_pointer;
            }
        }

        int code_gen(const Node *node) {
            for (const auto &f : include_files) {
                outputBuff.writeln(fmt::format("#include <{}>", f));
            }

            if (node->type != Type::Program) {
                assert(false);
                return TranslateFailed;
            }

            int code = code_gen_node(node);

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
                x.second.formalPara.pop_back();
                x.second.formalPara.pop_back();
                this->outputBuff.writeln(
                        x.second.returnType + " " + x.second.funcName + "("
                        + x.second.formalPara + "){\n"
                );
                this->outputBuff.write(x.second.funcBody);
                this->outputBuff.write("}");
            }

            //输出主函数内容
            outputBuff
                    .writeln("int main(){")
                    .writeln(fmt::format("{}", this->mainBuff))
                    .writeln("return 0;")
                    .writeln("}");
            return code;
        }

        int keyword2str(const KeywordType kt, std::string &result) {
            switch (kt) {
                case KeywordType::Boolean:
                    result = "bool";
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
                default:
                    assert(false);
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
                default:
                    assert(false);
                    return TranslateFailed;
            }
        }

        int code_gen_node(const Node *node) {
            switch (node->type) {
                default:
                    assert(false);
                    return TranslateFailed;
                case Type::Unknown:
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
                case Type::FunctionDecl:
                    return code_gen_FunctionDecl(
                            reinterpret_cast<const FunctionDecl *>(node));
                case Type::Procedure:
                    return code_gen_Procedure(
                            reinterpret_cast<const Procedure *>(node));
                case Type::SubprogramBody:
                    return code_gen_SubprogramBody(
                            reinterpret_cast<const SubprogramBody *>(node));
//                case Type::Procedure:
//                    return code_gen_procedure(
//                            reinterpret_cast<const Procedure *>(node));
//                case Type::Function:
//                    return code_gen_function(
//                            reinterpret_cast<const Function *>(node));
//                case Type::StatementBlock:
//                    return code_gen_statement_block(
//                            reinterpret_cast<const StatementBlock *>(node));
//                case Type::ExpCall:
//                    return code_gen_exp_call(
//                            reinterpret_cast<const ExpCall *>(node));
//                case Type::ExecStatement:
//                    return code_gen_exec_statement(
//                            reinterpret_cast<const ExecStatement *>(node));
//                case Type::IfElseStatement:
//                    return code_gen_if_else_statement(
//                            reinterpret_cast<const IfElseStatement *>(node));
//                case Type::ForStatement:
//                    return code_gen_for_statement(
//                            reinterpret_cast<const ForStatement *>(node));
//                case Type::ExpConstantInteger:
//                    return code_gen_exp_constant_integer(
//                            reinterpret_cast<const ExpConstantInteger *>(node));
//                case Type::ExpConstantChar:
//                    return code_gen_exp_constant_char(
//                            reinterpret_cast<const ExpConstantChar *>(node));
//                case Type::ExpConstantBoolean:
//                    return code_gen_exp_constant_boolean(
//                            reinterpret_cast<const ExpConstantBoolean *>(node));
//                case Type::ExpConstantString:
//                    return code_gen_exp_constant_string(
//                            reinterpret_cast<const ExpConstantString *>(node));
//                case Type::ExpConstantReal:
//                    return code_gen_exp_constant_real(
//                            reinterpret_cast<const ExpConstantReal *>(node));
//                case Type::Ident:
//                    return code_gen_ident(
//                            reinterpret_cast<const Ident *>(node));
//            case Type::ParamList:
//                return code_gen_param_list(
//                        reinterpret_cast<const ParamList *>(node));
//            case Type::VariableList:
//                return code_gen_variable_list(
//                        reinterpret_cast<const VariableList *>(node));
//            case Type::IdentList:
//                return code_gen_ident_list(
//                        reinterpret_cast<const IdentList *>(node));
//                case Type::ConstDecl:
//                    return code_gen_const_decl(
//                            reinterpret_cast<const ConstDecl *>(node));
//            case Type::ConstDecls:
//                return code_gen_const_decls(
//                        reinterpret_cast<const ConstDecls *>(node));
//            case Type::VarDecl:
//                return code_gen_var_decl(
//                        reinterpret_cast<const VarDecl *>(node));
//            case Type::VarDecls:
//                return code_gen_var_decls(
//                        reinterpret_cast<const VarDecls *>(node));
//            case Type::FunctionDecls:
//                return code_gen_function_decls(
//                        reinterpret_cast<const FunctionDecls *>(node));
//                case Type::ExpAssign:
//                    return code_gen_exp_assign(
//                            reinterpret_cast<const ExpAssign *>(node));
//                case Type::UnExp:
//                    return code_gen_unary_exp(
//                            reinterpret_cast<const UnExp *>(node));
//                case Type::BiExp:
//                    return code_gen_binary_exp(
//                            reinterpret_cast<const BiExp *>(node));
//            case Type::BasicTypeSpec:
//                return code_gen_BasicTypeSpec(
//                        reinterpret_cast<const BasicTypeSpec*>(node))
//                case Type::ArrayTypeSpec:
//                    return code_gen_ArrayTypeSpec(
//                            reinterpret_cast<const ArrayTypeSpec *>(node));
            }
        }

        int code_gen_programHead(const ProgramHead *node) {
            // Currently there has no corresponding relation
            // from pascal head to C head
            return OK;
        }

        int code_gen_programBody(const ProgramBody *node) {
            code_gen_ConstDecls(node->constdecls, this->mainBuff);
            code_gen_VarDecls(node->vardecls, this->mainBuff);
            code_gen_node(node->subprogram); //SubprogramDecls
            code_gen_CompoundStatement(node->compound, this->mainBuff); //CompoundStatement
        }

        int code_gen_program(const Program *node) {
            // in fmt::format {{ = {, }} = }
            //
            code_gen_node(node->programHead);
            code_gen_node(node->programBody);
            //buf.writeln(fmt::format("int {}(){{", node->name->content));
            //buf.writeln("printf(\"hello world\");");
            //buf.writeln("}");
            return OK;
        }

        int code_gen_ConstDecls(const ConstDecls *node, std::string &buffer) {
            for (auto x : node->decls) {
                code_gen_ConstDecl(x, buffer);
            }
            return OK;
        }

        int code_gen_ConstDecl(const ConstDecl *node, std::string &buffer) {
            std::string lhs = node->ident->content;
            struct SymbolEntry se;
            se.varType = ISCONSTANT;
            //se.newName = lhs + "_" + this->nowST_pointer->tableName;
            switch (node->rhs->type) {
                case Type::ExpConstantInteger:
                    se.typeDecl = "int";
                    se.value = std::to_string(reinterpret_cast<const ExpConstantInteger *>(node)->value->attr);
                    break;
                case Type::ExpConstantString:
                    se.typeDecl = "char*";
                    se.value = std::string(reinterpret_cast<const ExpConstantString *>(node)->value->attr);
                    break;
                case Type::ExpConstantReal:
                    se.typeDecl = "double";
                    se.value = std::to_string(reinterpret_cast<const ExpConstantReal *>(node)->value->attr);
                    break;
                case Type::ExpConstantChar:
                    se.typeDecl = "char";
                    se.value = ("'" + std::string(1, reinterpret_cast<const ExpConstantChar *>(node)->value->attr) +
                                "'");
                    break;
                case Type::ExpConstantBoolean:
                    se.typeDecl = "bool";
                    se.value = std::to_string(reinterpret_cast<const ExpConstantBoolean *>(node)->value->attr);
                    break;
                default:
                    assert(false);
                    return TranslateFailed;
            }
            this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(lhs, se));
            buffer += fmt::format("const {0} {1} = {2};\n", se.typeDecl, lhs, se.value);
            return OK;
        }

        int code_gen_VarDecls(const VarDecls *node, std::string &buffer) {
            for (auto x : node->decls) {
                code_gen_VarDecl(x, buffer);
            }
            return OK;
        }

        int code_gen_VarDecl(const VarDecl *node, std::string &buffer) {
            for (auto x : node->idents->idents) {
                std::string name = x->content;
                struct SymbolEntry se;
                //se.newName = name + "_" + this->nowST_pointer->tableName;
                if (node->type_spec->type == Type::BasicTypeSpec) {
                    keyword2str(reinterpret_cast<const BasicTypeSpec *>(node)->keyword->key_type, se.typeDecl);
                    se.varType = ISBASIC;
                    buffer += fmt::format("{0} {1};\n", se.typeDecl, name);
                } else if (node->type_spec->type == Type::ArrayTypeSpec) {
                    se.arrayInfo = reinterpret_cast<const ArrayTypeSpec *>(node);
                    se.varType = ISARRAY;
                    keyword2str(se.arrayInfo->keyword->key_type, se.typeDecl);
                    for(int i=0; i<se.arrayInfo->periods.size(); i++){
                        se.typeDecl += "*"; //数组类型 example：char**
                    }
                    buffer += fmt::format("{0} {1}", se.typeDecl, name);
                    for (auto x : se.arrayInfo->periods) {
                        buffer += "[" + std::to_string(x.second) + "]";
                    }
                    buffer += ";\n";
                } else {
                    assert(false);
                    return TranslateFailed;
                }
                this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(name, se));
            }
            return OK;
        }

        int code_gen_SubprogramDecls(const SubprogramDecls *node) {
            for (auto x : node->subprogram) {
                code_gen_node(x);
            }
            return OK;
        }

        int code_gen_Subprogram(const Subprogram *node) {
            //符号表的初始化，在subprogram_head中完成
            code_gen_node(node->subhead);
            code_gen_node(node->subbody);
            this->nowST_pointer = this->nowST_pointer->prev; // 回到上层符号表，subprogram生成完毕
            return OK;
        }

        int code_gen_SubprogramHead(const SubprogramHead *node) {
            struct SymbolTable *st_pointer = new struct SymbolTable;
            st_pointer->prev = this->nowST_pointer;
            struct FuncInfo functionInfo;
            functionInfo.funcBody = "";
            functionInfo.formalPara = "";
            functionInfo.additionPara = "";
            if (node->func != NULL) {
                std::string funcName = node->func->name->content;
                st_pointer->tableName = funcName;
                functionInfo.funcName = funcName;
                this->functionBuff.insert(std::pair<std::string, struct FuncInfo>(funcName, functionInfo));
                this->nowST_pointer->nextTable.insert(
                        std::pair<std::string, struct SymbolTable *>(funcName, st_pointer));
                this->nowST_pointer = st_pointer;
                code_gen_node(node->func);
            } else if (node->proc != NULL) {
                std::string procName = node->proc->name->content;
                st_pointer->tableName = procName;
                functionInfo.funcName = procName;
                this->functionBuff.insert(std::pair<std::string, struct FuncInfo>(procName, functionInfo));
                this->nowST_pointer->nextTable.insert(
                        std::pair<std::string, struct SymbolTable *>(procName, st_pointer));
                this->nowST_pointer = st_pointer;
                code_gen_node(node->proc);
            } else {
                assert(false);
                return TranslateFailed;
            }
            return OK;
        }

        int code_gen_headerDecl_helper(const std::vector<VarDecl *> &decls, struct FuncInfo &nowFuncInfo) {
            for (const auto x : decls) {
                //本来函数形参表的node表示，应该是文法里的formal_parameter
                //但是实际ast实现里，形参还是用varDecls表示的
                //形参的varDecls，和变量定义的varDecls需要区分开来。
                //故这里不调用code_gen_node
                for (const auto y : x->idents->idents) {
                    struct SymbolEntry se;
                    if (x->type_spec->type == Type::BasicTypeSpec) {
                        keyword2str(reinterpret_cast<const BasicTypeSpec *>(x)->keyword->key_type, se.typeDecl);
                        nowFuncInfo.paraType.push_back(se.typeDecl);
                        se.varType = ISBASIC;
                    } else if (x->type_spec->type == Type::ArrayTypeSpec) {
                        keyword2str(reinterpret_cast<const ArrayTypeSpec *>(x)->keyword->key_type, se.typeDecl);
                        for(int i=0; i<reinterpret_cast<const ArrayTypeSpec *>(x)->periods.size(); i++){
                            se.typeDecl += "*"; //数组类型
                        }
                        nowFuncInfo.paraType.push_back(se.typeDecl);
                        se.varType = ISARRAY;
                        se.arrayInfo = reinterpret_cast<const ArrayTypeSpec *>(x->type_spec);
                    } else {
                        assert(false);
                        return TranslateFailed;
                    }

                    this->nowST_pointer->content.insert(std::pair<std::string, struct SymbolEntry>(y->content, se));
                    nowFuncInfo.formalPara += se.typeDecl + " " + y->content + ", ";
                }
            }
            return OK;
        };

        int code_gen_FunctionDecl(const FunctionDecl *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                assert(false); //未找到函数
                return TranslateFailed;
            }
            struct FuncInfo &nowFuncInfo = iter->second;
            keyword2str(node->basic->keyword->key_type, nowFuncInfo.returnType);
            code_gen_headerDecl_helper(node->decls->decls, nowFuncInfo);
            return OK;
        }

        int code_gen_Procedure(const Procedure *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                assert(false); //未找到函数
                return TranslateFailed;
            }
            struct FuncInfo &nowFuncInfo = iter->second;
            nowFuncInfo.returnType = "void";
            code_gen_headerDecl_helper(node->decls->decls, nowFuncInfo);
            return OK;
        }

        int code_gen_SubprogramBody(const SubprogramBody *node) {
            auto iter = this->functionBuff.find(this->nowST_pointer->tableName);
            if (iter == this->functionBuff.end()) {
                assert(false); //未找到函数
                return TranslateFailed;
            }
            struct FuncInfo &nowFuncInfo = iter->second;
            code_gen_ConstDecls(node->constdecls, nowFuncInfo.funcBody);
            code_gen_VarDecls(node->vardecls, nowFuncInfo.funcBody);
            code_gen_CompoundStatement(node->compound, nowFuncInfo.funcBody);
        }

        int code_gen_CompoundStatement(const CompoundStatement *node, std::string &buffer) {
            for (auto x : node->state->statement) {
                code_gen_Statement(x, buffer);
                //buffer += ";\n";
            }
            return OK;
        }

        int code_gen_exp(const Exp *node, std::string &buffer, std::string &expType) {
            switch (node->type) {
                case Type::BiExp:
                    return code_gen_BiExp(reinterpret_cast<const BiExp *>(node), buffer, expType);
                case Type::UnExp:
                    return code_gen_UnExp(reinterpret_cast<const UnExp *>(node), buffer, expType);
                case Type::ExpCall:
                    return code_gen_ExpCall(reinterpret_cast<const ExpCall *>(node), buffer, expType);
                case Type::ExpAssign:
                    return code_gen_ExpAssign(reinterpret_cast<const ExpAssign *>(node), buffer, expType);
                case Type::Variabele: // AST里的Variabele有拼写错误
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
                default:
                    assert(false);
                    return TranslateFailed;
            }
        }

        int code_gen_Statement(const Statement *node, std::string &buffer) {
            // 该函数负责statement的生成。
            std::string tempString;
            switch (node->type) {
                case Type::ExecStatement:
                    return code_gen_exp(reinterpret_cast<const ExecStatement *>(node)->exp, buffer, tempString);
                case Type::IfElseStatement:
                    return code_gen_IfElseStatement(reinterpret_cast<const IfElseStatement *>(node), buffer);
                case Type::ForStatement:
                    return code_gen_ForStatement(reinterpret_cast<const ForStatement *>(node), buffer);
                default:
                    assert(false);
                    return TranslateFailed;
            }
        }

        int code_gen_BiExp(const BiExp *node, std::string &buffer, std::string &expType) {
            std::string lhsType;
            std::string rhsType;
            code_gen_exp(node->lhs, buffer, lhsType);
            std::string markerStr;
            marker2str(node->marker->marker_type, markerStr);
            buffer += " " + markerStr + " ";
            code_gen_exp(node->rhs, buffer, rhsType);
            buffer += ";\n";
            return OK;
        }

        int code_gen_ExpCall(const ExpCall *node, std::string &buffer, std::string &expType) {
            auto iter = this->functionBuff.find(node->fn->content);
            if (iter == this->functionBuff.end()) {
                assert(false); //未找到函数
                return TranslateFailed;
            }
            const struct FuncInfo callInfo = iter->second;
            buffer += node->fn->content;
            buffer += "(";
            for (auto x : node->params->params) {
                code_gen_Variable(x, buffer, expType);

                buffer += ", ";
            }
            std::string otherPara = callInfo.additionPara;
            otherPara.pop_back();
            otherPara.pop_back();
            buffer += otherPara;
            buffer += ");\n";
            return OK;
        }

        int code_gen_Variable(const Variable *node, std::string &buffer, std::string &expType) {
            bool varFind = false;
            struct SymbolTable *theTable = this->nowST_pointer;
            auto iterTable = theTable->content.find(node->id->content);
            if (iterTable != theTable->content.end())
                varFind = true;
            else {
                while (theTable->prev != NULL) { //在当前符号表找不到变量。向上层符号表寻找。
                    auto iterTable = theTable->content.find(node->id->content);
                    if (iterTable != theTable->content.end()) {
                        varFind = true;
                        //对在上层符号表找到的变量，追加函数调用参数。
                        std::string funcName = this->nowST_pointer->tableName; //符号表名称即当前函数名称
                        auto iterFunc = this->functionBuff.find(funcName);
                        if (iterFunc == this->functionBuff.end()) {
                            //没找到函数定义
                            assert(false);
                            return TranslateFailed;
                        }
                        expType = iterTable->second.typeDecl;
                        iterFunc->second.formalPara += fmt::format(
                                "{0} {1}, ", iterTable->second.typeDecl, iterTable->first);
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

            if (varFind) {
                buffer += fmt::format("{0}", node->id->content);
                return OK;
            } else {
                assert(false);
                return TranslateFailed;
            }
        }

        int code_gen_ExpAssign(const ExpAssign *node, std::string &buffer, std::string &expType) {
            //类型检查
            std::string lhsType;
            std::string rhsType;
            code_gen_exp(node->lhs, buffer, lhsType);
            buffer += " " + std::string("=") + " ";
            code_gen_exp(node->rhs, buffer, rhsType);
            buffer += ";\n";
            return OK;
        }

        int code_gen_UnExp(const UnExp *node, std::string &buffer, std::string &expType) {
            return OK;
        }

        int code_gen_IfElseStatement(const IfElseStatement *node, std::string &buffer) {
            return OK;
        }

        int code_gen_ForStatement(const ForStatement *node, std::string &buffer) {
            return OK;
        }

        int code_gen_ExpConstantBoolean(const ExpConstantBoolean *node, std::string &buffer, std::string &expType) {
            return OK;
        }

        int code_gen_ExpConstantChar(const ExpConstantChar *node, std::string &buffer, std::string &expType) {
            return OK;
        }

        int code_gen_ExpConstantReal(const ExpConstantReal *node, std::string &buffer, std::string &expType) {
            return OK;
        }

        int code_gen_ExpConstantInteger(const ExpConstantInteger *node, std::string &buffer, std::string &expType) {
            return OK;
        }

        int code_gen_ExpConstantString(const ExpConstantString *node, std::string &buffer, std::string &expType) {
            return OK;
        }

        /*
        int search_for_symbol(const std::string &symbol, std::string &value) {
            LinkedContext *now_ctx = current_linkedCtx;
            while (now_ctx != NULL) {
                if (now_ctx->content->count(symbol) > 0) {
                    value = now_ctx->content->find(symbol)->second;
                    return OK;
                } else {
                    now_ctx = current_linkedCtx->last;
                }
            }
            throw std::runtime_error(fmt::format("symbol {} not found", symbol));
            return TranslateFailed;
        }


        void insert_const_decls(std::map<std::string, std::string> &map, ConstDecls *pDecls) {
            if (pDecls != nullptr) {
                for (auto decl : pDecls->decls) {
                }
            }
        }

        int convert_exp_to_str(const Exp *expression, std::string &result) {
            switch (expression->type) {
                case Type::UnExp:
                    result += reinterpret_cast<const UnExp *>(expression)->marker->content;
                    return convert_exp_to_str(reinterpret_cast<const UnExp *>(expression)->lhs, result);
                case Type::BiExp:
                    convert_exp_to_str(reinterpret_cast<const BiExp *>(expression)->lhs, result);
                    result += std::string(" ") + reinterpret_cast<const BiExp *>(expression)->marker->content +
                              std::string(" ");
                    return convert_exp_to_str(reinterpret_cast<const BiExp *>(expression)->rhs, result);
                case Type::ExpConstantInteger:
                    result += reinterpret_cast<const ExpConstantInteger *>(expression)->value->content;
                    return OK;
                case Type::ExpConstantChar:
                    result += reinterpret_cast<const ExpConstantChar *>(expression)->value->content;
                    return OK;
                case Type::ExpConstantBoolean:
                    if (reinterpret_cast<const ExpConstantBoolean *>(expression)->value->attr == 1)
                        result += "1";
                    else if (reinterpret_cast<const ExpConstantBoolean *>(expression)->value->attr == 0)
                        result += "0";
                    else
                        return TranslateFailed;
                    return OK;
                case Type::ExpConstantString:
                    result += reinterpret_cast<const ExpConstantString *>(expression)->value->content;
                    return OK;
                case Type::ExpConstantReal:
                    result += reinterpret_cast<const ExpConstantString *>(expression)->value->content;
                    return OK;
                default:
                    throw std::runtime_error("expression_to_str error");
            }
        }
         */
    };
}
#endif //PASCAL_S_TARGET_C_H

