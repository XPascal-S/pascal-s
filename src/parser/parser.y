
%language "c++"

%{
#define YYSTYPE void *
using namespace ast;
%}

%token  KEYWORD            1
%token  STR                2
%token  CHAR               3
%token  REAL               4
%token  INT                5
%token  BOOL               6
%token  IDENT              7
 //                 %token   MARKER  8
%token  NULLPTR            9
%token  ERRORTOKEN         10
%token  COMMENT            11
%token  LENGTH             12

//                 KEYWORD  =       0x100  +  type
%token  KEYWORD_PROGRAM    0x100
%token  KEYWORD_CONST      0x101
%token  KEYWORD_VAR        0x102
%token  KEYWORD_PROCEDURE  0x103
%token  KEYWORD_FUNCTION   0x104
%token  KEYWORD_BEGIN      0x105
%token  KEYWORD_END        0x106
%token  KEYWORD_ARRAY      0x107
%token  KEYWORD_INTEGER    0x108
%token  KEYWORD_REAL       0x109
%token  KEYWORD_BOOLEAN    0x10a
%token  KEYWORD_CHAR       0x10b
%token  KEYWORD_IF         0x10c
%token  KEYWORD_THEN       0x10d
%token  KEYWORD_ELSE       0x10e
%token  KEYWORD_FOR        0x10f
%token  KEYWORD_TO         0x110
%token  KEYWORD_DO         0x111
%token  KEYWORD_OF         0x112
%token  KEYWORD_DIV        0x113
%token  KEYWORD_MOD        0x114
%token  KEYWORD_AND        0x115
%token  KEYWORD_OR         0x116
%token  KEYWORD_NOT        0x117
%token  KEYWORD_READ       0x118
%token  KEYWORD_WRITE      0x119
%token  KEYWORD_LENGTH     0x11a


//                 MARKER   =       0x200  +  type
%token  MARKER_RANGE      0x200
%token  MARKER_LOGICNOT   0x201
%token  MARKER_NEQ        0x211
%token  MARKER_LE         0x212
%token  MARKER_GE         0x213
%token  MARKER_LT         0x214
%token  MARKER_EQ         0x215
%token  MARKER_GT         0x216
%token  MARKER_ADD        0x220
%token  MARKER_SUB        0x221
%token  MARKER_LOGICOR    0x222
%token  MARKER_MUL        0x230
%token  MARKER_DIV        0x231
%token  MARKER_MOD        0x232
%token  MARKER_LOGICAND   0x233
%token  MARKER_LPAREN     0x240
%token  MARKER_RPAREN     0x241
%token  MARKER_LBRACKET   0x250
%token  MARKER_RBRACKET   0x251
%token  MARKER_ASSIGN     0x260
%token  MARKER_COMMA      0x261
%token  MARKER_DOT        0x262
%token  MARKER_SEMICOLON  0x263
%token  MARKER_COLON      0x264

 // %nonassoc IFX
 // %nonassoc ELSE
%start programstruct
 // %start statement
%%

programstruct:  program_head semicolon program_body dot {
  $$ = new ast::Program((ProgramHead*)$1, (ProgramBody*)$3);
  // printf("%x %d %d\n", $$, ((Program*)$$)->type, ((Node*)$$)->type);
  access_ast($$);
  //printf("finish!\n");
  /* Program *node = reinterpret_cast<Program*> (ast_reduce_nodes(4, Type::Program)); */
  /* node->programHead = (ProgramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop semicolon */
  /* node->programBody = (ProgramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop dot */
 }
//|  program_head semicolon program_body error{ printf("\n\n\n\n Missing dot\n"); yyerrok; }
//|  program_head error program_body { printf("\n\n\n\nMissing semicolon\n"); yyerrok; }
;

dot: MARKER_DOT{
  $$ = new ExpMarker((const Marker *)($1));
 }
;

errort: ERRORTOKEN;

