%{
	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	int yyerror (char* h);
	int yylex(void);
	typedef struct node node;
	typedef struct list list;
	typedef struct tablenode tablenode;
	typedef struct listnode listnode;
	typedef struct table table;
	typedef struct listoflist listoflist;
	struct node
	{
		char* val;//helps store expressions etc
		node* next;
	};
	struct list
	{
		node* head;
		node* tail;
	};
	struct tablenode
	{	
		char* id;//macro name
		int args;//how many arguments?
		list* statements;//what are the tokens of the macro definition?
		list* variables;//what are the variable names in the macro definition?
		struct tablenode* next;
	};
	struct table
	{
		tablenode* head;
		tablenode* tail;
	};
	struct listnode
	{
		list* val;
		struct listnode* next;
	};
	struct listoflist
	{
		listnode* head;
		listnode* tail;
	};
	char* itoa(int x)
	{
		int t = x;
		int cnt = 0;
		do
		{
			cnt++;
			t /= 10;
		}
		while(t != 0);
		char* arr = malloc(sizeof(char) * (cnt+1));
		t = x;
		int temp = 0;
		do
		{
			temp++;
			int r = t % 10;
			t /= 10;
			arr[cnt-temp] = (48+r);
		}while(t != 0);
		arr[cnt] = '\0';
		return arr;
	}
	void insertIntoList(list* l,char* v)
	{
		if(l->head == NULL)
		{
			l->head = (node*)malloc(sizeof(node));
			l->head->val = v;
			l->tail = l->head;
		}
		else
		{
			node* t = (node*)malloc(sizeof(node));
			t->val = v;
			l->tail->next = t;
			l->tail = t;
		}
	}
	void printListLine(list* l)
	{
		if(l == NULL)
			return;
		node* x = l->head;
		while(x != NULL)
		{
			printf("%s\n",x->val);
			x =x->next;
		}
		return;
	}
	void printListSpace(list* l)
	{
		if(l == NULL)
			return;
		node* x = l->head;
		while(x != NULL)
		{
			printf("%s ",x->val);
			x =x->next;
		}
		return;
	}
	void appendList(list* l1,list* l2)//Please change syntax elsewhere!
	{
		if(l1->head == NULL)
		{
			l1->head = l2->head;
			l1->tail = l2->tail;
			//free(l2);
		}
		else
		{
			l1->tail->next = l2->head;
			if(l2->head != NULL)
				l1->tail = l2->tail;
			//free(l2);
		}
	}
	list* clone(list* a)
	{
		list* ans = (list*)malloc(sizeof(list));
		node* prev = NULL;
		node* h = NULL;
		node* t = a->head;
		while(t != NULL)
		{
			node* n = (node*)malloc(sizeof(node));
			n->val = (char*)malloc(sizeof(t->val));
			strcpy(n->val,t->val);
			if(prev == NULL)
				h = n;
			else
				prev->next = n;
			prev = n;
			t = t->next;
		}
		ans->head = h;
		ans->tail = prev;//final state of prev
		return ans;
	}
	list* substitute_helper(tablenode* t, list** values_sub)
	{
		list* ans = (list*)malloc(sizeof(list));//has to keep a copy of the statements array
		node* temp = (t->statements == NULL)?(NULL):(t->statements->head);
		while(temp != NULL)
		{
			if(ans->head == NULL)
			{
				ans->head = ans->tail = (node*)malloc(sizeof(node));
				ans->head->val = (char*)malloc(sizeof(temp->val));
				strcpy(ans->head->val,temp->val);
			}
			else
			{
				node* t1 = (node*)malloc(sizeof(node));
				t1->val = (char*)malloc(sizeof(temp->val));
				strcpy(t1->val,temp->val);
				ans->tail->next = t1;
				ans->tail = t1;
			}
			temp = temp->next;
		}

		node* x = (t->variables == NULL)?(NULL):(t->variables->head);//the identifiers of the variables
		int cnt = 0;
		while(x != NULL)
		{
			char* f = x->val;
			node* y  = ans->head;
			node* prev = NULL;
			while(y != NULL)
			{
				if(strcmp(f,y->val) == 0)
				{
					//we have to append an entire list's contents over here for this purpose
					node* u = y->next;
					list* t = clone(values_sub[cnt]);
					if(prev != NULL)
						prev->next = t->head;
					else
						ans->head = ans->tail = t -> head;
					t->tail->next = u;
					prev = t->tail;
					if(y == ans->tail)
						ans->tail = prev;//the new tail end of the list!
					//free(y);//this pointer is now useless
					y = u;
				}
				else
				{
					prev = y;
					y = y->next;
				}
			}
			x = x->next;
			cnt++;
		}
		//free(values_sub);//not useful anymore
		return ans;
	}
	list* substitute(table* h,char* id,list** values_sub,int args)
	{
		tablenode* t = h->head;
		while(t != NULL)
		{
			if(strcmp(t->id,id) == 0)
			{
				if(t->args == args)
					return substitute_helper(t,values_sub);
				else
					return NULL;
			}
			t = t->next;
		}
		return NULL;
	} 
	
	int add_to_table(table* h,char* id,list* statements,list* variables,int args)
	{
		if(h->head == NULL)
		{
			h->head = (tablenode*)(malloc(sizeof(tablenode)));
			h->head->id = id;
			h->head->statements = statements;
			h->head->variables = variables;
			h->head->args = args;
			h->tail = h->head;
			return 0;
		}
		else
		{
			tablenode* h1 = h->head;
			int x = 0;
			int fl = 0;
			while(h1 != NULL)
			{
				if(strcmp(h1->id,id) == 0)
				{
					fl = 1;
					break;
				}
				h1 = h1->next;
			}
			if(fl == 0)
			{
				tablenode* t = (tablenode*)(malloc(sizeof(tablenode)));
				t->id = id;
				t->statements = statements;
				t->variables = variables;
				t->args = args;
				h->tail->next = t;
				h->tail = t;
				return 0;
			}
			else
			{
				h1->statements = statements;
				h1->variables = variables;
				h1->args = args;
			}
		}
		return 0;
	}
	table* macro_table;
%}
%union
{
    int integer;
    char character;
    char* string;
    struct list* List;
    struct listoflist* ListofList;
}
%start goal;
%type <integer> Integer
%type <ListofList> RepeatedParametersExpression
%type <List> goal StatementStar Statement IfElseStatement MacroDefStatement MacroDefExpression MacroDefinition MacroDefinition_extended TypeDeclaration_extended TypeIdentifierExtended ClassDefinition PrimaryExpression Expression RepeatedParameters MethodDeclaration MethodDeclarationExtended MainClass TypeIdentifierComma
%type <string> Identifier  AccessSpecifier Type
%token Plus Minus Mult Div Modulo Semicolon Equal Comma OpeningBrace Identifier ClosingBrace OpeningBracket ClosingBracket OpeningSquareBracket ClosingSquareBracket Dot Return Main GreaterThan LessThan LessEqual GreaterEqual DoubleEqual NotEqual Or And Class While If Else True False New Length Define Hashtag Extends System Out Print Println Integer Public Private Protected Void Bool Not Static String This Int
%%
ClassDefinition: Class Identifier OpeningBrace TypeIdentifierExtended MethodDeclarationExtended ClosingBrace 
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"class");
	insertIntoList($$,$2);
	insertIntoList($$,"{");
	appendList($$,$4);
	appendList($$,$5);
	insertIntoList($$,"}");
}
	| Class Identifier Extends Identifier OpeningBrace TypeIdentifierExtended MethodDeclarationExtended ClosingBrace
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"class");
	insertIntoList($$,$2);
	insertIntoList($$,"extends");
	insertIntoList($$,$4);
	insertIntoList($$,"{");
	appendList($$,$6);
	appendList($$,$7);
	insertIntoList($$,"}");
};

