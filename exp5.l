%{
   /* Definition section */
  #include<stdio.h>
  #include "y.tab.h"
  extern int yylval;
%}
  
/* Rule Section */
%%
[0-9]+ {
          yylval=atoi(yytext);
          return NUMBER;
  
       }
if {return IF;}
else_if {return ELSE_IF;}
else {return ELSE;}
[a-zA-Z0-9]+ {return STRING;}
; {return SEMICOLON;}
[\t] ;

[\n] return 0;
  
  