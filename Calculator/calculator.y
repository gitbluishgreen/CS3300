%{
	#include <stdio.h>
	#include <string.h>
	int yyerror (char* h);
	int yylex(void) ;
	int value[26];

%}
%union
{
    int integer;
	char character;
}
%start goal ;
%type <integer> goal expression term Factor Integer
%type <character> Variable
%token Integer Plus Minus Mult Div End Variable Equal
%%
goal : goal expression End
{
	printf("%d\n",$2);
} 
	| goal Variable Equal expression End
{
	value[$2- 'a'] = $4;
}
	| expression End
{
    $$ = $1;
	printf("%d\n",$$);
    
}
	| Variable Equal expression End
{
	value[$1 - 'a'] = $3;
};

expression : expression Plus term 
{ 
    $$ = $1 + $3;
}
    | expression Minus term
{ 
    $$ = $1 - $3;
}
    | term
{ 
    $$ = $1;
};

term : term Mult Factor
{
	$$ = $1 * $3;
}
	| term Div Factor
{
	$$ = $1 / $3;
}
	| Factor
{
	$$ = $1;
};

Factor: Integer
{ 
	$$ = $1;
}
	| Variable
{
	$$ = value[$1 - 'a'];
}
	| Minus Integer
{
	$$ = -1 * $2;
}
	| Plus Integer
{
	$$ = $2;
}
	| Minus Variable
{
	$$ = -1* value[$2 - 'a'];
}
	| Plus Variable
{
	$$ = value[$2 - 'a'];
};
%%

int yyerror(char *s)
{
	printf ("%s ERROR\n",s);
	return 0;
  
}
int main ()
{
	yyparse();
	return 0;
}
