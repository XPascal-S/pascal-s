
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

/* %token char 3 */
/* %token real 4 */
/* %token int 5 */
/* %token boolean 6 */

%start ifstatement

%%

ifstatement: if expression then expression{
  ast_reduce_nodes(4, Type::IfElseStatement);
}
| if expression then expression else expression{
  ast_reduce_nodes(6, Type::IfElseStatement);
}

if : KEYWORD_IF {
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}

then: KEYWORD_THEN {
  $$ = new ExpKeyword((const Keyword *)($1));
  access_ast($$);
}

else : KEYWORD_ELSE {
    $$ = new ExpKeyword((const Keyword *)($1));
    access_ast($$);
}

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

mulop : MARKER_MUL {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
}
| MARKER_DIV {
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
  }

relop : MARKER_EQ {
    $$ = new ExpMarker((const Marker *)($1));
    access_ast($$);
  }

%%
