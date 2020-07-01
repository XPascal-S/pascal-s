//
// Created by kamiyoru on 2020/5/12.
//
#include <pascal-s/AST.h>
#include <pascal-s/token.h>
#include <target/c.h>
#include <iostream>

/*
Program * test_gcd() {
    auto *integer = new Keyword(KeywordType::Integer);
    auto *intKeyWord = new ExpKeyword(integer);
    auto *mainIdentifier = new Identifier("example");
    auto *mainIdent = new Ident(mainIdentifier);
    auto *mainHead = new ProgramHead(intKeyWord, mainIdent, nullptr);

    auto *varDecls = new VarDecls;
    auto identList = new IdentList;
    identList->idents.push_back(new Identifier("x"));
    identList->idents.push_back(new Identifier("y"));
    varDecls->decls.push_back(new VarDecl(identList, new BasicTypeSpec(new Keyword(KeywordType::Integer))));

    auto *subprogramDecls = new SubprogramDecls;
    auto *gcdVar = new Variable;
    gcdVar->id = new Identifier("gcd");
    auto *varA = new Variable;
    varA->id = new Identifier("a");
    auto *varB = new Variable;
    varB->id = new Identifier("b");

    // ----function write_char
    auto *readInt = new Identifier("read");
    Identifier *writeChar = new Identifier("write_char");
    Keyword *charC = new Keyword(KeywordType::Char);
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
    ConstantInteger *return1 = new ConstantInteger(1);
    ExpConstantInteger *returnvalue = new ExpConstantInteger(return1);
    ExpAssign *funcReturnStat = new ExpAssign(funcName, returnvalue); // write_char := 0
    ExecStatement *statement0 = new ExecStatement(funcReturnStat);
    StatementList *funcStatementlist = new StatementList;
    funcStatementlist->statement.push_back(statement0);
    CompoundStatement *funcCompoundStatement = new CompoundStatement(funcStatementlist);
    SubprogramBody *funcBody = new SubprogramBody(nullptr, nullptr, funcCompoundStatement);

    Subprogram *function = new Subprogram(functionHeader, funcBody);
    subprogramDecls->subprogram.push_back(function);
    // ----function write_char

    // ----function read
    FunctionDecl *functionDecl_read = new FunctionDecl(readInt, functionPara, intType);
    SubprogramHead *functionHeader_read = new SubprogramHead;
    functionHeader_read->func = functionDecl_read;
    Variable *funcName_read = new Variable();
    funcName_read->id = readInt;
    ExpAssign *funcReturnStat_read = new ExpAssign(funcName_read, returnvalue); // read := 0
    ExecStatement *statement_read = new ExecStatement(funcReturnStat_read);
    StatementList *funcStatementlist_read = new StatementList;
    funcStatementlist_read->statement.push_back(statement_read);
    CompoundStatement *funcCompoundStatement_read = new CompoundStatement(funcStatementlist_read);
    SubprogramBody *funcBody_read = new SubprogramBody(nullptr, nullptr, funcCompoundStatement_read);
    Subprogram *function_read = new Subprogram(functionHeader_read, funcBody_read);
    subprogramDecls->subprogram.push_back(function_read);
    // ---- function read

    auto *gcdHead = new SubprogramHead;
    auto *gcdVarDecls = new VarDecls;
    auto *gcdVarIdentList = new IdentList;
    gcdVarIdentList->idents.push_back(new Identifier("a"));
    gcdVarIdentList->idents.push_back(new Identifier("b"));
    auto *gcdVarDecl = new VarDecl(gcdVarIdentList, new BasicTypeSpec(new Keyword(KeywordType::Integer)));
    gcdVarDecls->decls.push_back(gcdVarDecl);
    auto *gcdFuncDecl = new FunctionDecl(new Identifier("gcd"), gcdVarDecls, new BasicTypeSpec(new Keyword(KeywordType::Integer)));
    gcdHead->func = gcdFuncDecl;

    auto *gcdStatList = new StatementList;

    auto *gcdIfElseStat = new IfElseStatement;
    auto *gcdIfElseJudgeExpLhs = new Variable;
    gcdIfElseJudgeExpLhs->id = new Identifier("b");
    auto *gcdIfElseJudgeExp = new BiExp(gcdIfElseJudgeExpLhs, new Marker(MarkerType::EQ), new ExpConstantInteger(new ConstantInteger(0)));
    auto *gcdIfElseJudge = new ExecStatement(gcdIfElseJudgeExp);
    gcdIfElseStat->expression = gcdIfElseJudge;
    auto *gcdIfStatList = new StatementList;
    auto *gcdIfAssign = new ExpAssign(gcdVar, varA);
    auto *gcdIfStat = new ExecStatement(gcdIfAssign);
    gcdIfStatList->statement.push_back(gcdIfStat);
    gcdIfElseStat->if_part = gcdIfStatList;
    auto *gcdElseStatList = new StatementList;
    auto *gcdElseAssignRhsExpressList = new ExpressionList;
    gcdElseAssignRhsExpressList->explist.push_back(varB);
    gcdElseAssignRhsExpressList->explist.push_back(new BiExp(varA, new Marker(MarkerType::MOD), varB));
    auto *gcdElseAssignRhs = new ExpCall(new Identifier("gcd"), gcdElseAssignRhsExpressList);
    auto *gcdElseAssign = new ExpAssign(gcdVar, gcdElseAssignRhs);
    auto *gcdElseStat = new ExecStatement(gcdElseAssign);
    gcdElseStatList->statement.push_back(gcdElseStat);
    gcdIfElseStat->else_part = gcdElseStatList;

    gcdStatList->statement.push_back(gcdIfElseStat);
    auto *gcdBody = new SubprogramBody(nullptr, nullptr, new CompoundStatement(gcdStatList));
    auto *gcdSubprogram = new Subprogram(gcdHead, gcdBody);
    subprogramDecls->subprogram.push_back(gcdSubprogram);

    auto *mainStatList = new StatementList;
    auto *readIdent = new Identifier("read");
    auto *writeIdent = new Identifier("write_char");
    auto *varX = new Variable;
    varX->id = new Identifier("x");
    auto *varY = new Variable;
    varY->id = new Identifier("y");
    auto *readExpressList1 = new ExpressionList;
    readExpressList1->explist.push_back(varX);
    mainStatList->statement.push_back(new ExecStatement(new ExpCall(readIdent, readExpressList1)));
    auto *readExpressList2 = new ExpressionList;
    readExpressList2->explist.push_back(varY);
    mainStatList->statement.push_back(new ExecStatement(new ExpCall(readIdent, readExpressList2)));
    auto *writeExpressList = new ExpressionList;
    auto *gcdExpressList = new ExpressionList;
    gcdExpressList->explist.push_back(varX);
    gcdExpressList->explist.push_back(varY);
    writeExpressList->explist.push_back(new ExpCall(new Identifier("gcd"), gcdExpressList));
    mainStatList->statement.push_back(new ExecStatement(new ExpCall(writeIdent, writeExpressList)));

    auto *mainBody = new ProgramBody(nullptr, varDecls, subprogramDecls, new CompoundStatement(mainStatList));
    auto *mainProgram = new Program(mainHead, mainBody);
    return mainProgram;
}
*/

