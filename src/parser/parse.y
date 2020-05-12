%{
  #include <cstring>
  #include <string>
  #include <iostream>
  #include <pascal-s/AST.h>
  #define YYDEBUG 1
  extern "C" {
    void yyerror(const char *){};
    extern int yylex(void);
    extern char *yytext;
    extern int yydebug;
  }

  string string_const(string temp) {
	string ans;
	ans += "const ";
	string name;
	string value;
	int flag = 0;
	int flag2 = 0;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] == '=') {
			flag = 1;
		}
		else if (temp[i] == '\'') {
			if (!flag2)
				ans += "char ";
			flag2 = 1;
			value += '\'';
		}
		else if (temp[i] == '.') {
			ans += "double ";
			flag2 = 1;
			value += '.';
		}
		else if (temp[i] == ';') {
			if (!flag2)
				ans += "int";
			flag2 = 0;
			ans += name;
			name.clear();
			ans += " = ";
			ans += value;
			value.clear();
			ans += ";\nconst ";
			flag = 0;
		}
		else {
			if (!flag)
				name += temp[i];
			else
				value += temp[i];
		}
	}
	if (!flag2)
		ans += "int";
	ans += name;
	ans += " = ";
	ans += value;
	ans += ";\n";
	return ans;
  }

  string string_var(string temp) {
	string ans;;
	string name;
	string type;
	int flag = 0;
	int flag2 = 0;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] == ':') {
			flag = 1;
		}
		else if (temp[i] == ';') {
			ans += type;
			ans += " ";
			ans += name;
			ans += ";\n";
			type.clear();
			name.clear();
			flag = 0;
		}
		else {
			if (!flag)
				name += temp[i];
			else
				type += temp[i];
		}
	}
	ans += type;
	ans += " ";
	ans += name;
	ans += ";\n";
	return ans;
  }

  string string_canshu(string temp) {
	string ans;
	string name;
	string type;
	int flag = 0;
	int flag2 = 0;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] == ':') {
			flag = 1;
		}
		else {
			if (!flag)
				name += temp[i];
			else
				type += temp[i];
		}
	}
	ans += type;
	ans += " ";
	for (int j = 0; j < name.length(); j++) {
		if (name[j] != ',')
			ans += name[j];
		else {
			ans += ", " + type + " ";
		}
	}
	return ans;
  }
  
  string string_shuzu(string temp) {
	string ans;
	for (int i = 0; i < temp.length(); i++) {
		if (temp[i] != ',') {
			ans += temp[i];
		}
		else {
			ans += "][";
		}
	}
	return ans;
  }

  using namespace std;

%}

%start programstruct

%token <string> program const letter integer real boolean char num id not umnius
%token <string> var array of procedure function begin end if then for to do else
//%token <string> num id

%type <string> programstruct program_head program_body idlist const_declarations const_declaration const_value var_declarations
%type <string> var_declaration type basic_type subprogram_declarations subprogram subprogram_head subprogram_body formal_parameter
%type <string> parameter_list parameter var_parameter value_parameter compound_statement statement_list statement variable_list
%type <string> variable expression_list procedure_call else_part expression simple_expression term factor period id_varpart
// %type <string>

%%
programstruct:program_head ';' program_body '.' {printf("%s{\n%s}\n",$1,$3);}
    ;

program_head:program id '(' idlist ')'  {$$ = "int main("+$4+")";}
    |program id                      {$$ = "int main()";}
    ;

program_body:const_declarations var_declarations subprogram_declarations compound_statement  {$$ = $1+$2+$3+$4;}
    ;

idlist:idlist ',' id  {$$ = $1+","+$3;}
    |id             {$$ = $1;}
    ;

const_declarations:const const_declaration ';'{$$ = $2 + ";\n";}
    |                                       {$$ = "";} 
    ;

const_declaration:const_declaration ';' id '=' const_value  {string temp = $1 + ";" + $3 + "=" + $5;
                                                             $$ = string_const(temp);}
    |id'='const_value           {$$ = $1+"="+$3;}
    ;

const_value:'+'num          {$$ = $2;}
    |'-'num             {$$ = "-"+$2;}
    |num                {$$ = $1;}
    |'\''letter'\''        {$$ = $2;}
    ;

