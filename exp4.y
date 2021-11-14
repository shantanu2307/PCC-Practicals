%{
   /* Definition section */
  #include<stdio.h>
  int flag=0;
  int yylex();
int yyerror(char *s);
%}
  
%token NUMBER
  
%left '+' '-'
  
%left '*' '/' 
  
%left '(' ')'
  
/* Rule Section */
%%
  
exp: E{
  
         printf("\nResult=%d\n", $$);
  
         return 0;
  
        };
E : E '+' T { $$ = $1 + $3; }
| E '-' T {$$ = $1 - $3; }
| T { $$ = $1; }
;
T : T '*' F { $$ = $1 * $3; }
| T '/' F {$$ = $1/$3; }
| F { $$ = $1; }
;
F : '(' E ')' { $$ = $2; }
| NUMBER { $$ = $1; }
  
%%
  
//driver code
void main()
{
   printf("\nEnter Any Arithmetic Expression which can have operations Addition, Subtraction, Multiplication, Division and Round brackets:\n");
  
   yyparse();
   if(flag==0)
   printf("\nEntered arithmetic expression is Valid\n\n");
}
  
int yyerror(char *s)
{
   printf("\nEntered arithmetic expression is Invalid\n\n");
   flag=1;
   return 0;
}