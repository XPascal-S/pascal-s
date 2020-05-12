

%language "c++"

%{
#define YYSTYPE void*

%}

%token NUM 5

%%

exp:
  NUM {
    printf("access integer attribute %lld\n", ((const ConstantInteger*)($1))->attr);
    $$ = new ExpConstantInteger(((const ConstantInteger*)($1)));
    access_ast($$);
  }


%%