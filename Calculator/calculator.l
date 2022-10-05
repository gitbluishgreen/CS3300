%{";"
	#include <stdio.h>
	#include <string.h>
	#include "test.tab.h"
%}

/*Flex definitions*/
digit [0-9]
integer (0|([1-9]{digit}*))
variable [a-z]|[A-Z]
space "\t"|"\n"|"\r"|"\f"|" "
%% 

"//".* {;}
{integer}  {yylval.integer=atoi(yytext);return Integer;}
{variable} {yylval.character=yytext[0];return Variable;}
"+" {return Plus;}
"-"  {return Minus;}
"*" {return Mult;}
"/" {return Div;}
";" {return End;}
"=" {return Equal;}
{space} {;}
%%

/*C Code to start scanning
main()
{
  printf("Enter the input:\n");
  yylex();
}*/
