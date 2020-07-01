//
// Created by kamiyoru on 2020/5/12.
//
#include <pascal-s/AST.h>
#include <pascal-s/token.h>
#include <target/c.h>
#include <iostream>

char testChar[6] = "hello";

/*
program main;
begin
    function write_char(a:char):int;
        begin
            write_char:= 1
        end
    write_char('h');
    write_char('e');
    write_char('l');
    write_char('l');
    write_char('o');
main := 0;
end

 */

int main()
{

    Keyword *integer = new Keyword(KeywordType::Integer);
    Keyword *charC = new Keyword(KeywordType::Char);
    ExpKeyword *intKeyWord = new ExpKeyword(integer);
    Identifier *mainIdentifier = new Identifier("main");
    Ident *mainIdent = new Ident(mainIdentifier);
    ProgramHead *promHead = new ProgramHead(intKeyWord, mainIdent, nullptr);
    StatementList *mainStatementList = new StatementList;
    Identifier *writeChar = new Identifier("write_char");

    for(int i=0; i<5; i++) {
        //  write_char('h') --- write_char('0')
        ExpressionList *constStringList = new ExpressionList;
        ConstantChar *hchar = new ConstantChar(testChar[i]);
        ExpConstantChar *inputHchar = new ExpConstantChar(hchar);
        constStringList->explist.push_back(inputHchar);
        ExpCall *callNode1 = new ExpCall(writeChar, constStringList);
        ExecStatement *statement1 = new ExecStatement(callNode1);
        mainStatementList->statement.push_back(statement1);
    }

    //主函数内容
    Variable *mainFunc = new Variable();
    mainFunc->id = mainIdentifier;
    ConstantInteger *return1 = new ConstantInteger(1);
    ExpConstantInteger *returnvalue = new ExpConstantInteger(return1);
    ExpAssign *returnStat = new ExpAssign(mainFunc, returnvalue); // main := 0
    ExecStatement *statement2 = new ExecStatement(returnStat);
    mainStatementList->statement.push_back(statement2);
    CompoundStatement *mainCompoundStatement = new CompoundStatement(mainStatementList);


    Identifier *functionParaIden = new Identifier("a");
    SubprogramHead *functionHeader = new SubprogramHead;
    BasicTypeSpec *intType = new BasicTypeSpec(integer);
    BasicTypeSpec *charType = new BasicTypeSpec(charC);
    VarDecls *functionPara = new VarDecls;
    IdentList *functionident = new IdentList;
    functionident->idents.push_back(functionParaIden); // function write_char(a:char):int;
    VarDecl *charPara = new VarDecl(functionident, charType);
    functionPara->decls.push_back(charPara);
    FunctionDecl *functionDecl = new FunctionDecl(writeChar, functionPara, intType);
    functionHeader->func = functionDecl;


    Variable *funcName = new Variable();
    funcName->id = writeChar;
    ExpAssign *funcReturnStat = new ExpAssign(funcName, returnvalue); // write_char := 1
    ExecStatement *statement0 = new ExecStatement(funcReturnStat);
    StatementList *funcStatementlist = new StatementList;
    funcStatementlist->statement.push_back(statement0);
    CompoundStatement *funcCompoundStatement = new CompoundStatement(funcStatementlist);
    SubprogramBody *funcBody = new SubprogramBody(nullptr, nullptr, funcCompoundStatement);

    Subprogram *function = new Subprogram(functionHeader, funcBody);
    SubprogramDecls *functions = new SubprogramDecls;
    functions->subprogram.push_back(function);


    ProgramBody *mainBody = new ProgramBody(nullptr, nullptr, functions, mainCompoundStatement);

    Program *mainProgram = new Program(promHead, mainBody);

    target_c::Buffer tempBuffer(std::cout);
    std::vector<std::string> include_files;
    target_c::CBuilder theBuilder(include_files, tempBuffer);
    theBuilder.code_gen(mainProgram);

    return 0;
}

