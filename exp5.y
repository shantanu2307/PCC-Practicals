%{
   /* Definition section */
  #include<stdio.h>
  int yylex();
int yyerror(char *s);
%}
  
%token NUMBER STRING SEMICOLON IF ELSE_IF ELSE;

  
/* Rule Section */
%%
prog : stmts {printf("Valid program");};
stmts: stmt SEMICOLON stmts 
| stmt SEMICOLON| cond;
stmt: STRING
| NUMBER
;
cond : IF stmt  stmts ELIF;
ELIF : ELSE_IF  stmt stmts ELIF
    | ELSE stmts;

%%
  
//driver code
int main()
{
   printf("\nEnter the program. Only statements and consitionals are allowed\n");
  
   yyparse();
   return 0;
}
  
int yyerror(char *s)
{
   printf("\nEntered Program is Invalid\n\n");
   return 0;
}