MainClass: Class Identifier OpeningBrace AccessSpecifier Static Void Main OpeningBracket String OpeningSquareBracket ClosingSquareBracket Identifier ClosingBracket OpeningBrace StatementStar ClosingBrace ClosingBrace
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"class");
	insertIntoList($$,$2);
	insertIntoList($$,"{");
	insertIntoList($$,$4);
	insertIntoList($$,"static");
	insertIntoList($$,"void");
	insertIntoList($$,"main");
	insertIntoList($$,"(");
	insertIntoList($$,"String");
	insertIntoList($$,"[]");
	insertIntoList($$,$12);
	insertIntoList($$,"){");
	appendList($$,$15);
	insertIntoList($$,"}");
	insertIntoList($$,"}");
	//free($15);
};
RepeatedParameters: RepeatedParameters Comma Identifier
{
	appendList($$,$1);
	insertIntoList($$,",");
	insertIntoList($$,$3);
}
	| //empty projection!
{
	$$ = (list*)(malloc(sizeof(list)));//no more to do after allocating space
};

RepeatedParametersExpression: RepeatedParametersExpression Comma Expression
{
	$$ = $1;
	if($$ == NULL)
	{
		$$ = (listoflist*)malloc(sizeof(listoflist));
		listnode* t = (listnode*)malloc(sizeof(listnode));
		t->val = (list*)malloc(sizeof(list));
		t->val->head = t->val->tail = (node*)malloc(sizeof(node));
		t->val->head->val = ",";
		listnode* t2 = (listnode*)malloc(sizeof(listnode));
		t2->val = $3;
		t->next = t2;
		$$->head = t;
		$$->tail = t2;
	}
	else
	{
		listnode* t1 = (listnode*)malloc(sizeof(listnode));
		listnode* t2 = (listnode*)malloc(sizeof(listnode));
		t1->val = (list*)malloc(sizeof(list));
		t1->val->head = t1->val->tail = (node*)malloc(sizeof(node));
		t1->val->head->val = ",";
		t1->next = t2;
		t2->val = $3;
		$$->tail->next = t1;
		$$->tail = t2;
	}
}
	| 	//null rule
{
	$$ = NULL;
};
IfElseStatement: If OpeningBracket Expression ClosingBracket Statement
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"if");
	insertIntoList($$,"(");
	appendList($$,$3);
	insertIntoList($$,")");
	appendList($$,$5);
}	
	| If OpeningBracket Expression ClosingBracket Statement Else Statement//will suffer from shift reduce errors but stack matching should take care anyways 
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"if");
	insertIntoList($$,"(");
	appendList($$,$3);
	insertIntoList($$,")");
	appendList($$,$5);
	insertIntoList($$,"else");
	appendList($$,$7);
};

