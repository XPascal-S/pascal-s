out=parser.example.h

bison -o ${out} parser.example.y
sed ${out} -e "s|/// Tokens.|///yylex interface\n    virtual int yylex(void**) = 0;\n    virtual void access_ast(void*) = 0;\n    \0|g" > ${out}.tmp
mv ${out}.tmp ${out}
