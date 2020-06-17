
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

programstruct: program_head semicolon program_body dot {
  ast_reduce_nodes(4, Type::Program);
 }
;

dot: MARKER_DOT{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
;

program_head:
  program id lparen idlist rparen {
    ast_reduce_nodes(5, Type::ProgramHead);
  }
| program id{
  ProgramHead *node = reinterpret_cast<ProgramHead *>(ast_reduce_nodes(2, Type::ProgramHead));
  node->programKeyword = (const ExpKeyword*)(node->children.front());
  node->children.pop_front();
  node->id = (const Ident*)(node->children.front());
  node->children.pop_front();
  }
;

program:KEYWORD_PROGRAM{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

program_body : const_declarations var_declarations subprogram_declarations compound_statement {
  ast_reduce_nodes(4, Type::Program);
}
;

idlist:
  idlist comma id  {ast_reduce_nodes(3, Type::IdentList);}
| id             {$$ = $1;}
;

const_declarations:
  const const_declaration semicolon {ast_reduce_nodes(3, Type::ConstDecls);}
|                                       { $$ = new ExpVoid();  access_ast($$); }
;

const:KEYWORD_CONST{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

const_declaration:
  const_declaration semicolon id eq const_value {ast_reduce_nodes(5, Type::ConstDecls);}
|id eq const_value           {ast_reduce_nodes(3, Type::ConstDecl);}
;

eq:MARKER_EQ {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }
;

const_value:add num          {ast_reduce_nodes(2, Type::Statement);}
    |sub num             {ast_reduce_nodes(2, Type::Statement);}
    |num                {$$ = $1;}
    |quo char quo        {ast_reduce_nodes(3, Type::Statement);}
    ;

quo:MARKER_QUO {                   // to do!!!!!!
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
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
|var var_declaration semicolon {ast_reduce_nodes(3, Type::VarDecls);}
;

var_declaration:
  var_declaration semicolon idlist colon type   {ast_reduce_nodes(5, Type::VarDecls);}
| idlist colon type                             {ast_reduce_nodes(3, Type::VarDecls);}
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

period:
  period comma num range num        {ast_reduce_nodes(5, Type::ArrayTypeSpec);}
| num range num                    {ast_reduce_nodes(3, Type::ArrayTypeSpec);}
;

range: MARKER_RANGE{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

subprogram_declarations:                    { $$ = new ExpVoid();  access_ast($$); }
| subprogram_declarations subprogram semicolon  {ast_reduce_nodes(3, Type::Program);}
;

subprogram:
  subprogram_head semicolon subprogram_body {ast_reduce_nodes(3, Type::Program);}
;

subprogram_head:
  procedure id formal_parameter   {ast_reduce_nodes(3, Type::Procedure );}
| function id formal_parameter colon basic_type  {ast_reduce_nodes(5, Type::FunctionDecl);}
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
|lparen parameter_list rparen       {ast_reduce_nodes(3, Type::ParamList);}
;

parameter_list:
  parameter_list semicolon parameter   {ast_reduce_nodes(2, Type::ParamList);}
| parameter                     {$$ = $1;}
;

parameter:
  var_parameter         {$$ = $1;}
| value_parameter       {$$ = $1;}
;

var_parameter:
  var value_parameter  {
   ast_reduce_nodes(2, Type::VarDecl);
}
;

var:KEYWORD_VAR{
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}
;

value_parameter:
  idlist colon basic_type       {
    ast_reduce_nodes(3, Type::VarDecl);
}
;

colon: MARKER_COLON{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

subprogram_body:
const_declarations var_declarations compound_statement  {ast_reduce_nodes(3, Type::Statement);}
;

compound_statement:
begin statement_list end         {ast_reduce_nodes(3, Type::Statement);}
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
  statement_list semicolon statement     {ast_reduce_nodes(3, Type::Statement);}
| statement                              {$$ = $1;}
;

semicolon: MARKER_SEMICOLON{
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}

statement:                                          {$$ = new ExpVoid();  access_ast($$);}
| variable assign expression                        {ast_reduce_nodes(3, Type::Statement);}
| procedure_call                                    {$$ = $1;}
| compound_statement                                {$$ = $1;}
  if expression then statement else_part            {ast_reduce_nodes(5, Type::IfElseStatement);}
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

else_part:           /*empty*/
  else statement    {
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

variable_list: variable_list comma variable  {printf("variable_list\n"); ast_reduce_nodes(3, Type::Statement);}
| variable                                {$$ = $1;}
;

variable:
  id id_varpart  {
  printf("access ID attribute value: %s\n", ((const Identifier*)($1))->attr);
  ast_reduce_nodes(2,Type::Statement);
}
;

id_varpart:                 /*empty*/
| lbracket expression_list rbracket {
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

procedure_call:
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
    printf("expression list , expression\n");
    ast_reduce_nodes(3, Type::Exp);
}
| expression                   {$$ = $1;}
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