Program * test_write_char(){
    Keyword *integer = new Keyword(KeywordType::Integer);
    Keyword *charC = new Keyword(KeywordType::Char);
    ExpKeyword *intKeyWord = new ExpKeyword(integer);
    Identifier *mainIdentifier = new Identifier("main");
    Ident *mainIdent = new Ident(mainIdentifier);
    ProgramHead *promHead = new ProgramHead(intKeyWord, mainIdent, nullptr);
    StatementList *mainStatementList = new StatementList;
    Identifier *writeChar = new Identifier("write_char");

    char testChar[6] = "hello";
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
    ConstantInteger *return0 = new ConstantInteger(0);
    ExpConstantInteger *returnvalue = new ExpConstantInteger(return0);
    ExpAssign *returnStat = new ExpAssign(mainFunc, returnvalue); // main := 0
    ExecStatement *statement2 = new ExecStatement(returnStat);
    mainStatementList->statement.push_back(statement2);
    CompoundStatement *mainCompoundStatement = new CompoundStatement(mainStatementList);


    Identifier *functionParaIden = new Identifier("a");
    SubprogramHead *functionHeader = new SubprogramHead;
    BasicTypeSpec *intType = new BasicTypeSpec(integer);
    BasicTypeSpec *charType = new BasicTypeSpec(charC);
    ParamList *functionPara = new ParamList;
    IdentList *functionident = new IdentList;
    functionident->idents.push_back(functionParaIden); // function write_char(a:char):int;
    ParamSpec *charPara = new ParamSpec(nullptr, functionident, charType);
    functionPara->params.push_back(charPara);
    functionHeader->name = writeChar;
    functionHeader->decls = functionPara;
    functionHeader->ret_type = intType;


    Variable *funcName = new Variable();
    funcName->id = writeChar;
    ExpAssign *funcReturnStat = new ExpAssign(funcName, returnvalue); // write_char := 0
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
    return mainProgram;
}