Statement: OpeningBrace StatementStar ClosingBrace
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"{");
	appendList($$,$2);
	insertIntoList($$,"}");
}
	| System Dot Out Dot Print OpeningBracket Expression ClosingBracket Semicolon
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"System.out.print(");
	appendList($$,$7);
	insertIntoList($$,");");
}
	| System Dot Out Dot Println OpeningBracket Expression ClosingBracket Semicolon
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"System.out.println(");
	appendList($$,$7);
	insertIntoList($$,");");
}
	| Identifier Equal Expression Semicolon
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,$1);
	insertIntoList($$,"=");
	appendList($$,$3);
	insertIntoList($$,";");
}
	| Identifier OpeningSquareBracket Expression ClosingSquareBracket Equal Expression Semicolon
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,$1);
	insertIntoList($$,"[");
	appendList($$,$3);
	insertIntoList($$,"]");
	insertIntoList($$,"=");
	appendList($$,$6);
	insertIntoList($$,";");
}
	| IfElseStatement
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
}
	| While OpeningBracket Expression ClosingBracket Statement
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"while");
	insertIntoList($$,"(");
	appendList($$,$3);
	insertIntoList($$,")");
	appendList($$,$5);
} 
	| Identifier OpeningBracket Expression RepeatedParametersExpression ClosingBracket Semicolon//for macros
{
	$$ = (list*)malloc(sizeof(list));//now we've to test for syntax errors due to poor macro usage or wrong macro names
	//identify all the parameters of the call, and then proceed to try for a macro matching.
	listnode* t = $4 -> head;//head to a list of lists
	int cnt = 0;
	while(t != NULL)
	{
		if((t->val != NULL) && (t->val->head != NULL) && strcmp(t->val->head->val,",") == 0)
			cnt++;
		t = t->next;
	}
	//there are now cnt+1 function arguments that are possible
	list* arr[cnt+1];
	arr[0] = $3;
	int i = 1;
	t = $4 -> head;
	while(t != NULL)
	{
		if(t->val != NULL && (t->val->head != NULL) && strcmp(t->val->head->val,",") != 0)
			arr[i++] = t->val;//new identifier syntax to be replaced
		 t = t->next;
	}
	list* ans = substitute(macro_table,$1,arr,cnt+1);//check if we got a valid macro substitution now
	if(ans == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList($$,ans);//store the result over here please!
}
	| Identifier OpeningBracket ClosingBracket Semicolon //for void function macros
{
	$$ = (list*)malloc(sizeof(list));
	list* an = substitute(macro_table,$1,NULL,0);
	if(an == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList($$,an);
}
	| Semicolon //trivial statement
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,";");
};

