//
// Created by kamiyoru on 2020/5/12.
//
#include <pascal-s/AST.h>
#include <pascal-s/token.h>
#include <target/c.h>
#include <iostream>


Program * test_if_else() {
    auto *integer = new Keyword(KeywordType::Integer);
    auto *intKeyWord = new ExpKeyword(integer);
    auto *mainIdentifier = new Identifier("main");
    auto *mainIdent = new Ident(mainIdentifier);
    auto *promHead = new ProgramHead(intKeyWord, mainIdent, nullptr);

    auto *varDecls = new VarDecls;
    auto identList = new IdentList;
    identList->idents.push_back(new Identifier("a"));
    varDecls->decls.push_back(new VarDecl(identList, new TypeSpec(Type::BasicTypeSpec)));

    auto *readInt = new Identifier("read_int64");
    auto *writeChar = new Identifier("write_char");
    auto *varA = new Variable;
    varA->id = new Identifier("a");
    auto *varMain = new Variable;
    varMain->id = new Identifier("main");
    auto mainStatementList = new StatementList;

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
    auto *mainBody = new ProgramBody(nullptr, varDecls, nullptr, mainCompoundStat);

    auto *mainProgram = new Program(promHead, mainBody);
    return mainProgram;
}

int main()
{
    Keyword *integer = new Keyword(KeywordType::Integer);
    ExpKeyword *intKeyWord = new ExpKeyword(integer);
    Identifier *mainIdentifier = new Identifier("main");
    Ident *mainIdent = new Ident(mainIdentifier);
    ProgramHead *promHead = new ProgramHead(intKeyWord, mainIdent, nullptr);
    StatementList *mainStatementList = new StatementList;
    Identifier *writeChar = new Identifier("write_char");

    char testChar[6] = "hello";
    for(int i=0; i<5; i++) {
        ExpressionList *constStringList = new ExpressionList;
        ConstantChar *hchar = new ConstantChar(testChar[i]);
        ExpConstantChar *inputHchar = new ExpConstantChar(hchar);
        constStringList->explist.push_back(inputHchar);
        ExpCall *callNode1 = new ExpCall(writeChar, constStringList);
        ExecStatement *statement1 = new ExecStatement(callNode1);
        mainStatementList->statement.push_back(statement1);
    }

    CompoundStatement *mainCompoundStatement = new CompoundStatement(mainStatementList);

    ProgramBody *mainBody = new ProgramBody(nullptr, nullptr, nullptr, mainCompoundStatement);

    Program *mainProgram = new Program(promHead, mainBody);

    target_c::Buffer tempBuffer(std::cout);
    std::vector<std::string> include_files;
    target_c::CBuilder theBuilder(include_files, tempBuffer);
    theBuilder.code_gen(mainProgram);

}

