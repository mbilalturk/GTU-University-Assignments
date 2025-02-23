%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern FILE* yyin;
extern int yylex(void);
extern int yyparse(void);
extern char* yytext;

void yyerror(const char *s);

#define MAX_LIST_SIZE 100
#define MAX_FUNCTIONS 50

// Fraction structure
typedef struct {
    int numerator;
    int denominator;
} Fraction;

void print_prompt() {
    printf("> ");
    fflush(stdout);
}

%}

%union {
    struct {
        int numerator;
        int denominator;
    } frac;
    char identifier[256];
    struct {
        int list_index;
    } list;
}

%token KW_AND KW_OR KW_NOT KW_EQUAL KW_LESS KW_NIL KW_LIST KW_APPEND
%token KW_CONCAT KW_SET KW_DEFFUN KW_FOR KW_IF KW_EXIT KW_LOAD KW_PRINT
%token KW_TRUE KW_FALSE
%token OP_PLUS OP_MINUS OP_DIV OP_MULT OP_OP OP_CP OP_COMMA OP_QUOTE
%token VALUEF VALUEI IDENTIFIER COMMENT

%type <frac> expression number
%type <identifier> IDENTIFIER

%%

start:
    | start line    { print_prompt(); }
    ;

line:
    expression              { printf("%d/%d\n", $1.numerator, $1.denominator); }
    | COMMENT
    | OP_OP KW_EXIT OP_CP  { printf("Goodbye!\n"); exit(0); }
    | error '\n'           { yyerrok; }
    ;

/* Basic expressions */
expression:
    number                              { $$ = $1; }
    | OP_OP OP_PLUS expression expression OP_CP {
        $$.numerator = $3.numerator * $4.denominator + $4.numerator * $3.denominator;
        $$.denominator = $3.denominator * $4.denominator;
    }
    | OP_OP OP_MINUS expression expression OP_CP {
        $$.numerator = $3.numerator * $4.denominator - $4.numerator * $3.denominator;
        $$.denominator = $3.denominator * $4.denominator;
    }
    | OP_OP OP_MULT expression expression OP_CP {
        $$.numerator = $3.numerator * $4.numerator;
        $$.denominator = $3.denominator * $4.denominator;
    }
    | OP_OP OP_DIV expression expression OP_CP {
        if ($4.numerator == 0) {
            yyerror("Division by zero");
            $$.numerator = 0;
            $$.denominator = 1;
        } else {
            $$.numerator = $3.numerator * $4.denominator;
            $$.denominator = $3.denominator * $4.numerator;
        }
    }
    | OP_OP KW_AND expression expression OP_CP {
        $$.numerator = ($3.numerator != 0 && $4.numerator != 0);
        $$.denominator = 1;
    }
    | OP_OP KW_OR expression expression OP_CP {
        $$.numerator = ($3.numerator != 0 || $4.numerator != 0);
        $$.denominator = 1;
    }
    | OP_OP KW_NOT expression OP_CP {
        $$.numerator = ($3.numerator == 0);
        $$.denominator = 1;
    }
    | OP_OP KW_IF expression expression expression OP_CP {
        $$ = ($3.numerator != 0) ? $4 : $5;
    }
    | OP_OP KW_EQUAL expression expression OP_CP {
        $$.numerator = ($3.numerator * $4.denominator == $4.numerator * $3.denominator);
        $$.denominator = 1;
    }
    | OP_OP KW_LESS expression expression OP_CP {
        $$.numerator = ($3.numerator * $4.denominator < $4.numerator * $3.denominator);
        $$.denominator = 1;
    }
    | KW_TRUE {
        $$.numerator = 1;
        $$.denominator = 1;
    }
    | KW_FALSE {
        $$.numerator = 0;
        $$.denominator = 1;
    }
    | KW_NIL {
        $$.numerator = 0;
        $$.denominator = 1;
    }
    ;

number:
    VALUEI  { $$ = yylval.frac; }
    | VALUEF { $$ = yylval.frac; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "SYNTAX_ERROR: %s\n", s);
}

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILE *file = fopen(argv[1], "r");
        if (!file) {
            printf("Cannot open file: %s\n", argv[1]);
            return 1;
        }
        yyin = file;
        printf("$ g++ %s\n", argv[1]);
    } else {
        printf("$ g++\n");
    }
    
    print_prompt();
    yyparse();
    
    return 0;
}