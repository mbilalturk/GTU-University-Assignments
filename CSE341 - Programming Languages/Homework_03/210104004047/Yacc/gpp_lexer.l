%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gpp_interpreter.tab.h"

extern YYSTYPE yylval;
%}

%%
"and"           { return KW_AND; }
"or"            { return KW_OR; }
"not"           { return KW_NOT; }
"equal"         { return KW_EQUAL; }
"less"          { return KW_LESS; }
"nil"           { return KW_NIL; }
"list"          { return KW_LIST; }
"append"        { return KW_APPEND; }
"concat"        { return KW_CONCAT; }
"set"           { return KW_SET; }
"deffun"        { return KW_DEFFUN; }
"for"           { return KW_FOR; }
"if"            { return KW_IF; }
"exit"          { return KW_EXIT; }
"load"          { return KW_LOAD; }
"print"         { return KW_PRINT; }
"true"          { return KW_TRUE; }
"false"         { return KW_FALSE; }

"+"             { return OP_PLUS; }
"-"             { return OP_MINUS; }
"/"             { return OP_DIV; }
"*"             { return OP_MULT; }
"("             { return OP_OP; }
")"             { return OP_CP; }
","             { return OP_COMMA; }

[0-9]+          { 
    yylval.frac.numerator = atoi(yytext); 
    yylval.frac.denominator = 1;
    return VALUEI; 
}

[0-9]+:[0-9]+   { 
    sscanf(yytext, "%d:%d", &yylval.frac.numerator, &yylval.frac.denominator);
    return VALUEF; 
}

[A-Za-z][A-Za-z0-9_]*  { 
    strncpy(yylval.identifier, yytext, 255);
    yylval.identifier[255] = '\0';
    return IDENTIFIER; 
}

";;".*          { return COMMENT; }
[ \t\n\r]       ; /* Skip whitespace */
.               { printf("Invalid character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}