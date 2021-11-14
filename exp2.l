%{
#include <stdio.h>
%}
%%
"if"|"then"|"else"|"for"|"while"|"struct" printf("Keyword");
^" "
^[a-zA-Z_][a-zA-Z0-9_]  printf("Valid Identifier");
^[^a - z A - Z _] printf("Invalid Identifier");
. ; 
%%
int main()
{ yylex();
}