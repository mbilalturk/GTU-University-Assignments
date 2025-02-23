/*
To run without a file: make run (terminate by entering "quit") 
To run with a file: make run_file (default file is input.g++ in makefile)
*/

%{
#include <stdio.h>
#include <string.h>

int should_exit = 0;
int start_interpreter();
%}

%%
"and"           { printf("KW_AND\n"); }
"or"            { printf("KW_OR\n"); }
"not"           { printf("KW_NOT\n"); }
"equal"         { printf("KW_EQUAL\n"); }
"less"          { printf("KW_LESS\n"); }
"nil"           { printf("KW_NIL\n"); }
"list"          { printf("KW_LIST\n"); }
"append"        { printf("KW_APPEND\n"); }
"concat"        { printf("KW_CONCAT\n"); }
"set"           { printf("KW_SET\n"); }
"deffun"        { printf("KW_DEFFUN\n"); }
"for"           { printf("KW_FOR\n"); }
"if"            { printf("KW_IF\n"); }
"exit"          { printf("KW_EXIT\n"); }
"load"          { printf("KW_LOAD\n"); }
"print"         { printf("KW_PRINT\n"); }
"true"          { printf("KW_TRUE\n"); }
"false"         { printf("KW_FALSE\n"); }

"quit"          { should_exit = 1; }

"+"             { printf("OP_PLUS\n"); }
"-"             { printf("OP_MINUS\n"); }
"/"             { printf("OP_DIV\n"); }
"*"             { printf("OP_MULT\n"); }
"("             { printf("OP_OP\n"); }
")"             { printf("OP_CP\n"); }
","             { printf("OP_COMMA\n"); }

[0-9]+f[0-9]+   { printf("VALUEF\n"); }
[0-9]+:[0-9]+   { printf("VALUEF\n"); } 
[0-9]+          { printf("VALUEI\n"); }
[0-9]+[A-Za-z][A-Za-z0-9_]*  { printf("SYNTAX_ERROR %s cannot be tokenized\n", yytext); }
[A-Za-z][A-Za-z0-9_]*  { printf("IDENTIFIER\n"); }
";;".*          { printf("COMMENT\n"); }
[\r]            ; /* Skip carriage returns */
[ \t\n]+        
.               { printf("SYNTAX_ERROR %s cannot be tokenized\n", yytext); return 0; }

%%

int yywrap() {
    return 1;
}

int start_interpreter() {
    char line[1024];
    printf("> ");
    while (fgets(line, sizeof(line), stdin)) {
        YY_BUFFER_STATE buffer = yy_scan_string(line);
        yylex();
        yy_delete_buffer(buffer);
        if(should_exit) return 0;
        printf("> ");
    }
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("Error: Could not open file %s\n", argv[1]);
            return 1;
        }
        yyin = file;
        yylex();
        fclose(file);
        
        // Start interpreter after file processing
        start_interpreter();
    } else {
        start_interpreter();
    }
    return 0;
}