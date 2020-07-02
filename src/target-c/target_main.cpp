//
// Created by kamiyoru on 2020/5/12.
//
#include <pascal-s/AST.h>
#include <pascal-s/token.h>
#include <target/c.h>
#include <iostream>


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
    auto arrayidentlist = new IdentList;
    arrayidentlist->idents.push_back(new Identifier("c"));
    auto *arrayTypesp = new ArrayTypeSpec(new Keyword(KeywordType::Integer));
    arrayTypesp->periods.push_back(std::pair<int, int>(0, 10));

    varDecls->decls.push_back(new VarDecl(identList, new BasicTypeSpec(new Keyword(KeywordType::Integer))));
    varDecls->decls.push_back(new VarDecl(arrayidentlist, arrayTypesp));
    auto *subprogramDecls = new SubprogramDecls;
    auto *gcdVar = new Variable;
    gcdVar->id = new Identifier("gcd");

    auto *gcdVarIdentList = new IdentList;
    gcdVarIdentList->idents.push_back(new Identifier("a"));
    gcdVarIdentList->idents.push_back(new Identifier("b"));
    BasicTypeSpec *integerType = new BasicTypeSpec(integer);
    auto *gcdvarList = new ParamSpec(nullptr, gcdVarIdentList, integerType);
    ParamList *gcdParamList = new ParamList();
    gcdParamList->params.push_back(gcdvarList);
    auto *gcdVarDecls = new VarDecls;
    auto *gcdVarDecl = new VarDecl(gcdVarIdentList, new BasicTypeSpec(new Keyword(KeywordType::Integer)));
    gcdVarDecls->decls.push_back(gcdVarDecl);
    SubprogramHead *gcdHeader = new SubprogramHead;
    gcdHeader->name = new Identifier("gcd");
    gcdHeader->ret_type = new BasicTypeSpec(new Keyword(KeywordType::Integer));
    gcdHeader->decls = gcdParamList;


    auto *gcdStatList = new StatementList;

    auto *gcdIfElseStat = new IfElseStatement;
    auto *gcdIfElseJudgeExpLhs = new Variable;
    gcdIfElseJudgeExpLhs->id = new Identifier("b");
    auto *gcdIfElseJudgeExp = new BiExp(gcdIfElseJudgeExpLhs, new Marker(MarkerType::EQ), new ExpConstantInteger(new ConstantInteger(0)));
    gcdIfElseStat->expression = gcdIfElseJudgeExp;
    auto *aidentToken = new Identifier("a");
    auto *varIdent = new Ident(aidentToken);
    auto *varA = new Variable();
    varA->id = aidentToken;
    auto *gcdIfAssign = new ExpAssign(gcdVar, varA);
    auto *gcdIfStat = new ExecStatement(gcdIfAssign);
    gcdIfElseStat->if_part = gcdIfStat;

    auto *gcdElseAssignRhsExpressList = new ExpressionList;
    auto *varB = new Variable;
    varB->id = new Identifier("b");
    gcdElseAssignRhsExpressList->explist.push_back(varB);
    gcdElseAssignRhsExpressList->explist.push_back(new BiExp(varA, new Marker(MarkerType::Mod), varB));
    auto *gcdElseAssignRhs = new ExpCall(new Identifier("gcd"), gcdElseAssignRhsExpressList);
    auto *gcdElseAssign = new ExpAssign(gcdVar, gcdElseAssignRhs);
    auto *gcdElseStat = new ExecStatement(gcdElseAssign);
    gcdIfElseStat->else_part = gcdElseStat;

    gcdStatList->statement.push_back(gcdIfElseStat);
    //
    auto *varC = new Variable;
    varC->id = new Identifier("c");
    auto *arrayExp = new ExpressionList;
    arrayExp->explist.push_back(new ExpConstantInteger(new ConstantInteger(2)));
    varC->id_var = arrayExp;
    auto *c_exp = new BiExp(varC, new Marker(MarkerType::Assign), new ExpConstantInteger(new ConstantInteger(1)));
    auto *c_statement = new ExecStatement(c_exp);
    gcdStatList->statement.push_back(c_statement);
    //
    auto *gcdBody = new SubprogramBody(nullptr, nullptr, new CompoundStatement(gcdStatList));
    auto *gcdSubprogram = new Subprogram(gcdHeader, gcdBody);
    subprogramDecls->subprogram.push_back(gcdSubprogram);

    auto *mainStatList = new StatementList;
    auto *readIdent = new Identifier("read");
    auto *writeIdent = new Identifier("write");
    auto *varX = new Variable;
    varX->id = new Identifier("x");
    auto *varY = new Variable;
    varY->id = new Identifier("y");
    auto *readExpressList1 = new VariableList;
    readExpressList1->params.push_back(varX);
    auto *read1 = new Read;
    read1->var_list = readExpressList1;
    mainStatList->statement.push_back(new ExecStatement(read1));

    auto *readExpressList2 = new VariableList;
    readExpressList2->params.push_back(varY);
    auto *read2 = new Read;
    read2->var_list = readExpressList2;
    mainStatList->statement.push_back(new ExecStatement(read2));

    auto *writeExpressList = new ExpressionList;
    auto *gcdExpressList = new ExpressionList;
    gcdExpressList->explist.push_back(varX);
    gcdExpressList->explist.push_back(varY);
    writeExpressList->explist.push_back(new ExpCall(new Identifier("gcd"), gcdExpressList));
    auto *write = new Write;
    write->exp_list = writeExpressList;
    mainStatList->statement.push_back(new ExecStatement(write));

    auto *mainBody = new ProgramBody(nullptr, varDecls, subprogramDecls, new CompoundStatement(mainStatList));
    auto *mainProgram = new Program(mainHead, mainBody);
    return mainProgram;
}



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
        Write *writeStat = new Write;
        ExpressionList *writeExpression = new ExpressionList;
        ConstantChar *hchar = new ConstantChar(testChar[i]);
        ExpConstantChar *inputHchar = new ExpConstantChar(hchar);
        writeExpression->explist.push_back(inputHchar);
        writeStat->exp_list = writeExpression;
        ExecStatement *statement1 = new ExecStatement(writeStat);
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


    ProgramBody *mainBody = new ProgramBody(nullptr, nullptr, nullptr, mainCompoundStatement);

    Program *mainProgram = new Program(promHead, mainBody);
    return mainProgram;
}



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
    auto *writeC = new Identifier("write");

    auto *readInt = new Identifier("read");
    auto *varA = new Variable;
    varA->id = new Identifier("a");
    auto *varMain = new Variable;
    varMain->id = new Identifier("main");
    auto mainStatementList = new StatementList;

    auto *readExpList = new VariableList;
    readExpList->params.push_back(varA);
    auto *readExp = new Read;
    readExp->var_list = readExpList;
    mainStatementList->statement.push_back(new ExecStatement(readExp));

    auto *ifelseStatement = new IfElseStatement;
    auto *judgeExp = new BiExp(varA, new Marker(MarkerType::LT), new ExpConstantInteger(new ConstantInteger(0)));
    ifelseStatement->expression = judgeExp;

    auto *ifPart = new StatementList;
    auto *writeCharExpList1 = new ExpressionList;
    writeCharExpList1->explist.push_back(new ExpConstantChar(new ConstantChar('<')));
    auto *callWriteChar = new Write;
    callWriteChar->exp_list = writeCharExpList1;
    auto *ifStat = new ExecStatement(callWriteChar);
    ifPart->statement.push_back(ifStat);
    CompoundStatement *ifCompoundStatement = new CompoundStatement;
    ifCompoundStatement->state = ifPart;
    ifelseStatement->if_part = ifCompoundStatement;

    auto *elsePart = new StatementList;
    auto *writeCharExpList2 = new ExpressionList;
    writeCharExpList2->explist.push_back(new ExpConstantChar(new ConstantChar('>')));
    auto *callWriteChar2 = new Write;
    callWriteChar2->exp_list = writeCharExpList2;
    auto *elseStat1 = new ExecStatement(callWriteChar2);
    auto *writeCharExpList3 = new ExpressionList;
    writeCharExpList3->explist.push_back(new ExpConstantChar(new ConstantChar('=')));

    auto *callWriteChar3 = new Write;
    callWriteChar3->exp_list = writeCharExpList3;

    auto *elseStat2 = new ExecStatement(callWriteChar3);
    elsePart->statement.push_back(elseStat1);
    elsePart->statement.push_back(elseStat2);
    CompoundStatement *elseCompoundStatement = new CompoundStatement;
    elseCompoundStatement->state = elsePart;
    ifelseStatement->else_part = elseCompoundStatement;

    mainStatementList->statement.push_back(ifelseStatement);

    auto *returnExp = new ExpAssign(varMain, new ExpConstantInteger(new ConstantInteger(0)));
    auto *returnStat = new ExecStatement(returnExp);
    mainStatementList->statement.push_back(returnStat);

    auto *mainCompoundStat = new CompoundStatement(mainStatementList);
    auto *mainBody = new ProgramBody(nullptr, varDecls, nullptr, mainCompoundStat);

    auto *mainProgram = new Program(mainHead, mainBody);
    return mainProgram;
}


/*
program main;
begin
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
    Program *mainProgram = test_if_else();
    target_c::Buffer tempBuffer(std::cout);
    std::vector<std::string> include_files;
    target_c::CBuilder theBuilder(include_files, tempBuffer);
    theBuilder.code_gen(mainProgram);

    return 0;
}

