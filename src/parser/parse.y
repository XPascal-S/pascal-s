%{
  #include <cstring>
  #include <>
  #define YYDEBUG 1
  extern "C" {
    void yyerror(const char *){};
    extern int yylex(void);
    extern char *yytext;
    extern int yydebug;
  }

  using namespace std;
}%

%union {
  char char_value;
  double double_value;
  int int_value;
  const char* char_ptr_value
}

%start programstruct

%token program id const num letter integer real boolean char num id not umnius
%token var array of procedure function begin end if then for to do else
%token

%type <char_ptr_value> programstruct program_head program_body idlist const_declarations const_declaration const_value var_declarations
%type <char_ptr_value> var_declaration type basic_type subprogram_declarations subprogram subprogram_head subprogram_body formal_parameter
%type <char_ptr_value> parameter_list parameter var_parameter value_parameter compound_statement statement_list statement variable_list
%type <char_ptr_value> variable expression_list procedure_call else_part expression simple_expression term factor
%type <int_value>
%type <double_value>
%type <char_value>

%%
programstruct:program_head';'program_body'.';

program_head:program id'('idlist')'
    |program id;

program_body:const_declarations
    |var_declarations
    |subprogram_declarations
    |compound_statement
    ;

idlist:idlist','id
    |id
    ;

const_declarations:const const_declaration';'
    |
    ;

const_declaration:const_declaration';'id'='const_value
    |id'='const_value
    ;

const_value:'+'num
    |'-'num
    |num
    |\'letter\'
    ;

var_declarations:
    |var var_declaration';'
    ;

var_declaration:var_declaration';'idlist':'type
    |idlist':'type
    ;

type:basic_type
    |array'['period']'of basic_type
    ;

basic_type:integer | real | boolean | char;

period:period','digits'..'digits
    | digits'..'digits
    ;

subprogram_declarations:
    |subprogram_declarations subprogram';'
    ;

subprogram:subprogram_head';'subprogram_body;

subprogram_head:procedure id formal_parameter
    |function id formal_parameter : basic_type
    ;

formal_parameter:
    |'('parameter_list')'
    ;

parameter_list:parameter_list';'parameter
    | parameter
    ;

parameter:var_parameter | value_parameter;

var_parameter: var value_parameter;

value_parameter: idlist':'basic_type;

subprogram_body:const_declarations var_declarations compound_statement;

compound_statement:begin statement_list end;

statement_list:statement_list';'statement
    | statement
    ;

statement:
| variable':='expression
| procedure_call
| compound_statement
| if expression then statement else_part
| for id assignop expression to expression do statement
| read ( variable_list )
| write ( expression_list )
;

variable_list:variable_list','variable
| variable
;

variable:id id_varpart;

id_varpart:
|'['expression_list']'
;

procedure_call:id 
| id'('expression_list')'
;

else_part:
|else statement
;

expression_list:expression_list','expression
| expression
;

expression:simple_expression relop simple_expression  //relop 关系运算符
| simple_expression
;

simple_expression:simple_expression addop term  //addop + - or
| term 
;

term:term mulop factor  //mulop *、 /、 div、 mod 和 and
| factor
;

factor:num
| variable
| id ( expression_list )
| ( expression )
| not factor
| uminus factor
;

%%

int main() {
  yydebug = 1;
  return yyparse();
}