StatementStar: Statement StatementStar 
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	appendList($$,$2);
}
 	| 
{
	$$ = (list*)malloc(sizeof(list));
};

PrimaryExpression: Integer
{
	$$ = (list*)malloc(sizeof(list));
	$$->head = $$->tail = (node*)(malloc(sizeof(node)));
	$$->head->val = itoa($1);
}
	| True
{
	$$ = (list*)malloc(sizeof(list));
	$$->head = $$->tail = (node*)malloc(sizeof(node));
	$$->head->val = "true";
}
	| False
{
	$$ = (list*)malloc(sizeof(list));
	$$->head = $$->tail = (node*)malloc(sizeof(node));
	$$->head->val = "false";
}
	| Identifier
{
	$$ = (list*)malloc(sizeof(list));
	$$->head = $$->tail = (node*)malloc(sizeof(node));
	$$->head->val = $1;
}
	| This
{
	$$ = (list*)malloc(sizeof(list));
	$$->head = $$->tail = (node*)malloc(sizeof(node));
	$$->head->val = "this";
}
	| New Type OpeningSquareBracket Expression ClosingSquareBracket
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"new");
	insertIntoList($$,$2);
	insertIntoList($$,"[");
	appendList($$,$4);
	insertIntoList($$,"]");
}
	| New Identifier OpeningBracket ClosingBracket
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"new");
	insertIntoList($$,$2);
	insertIntoList($$,"()");
}
	| Not Expression
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"!");
	appendList($$,$2);
}
	| OpeningBracket Expression ClosingBracket
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,"(");
	appendList($$,$2);
	insertIntoList($$,")");
};

Expression: PrimaryExpression And PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"&&");
	appendList($$,$3);
}
	| PrimaryExpression Or PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"||");
	appendList($$,$3);
}
	| PrimaryExpression NotEqual PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"!=");
	appendList($$,$3);
}
	| PrimaryExpression DoubleEqual PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"==");
	appendList($$,$3);
}
	| PrimaryExpression GreaterThan PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,">");
	appendList($$,$3);
}
	| PrimaryExpression LessThan PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"<");
	appendList($$,$3);
}
	| PrimaryExpression LessEqual PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"<=");
	appendList($$,$3);
}
	| PrimaryExpression GreaterEqual PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,">=");
	appendList($$,$3);
}
	| PrimaryExpression Plus PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"+");
	appendList($$,$3);
}
	| PrimaryExpression Minus PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"-");
	appendList($$,$3);
}
	| PrimaryExpression Mult PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"*");
	appendList($$,$3);
}
	| PrimaryExpression Div PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"/");
	appendList($$,$3);
}
	| PrimaryExpression Modulo PrimaryExpression
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,"%");
	appendList($$,$3);
}
	| PrimaryExpression Dot Identifier OpeningBracket Expression RepeatedParametersExpression ClosingBracket //function call
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,".");
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	appendList($$,$5);
	listnode* h = ($6 == NULL)?NULL:($6->head);
	while(h != NULL)
	{
		appendList($$,(h->val));
		h = h->next;
	}
	insertIntoList($$,")");
}
	| Identifier OpeningBracket Expression RepeatedParametersExpression ClosingBracket //macro call
{
	$$ = (list*)malloc(sizeof(list));//now we've to test for syntax errors due to poor macro usage or wrong macro names
	//identify all the parameters of the call, and then proceed to try for a macro matching.
	listnode* t = $4 -> head;//head to a list of lists
	int cnt = 0;
	while(t != NULL)
	{
		if((t->val != NULL) && (t->val->head != NULL) && strcmp(t->val->head->val,",") == 0)
			cnt++;
		t = t->next;
	}
	//there are now cnt+1 function arguments that are possible
	list* arr[cnt+1];
	arr[0] = $3;
	int i = 1;
	t = $4 -> head;
	while(t != NULL)
	{
		if(t->val != NULL && (t->val->head != NULL) && strcmp(t->val->head->val,",") != 0)
			arr[i++] = t->val;//new identifier syntax to be replaced
		 t = t->next;
	}
	list* ans = substitute(macro_table,$1,arr,cnt+1);//check if we got a valid macro substitution now
	if(ans == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList($$,ans);//store the result over here please!
}
	| Identifier OpeningBracket ClosingBracket //calling a void macro
{
	$$ = (list*)malloc(sizeof(list));
	list* an = substitute(macro_table,$1,NULL,0);
	if(an == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList($$,an);
}
	| PrimaryExpression Dot Identifier OpeningBracket ClosingBracket //void function call
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,".");
	insertIntoList($$,$3);
	insertIntoList($$,"()");
}
	| PrimaryExpression Dot Identifier	//member access operator.
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,".");
	insertIntoList($$,$3);
}
	| PrimaryExpression
{
	$$ = $1;
};


