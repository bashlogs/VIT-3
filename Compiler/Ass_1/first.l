%{
#include <stdio.h>
int count=0;
%}
letter [a-zA-Z0-9_$]
%%
{letter} {
    count++;
}
%%
int yywrap() {
    return 1;
}
int main()
{
yylex();
printf("Count: %d",count);
return 0;
}