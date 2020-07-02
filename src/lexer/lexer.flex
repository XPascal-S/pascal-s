

%option c++
%option yyclass="Lexer"
%option noyywrap
%option yylineno

%{
#include <pascal-s/lexer.h>
#include "gulp.h"
%}


%%
\n { return recordNewLine(); }
\{[^}]*\} {} /* do nothing */
\/\/.*\n {} /* do nothing */
(?i:to|do|of|for|else|if|then|char|boolean|real|integer|array|end|begin|function|procedure|var|const|program|read|write) { return addKeyword(); }
(?i:div|mod|and|or|not) { return addMarker(); }
\<>|\<=|>=|:=|\.\.|[()\[\]<=>,.;:+\-*/] { return addMarker(); }
% { return addMarker(); }
true|false { return addBoolean(); }
[\_a-zA-Z][\_a-zA-Z0-9]* { return addIdentifier(); }
[0-9]*\.[0-9]+ { return addReal(); }
[0-9]+ { return addInteger(); }
'.*' { return addChar(); }

[\_a-zA-Z0-9]* { return skipErrorString("lexical error: identifier started with number is not allow"); }
[^[:space:]] { return skipErrorString("lexical error: unknown character in input stream"); }
[[:space:]] {} /* do nothing */

%%