program_head:
program id lparen idlist rparen {
  $$ = new ProgramHead((const ExpKeyword*)$1, new Ident((const Identifier*)$2), (IdentList*)$4);
    /* ProgramHead *node = reinterpret_cast<ProgramHead *>(ast_reduce_nodes(5, Type::ProgramHead)); */
  /* node->programKeyword = (const ExpKeyword*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->id = (Ident*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front(); //pop lparen */
  /* node->idlist = ( IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
}
| program id{
  $$ = new ProgramHead((const ExpKeyword*)$1, new Ident((const Identifier*)$2));
}
| program id lparen rparen{
  IdentList* idlist = new IdentList();
  ast::copy_pos_with_check(idlist, (ExpMarker*)$3);
  ast::copy_pos_with_check(idlist, (ExpMarker*)$4);
  $$ = new ProgramHead((const ExpKeyword*)$1, new Ident((const Identifier*)$2), idlist);
}
//| program id error idlist {printf("\n\n\n\nMissing lparen\n"); yyerrok;}
//| program id lparen idlist error {printf("\n\n\n\nMissing rparen\n"); yyerrok;}
;

program:KEYWORD_PROGRAM{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

program_body: const_declarations var_declarations subprogram_declarations compound_statement {
  $$ = new ProgramBody((ConstDecls*)$1, (VarDecls*)$2, (SubprogramDecls*)$3, (CompoundStatement*)$4);
  /* ProgramBody *node = reinterpret_cast<ProgramBody*> (ast_reduce_nodes(4, Type::ProgramBody)); */

  /* node->constdecls = (ConstDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->vardecls = (VarDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->subprogram = (SubprogramDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->compound = (CompoundStatement*)(node->children.front()); */
  /* node->children.pop_front(); */
}
;

idlist:
idlist comma id  {
  $$ = $1;
  ((IdentList*)$$)->idents.push_back((Identifier*)$3);
  ast::copy_pos_with_check((IdentList*)$$, (Identifier*)$3);
  /* IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(3, Type::IdentList)); */
  /* node->idents = reinterpret_cast<IdentList*>(node->children.front())->idents; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop comma */
  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->idents.push_back(id); */
  /* node->children.pop_front(); */
}
| id      {
  $$ = new IdentList();
  ((IdentList*)$$)->idents.push_back((Identifier*)$1);
  ast::copy_pos_with_check((IdentList*)$$, (Identifier*)$1);
  /* IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(1, Type::IdentList)); */
  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->idents.push_back(id); */
  /* node->children.pop_front(); */
  }
//| idlist error id {printf("\n\n\n\nMissing comma\n"); yyerrok;}
;

const_declarations:
const const_declaration semicolon {
  $$ = $2;
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls)); */
  /* node->children.pop_front();// pop const */
  /* node->decls = reinterpret_cast<ConstDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
}
|                                       { $$ = nullptr; }
//| error const_declaration semicolon {printf("\n\n\n\nMissing const\n"); yyerrok;}
//| const const_declaration error {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

const:KEYWORD_CONST{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

const_declaration:
const_declaration semicolon id eq const_value {
  $$ = $1;
  ConstDecl* constDecl = new ConstDecl((const Identifier*)$3, (Exp*)$5);
  ((ConstDecls*)$$)->decls.push_back(constDecl);
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(5, Type::ConstDecls)); */

  /* node->decls = reinterpret_cast<ConstDecls*> (node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  /* Identifier* id = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop eq */
  /* Exp* rhs = (Exp*)(node->children.front()); */
  /* ConstDecl* constDecl = new ConstDecl(id, rhs); */
  /* // constDecl->ident = ; */
  /* // constDecl->rhs = ; */
  /* node->decls.push_back(constDecl); */
  /* node->children.pop_front(); */
}
|id eq const_value  {
  ConstDecl* constDecl = new ConstDecl((const Identifier*)$1, (Exp*)$3);
  $$ = new ConstDecls();
  ((ConstDecls*)$$)->decls.push_back(constDecl);
  /* ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls)); */

  /* Identifier* ident = (Identifier*)(node->children.front()); */
  /* // const->ident = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop eq */
  /* // const->rhs = (Exp*)(node->children.front()); */
  /* Exp* rhs = (Exp*)(node->children.front()); */

  /* ConstDecl* constDecl = new ConstDecl(ident, rhs); */
  /* printf("\n\nget constDecls\n\n"); */
  /* node->children.pop_front(); */
  /* printf("\n\n pop front \n\n"); */
  /* node->decls.push_back(constDecl); */
  /* printf("%d\n\n", node->decls.size()); */
  /* printf("\n\n push back \n\n"); */
}
//| const_declaration error id eq const_value {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