MacroDefStatement: Hashtag Define Identifier OpeningBracket Identifier RepeatedParameters ClosingBracket Statement//macro function
{
	//insert into the macro definition table
	$$ = (list*)malloc(sizeof(list));
	//insertIntoList($$,"#define");
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	insertIntoList($$,$5);
	appendList($$,$6);
	insertIntoList($$,")");
	//appendList($$,$8);
	list* var = (list*)malloc(sizeof(list));
	insertIntoList(var,$5);
	int cnt = 1;
	node* h = ($6 == NULL)?(NULL):($6->head);
	while(h != NULL)
	{
		if(strcmp(h->val,",") == 0)
		{
			cnt++;
			insertIntoList(var,h->next->val);
		}
		h = h->next;
	}
	add_to_table(macro_table,$3,$8,var,cnt);
}
	|	Hashtag Define Identifier OpeningBracket ClosingBracket Statement //void function
{
	$$ = (list*)malloc(sizeof(list));
	//insertIntoList($$,"#define");
	insertIntoList($$,$3);
	insertIntoList($$,"()");
	//appendList($$,$6);
	add_to_table(macro_table,$3,$6,NULL,0);
};

MacroDefExpression: Hashtag Define Identifier OpeningBracket Identifier RepeatedParameters ClosingBracket Expression//macro function
{
	$$ = (list*)malloc(sizeof(list));
	//insertIntoList($$,"#define");
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	insertIntoList($$,$5);
	appendList($$,$6);
	insertIntoList($$,")");
	list* var = (list*)malloc(sizeof(list));
	insertIntoList(var,$5);
	int cnt = 1;
	node* h = ($6 == NULL)?(NULL):($6->head);
	while(h != NULL)
	{
		if(strcmp(h->val,",") == 0)
		{
			cnt++;
			insertIntoList(var,h->next->val);
		}
		h = h->next;
	}
	add_to_table(macro_table,$3,$8,var,cnt);
}
	|	Hashtag Define Identifier OpeningBracket ClosingBracket Expression //void function
{
	$$ = (list*)malloc(sizeof(list));
	//insertIntoList($$,"#define");
	insertIntoList($$,$3);
	insertIntoList($$,"()");
	appendList($$,$6);
	add_to_table(macro_table,$3,$6,NULL,0);
};

