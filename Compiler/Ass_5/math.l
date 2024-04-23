%{
#include <stdio.h>
%}

%%

[0-9]+ { printf("\nNUMBER: %s\n", yytext); }
"+" { printf("\nADD\n"); }
"-" { printf("\nSUBTRACT\n"); }
"*" { printf("\nMULTIPLY\n"); }
"/" { printf("\nDIVIDE\n"); }
"(" { printf("\nLPAREN\n"); }
")" { printf("\nRPAREN\n"); }
[ \t] ; // Ignore whitespace characters.
\n ; // Ignore newline characters.

. { printf("\nERROR: Invalid character: %s\n", yytext); }

%%

int yywrap(void) {}

int main() {
    yylex();
    return 0;
}
