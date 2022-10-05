%{";"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "P1.tab.h"
%}

/*Flex definitions*/
digit [0-9]
integer (0|([1-9]{digit}*))
identifier [a-zA-Z_][0-9a-zA-Z_]*
space "\t"|"\n"|"\r"|"\f"|" "
%% 

"//".* {;}//ignores any comments present in the program. Multiline comments need to be ignored as well.
{integer}  {yylval.integer=atoi(yytext);return Integer;}
"+" {return Plus;}
"-"  {return Minus;}
"*" {return Mult;}
"/" {return Div;}
"%" {return Modulo;}
";" {return Semicolon;}
"=" {return Equal;}
"==" {return DoubleEqual;}
"!=" {return NotEqual;}
">" {return GreaterThan;}
"<" {return LessThan;}
">=" {return GreaterEqual;}
"<=" {return LessEqual;}
"!" {return Not;}
"{" {return OpeningBrace;}
"}" {return ClosingBrace;}
"[" {return OpeningSquareBracket;}
"]" {return ClosingSquareBracket;}
"(" {return OpeningBracket;}
")" {return ClosingBracket;}
"." {return Dot;}
"," {return Comma;}
"&&" {return And;}
"||" {return Or;}
"class" {return Class;}
"while" {return While;}
"if" {return If;}
"else" {return Else;}
"new" {return New;}
"true" {return True;}
"false" {return False;}
"length" {return Length;}
"#" {return Hashtag;}
"define" {return Define;}
"extends" {return Extends;}
"System" {return System;}
"out" {return Out;}
"print" {return Print;}
"println" {return Println;}
"public" {return Public;}
"private" {return Private;}
"protected" {return Protected;}
"void" {return Void;}
"boolean" {return Bool;}
"static" {return Static;}
"String" {return String;}
"this" {return This;}
"main" {return Main;}
"return" {return Return;}
"int" {return Int;}
{identifier} {yylval.string = (char*)malloc(strlen(yytext)+1); strcpy(yylval.string,yytext);return Identifier;}
{space} {;}
%%