eq:MARKER_EQ {
  $$ = new ExpMarker((const Marker *)($1));
}
;

const_value:
 add num  {$$ = new UnExp((const Marker*)$1, (Exp*)$2);}
|sub num  {$$ = new UnExp((const Marker*)$1, (Exp*)$2);}
|num      {$$ = $1;}
|char     {$$ = $1;}
|bool     {$$ = $1;}
;

bool:BOOL{$$ = new ExpConstantBoolean(((const ConstantBoolean*)($1)));}

num: INT {
  $$ = new ExpConstantInteger(((const ConstantInteger*)($1)));
}
| REAL {
  $$ = new ExpConstantReal(((const ConstantReal*)($1)));
  }
;

char:CHAR {
  $$ = new ExpConstantChar(((const ConstantChar*)($1)));
}
;

add:MARKER_ADD {
  $$ = new ExpMarker((const Marker *)($1));
}
;

sub:MARKER_SUB {
  $$ = new ExpMarker((const Marker *)($1));
}
;

var_declarations:              { $$ = nullptr;  /* new ExpVoid(); */ }
|var var_declaration semicolon {
  $$ = $2;
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls)); */
  /* node->children.pop_front();// pop var */
  /* node->decls = reinterpret_cast<VarDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
}
//| var var_declaration error {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

var_declaration:
var_declaration semicolon idlist colon type   {
  $$ = $1;
  VarDecl* vdecl = new VarDecl((IdentList*)$3, (TypeSpec*)$5);
  ((VarDecls*)$$)->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)$$, vdecl);
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(5, Type::VarDecls)); */

  /* node->decls = reinterpret_cast<VarDecls*>(node->children.front())->decls; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  /* IdentList* idents = (IdentList*)(node->children.front()); */
  /* // const->idents = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); // idlist */
  /* node->children.pop_front(); // pop colon */
  /* // const->type_spec = (TypeSpec*)(node->children.front()); */
  /* TypeSpec* type_spec = (TypeSpec*)(node->children.front()); */
  /* VarDecl* varDecl = new VarDecl(idents, type_spec); */
  /* node->decls.push_back(varDecl); */

  /* node->children.pop_front(); */
}
| idlist colon type {
  $$ = new VarDecls();
  VarDecl* vdecl = new VarDecl((IdentList*)$1, (TypeSpec*)$3);
  ast::copy_pos_with_check((VarDecls*)$$, (IdentList*)$1);
  ((VarDecls*)$$)->decls.push_back(vdecl);
  ast::copy_pos_with_check((VarDecls*)$$, vdecl);
  /* VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls)); */

  /* // const->idents = (IdentList*)(node->children.front()); */
  /* IdentList* idents = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* // const->type_spec = (TypeSpec*)(node->children.front()); */
  /* TypeSpec* type_spec = (TypeSpec*)(node->children.front()); */

  /* node->children.pop_front(); *
     /
     /* VarDecl* varDecl = new VarDecl(idents, type_spec); */
  /* node->decls.push_back(varDecl); */
}
//| var_declaration error idlist colon type {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

