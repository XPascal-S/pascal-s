out=yacc_bison.h

bison -o ${out} parser.y
sed ${out} -e "s|/// Tokens.|///yylex interface\n    virtual int yylex(void**) = 0;\n    virtual void access_ast(void*) = 0;\n    virtual Node* ast_reduce_nodes(int, Type)=0;\n    \0|g" > ${out}.tmp
mv ${out}.tmp ../../include/pascal-s/${out}
