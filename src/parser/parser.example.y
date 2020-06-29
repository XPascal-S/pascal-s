
%language "c++"

%{
#define YYSTYPE void *
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
%token  LENGTH             10

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
%token  KEYWORD_LENGTH     0x113

//                 MARKER   =       0x200  +  type
%token  MARKER_RANGE       0x200
%token  MARKER_NEQ         0x201
%token  MARKER_LE          0x202
%token  MARKER_GE          0x203
%token  MARKER_LT          0x204
%token  MARKER_EQ          0x205
%token  MARKER_GT          0x206
%token  MARKER_ADD         0x210
%token  MARKER_SUB         0x211
%token  MARKER_MUL         0x220
%token  MARKER_DIV         0x221
%token  MARKER_LPAREN      0x230
%token  MARKER_RPAREN      0x231
%token  MARKER_LBRACKET    0x240
%token  MARKER_RBRACKET    0x241
%token  MARKER_ASSIGN      0x250
%token  MARKER_COMMA       0x251
%token  MARKER_DOT         0x252
%token  MARKER_SEMICOLON   0x253
%token  MARKER_COLON       0x254

 // TODO
%token  MARKER_AND         0xfff0
%token  MARKER_OR          0xfff1
%token  MARKER_MOD         0xfff2
%token  MARKER_QUO         0xfff3


 // TODO
%token  READ               0xffff0
%token  WRITE              0xffff1

/* %token char 3 */
/* %token real 4 */
/* %token int 5 */
/* %token boolean 6 */

 // %nonassoc IFX
 // %nonassoc ELSE

%start programstruct
 // %start statement
%%

programstruct:  program_head semicolon program_body dot {
  Program *node = reinterpret_cast<Program*> (ast_reduce_nodes(4, Type::Program));
  node->programHead = (ProgramHead*)(node->children.front());
  node->children.pop_front();
  node->children.pop_front();//pop semicolon
  node->programBody = (ProgramBody*)(node->children.front());
  node->children.pop_front();
  node->children.pop_front();//pop dot
 }
|  program_head semicolon program_body error{ printf("\n\n\n\n Missing dot\n"); yyerrok; }
|  program_head error program_body { printf("\n\n\n\nMissing semicolon\n"); yyerrok; }

;

dot: MARKER_DOT{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
;

program_head:
  program id lparen idlist rparen {
    ProgramHead *node = reinterpret_cast<ProgramHead *>(ast_reduce_nodes(5, Type::ProgramHead));
    node->programKeyword = (const ExpKeyword*)(node->children.front());
    node->children.pop_front();
    node->id = (const Ident*)(node->children.front());
    node->children.pop_front();   
    node->children.pop_front(); //pop lparen
    node->idlist = (const IdentList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();//pop rparen
  }
| program id{
  ProgramHead *node = reinterpret_cast<ProgramHead *>(ast_reduce_nodes(2, Type::ProgramHead));
  node->programKeyword = (const ExpKeyword*)(node->children.front());
  node->children.pop_front();
  node->id = (const Ident*)(node->children.front());
  node->children.pop_front();
  }

program:KEYWORD_PROGRAM{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

program_body : const_declarations var_declarations subprogram_declarations compound_statement {
  ProgramBody *node = reinterpret_cast<ProgramBody*> (ast_reduce_nodes(4, Type::ProgramBody));

  node->constdecls = (ConstDecls*)(node->children.front());
  node->children.pop_front();

  node->vardecls = (VarDecls*)(node->children.front());
  node->children.pop_front();

  node->subprogram = (SubprogramDecls*)(node->children.front());
  node->children.pop_front();

  node->compound = (CompoundStatement*)(node->children.front());
  node->children.pop_front();
}
;

idlist:
  idlist comma id  {
    IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(3, Type::IdentList));
    node->idents = (std::vector<const Identifier*>)(node->children.front()->idents);
    node->children.pop_front();
    node->children.pop_front();// pop comma
    Identifier* id = (Identifier*)(node->children.front());
    node->idents.push_back(id);
    node->children.pop_front();
  }
| id      {
    IdentList* node = reinterpret_cast<IdentList*> (ast_reduce_nodes(1, Type::IdentList));
    Identifier* id = (Identifier*)(node->children.front());
    node->idents.push_back(id);
    node->children.pop_front();
  }
;

const_declarations:
  const const_declaration semicolon {
    ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(3, Type::ConstDecls));
    node->children.pop_front();// pop const
    node->decls = node->children.front()->decls;
    node->children.pop_front();
    node->children.pop_front();// pop semicolon
  }
|                                       { $$ = new ExpVoid();  access_ast($$); }
;

const:KEYWORD_CONST{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

const_declaration:
  const_declaration semicolon id eq const_value {
    ConstDecls* node = reinterpret_cast<ConstDecls*> (ast_reduce_nodes(5, Type::ConstDecls));

    node->decls = (std::vector<ConstDecl*>)(node->children.front()->decls);
    node->children.pop_front();
    node->children.pop_front();// pop semicolon

    ConstDecl* const = new ConstDecl();
    const->ident = (Identifier*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop eq
    const->rhs = (Exp*)(node->children.front());
    node->decls.push_back(const);
    node->children.pop_front();
  }
|id eq const_value  {
    ConstDecls* node = reinterpret_cast<ConstDecl*> (ast_reduce_nodes(3, Type::ConstDecls));

    ConstDecl* const = new ConstDecl();
    const->ident = (Identifier*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop eq
    const->rhs = (Exp*)(node->children.front());
    node->children.pop_front();

    node->decls.push_back(const);
}
;

eq:MARKER_EQ {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
;

const_value:add num          {ast_reduce_nodes(2, Type::Statement);}
    |sub num             {ast_reduce_nodes(2, Type::Statement);}
    |num                {$$ = $1;}
    |char        {$$ = $1;}
    ;


num:INT {
  $$ = new ExpConstantInteger(((const ConstantInteger*)($1)));
  access_ast($$);
}
;

char:CHAR {
  $$ = new ExpConstantChar(((const ConstantChar*)($1)));
  access_ast($$);
}
;

add:MARKER_ADD {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
;

sub:MARKER_SUB {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
;

var_declarations:              { $$ = new ExpVoid();  access_ast($$); }
|var var_declaration semicolon {
    VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls));
    node->children.pop_front();// pop var
    node->decls = node->children.front()->decls;
    node->children.pop_front();
    node->children.pop_front();// pop semicolon
}
;

var_declaration:
  var_declaration semicolon idlist colon type   {
    VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(5, Type::VarDecls));

    node->decls = (std::vector<VarDecl*>)(node->children.front()->decls);
    node->children.pop_front();
    node->children.pop_front();// pop semicolon

    VarDecl* const = new VarDecl();
    const->idents = (IdentList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop colon
    const->type_spec = (TypeSpec*)(node->children.front());
    node->children.pop_front();

}
| idlist colon type                             {
    VarDecls* node = reinterpret_cast<VarDecls*> (ast_reduce_nodes(3, Type::VarDecls));

    VarDecl* const = new VarDecl();
    const->idents = (IdentList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop colon
    const->type_spec = (TypeSpec*)(node->children.front());
    node->children.pop_front();

    node->decls.push_back(const);
}
;

type:
  basic_type                               {$$ = $1;}
| array lbracket period rbracket of basic_type         {ast_reduce_nodes(6, Type::TypeSpec);}
;

array:KEYWORD_ARRAY{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

of:KEYWORD_OF{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
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
  access_ast($$);
}
;

char:KEYWORD_CHAR{
  $$ = new BasicTypeSpec((const Keyword *)($1));
  access_ast($$);
}
;

real:KEYWORD_REAL{
  $$ = new BasicTypeSpec((const Keyword *)($1));
  access_ast($$);
}
;

boolean:KEYWORD_BOOLEAN{
  $$ = new BasicTypeSpec((const Keyword *)($1));
  access_ast($$);
}
;

period: // TODO
  period comma num range num        {ast_reduce_nodes(5, Type::ArrayTypeSpec);}
| num range num                    {ast_reduce_nodes(3, Type::ArrayTypeSpec);}
;

range: MARKER_RANGE{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

subprogram_declarations:                    { $$ = new ExpVoid();  access_ast($$); }
| subprogram_declarations subprogram semicolon  {
    SubprogramDecls* node = reinterpret_cast<SubprogramDecls*> (ast_reduce_nodes(3, Type::SubprogramDecls));

    node->subprogram = (std::vector<Subprogram*>)(node->children.front()->subprogram);
    node->children.pop_front();
    
    Subprogram* sub = (Subprogram*)(node->children.front());
    node->subprogram.push_back(sub);
    node->children.pop_front();
    node->children.pop_front();// pop semicolon

    //ast_reduce_nodes(3, Type::SubprogramDecls);
}
;

subprogram:
  subprogram_head semicolon subprogram_body {
    
    Subprogram* node = reinterpret_cast<Subprogram*> (ast_reduce_nodes(3, Type::Subprogram));
    node->subhead = (SubprogramHead*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop semicolon
    node->subbody = (SubprogramBody*)(node->children.front());
    node->children.pop_front();
}
;

subprogram_head:
  procedure id formal_parameter   {
  SubprogramHead* node = reinterpret_cast<SubprogramHead*> (ast_reduce_nodes(3, Type::SubprogramHead));

   Procedure* pro = new Procedure();
   node->children.pop_front();// pop procedure
   pro->name = (Identifier*)(node->children.front());
   node->children.pop_front();
   pro->decls = (ParamList*)(node->children.front());
   node->children.pop_front();

   node->proc = pro;
}
| function id formal_parameter colon basic_type  {
    SubprogramHead* node = reinterpret_cast<SubprogramHead*> (ast_reduce_nodes(5, Type::SubprogramHead));

    FunctionDecl* func = new FunctionDecl();
    node->children.pop_front();// pop function
    func->name = (Identifier*)(node->children.front());
    node->children.pop_front();
    func->decls = (ParamList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();//pop colon
    func->basic = (BasicTypeSpec*)(node->children.front());
    node->children.pop_front();

    node->func = func;
}
;

procedure:KEYWORD_PROCEDURE{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

function:KEYWORD_FUNCTION{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

formal_parameter:               { $$ = new ExpVoid();  access_ast($$);  }
|lparen parameter_list rparen       {
    ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList));
    node->children.pop_front();//pop lparen
    node->params = (std::vector<ParamSpec*>)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();//pop rparen
    //ast_reduce_nodes(3, Type::ParamList);
}
;

parameter_list:
  parameter_list semicolon parameter   {
    ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(3, Type::ParamList));
    node->params = (std::vector<ParamSpec*>)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop semicolon
    
    ParamSpec* param = (ParamSpec*)(node->children.front());
    node->children.pop_front();
    node->params.push_back(param);

  }
| parameter                     {
    ParamList* node =  reinterpret_cast<ParamList*> (ast_reduce_nodes(1, Type::ParamList));
    ParamSpec* param = (ParamSpec*)(node->children.front());
    node->children.pop_front();
    node->params.push_back(param);
    //$$ = $1;
}
;


parameter:
  var idlist colon basic_type         {
    ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(4, Type::ParamSpec));

    node->keyword_var = (const Keyword*)(node->children.front());
    node->children.pop_front();
    node->id_list = (IdentList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop colon
    node->spec = (TypeSpec*)(node->children.front());
    node->children.pop_front();
}
| idlist colon basic_type       {
    ParamSpec* node = reinterpret_cast<ParamSpec*> (ast_reduce_nodes(3, Type::ParamSpec));

    node->id_list = (IdentList*)(node->children.front());
    node->children.pop_front();
    node->children.pop_front();// pop colon
    node->spec = (TypeSpec*)(node->children.front());
    node->children.pop_front();
}
;


var:KEYWORD_VAR{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;


colon: MARKER_COLON{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

subprogram_body:
const_declarations var_declarations compound_statement  {
    SubprogramBody* node = reinterpret_cast<SubprogramBody*> (ast_reduce_nodes(3, Type::SubprogramBody));

    node->constdecls = (ConstDecls*)(node->children.front());
    node->children.pop_front();

    node->vardecls = (VarDecls*)(node->children.front());
    node->children.pop_front();

    node->compound = (CompoundStatement*)(node->children.front());
    node->children.pop_front();

    //ast_reduce_nodes(3, Type::Statement);
}
;

compound_statement:             { $$ = new ExpVoid();  access_ast($$);  }
begin statement_list end         {
    CompoundStatement* node = reinterpret_cast<CompoundStatement*> (ast_reduce_nodes(3, Type::CompoundStatement));
    node->children.pop_front();//pop begin

    StatementList* state = (StatementList*)(node->children.front());
    node->state = state;

    node->children.pop_front();
    node->children.pop_front();//pop end
    //ast_reduce_nodes(3, Type::Statement);
}
;

begin:KEYWORD_BEGIN{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

end:KEYWORD_END{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

statement_list:
  statement_list semicolon statement     {
    StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(3, Type::StatementList));

    node->statement = (std::vector<Statement*>)(node->children.front()->statement);
    node->children.pop_front();
    
    node->children.pop_front();// pop semicolon

    Statement* sta = (Statement*)(node->children.front());
    node->statement.push_back(sta);
    node->children.pop_front();
    
    //ast_reduce_nodes(3, Type::Statement);
}
| statement                              {
    StatementList* node = reinterpret_cast<StatementList*> (ast_reduce_nodes(1, Type::StatementList));

    Statement* sta = (Statement*)(node->children.front());
    node->statement.push_back(sta);
    node->children.pop_front();
}
;

semicolon: MARKER_SEMICOLON{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

statement:                                          {$$ = new ExpVoid();  access_ast($$);} //TODO
| variable assign expression                        {ast_reduce_nodes(3, Type::Statement);}
| procedure_call                                    {$$ = $1;}
| compound_statement                                {$$ = $1;}
| if expression then statement else_part            {ast_reduce_nodes(5, Type::IfElseStatement);}
// if expression then statement else statement            {ast_reduce_nodes(5, Type::IfElseStatement);}
| for id assign expression to expression do statement {ast_reduce_nodes(8, Type::ForStatement);}
| READ lparen variable_list rparen                   {}
| WRITE lparen expression_list rparen                {}
;

for:KEYWORD_FOR{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

to:KEYWORD_TO{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

do:KEYWORD_DO{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

assign: MARKER_ASSIGN{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

else_part:           { $$ = new ExpVoid();  access_ast($$);  }/*empty*/
  else statement    { //TODO
  ast_reduce_nodes(2, Type::IfElseStatement);
}
;

if : KEYWORD_IF {
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

then: KEYWORD_THEN {
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

else : KEYWORD_ELSE {
    $$ = new ExpKeyword((const Keyword *)($1));
    access_ast($$);
}
;

variable_list:
  variable_list comma variable  {
    VariableList* node = reinterpret_cast<VariableList*> (ast_reduce_nodes(3, Type::VariableList));

    node->params = (std::vector<Variable*>)(node->children.front()->params);
    node->children.pop_front();
    
    node->children.pop_front();// pop comma

    Variable* var = (Variable*)(node->children.front());
    node->params.push_back(var);
    node->children.pop_front();

    printf("variable_list\n"); 
}
| variable      {
    VariableList* node = reinterpret_cast<VariableList*> (ast_reduce_nodes(1, Type::VariableList));

    Variable* var = (Variable*)(node->children.front());
    node->params.push_back(var);
    node->children.pop_front();

}
;

variable:
  id id_varpart  {
    Variable* node = reinterpret_cast<Variable*> (ast_reduce_nodes(2, Type::Variable));
    node->id = (Identifier*)(node->children.front());
    node->children.pop_front();
    node->id_var = (ExpressionList*)(node->children.front());
    node->children.pop_front();
    printf("access ID attribute value: %s\n", ((const Identifier*)($1))->attr);
}
;

id_varpart:           { $$ = new ExpVoid();  access_ast($$);  }      /*empty*/
| lbracket expression_list rbracket {
    ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList));
    node->children.pop_front();//pop lbracket

    node->explist = (std::vector<Exp*>)(node->children.front()->explist);
    node->children.pop_front();

    node->children.pop_front();//pop rbracket
    ast_reduce_nodes(3,Type::Statement);
  }
;

lbracket: MARKER_LBRACKET{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

rbracket: MARKER_RBRACKET{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

procedure_call:    //TODO
 id          {
    printf("access ID attribute value: %s\n", ((const Identifier*)($1))->attr);
    ast_reduce_nodes(1,Type::ExpCall);
  }
| id lparen expression_list rparen    {
    printf("access ID attribute value: %s\n", ((const Identifier*)($1))->attr);
    ast_reduce_nodes(4,Type::ExpCall);
  }
;

lparen: MARKER_LPAREN{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

rparen: MARKER_RPAREN{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

id: IDENT{
    $$ = new Ident((const Identifier *)($1));
    access_ast($$);
}

expression_list:
  expression_list comma expression {
    ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(3, Type::ExpressionList));

    node->explist = (std::vector<Exp*>)(node->children.front()->explist);
    node->children.pop_front();
    
    node->children.pop_front();// pop comma

    Exp* exp = (Exp*)(node->children.front());
    node->params.push_back(exp);
    node->children.pop_front();

    printf("expression list , expression\n");
}
| expression        {
    ExpressionList* node = reinterpret_cast<ExpressionList*> (ast_reduce_nodes(1, Type::ExpressionList));

    Exp* exp = (Exp*)(node->children.front());
    node->explist.push_back(exp);
    node->children.pop_front();
}
;

comma : MARKER_COMMA {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
}
;

expression : simple_expression relop simple_expression {
  ast_reduce_nodes(3, Type::ExpAssign);
}
// simple_expression relop simple_expression
// simple_expression '<' simple_expression {printf("expression relop<\n"); $$ = $1;}
// | simple_expression "<=" simple_expression {printf("expression relop<=\n"); }
// | simple_expression '=' simple_expression {printf("expression relop=\n"); $$ = $1;}
// | simple_expression "<>" simple_expression {printf("expression relop<>\n"); }
// | simple_expression '>' simple_expression {printf("expression relop>\n"); }
// | simple_expression ">=" simple_expression {printf("expression relop>=\n"); }
| simple_expression { }
;

simple_expression:
simple_expression addop term {ast_reduce_nodes(3, Type::BiExp); }
| term {$$ = $1;}
;

term : term mulop factor{ast_reduce_nodes(3, Type::BiExp);}
| factor {  };

factor:
INT {
  $$ = new ExpConstantInteger(((const ConstantInteger*)($1)));
  access_ast($$);
}
| IDENT {
  $$ = new Ident(((const Identifier*)($1)));
  access_ast($$);
}

addop : MARKER_ADD {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
| MARKER_SUB {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
| MARKER_OR{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}


mulop : MARKER_MUL {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
| MARKER_DIV {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
  }
| MARKER_MOD {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
  }
| MARKER_AND {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
  }

relop : MARKER_EQ {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
| MARKER_NEQ {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
| MARKER_LT {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
| MARKER_GT {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
| MARKER_LE {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
| MARKER_GE {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
%%