/*
Program * test_if_else() {
    auto *integer = new Keyword(KeywordType::Integer);
    auto *intKeyWord = new ExpKeyword(integer);
    auto *mainIdentifier = new Identifier("main");
    auto *mainIdent = new Ident(mainIdentifier);
    auto *mainHead = new ProgramHead(intKeyWord, mainIdent, nullptr);

    auto *varDecls = new VarDecls;
    auto identList = new IdentList;
    identList->idents.push_back(new Identifier("a"));
    varDecls->decls.push_back(new VarDecl(identList, new BasicTypeSpec(new Keyword(KeywordType::Integer))));
    auto *writeChar = new Identifier("write_char");


    auto *readInt = new Identifier("read");
    auto *varA = new Variable;
    varA->id = new Identifier("a");
    auto *varMain = new Variable;
    varMain->id = new Identifier("main");
    auto mainStatementList = new StatementList;

    // ----function write_char
    Keyword *charC = new Keyword(KeywordType::Char);
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
    ConstantInteger *return1 = new ConstantInteger(1);
    ExpConstantInteger *returnvalue = new ExpConstantInteger(return1);
    ExpAssign *funcReturnStat = new ExpAssign(funcName, returnvalue); // write_char := 0
    ExecStatement *statement0 = new ExecStatement(funcReturnStat);
    StatementList *funcStatementlist = new StatementList;
    funcStatementlist->statement.push_back(statement0);
    CompoundStatement *funcCompoundStatement = new CompoundStatement(funcStatementlist);
    SubprogramBody *funcBody = new SubprogramBody(nullptr, nullptr, funcCompoundStatement);

    Subprogram *function = new Subprogram(functionHeader, funcBody);
    SubprogramDecls *functions = new SubprogramDecls;
    functions->subprogram.push_back(function);
    // ----function write_char

    // ----function read
    FunctionDecl *functionDecl_read = new FunctionDecl(readInt, functionPara, intType);
    SubprogramHead *functionHeader_read = new SubprogramHead;
    functionHeader_read->func = functionDecl_read;
    Variable *funcName_read = new Variable();
    funcName_read->id = readInt;
    ExpAssign *funcReturnStat_read = new ExpAssign(funcName_read, returnvalue); // read := 0
    ExecStatement *statement_read = new ExecStatement(funcReturnStat_read);
    StatementList *funcStatementlist_read = new StatementList;
    funcStatementlist_read->statement.push_back(statement_read);
    CompoundStatement *funcCompoundStatement_read = new CompoundStatement(funcStatementlist_read);
    SubprogramBody *funcBody_read = new SubprogramBody(nullptr, nullptr, funcCompoundStatement_read);
    Subprogram *function_read = new Subprogram(functionHeader_read, funcBody_read);
    functions->subprogram.push_back(function_read);
    // ---- function read

    auto *readExpList = new ExpressionList;
    readExpList->explist.push_back(varA);
    auto *readExp = new ExpCall(readInt, readExpList);
    mainStatementList->statement.push_back(new ExecStatement(readExp));

    auto *ifelseStatement = new IfElseStatement;
    auto *judgeExp = new BiExp(varA, new Marker(MarkerType::LT), new ExpConstantInteger(new ConstantInteger(0)));
    auto *judgeStat = new ExecStatement(judgeExp);
    ifelseStatement->expression = judgeStat;

    auto *ifPart = new StatementList;
    auto *writeCharExpList1 = new ExpressionList;
    writeCharExpList1->explist.push_back(new ExpConstantChar(new ConstantChar('<')));
    auto *callWriteChar1 = new ExpCall(writeChar, writeCharExpList1);
    auto *ifStat = new ExecStatement(callWriteChar1);
    ifPart->statement.push_back(ifStat);
    ifelseStatement->if_part = ifPart;

    auto *elsePart = new StatementList;
    auto *writeCharExpList2 = new ExpressionList;
    writeCharExpList2->explist.push_back(new ExpConstantChar(new ConstantChar('>')));
    auto *callWriteChar2 = new ExpCall(writeChar, writeCharExpList2);
    auto *elseStat1 = new ExecStatement(callWriteChar2);
    auto *writeCharExpList3 = new ExpressionList;
    writeCharExpList3->explist.push_back(new ExpConstantChar(new ConstantChar('=')));
    auto *callWriteChar3 = new ExpCall(writeChar, writeCharExpList3);
    auto *elseStat2 = new ExecStatement(callWriteChar3);
    elsePart->statement.push_back(elseStat1);
    elsePart->statement.push_back(elseStat2);
    ifelseStatement->else_part = elsePart;

    mainStatementList->statement.push_back(ifelseStatement);

    auto *returnExp = new ExpAssign(varMain, new ExpConstantInteger(new ConstantInteger(0)));
    auto *returnStat = new ExecStatement(returnExp);
    mainStatementList->statement.push_back(returnStat);

    auto *mainCompoundStat = new CompoundStatement(mainStatementList);
    auto *mainBody = new ProgramBody(nullptr, varDecls, functions, mainCompoundStat);

    auto *mainProgram = new Program(mainHead, mainBody);
    return mainProgram;
}
*/

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

    Program *mainProgram = test_write_char();
    target_c::Buffer tempBuffer(std::cout);
    std::vector<std::string> include_files;
    target_c::CBuilder theBuilder(include_files, tempBuffer);
    theBuilder.code_gen(mainProgram);

    return 0;
}