type:
basic_type           {
  $$ = $1;
}
| array lbracket period rbracket of basic_type         {
  $$ = $3;
  ((ArrayTypeSpec*)$$)->keyword = ((BasicTypeSpec*)$6)->keyword;
  ast::copy_pos_with_check((ArrayTypeSpec*)$$, ((BasicTypeSpec*)$6)->keyword);
}
;

array:KEYWORD_ARRAY{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

of:KEYWORD_OF{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

basic_type:
integer           {$$ = $1;}
| real          {$$ = $1;}
| boolean          {$$ = $1;}
| char          {$$ = $1;}
;

integer:KEYWORD_INTEGER{
  $$ = new BasicTypeSpec((const Keyword *)($1));
}
;

char:KEYWORD_CHAR{
  $$ = new BasicTypeSpec((const Keyword *)($1));
}
;

real:KEYWORD_REAL{
  $$ = new BasicTypeSpec((const Keyword *)($1));
}
;

boolean:KEYWORD_BOOLEAN{
  $$ = new BasicTypeSpec((const Keyword *)($1));
}
;

period:
period comma num range num        {
  $$ = $1;
  ((ArrayTypeSpec*)$$)->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)$3)->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)$5)->value)->attr)));

  //ast_reduce_nodes(5, Type::ArrayTypeSpec);
}
| num range num                    {
  $$ = new ArrayTypeSpec(nullptr);
  ((ArrayTypeSpec*)$$)->periods.push_back(std::make_pair((int64_t)((ConstantInteger*)(((ExpConstantInteger*)$1)->value)->attr), (int64_t)((ConstantInteger*)(((ExpConstantInteger*)$3)->value)->attr)));
  //ast_reduce_nodes(3, Type::ArrayTypeSpec);
}
| num range unimus num error{
    pascal_s::Pos* pos = ((Node*)$2)->visit_pos();
    //printf("%d\n",yychar);
    #define cur_node (reinterpret_cast<const ast::ExpMarker*>($3))
    printf("\nperiod parse failed at line:%d column:%d: expect: num but got %s\n", pos->line,pos->column+pos->length+1,convertToString(cur_node->value).c_str());
    #undef  cur_node
    //printf("the error occur at line:%d   column:%d\n", pos->line,pos->column+pos->length+1);
    yyerrok;
}
;
range: MARKER_RANGE{
  $$ = new ExpMarker((const Marker *)($1));
}

subprogram_declarations:
subprogram_declarations subprogram semicolon  {
  if( $1 == nullptr ){
    $$ = new SubprogramDecls();
  }else{
    $$ = $1;
  }
  ((SubprogramDecls*)$$)->subprogram.push_back(((Subprogram*)$2));
  /* SubprogramDecls* node = reinterpret_cast<SubprogramDecls*> (ast_reduce_nodes(3, Type::SubprogramDecls)); */

  /* node->subprogram = reinterpret_cast<SubprogramDecls*>(node->children.front())->subprogram; */
  /* node->children.pop_front(); */

  /* Subprogram* sub = (Subprogram*)(node->children.front()); */
  /* node->subprogram.push_back(sub); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  //ast_reduce_nodes(3, Type::SubprogramDecls);
}
| { $$ = nullptr;  }
//| subprogram_declarations subprogram error  {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

subprogram:
subprogram_head semicolon subprogram_body {
  $$ = new Subprogram((SubprogramHead*)$1, (SubprogramBody*)$3);
  /* Subprogram* node = reinterpret_cast<Subprogram*> (ast_reduce_nodes(3, Type::Subprogram)); */
  /* node->subhead = (SubprogramHead*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */
  /* node->subbody = (SubprogramBody*)(node->children.front()); */
  /* node->children.pop_front(); */
}
//| subprogram_head error subprogram_body {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

