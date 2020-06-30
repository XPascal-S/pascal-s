//
// Created by kamiyoru on 2020/5/12.
//
#include <target/c.h>


char testChar[6] = "hello";

int main()
{
    Keyword *integer = new Keyword(KeywordType::Integer);
    ExpKeyword *intKeyWord = new ExpKeyword(integer);
    Identifier *mainIdentifier = new Identifier("main");
    Ident *mainIdent = new Ident(mainIdentifier);
    ProgramHead *promHead = new ProgramHead(intKeyWord, mainIdent, nullptr);
    StatementList *mainStatementList = new StatementList;
    Identifier *writeChar = new Identifier("write_char");

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


}
