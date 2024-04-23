%{ 
#include <stdio.h> 
%} 
 
%x COMMENT 
 
%% 
 
"/*"            { BEGIN(COMMENT); } 
<COMMENT>"*/"   { BEGIN(INITIAL); } 
<COMMENT>.|\n   { /* ignore */ } 
 
"//".*          { /* ignore single line comment */ } 
 
[ \t\n]+        { /* ignore whitespace */ } 
 
"if"|"else"|"for"|"while"|"do"|"int"|"float"|"char"|"double"|"return"  { printf("Keyword: %s\n", yytext); } 
 
[a-zA-Z_][a-zA-Z_0-9]*  { printf("Identifier: %s\n", yytext); } 
 
[0-9]+("."[0-9]+)?([eE][-+]?[0-9]+)?  { printf("Number: %s\n", 
yytext); } 
 
"\""([^"\\]|\\.)*"\""  { printf("String: %s\n", yytext); } 
 
'.'|"+"|"-"|"*"|"/"|"="|"=="|"!="|"<"|"<="|">"|">="|"&&"|"||"|"!"|"&"|"|"|"~"|"^"|"<<"|">>"  { printf("Operator: %s\n", yytext); } 
 
"("|")"|"{"|"}"|"["|"]"|"."|","|";"  { printf("Symbol: %s\n", yytext); } 
 
%% 
 
int main() { 
    yylex(); 
    return 0; 
} 
 
int yywrap() { 
    return 1; 
} 