subprogram_head:
procedure id formal_parameter   {
  $$ = new SubprogramHead((const Keyword*)$1, (const Identifier*)$2, (ParamList*)$3, nullptr);
  /* SubprogramHead* node = reinterpret_cast<SubprogramHead*> (ast_reduce_nodes(3, Type::SubprogramHead)); */


  /*  node->children.pop_front();// pop procedure */
  /*  // pro->name = (Identifier*)(node->children.front()); */
  /*  Identifier* name = (Identifier*)(node->children.front()); */
  /*  node->children.pop_front(); */
  /*  // pro->decls = (ParamList*)(node->children.front()); */
  /*  ParamList* decls = (ParamList*)(node->children.front()); */
  /*  node->children.pop_front(); */

  /*  Procedure* pro = new Procedure(name, decls); */
  /*  node->proc = pro; */
}
| function id formal_parameter colon basic_type  {
  $$ = new SubprogramHead((const Keyword*)$1, (const Identifier*)$2, (ParamList*)$3, (BasicTypeSpec*)$5);
  /* SubprogramHead* node = reinterpret_cast<SubprogramHead*> (ast_reduce_nodes(5, Type::SubprogramHead)); */

  /* FunctionDecl* func = new FunctionDecl(); */
  /* node->children.pop_front();// pop function */
  /* func->name = (Identifier*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* func->decls = (ParamList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop colon */
  /* func->basic = (BasicTypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->func = func; */
}
;

procedure: KEYWORD_PROCEDURE{
  // $$ = new ExpKeyword((const Keyword *)($1));
  $$ = $1;
}
;

function: KEYWORD_FUNCTION{
  // $$ = new ExpKeyword((const Keyword *)($1));
  $$ = $1;
}
;

formal_parameter: { $$ =  nullptr; /* new ParamList(); */  }
| lparen parameter_list rparen {
  $$ = $2;
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList)); */
  /* node->children.pop_front();//pop lparen */
  /* node->params = reinterpret_cast<ParamList*>(node->children.front())->params; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop rparen */
  //ast_reduce_nodes(3, Type::ParamList);
}
//| error parameter_list rparen {printf("\n\n\n\nMissing lparen\n"); yyerrok;}
//| lparen parameter_list error {printf("\n\n\n\nMissing rparen\n"); yyerrok;}
////| error parameter_list error {printf("\n\n\n\nMissing lparen and rparen\n"); yyerrok;}
;

parameter_list:
parameter_list semicolon parameter   {
  $$ = $1;
  ((ParamList*)$$)->params.push_back((ParamSpec*)$3);
  ast::copy_pos_with_check((ParamList*)$$, (ParamSpec*)$3);
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList)); */
  /* node->params = reinterpret_cast<ParamList*>(node->children.front())->params; */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop semicolon */

  /* ParamSpec* param = (ParamSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->params.push_back(param); */
}
| parameter                     {
  $$ = new ParamList();
  ((ParamList*)$$)->params.push_back((ParamSpec*)$1);
  ast::copy_pos_with_check((ParamList*)$$, (ParamSpec*)$1);
  /* ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(1, Type::ParamList)); */
  /* ParamSpec* param = (ParamSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->params.push_back(param); */
  //$$ = $1;
  }
//| parameter_list error parameter {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;


parameter:
var idlist colon basic_type         {
  $$ = new ParamSpec((const Keyword*)$1, (IdentList*)$2, (TypeSpec*)$4);
  /* ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(4, Type::ParamSpec)); */

  /* node->keyword_var = (const Keyword*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->id_list = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* node->spec = (TypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
}
| idlist colon basic_type       {
  $$ = new ParamSpec(nullptr, (IdentList*)$1, (TypeSpec*)$3);
  /* ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(3, Type::ParamSpec)); */

  /* node->id_list = (IdentList*)(node->children.front()); */
  /* node->children.pop_front(); */
  /* node->children.pop_front();// pop colon */
  /* node->spec = (TypeSpec*)(node->children.front()); */
  /* node->children.pop_front(); */
}
;