var_declarations:              {$$ = "";} 
    |var var_declaration';'{$$ = $2+";\n";}
    ;

var_declaration:var_declaration ';' idlist ':' type   {string temp = $1+$5+" "+$3+";";
                                                        $$ = string_var(temp);}
    |idlist':'type                      {$$ = $3 + " " + $1 + ";";}
    ;

type:basic_type                             {$$ = $1;}
    |array '[' period ']' of basic_type         {$$ = $6+$3;}
    ;

basic_type:integer  {$$ = "int";}
    | real          {$$ = "double";}
    | boolean       {$$ = "bool";}
    | char          {$$ = "char";}
    ; 

period:period ',' num '..' num        {$$ = $1+","+$3+".."+$5;}
    | num '..' num                    {$$ = $1+".."+$3;}
    ;

subprogram_declarations:                    {$$ = "";} 
    |subprogram_declarations subprogram';'  {$$ = $1 + $2 + ";\n";} 
    ;

subprogram:subprogram_head ';' subprogram_body {$$ = $1+";"+$3+"\n";}
    ;

subprogram_head:procedure id formal_parameter   {$$ = "void "+$2+$3;}
    |function id formal_parameter ':' basic_type  {$$ = $5 + $2 + $3;}
    ;

formal_parameter:               {$$ = "";} 
    |'('parameter_list')'       {$$ = "("+$2+")";} 
    ;

parameter_list:parameter_list';'parameter   {$$ = $1 + "," +$3;}
    | parameter                     {$$ = $1;}
    ;

parameter:var_parameter         {$$ = $1;}
    | value_parameter           {$$ = $1;}
    ;

var_parameter: var value_parameter      {$$ = $2;}
    ;     

value_parameter: idlist':'basic_type            {string temp = $3+" "+$1;
                                                  $$ = string_canshu(temp);}
    ;   

subprogram_body:const_declarations var_declarations compound_statement  {$$ = $1+$2+$3;}
    ;

compound_statement:begin statement_list end         {$$ = "{\n"+$2+"}\n";}
    ;

statement_list:statement_list ';' statement           {$$ = $1+$3+";\n"}
    | statement                                       {$$ = $1+";\n"}
    ;

statement:
| variable ":=" expression                          {$$ = $1+" = "+$3;}
| procedure_call                                    {$$ = $1;}
| compound_statement                                {$$ = $1;}
| if expression then statement else_part            {$$ = "if("+$2+"){"+$4+"}\n"+$5;}
| for id ":=" expression to expression do statement {$$ = "for("+$2+"="+$4+";"+$2+"<="+$6+";"+$2+"++){\n"+$8+"}\n";}
| read '(' variable_list ')'
| write '(' expression_list ')'
;

variable_list:variable_list','variable         {$$ = $1+","+$3;}
| variable                                  {$$ = $1;}
;

variable:id id_varpart  {$$ = $1+$2;}
;

id_varpart:                 {$$ = "";} 
|'['expression_list']'      {string temp = "["+$2+"]";
                             $$ = string_shuzu(temp);}
;

procedure_call:id           {$$ = $1+"()"}
| id'('expression_list')'    {$$ = $1+"("+$3+")";}
;

else_part:                      {$$ = "";} 
|else statement                 {$$ = "else{"+$2+"}\n";} 
;

expression_list:expression_list','expression    {$$ = $1+","+$3;}
| expression                                {$$ = $1;}
;

expression:simple_expression relop simple_expression  //relop ��ϵ����� {$$ = $1+$2+$3;}
| simple_expression                                     {$$ = $1;}
;

simple_expression:simple_expression addop term  //addop + - or          {$$ = $1+$2+$3;}
| term                                                              {$$ = $1;}
;

term:term mulop factor  //mulop *�� /�� div�� mod �� and   {$$ = $1+$2+$3;}
| factor                                                   {$$ = $1;}
;

factor:num                                      {$$ = $1;}
| variable                                      {$$ = $1;}
| id '(' expression_list ')'                        {$$ = $1+"("+$3+")";}
| '(' expression ')'                               {$$ = "("+$2+")";}
| "not" factor                                    {$$ = "!"+$2;}
| '-' factor                                 {$$ = "-"+$2;}
;

%%

int main() {
  yydebug = 1;
  return yyparse();
}
