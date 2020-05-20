

%option c++
%option yyclass="Lexer"
%option noyywrap
%option yylineno

%{
#include <pascal-s/lexer.h>
#include "gulp.h"
%}


%%
\{[^}]*\} {} /* do nothing */
\/\/.*\n {} /* do nothing */
[tT][oO]|[dD][oO]|[oO][fF]|[fF][oO][rR]|[eE][lL][sS][eE]|[iI][fF]|[tT][hH][eE][nN]|[cC][hH][aA][rR]|[bB][oO][oO][lL][eE][aA][nN]|[rR][eE][aA][lL]|[iI][nN][tT][eE][gG][eE][rR]|[aA][rR][rR][aA][yY]|[eE][nN][dD]|[bB][eE][gG][iI][nN]|[fF][uU][nN][cC][tT][iI][oO][nN]|[pP][rR][oO][cC][eE][dD][uU][rR][eE]|[vV][aA][rR]|[cC][oO][nN][sS][tT]|[pP][rR][oO][gG][rR][aA][mM] { return addKeyword(); }
[dD][iI][vV]|[mM][oO][dD]|[aA][nN][dD]|[oO][rR]|[nN][oO][tT] { return addKeyword(); }
[rR][eE][aA][dD]|[wW][rR][iI][tT][eE] {return addKeyword();}
% { return addMarker(); }
true|false { return addBoolean(); }
[\_a-zA-Z][\_a-zA-Z0-9]* { return addIdentifier(); }
[0-9]*\.[0-9]+ { return addReal(); }
[0-9]+ { return addInteger(); }
'.*' { return addChar(); }
\n { return recordNewLine(); }

\<>|\<=|>=|:=|\.\.|[()\[\]<=>,.;:+\-*/] { return addMarker(); }

%%