MacroDefinition: MacroDefStatement
{
	$$ = $1;	
}
	| MacroDefExpression
{
	$$ = $1;
};
MacroDefinition_extended: MacroDefinition_extended MacroDefinition
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	appendList($$,$2);
}
	| //null statement
{
	$$ = (list*)malloc(sizeof(list));
};
TypeDeclaration_extended: TypeDeclaration_extended ClassDefinition
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	appendList($$,$2);
}
	| //null rule
{
	$$ = (list*)malloc(sizeof(list));
};
TypeIdentifierExtended: TypeIdentifierExtended Type Identifier Semicolon
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	insertIntoList($$,$2);
	insertIntoList($$,$3);
	insertIntoList($$,";");
}
	| //null rule
{
	$$ = (list*)malloc(sizeof(list));
};
TypeIdentifierComma: TypeIdentifierComma Comma Type Identifier
{
	appendList($$,$1);
	insertIntoList($$,",");
	insertIntoList($$,$3);
	insertIntoList($$,$4);
}
	| 
{
	$$ = (list*)malloc(sizeof(list));
};
AccessSpecifier: Public
{
	$$ = "public";
}	| Private
{
	$$ = "private";
}	| Protected
{
	$$ = "protected";
}	| //blank, default is Private
{
	$$ = "private";
};
MethodDeclaration: AccessSpecifier Type Identifier OpeningBracket Type Identifier TypeIdentifierComma ClosingBracket OpeningBrace TypeIdentifierExtended StatementStar Return Expression Semicolon ClosingBrace
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,$1);
	insertIntoList($$,$2);
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	insertIntoList($$,$5);
	insertIntoList($$,$6);
	appendList($$,$7);
	insertIntoList($$,")");
	insertIntoList($$,"{");
	appendList($$,$10);
	appendList($$,$11);
	insertIntoList($$,"return");
	appendList($$,$13);
	insertIntoList($$,";");
	insertIntoList($$,"}");
}
	 | AccessSpecifier Type Identifier OpeningBracket ClosingBracket OpeningBrace TypeIdentifierExtended StatementStar Return Expression Semicolon ClosingBrace
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,$1);
	insertIntoList($$,$2);
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	insertIntoList($$,")");
	insertIntoList($$,"{");
	appendList($$,$7);
	appendList($$,$8);
	insertIntoList($$,"return");
	appendList($$,$10);
	insertIntoList($$,";");
	insertIntoList($$,"}");
}	
	| AccessSpecifier Type Identifier OpeningBracket Type Identifier TypeIdentifierComma ClosingBracket Return Expression Semicolon //one line function
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,$1);
	insertIntoList($$,$2);
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	insertIntoList($$,$5);
	insertIntoList($$,$6);
	appendList($$,$7);
	insertIntoList($$,")");
	insertIntoList($$,"return");
	appendList($$,$10);
	insertIntoList($$,";");
}	
	| AccessSpecifier Type Identifier OpeningBracket ClosingBracket Return Expression Semicolon//one line void param function
{
	$$ = (list*)malloc(sizeof(list));
	insertIntoList($$,$1);
	insertIntoList($$,$2);
	insertIntoList($$,$3);
	insertIntoList($$,"(");
	insertIntoList($$,")");
	insertIntoList($$,"return");
	appendList($$,$7);
	insertIntoList($$,";");
};

MethodDeclarationExtended: MethodDeclarationExtended MethodDeclaration
{
	$$ = (list*)malloc(sizeof(list));
	appendList($$,$1);
	appendList($$,$2);
} 
	|  
{
	$$ = (list*)malloc(sizeof(list));
};

Type: Int
{
	$$ = "int";
}
	| Bool
{
	$$ = "boolean";
}
	| Type OpeningSquareBracket ClosingSquareBracket
{
	//array type
	$$ = malloc(sizeof(char) * 40);
	strcpy($$,$1);
	strcat($$,"[]");
}	| Identifier
{
	$$ = $1;//simply copy the pointer!
};

goal: MacroDefinition_extended MainClass TypeDeclaration_extended 
{
	$$ = (list*)malloc(sizeof(list));
	//appendList($$,$1);
	appendList($$,$2);
	appendList($$,$3);
	printListLine($$);
	exit(0);
}
%%

int yyerror(char *s)
{
	printf ("// Failed to parse macrojava code.");
	return 0;
  
}
int main ()
{
	macro_table = (table*)(malloc(sizeof(table)));
	yyparse();
	return 0;
}
