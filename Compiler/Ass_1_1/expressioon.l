%{ 
#include <stdio.h> 
int identifierCount = 0; 
%} 
letter [a-zA-Z] 
digit [0-9] 
identifier ({letter}|_)({letter}|{digit}|_)* 
 
%% 
{identifier} { 
printf("Identifier found: %s\n", yytext); 
identifierCount++; 
} 
. ;  
%% 
int yywrap(void) { 
} 
int main() { 
yylex(); 
printf("Total number of identifiers: %d\n", identifierCount); 
return 0; 
} 