var:KEYWORD_VAR{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;


colon: MARKER_COLON{
  $$ = new ExpMarker((const Marker *)($1));
}

subprogram_body:
const_declarations var_declarations compound_statement  {
  $$ = new SubprogramBody((ConstDecls*)$1, (VarDecls*)$2, (CompoundStatement*)$3);
  /* SubprogramBody* node = reinterpret_cast<SubprogramBody*> (ast_reduce_nodes(3, Type::SubprogramBody)); */

  /* node->constdecls = (ConstDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->vardecls = (VarDecls*)(node->children.front()); */
  /* node->children.pop_front(); */

  /* node->compound = (CompoundStatement*)(node->children.front()); */
  /* node->children.pop_front(); */

  //ast_reduce_nodes(3, Type::Statement);
}
;

compound_statement:             { $$ = nullptr; }
| begin statement_list end         {
  $$ = new CompoundStatement((StatementList*)$2);
  /* CompoundStatement* node = reinterpret_cast<CompoundStatement*> (ast_reduce_nodes(3, Type::CompoundStatement)); */
  /* node->children.pop_front();//pop begin */

  /* StatementList* state = (StatementList*)(node->children.front()); */
  /* node->state = state; */

  /* node->children.pop_front(); */
  /* node->children.pop_front();//pop end */
  //ast_reduce_nodes(3, Type::Statement);
}
//| error statement_list end   {printf("\n\n\n\nMissing begin\n"); yyerrok;}
//| begin statement_list error {printf("\n\n\n\nMissing end\n"); yyerrok;}
////| error statement_list error {printf("\n\n\n\nMissing begin and end\n"); yyerrok;}
;

begin:KEYWORD_BEGIN{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

end:KEYWORD_END{
  $$ = new ExpKeyword((const Keyword *)($1));
             }
;

statement_list:
statement_list semicolon statement     {
  $$ = $1;
  // printf("statement list offset: %d, line: %d, column: %d\n\n", ((StatementList*)$$)->offset, ((StatementList*)$$)->line, ((StatementList*)$$)->column);
  if( $3 != nullptr ){
    ((StatementList*)$$)->statement.push_back((Statement*)$3);
    ast::copy_pos_with_check((StatementList*)$$, (Statement*)$3);
  }
  /* StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(3, Type::StatementList)); */

  /* node->statement = reinterpret_cast<StatementList*>(node->children.front())->statement; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();// pop semicolon */

  /* Statement* sta = (Statement*)(node->children.front()); */
  /* node->statement.push_back(sta); */
  /* node->children.pop_front(); */

  //ast_reduce_nodes(3, Type::Statement);
}
| statement {
  $$ = new StatementList();
  if( $1 != nullptr ){
    ((StatementList*)$$)->statement.push_back((Statement*)$1);
    ast::copy_pos_with_check((StatementList*)$$, (Statement*)$1);
  }
  /* StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(1, Type::StatementList)); */

  /* Statement* sta = (Statement*)(node->children.front()); */
  /* node->statement.push_back(sta); */
  /* node->children.pop_front(); */
  }
//| statement_list error statement {printf("\n\n\n\nMissing semicolon\n"); yyerrok;}
;

semicolon: MARKER_SEMICOLON{
  $$ = new ExpMarker((const Marker *)($1));
}

statement: //                                            {$$ = new ExpVoid();}
variable assign expression                            {$$ = new ExecStatement(new ExpAssign((Variable*)$1, (Exp*)$3));}
| procedure_call                                      {$$ = new ExecStatement((Exp*)$1);}
| compound_statement                                  {$$ = $1;}
| if expression then statement else statement
                                      {
                                        $$ = new IfElseStatement((Exp*)$2, (Statement*)$4, (Statement*)$6);
                                        ast::copy_pos_between_tokens((IfElseStatement*)$$, (ExpKeyword*)$1, (Statement*)$6);
                                      }
| if expression then statement
{
  $$ = new IfElseStatement((Exp*)$2, (Statement*)$4, nullptr);
  ast::copy_pos_between_tokens((IfElseStatement*)$$, (ExpKeyword*)$1, (Statement*)$4);
}
| for id assign expression to expression do statement
                                              {
                                                $$ = new ForStatement((const Identifier *)$2, (Exp*)$4, (Exp*)$6, (Statement*)$8);
                                                ast::copy_pos_between_tokens((ForStatement*)$$, (ExpKeyword*)$1, (Statement*)$8);
                                              }
| KEYWORD_READ lparen variable_list rparen
{
  $$ = new Read((VariableList*)$3);
  ast::copy_pos_with_check((Read*)$$, (VariableList*)$3);
}
| KEYWORD_WRITE lparen expression_list rparen
{
  $$ = new Write((ExpressionList*)$3);
  ast::copy_pos_with_check((Write*)$$, (ExpressionList*)$3);
}
;

for:KEYWORD_FOR{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

to:KEYWORD_TO{
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

do:KEYWORD_DO{
  $$ = new ExpKeyword((const Keyword *)($1));
   }
;

assign: MARKER_ASSIGN{
  $$ = new ExpMarker((const Marker *)($1));
}

if: KEYWORD_IF {
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

then: KEYWORD_THEN {
  $$ = new ExpKeyword((const Keyword *)($1));
}
;

 else: KEYWORD_ELSE {
   $$ = new ExpKeyword((const Keyword *)($1));
        }
;

variable_list:
variable_list comma variable  {
  $$ = $1 ;
  if( ((Node*)$3)->type == Type::Ident ){
    Variable* var = new Variable();
    var->id = ((Ident*)$3)->ident;
    ((Ident*)$3)->ident = nullptr;
    deleteAST((Ident*)$3);
    ast::copy_pos_with_check(var, var->id);
    ((VariableList*)$$)->params.push_back(var);
    ast::copy_pos_with_check((VariableList*)$$, var);
  }else{
    ((VariableList*)$$)->params.push_back((Variable*)$3);
    ast::copy_pos_with_check((VariableList*)$$, (Variable*)$3);
  }
}
| variable      {
  $$ = new VariableList();
  if( ((Node*)$1)->type == Type::Ident ){
    Variable* var = new Variable();
    var->id = ((Ident*)$1)->ident;
    ((Ident*)$1)->ident = nullptr;
    deleteAST((Ident*)$1);
    ast::copy_pos_with_check(var, var->id);
    ((VariableList*)$$)->params.push_back(var);
    ast::copy_pos_with_check((VariableList*)$$, var);
  }else{
    ((VariableList*)$$)->params.push_back((Variable*)$1);
    ast::copy_pos_with_check((VariableList*)$$, (Variable*)$1);
  }
  }
//| variable_list error variable {printf("\n\n\n\nMissing comma\n"); yyerrok;}
;

variable:
id id_varpart  {
  if( $2 == nullptr ){
    $$ = new Ident((Identifier*)$1);
    // ast::copy_pos_with_check((Variable*)$$, (Identifier*)$1);
  }else{
    $$ = new Variable((Identifier*)$1, (ExpressionList*)$2);
    ast::copy_pos_between_tokens((Variable*)$$, (Identifier*)$1, (ExpressionList*)$2);
  }
}
;

id_varpart:           { $$ = nullptr; /* new ExpressionList(); */ }      /*empty*/
| lbracket expression_list rbracket {
  $$ = $2;
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList)); */
  /* node->children.pop_front();//pop lbracket */

  /* node->explist = reinterpret_cast<ExpressionList*>(node->children.front())->explist; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();//pop rbracket */
  /* ast_reduce_nodes(3,Type::Statement); */
}
;

lbracket: MARKER_LBRACKET{
  $$ = new ExpMarker((const Marker *)($1));
}

rbracket: MARKER_RBRACKET{
  $$ = new ExpMarker((const Marker *)($1));
}

procedure_call:
id          {
  $$ = new Ident((const Identifier*)$1);
  // $$ = new ExpCall((const Identifier*)$1, nullptr);
}
| id lparen expression_list rparen    {
  $$ = new ExpCall((const Identifier*)$1, (ExpressionList*)$3);
}
| id lparen rparen    {
  $$ = new ExpCall((const Identifier*)$1, nullptr);
}
//| id error expression_list rparen {printf("\n\n\n\nMissing lparen\n"); yyerrok;}
//| id lparen expression_list error {printf("\n\n\n\nMissing rparen\n"); yyerrok;}
////| id error expression_list error  {printf("\n\n\n\nMissing lparen and rparen\n"); yyerrok;}
;

lparen: MARKER_LPAREN{
  $$ = new ExpMarker((const Marker *)($1));
}

rparen: MARKER_RPAREN{
  $$ = new ExpMarker((const Marker *)($1));
}

id: IDENT{
  // $$ = new Ident((const Identifier *)($1));
  $$ = $1;
}

expression_list:
expression_list comma expression {
  $$ = $1;
  ((ExpressionList*)$$)->explist.push_back((Exp*)$3);
  ast::copy_pos_with_check((ExpressionList*)$$, (Exp*)$3);
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList)); */

  /* node->explist = reinterpret_cast<ExpressionList*> (node->children.front())->explist; */
  /* node->children.pop_front(); */

  /* node->children.pop_front();// pop comma */

  /* Exp* exp = (Exp*)(node->children.front()); */
  /* node->explist.push_back(exp); */
  /* node->children.pop_front(); */
}
| expression        {
  $$ = new ExpressionList();
  ((ExpressionList*)$$)->explist.push_back((Exp*)$1);
  ast::copy_pos_with_check((ExpressionList*)$$, (Exp*)$1);
  /* ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(1, Type::ExpressionList)); */

  /* Exp* exp = (Exp*)(node->children.front()); */
  /* node->explist.push_back(exp); */
  /* node->children.pop_front(); */
  }
//| expression_list error expression {printf("\n\n\n\nMissing comma\n"); yyerrok;}
;

comma: MARKER_COMMA {
  $$ = new ExpMarker((const Marker *)($1));
}
;

expression: simple_expression relop simple_expression {
  $$ = new BiExp((Exp*)$1, (const Marker*)$2, (Exp*)$3);
}
| simple_expression { $$ = $1; }
;

simple_expression:
simple_expression addop term { $$ = new BiExp((Exp*)$1, (const Marker*)$2, (Exp*)$3); }
| term { $$ = $1; }
;

term: term mulop factor{
  $$ = new BiExp((Exp*)$1, (const Marker*)$2, (Exp*)$3);
}
| factor { $$=$1; };

factor:
variable {
  $$ = $1;
}
| id lparen expression_list rparen {
  $$ = new ExpCall((const Identifier*)$1, (ExpressionList*)$3);
}
| lparen expression rparen {
  $$ = $2;
}
| not factor{
  $$ = new UnExp((const Marker*)$1, (Exp*)$2);
}
| unimus factor{
  $$ = new UnExp((const Marker*)$1, (Exp*)$2);
}
| const_value {
  $$ = $1;
  }

not: MARKER_LOGICNOT {
  $$ = new ExpMarker((const Marker *)($1));
}

unimus: MARKER_SUB {
  $$ = new ExpMarker((const Marker *)($1));
}

addop: MARKER_ADD {
  $$ = new ExpMarker((const Marker *)($1));
}
| MARKER_SUB {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_LOGICOR{
  $$ = new ExpMarker((const Marker *)($1));
  }


mulop: MARKER_MUL {
  $$ = new ExpMarker((const Marker *)($1));
}
| MARKER_DIV {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_MOD {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_LOGICAND {
  $$ = new ExpMarker((const Marker *)($1));
  }

relop: MARKER_EQ {
  $$ = new ExpMarker((const Marker *)($1));
}
| MARKER_NEQ {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_LT {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_GT {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_LE {
  $$ = new ExpMarker((const Marker *)($1));
  }
| MARKER_GE {
  $$ = new ExpMarker((const Marker *)($1));
  }
%%
