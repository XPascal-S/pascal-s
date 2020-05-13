
%language "c++"

%{
#define YYSTYPE void *

%}

%token KWORD 1
%token STR 2
%token CHAR 3
%token REAL 4
%token INT 5
%token BOOL 6
%token IDENT 7
%token MARKER 8
%token NULLPTR 9
%token LEN 10

/* %token char 3 */
/* %token real 4 */
/* %token int 5 */
/* %token boolean 6 */

%start expression

%%

expression:
simple_expression relop simple_expression {
  printf("expression relop=\n");
  $$ = $1;
  ast_reduce_nodes(3, Type::ExpAssign);
}
// simple_expression relop simple_expression
// simple_expression '<' simple_expression {printf("expression relop<\n"); $$ = $1;}
// | simple_expression "<=" simple_expression {printf("expression relop<=\n"); }
// | simple_expression '=' simple_expression {printf("expression relop=\n"); $$ = $1;}
// | simple_expression "<>" simple_expression {printf("expression relop<>\n"); }
// | simple_expression '>' simple_expression {printf("expression relop>\n"); }
// | simple_expression ">=" simple_expression {printf("expression relop>=\n"); }
| simple_expression {$$ = $1;}
;

simple_expression:
simple_expression addop term {printf("simple_expression addop +\n"); ast_reduce_nodes(3, Type::BiExp); }
//simple_expression '+' term {printf("simple_expression addop +\n"); $$ = $1 ;}
// | simple_expression '-' term {printf("simple_expression addop +\n"); $$ = $1 ;}
| term {$$ = $1;}
;

term:
// term mulop factor
  term '*' factor {printf("tern mulop *"); $$ = $1;}
| term '/' factor {printf("tern mulop /"); $$ = $1;}
| factor {$$ = $1;}
;


factor:
INT {
  printf("access integer attribute value: %lld\n", ((const ConstantInteger*)($1))->attr);
  $$ = new ExpConstantInteger(((const ConstantInteger*)($1)));
  access_ast($$);
  // ast_insert_leaf_node($$);
}
| IDENT {
  printf("access identifier attribute attr: %s name: %s\n", ((const Identifier*)($1))->attr, ((const Identifier*)($1))->content);
  $$ = new Ident(((const Identifier*)($1)));
  access_ast($$);
  // ast_insert_leaf_node($$);
}

addop: MARKER {
  printf("access marker attribute %s %s\n", ((const Marker*)($1))->attr, ((const Marker*)($1))->content);
  $$ = new ExpMarker(((const Marker *)($1)));
  access_ast($$);
  // ast_insert_leaf_node($$);
}


relop: MARKER {
  printf("access marker attribute %s %s\n", ((const Marker*)($1))->attr, ((const Marker*)($1))->content);
  $$ = new ExpMarker((const Marker *)($1));
  access_ast($$);
// ast_insert_leaf_node($$);
}

%%
