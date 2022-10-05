/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison implementation for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

/* C LALR(1) parser skeleton written by Richard Stallman, by
   simplifying the original so-called "semantic" parser.  */

/* All symbols defined below should begin with yy or YY, to avoid
   infringing on user name space.  This should be done even for local
   variables, as they might otherwise be expanded by user macros.
   There are some unavoidable exceptions within include files to
   define necessary library symbols; they are noted "INFRINGES ON
   USER NAME SPACE" below.  */

/* Identify Bison output.  */
#define YYBISON 1

/* Bison version.  */
#define YYBISON_VERSION "3.0.4"

/* Skeleton name.  */
#define YYSKELETON_NAME "yacc.c"

/* Pure parsers.  */
#define YYPURE 0

/* Push parsers.  */
#define YYPUSH 0

/* Pull parsers.  */
#define YYPULL 1




/* Copy the first part of user declarations.  */
#line 1 "P1.y" /* yacc.c:339  */

	#include <stdio.h>
	#include <string.h>
	#include <stdlib.h>
	#include <math.h>
	#include "P1.tab.h"
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
	void appendList(list** l1,list** l2)//Please change syntax elsewhere!
	{
		if(l1 == NULL || (*l1) == NULL || (*l1)->head == NULL)
		{
			l1 = l2;
		}
		else
		{
			(*l1)->tail->next = (l2 == NULL)?NULL:(*l2)->head;
			(*l1)->tail = (l2 == NULL)?(*l1)->tail:(((*l2)->tail == NULL)?(*l1)->tail:(*l2)->tail);
			free(l2);
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
					free(y);//this pointer is now useless
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
		free(values_sub);//not useful anymore
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
			if(fl = 0)
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
		return 1;
	}
	table* macro_table;

#line 337 "P1.tab.c" /* yacc.c:339  */

# ifndef YY_NULLPTR
#  if defined __cplusplus && 201103L <= __cplusplus
#   define YY_NULLPTR nullptr
#  else
#   define YY_NULLPTR 0
#  endif
# endif

/* Enabling verbose error messages.  */
#ifdef YYERROR_VERBOSE
# undef YYERROR_VERBOSE
# define YYERROR_VERBOSE 1
#else
# define YYERROR_VERBOSE 0
#endif

/* In a future release of Bison, this section will be replaced
   by #include "P1.tab.h".  */
#ifndef YY_YY_P1_TAB_H_INCLUDED
# define YY_YY_P1_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    Plus = 258,
    Minus = 259,
    Mult = 260,
    Div = 261,
    Modulo = 262,
    Semicolon = 263,
    Equal = 264,
    Comma = 265,
    OpeningBrace = 266,
    Identifier = 267,
    ClosingBrace = 268,
    OpeningBracket = 269,
    ClosingBracket = 270,
    OpeningSquareBracket = 271,
    ClosingSquareBracket = 272,
    Dot = 273,
    Return = 274,
    Main = 275,
    GreaterThan = 276,
    LessThan = 277,
    LessEqual = 278,
    GreaterEqual = 279,
    DoubleEqual = 280,
    NotEqual = 281,
    Or = 282,
    And = 283,
    Class = 284,
    While = 285,
    If = 286,
    Else = 287,
    True = 288,
    False = 289,
    New = 290,
    Length = 291,
    Define = 292,
    Hashtag = 293,
    Extends = 294,
    System = 295,
    Out = 296,
    Print = 297,
    Println = 298,
    Integer = 299,
    Public = 300,
    Private = 301,
    Protected = 302,
    Void = 303,
    Bool = 304,
    Not = 305,
    Static = 306,
    String = 307,
    This = 308
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 272 "P1.y" /* yacc.c:355  */

    int integer;
    char character;
    char* string;
    struct list* List;
    struct listoflist* ListofList;

#line 439 "P1.tab.c" /* yacc.c:355  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_P1_TAB_H_INCLUDED  */

/* Copy the second part of user declarations.  */

#line 456 "P1.tab.c" /* yacc.c:358  */

#ifdef short
# undef short
#endif

#ifdef YYTYPE_UINT8
typedef YYTYPE_UINT8 yytype_uint8;
#else
typedef unsigned char yytype_uint8;
#endif

#ifdef YYTYPE_INT8
typedef YYTYPE_INT8 yytype_int8;
#else
typedef signed char yytype_int8;
#endif

#ifdef YYTYPE_UINT16
typedef YYTYPE_UINT16 yytype_uint16;
#else
typedef unsigned short int yytype_uint16;
#endif

#ifdef YYTYPE_INT16
typedef YYTYPE_INT16 yytype_int16;
#else
typedef short int yytype_int16;
#endif

#ifndef YYSIZE_T
# ifdef __SIZE_TYPE__
#  define YYSIZE_T __SIZE_TYPE__
# elif defined size_t
#  define YYSIZE_T size_t
# elif ! defined YYSIZE_T
#  include <stddef.h> /* INFRINGES ON USER NAME SPACE */
#  define YYSIZE_T size_t
# else
#  define YYSIZE_T unsigned int
# endif
#endif

#define YYSIZE_MAXIMUM ((YYSIZE_T) -1)

#ifndef YY_
# if defined YYENABLE_NLS && YYENABLE_NLS
#  if ENABLE_NLS
#   include <libintl.h> /* INFRINGES ON USER NAME SPACE */
#   define YY_(Msgid) dgettext ("bison-runtime", Msgid)
#  endif
# endif
# ifndef YY_
#  define YY_(Msgid) Msgid
# endif
#endif

#ifndef YY_ATTRIBUTE
# if (defined __GNUC__                                               \
      && (2 < __GNUC__ || (__GNUC__ == 2 && 96 <= __GNUC_MINOR__)))  \
     || defined __SUNPRO_C && 0x5110 <= __SUNPRO_C
#  define YY_ATTRIBUTE(Spec) __attribute__(Spec)
# else
#  define YY_ATTRIBUTE(Spec) /* empty */
# endif
#endif

#ifndef YY_ATTRIBUTE_PURE
# define YY_ATTRIBUTE_PURE   YY_ATTRIBUTE ((__pure__))
#endif

#ifndef YY_ATTRIBUTE_UNUSED
# define YY_ATTRIBUTE_UNUSED YY_ATTRIBUTE ((__unused__))
#endif

#if !defined _Noreturn \
     && (!defined __STDC_VERSION__ || __STDC_VERSION__ < 201112)
# if defined _MSC_VER && 1200 <= _MSC_VER
#  define _Noreturn __declspec (noreturn)
# else
#  define _Noreturn YY_ATTRIBUTE ((__noreturn__))
# endif
#endif

/* Suppress unused-variable warnings by "using" E.  */
#if ! defined lint || defined __GNUC__
# define YYUSE(E) ((void) (E))
#else
# define YYUSE(E) /* empty */
#endif

#if defined __GNUC__ && 407 <= __GNUC__ * 100 + __GNUC_MINOR__
/* Suppress an incorrect diagnostic about yylval being uninitialized.  */
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN \
    _Pragma ("GCC diagnostic push") \
    _Pragma ("GCC diagnostic ignored \"-Wuninitialized\"")\
    _Pragma ("GCC diagnostic ignored \"-Wmaybe-uninitialized\"")
# define YY_IGNORE_MAYBE_UNINITIALIZED_END \
    _Pragma ("GCC diagnostic pop")
#else
# define YY_INITIAL_VALUE(Value) Value
#endif
#ifndef YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
# define YY_IGNORE_MAYBE_UNINITIALIZED_END
#endif
#ifndef YY_INITIAL_VALUE
# define YY_INITIAL_VALUE(Value) /* Nothing. */
#endif


#if ! defined yyoverflow || YYERROR_VERBOSE

/* The parser invokes alloca or malloc; define the necessary symbols.  */

# ifdef YYSTACK_USE_ALLOCA
#  if YYSTACK_USE_ALLOCA
#   ifdef __GNUC__
#    define YYSTACK_ALLOC __builtin_alloca
#   elif defined __BUILTIN_VA_ARG_INCR
#    include <alloca.h> /* INFRINGES ON USER NAME SPACE */
#   elif defined _AIX
#    define YYSTACK_ALLOC __alloca
#   elif defined _MSC_VER
#    include <malloc.h> /* INFRINGES ON USER NAME SPACE */
#    define alloca _alloca
#   else
#    define YYSTACK_ALLOC alloca
#    if ! defined _ALLOCA_H && ! defined EXIT_SUCCESS
#     include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
      /* Use EXIT_SUCCESS as a witness for stdlib.h.  */
#     ifndef EXIT_SUCCESS
#      define EXIT_SUCCESS 0
#     endif
#    endif
#   endif
#  endif
# endif

# ifdef YYSTACK_ALLOC
   /* Pacify GCC's 'empty if-body' warning.  */
#  define YYSTACK_FREE(Ptr) do { /* empty */; } while (0)
#  ifndef YYSTACK_ALLOC_MAXIMUM
    /* The OS might guarantee only one guard page at the bottom of the stack,
       and a page size can be as small as 4096 bytes.  So we cannot safely
       invoke alloca (N) if N exceeds 4096.  Use a slightly smaller number
       to allow for a few compiler-allocated temporary stack slots.  */
#   define YYSTACK_ALLOC_MAXIMUM 4032 /* reasonable circa 2006 */
#  endif
# else
#  define YYSTACK_ALLOC YYMALLOC
#  define YYSTACK_FREE YYFREE
#  ifndef YYSTACK_ALLOC_MAXIMUM
#   define YYSTACK_ALLOC_MAXIMUM YYSIZE_MAXIMUM
#  endif
#  if (defined __cplusplus && ! defined EXIT_SUCCESS \
       && ! ((defined YYMALLOC || defined malloc) \
             && (defined YYFREE || defined free)))
#   include <stdlib.h> /* INFRINGES ON USER NAME SPACE */
#   ifndef EXIT_SUCCESS
#    define EXIT_SUCCESS 0
#   endif
#  endif
#  ifndef YYMALLOC
#   define YYMALLOC malloc
#   if ! defined malloc && ! defined EXIT_SUCCESS
void *malloc (YYSIZE_T); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
#  ifndef YYFREE
#   define YYFREE free
#   if ! defined free && ! defined EXIT_SUCCESS
void free (void *); /* INFRINGES ON USER NAME SPACE */
#   endif
#  endif
# endif
#endif /* ! defined yyoverflow || YYERROR_VERBOSE */


#if (! defined yyoverflow \
     && (! defined __cplusplus \
         || (defined YYSTYPE_IS_TRIVIAL && YYSTYPE_IS_TRIVIAL)))

/* A type that is properly aligned for any stack member.  */
union yyalloc
{
  yytype_int16 yyss_alloc;
  YYSTYPE yyvs_alloc;
};

/* The size of the maximum gap between one aligned stack and the next.  */
# define YYSTACK_GAP_MAXIMUM (sizeof (union yyalloc) - 1)

/* The size of an array large to enough to hold all stacks, each with
   N elements.  */
# define YYSTACK_BYTES(N) \
     ((N) * (sizeof (yytype_int16) + sizeof (YYSTYPE)) \
      + YYSTACK_GAP_MAXIMUM)

# define YYCOPY_NEEDED 1

/* Relocate STACK from its old location to the new one.  The
   local variables YYSIZE and YYSTACKSIZE give the old and new number of
   elements in the stack, and YYPTR gives the new location of the
   stack.  Advance YYPTR to a properly aligned location for the next
   stack.  */
# define YYSTACK_RELOCATE(Stack_alloc, Stack)                           \
    do                                                                  \
      {                                                                 \
        YYSIZE_T yynewbytes;                                            \
        YYCOPY (&yyptr->Stack_alloc, Stack, yysize);                    \
        Stack = &yyptr->Stack_alloc;                                    \
        yynewbytes = yystacksize * sizeof (*Stack) + YYSTACK_GAP_MAXIMUM; \
        yyptr += yynewbytes / sizeof (*yyptr);                          \
      }                                                                 \
    while (0)

#endif

#if defined YYCOPY_NEEDED && YYCOPY_NEEDED
/* Copy COUNT objects from SRC to DST.  The source and destination do
   not overlap.  */
# ifndef YYCOPY
#  if defined __GNUC__ && 1 < __GNUC__
#   define YYCOPY(Dst, Src, Count) \
      __builtin_memcpy (Dst, Src, (Count) * sizeof (*(Src)))
#  else
#   define YYCOPY(Dst, Src, Count)              \
      do                                        \
        {                                       \
          YYSIZE_T yyi;                         \
          for (yyi = 0; yyi < (Count); yyi++)   \
            (Dst)[yyi] = (Src)[yyi];            \
        }                                       \
      while (0)
#  endif
# endif
#endif /* !YYCOPY_NEEDED */

/* YYFINAL -- State number of the termination state.  */
#define YYFINAL  9
/* YYLAST -- Last index in YYTABLE.  */
#define YYLAST   277

/* YYNTOKENS -- Number of terminals.  */
#define YYNTOKENS  54
/* YYNNTS -- Number of nonterminals.  */
#define YYNNTS  22
/* YYNRULES -- Number of rules.  */
#define YYNRULES  78
/* YYNSTATES -- Number of states.  */
#define YYNSTATES  214

/* YYTRANSLATE[YYX] -- Symbol number corresponding to YYX as returned
   by yylex, with out-of-bounds checking.  */
#define YYUNDEFTOK  2
#define YYMAXUTOK   308

#define YYTRANSLATE(YYX)                                                \
  ((unsigned int) (YYX) <= YYMAXUTOK ? yytranslate[YYX] : YYUNDEFTOK)

/* YYTRANSLATE[TOKEN-NUM] -- Symbol number corresponding to TOKEN-NUM
   as returned by yylex, without out-of-bounds checking.  */
static const yytype_uint8 yytranslate[] =
{
       0,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
       2,     2,     2,     2,     2,     2,     1,     2,     3,     4,
       5,     6,     7,     8,     9,    10,    11,    12,    13,    14,
      15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
      25,    26,    27,    28,    29,    30,    31,    32,    33,    34,
      35,    36,    37,    38,    39,    40,    41,    42,    43,    44,
      45,    46,    47,    48,    49,    50,    51,    52,    53
};

#if YYDEBUG
  /* YYRLINE[YYN] -- Source line where rule number YYN was defined.  */
static const yytype_uint16 yyrline[] =
{
       0,   286,   286,   296,   309,   328,   335,   339,   369,   372,
     381,   393,   400,   407,   414,   422,   433,   438,   447,   478,
     489,   495,   501,   505,   511,   517,   523,   529,   535,   544,
     551,   557,   565,   572,   579,   586,   593,   600,   607,   614,
     621,   628,   635,   642,   649,   656,   672,   703,   714,   722,
     731,   758,   768,   793,   803,   807,   811,   816,   819,   824,
     827,   835,   838,   846,   849,   852,   855,   859,   862,   881,
     897,   912,   925,   930,   934,   939,   943,   949,   954
};
#endif

#if YYDEBUG || YYERROR_VERBOSE || 0
/* YYTNAME[SYMBOL-NUM] -- String name of the symbol SYMBOL-NUM.
   First, the terminals, then, starting at YYNTOKENS, nonterminals.  */
static const char *const yytname[] =
{
  "$end", "error", "$undefined", "Plus", "Minus", "Mult", "Div", "Modulo",
  "Semicolon", "Equal", "Comma", "OpeningBrace", "Identifier",
  "ClosingBrace", "OpeningBracket", "ClosingBracket",
  "OpeningSquareBracket", "ClosingSquareBracket", "Dot", "Return", "Main",
  "GreaterThan", "LessThan", "LessEqual", "GreaterEqual", "DoubleEqual",
  "NotEqual", "Or", "And", "Class", "While", "If", "Else", "True", "False",
  "New", "Length", "Define", "Hashtag", "Extends", "System", "Out",
  "Print", "Println", "Integer", "Public", "Private", "Protected", "Void",
  "Bool", "Not", "Static", "String", "This", "$accept", "ClassDefinition",
  "MainClass", "RepeatedParameters", "RepeatedParametersExpression",
  "IfElseStatement", "Statement", "StatementStar", "PrimaryExpression",
  "Expression", "MacroDefStatement", "MacroDefExpression",
  "MacroDefinition", "MacroDefinition_extended",
  "TypeDeclaration_extended", "TypeIdentifierExtended",
  "TypeIdentifierComma", "AccessSpecifier", "MethodDeclaration",
  "MethodDeclarationExtended", "Type", "goal", YY_NULLPTR
};
#endif

# ifdef YYPRINT
/* YYTOKNUM[NUM] -- (External) token number corresponding to the
   (internal) symbol number NUM (which must be that of a token).  */
static const yytype_uint16 yytoknum[] =
{
       0,   256,   257,   258,   259,   260,   261,   262,   263,   264,
     265,   266,   267,   268,   269,   270,   271,   272,   273,   274,
     275,   276,   277,   278,   279,   280,   281,   282,   283,   284,
     285,   286,   287,   288,   289,   290,   291,   292,   293,   294,
     295,   296,   297,   298,   299,   300,   301,   302,   303,   304,
     305,   306,   307,   308
};
# endif

#define YYPACT_NINF -81

#define yypact_value_is_default(Yystate) \
  (!!((Yystate) == (-81)))

#define YYTABLE_NINF -1

#define yytable_value_is_error(Yytable_value) \
  0

  /* YYPACT[STATE-NUM] -- Index in YYTABLE of the portion describing
     STATE-NUM.  */
static const yytype_int16 yypact[] =
{
     -81,   -13,     3,    25,    22,   -81,   -81,   -81,   -81,   -81,
      69,    74,   107,    80,   132,    90,   -81,   -81,   -81,   -81,
     124,    38,    -9,   134,   -81,     1,   -81,   173,   171,    11,
     -81,   157,   162,   110,   179,   184,   -81,   -81,    30,   187,
     -81,   110,   -81,   -81,   -81,   197,   -81,    44,   195,   193,
     196,     1,   170,   157,   198,   110,     5,   110,   199,   194,
     110,   110,   200,   -81,   -81,   201,   169,   -81,   139,   139,
     139,   139,   139,   204,   139,   139,   139,   139,   139,   139,
     139,   139,   -81,    16,    -6,   -81,   160,   -81,   -81,   -81,
      32,   -81,   -81,   223,   232,   -81,   224,    56,   -81,   227,
     228,   229,    61,   230,   -81,   -81,   -81,   -81,   -81,   -81,
     231,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,   -81,
      44,   -81,   238,   233,    44,   235,   232,   -81,   -81,   -81,
      62,   240,   -81,   -81,   157,   157,   -81,   -81,   236,   153,
     106,    96,   -81,    84,   237,    88,   110,   239,   110,    89,
     -81,   220,   -81,   241,   242,   -81,   -81,   243,   -81,   246,
     239,   -81,   -81,   251,   -81,   157,   110,   110,   113,    -1,
     245,   -81,   -81,   247,   248,   -81,    41,   136,   250,   256,
     257,   -81,   110,   -81,   157,   -81,   -81,   150,   258,   127,
     254,   170,   249,   -81,    44,    73,   259,   110,   154,   -81,
     110,   -81,   261,   -81,   150,   262,   260,   252,   -81,   -81,
     110,   266,   263,   -81
};

  /* YYDEFACT[STATE-NUM] -- Default reduction number in state STATE-NUM.
     Performed when YYTABLE does not specify something else to do.  Zero
     means the default is an error.  */
static const yytype_uint8 yydefact[] =
{
      57,     0,     0,     0,     0,    59,    54,    55,    56,     1,
       0,     0,    78,    67,     0,     0,    58,    64,    65,    66,
       0,     0,     0,     0,     6,     0,    61,     0,     0,     0,
      20,    22,    26,     0,     0,     0,    24,    25,     0,     0,
      23,     0,    27,    16,    51,     0,    53,    73,     0,     0,
       0,     0,     0,    22,     0,     0,     0,     0,    26,     0,
       0,     0,    77,    74,    75,     0,     0,    30,     0,     0,
       0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
       0,     0,    77,    67,     0,    61,     0,     5,    50,    52,
       0,    21,    11,     0,    47,     8,     0,     0,    31,     0,
       0,     0,     0,     0,    26,    40,    41,    42,    43,    44,
      49,    36,    37,    38,    39,    35,    34,    33,    32,     2,
       0,    72,     0,     0,    73,     0,     0,     8,    14,    19,
       0,     0,    47,     8,     0,     0,    29,    76,     0,     0,
       0,     0,    60,    67,     0,     0,     0,    46,     0,     0,
      17,     9,    28,     0,     0,    48,     8,     0,     3,     0,
       0,     7,    18,     0,    46,     0,     0,     0,     0,     0,
       0,    15,    10,     0,     0,    45,     0,     0,     0,     0,
       0,    61,     0,    63,    22,    12,    13,    22,     0,     0,
       0,    77,     0,    71,     0,     0,     0,     0,     0,    61,
       0,     4,     0,    62,    22,     0,     0,     0,    70,    69,
       0,     0,     0,    68
};

  /* YYPGOTO[NTERM-NUM].  */
static const yytype_int16 yypgoto[] =
{
     -81,   -81,   -81,   -81,   -46,   -81,   -18,   -49,   158,   -33,
     -81,   -81,   -81,   -81,   -81,   -80,   -81,   264,   -81,   151,
     -37,   -81
};

  /* YYDEFGOTO[NTERM-NUM].  */
static const yytype_int16 yydefgoto[] =
{
      -1,    16,     5,    29,   130,    43,    53,    54,    45,    46,
       6,     7,     8,     1,    12,    47,   189,   120,   121,    83,
      84,     2
};

  /* YYTABLE[YYPACT[STATE-NUM]] -- What to do in state STATE-NUM.  If
     positive, shift that token.  If negative, reduce the rule whose
     number is the opposite.  If YYTABLE_NINF, syntax error.  */
static const yytype_uint8 yytable[] =
{
      59,    65,    26,     9,    91,   124,   122,    44,    67,    30,
     123,    82,    31,    32,   176,    33,     3,    58,    89,    33,
      94,    50,    93,    95,    96,     4,    51,    99,   100,   119,
      27,    34,    35,    88,    36,    37,    38,    10,    36,    37,
      38,    39,    62,    63,    58,    40,    33,   126,    64,    40,
      24,    41,   181,    25,    42,    41,    82,   127,    42,    11,
     182,    17,    18,    19,   133,    36,    37,    38,    58,   138,
      33,   132,   146,    58,    63,    33,    40,   147,   137,    64,
      13,   145,    41,   141,   199,    42,    14,   149,    63,    36,
      37,    38,   200,    64,    36,    37,    38,   158,   146,   146,
      40,   187,    22,   160,   164,    40,    41,   156,   157,    42,
     168,    41,   123,   161,    42,   163,   150,   151,    58,   204,
      33,   155,    58,   146,    33,    17,    18,    19,   175,    17,
      18,    19,   177,   173,   174,   190,    15,   194,   192,    36,
      37,    38,   195,    36,    37,    38,    21,   172,   183,   188,
      40,   104,   123,    33,    40,   207,    41,   198,    30,    42,
      41,    31,   191,    42,   202,    30,   203,   205,    31,    52,
     123,    55,    36,    37,    38,    23,    56,   211,    57,    55,
      34,    35,    28,    40,    90,    48,    57,    34,    35,    41,
      39,    49,    42,    60,    63,   153,   154,    39,    61,    64,
      68,    69,    70,    71,    72,    66,    85,    86,    87,    98,
     103,    92,   125,    97,   101,    73,   110,   102,    74,    75,
      76,    77,    78,    79,    80,    81,   105,   106,   107,   108,
     109,   128,   111,   112,   113,   114,   115,   116,   117,   118,
     129,   131,   134,   135,   136,   140,   142,   162,   139,   148,
     137,   144,   165,   152,   159,   166,   167,   169,   170,   171,
     178,   184,   179,   180,   185,   186,   193,   196,   197,   206,
     208,   210,   201,   209,   212,   143,   213,    20
};

static const yytype_uint8 yycheck[] =
{
      33,    38,    11,     0,    53,    85,    12,    25,    41,     8,
      16,    12,    11,    12,    15,    14,    29,    12,    51,    14,
      15,    10,    55,    56,    57,    38,    15,    60,    61,    13,
      39,    30,    31,    51,    33,    34,    35,    12,    33,    34,
      35,    40,    12,    44,    12,    44,    14,    15,    49,    44,
      12,    50,    11,    15,    53,    50,    12,    90,    53,    37,
      19,    45,    46,    47,    97,    33,    34,    35,    12,   102,
      14,    15,    10,    12,    44,    14,    44,    15,    17,    49,
      11,   127,    50,   120,    11,    53,    12,   133,    44,    33,
      34,    35,    19,    49,    33,    34,    35,    13,    10,    10,
      44,   181,    12,    15,    15,    44,    50,   140,    12,    53,
     156,    50,    16,   146,    53,   148,   134,   135,    12,   199,
      14,    15,    12,    10,    14,    45,    46,    47,    15,    45,
      46,    47,   169,   166,   167,   184,    29,    10,   187,    33,
      34,    35,    15,    33,    34,    35,    14,   165,    12,   182,
      44,    12,    16,    14,    44,   204,    50,   194,     8,    53,
      50,    11,    12,    53,   197,     8,    12,   200,    11,    12,
      16,     9,    33,    34,    35,    51,    14,   210,    16,     9,
      30,    31,    48,    44,    14,    12,    16,    30,    31,    50,
      40,    20,    53,    14,    44,    42,    43,    40,    14,    49,
       3,     4,     5,     6,     7,    18,    11,    14,    12,    15,
      41,    13,    52,    14,    14,    18,    12,    16,    21,    22,
      23,    24,    25,    26,    27,    28,    68,    69,    70,    71,
      72,     8,    74,    75,    76,    77,    78,    79,    80,    81,
       8,    17,    15,    15,    15,    14,     8,     8,    18,     9,
      17,    16,    32,    17,    17,    14,    14,    14,    12,     8,
      15,    11,    15,    15,     8,     8,     8,    13,    19,     8,
       8,    19,    13,    13,     8,   124,    13,    13
};

  /* YYSTOS[STATE-NUM] -- The (internal number of the) accessing
     symbol of state STATE-NUM.  */
static const yytype_uint8 yystos[] =
{
       0,    67,    75,    29,    38,    56,    64,    65,    66,     0,
      12,    37,    68,    11,    12,    29,    55,    45,    46,    47,
      71,    14,    12,    51,    12,    15,    11,    39,    48,    57,
       8,    11,    12,    14,    30,    31,    33,    34,    35,    40,
      44,    50,    53,    59,    60,    62,    63,    69,    12,    20,
      10,    15,    12,    60,    61,     9,    14,    16,    12,    63,
      14,    14,    12,    44,    49,    74,    18,    63,     3,     4,
       5,     6,     7,    18,    21,    22,    23,    24,    25,    26,
      27,    28,    12,    73,    74,    11,    14,    12,    60,    63,
      14,    61,    13,    63,    15,    63,    63,    14,    15,    63,
      63,    14,    16,    41,    12,    62,    62,    62,    62,    62,
      12,    62,    62,    62,    62,    62,    62,    62,    62,    13,
      71,    72,    12,    16,    69,    52,    15,    63,     8,     8,
      58,    17,    15,    63,    15,    15,    15,    17,    63,    18,
      14,    74,     8,    73,    16,    58,    10,    15,     9,    58,
      60,    60,    17,    42,    43,    15,    63,    12,    13,    17,
      15,    63,     8,    63,    15,    32,    14,    14,    58,    14,
      12,     8,    60,    63,    63,    15,    15,    74,    15,    15,
      15,    11,    19,    12,    11,     8,     8,    69,    63,    70,
      61,    12,    61,     8,    10,    15,    13,    19,    74,    11,
      19,    13,    63,    12,    69,    63,     8,    61,     8,    13,
      19,    63,     8,    13
};

  /* YYR1[YYN] -- Symbol number of symbol that rule YYN derives.  */
static const yytype_uint8 yyr1[] =
{
       0,    54,    55,    55,    56,    57,    57,    58,    58,    59,
      59,    60,    60,    60,    60,    60,    60,    60,    60,    60,
      60,    61,    61,    62,    62,    62,    62,    62,    62,    62,
      62,    62,    63,    63,    63,    63,    63,    63,    63,    63,
      63,    63,    63,    63,    63,    63,    63,    63,    63,    63,
      64,    64,    65,    65,    66,    66,    67,    67,    68,    68,
      69,    69,    70,    70,    71,    71,    71,    71,    72,    72,
      72,    72,    73,    73,    74,    74,    74,    74,    75
};

  /* YYR2[YYN] -- Number of symbols on the right hand side of rule YYN.  */
static const yytype_uint8 yyr2[] =
{
       0,     2,     6,     8,    17,     3,     0,     3,     0,     5,
       7,     3,     9,     9,     4,     7,     1,     5,     6,     4,
       1,     2,     0,     1,     1,     1,     1,     1,     5,     4,
       2,     3,     3,     3,     3,     3,     3,     3,     3,     3,
       3,     3,     3,     3,     3,     7,     5,     3,     5,     3,
       8,     6,     8,     6,     1,     1,     2,     0,     2,     0,
       4,     0,     4,     0,     1,     1,     1,     0,    15,    12,
      11,     8,     2,     0,     1,     1,     3,     1,     3
};


#define yyerrok         (yyerrstatus = 0)
#define yyclearin       (yychar = YYEMPTY)
#define YYEMPTY         (-2)
#define YYEOF           0

#define YYACCEPT        goto yyacceptlab
#define YYABORT         goto yyabortlab
#define YYERROR         goto yyerrorlab


#define YYRECOVERING()  (!!yyerrstatus)

#define YYBACKUP(Token, Value)                                  \
do                                                              \
  if (yychar == YYEMPTY)                                        \
    {                                                           \
      yychar = (Token);                                         \
      yylval = (Value);                                         \
      YYPOPSTACK (yylen);                                       \
      yystate = *yyssp;                                         \
      goto yybackup;                                            \
    }                                                           \
  else                                                          \
    {                                                           \
      yyerror (YY_("syntax error: cannot back up")); \
      YYERROR;                                                  \
    }                                                           \
while (0)

/* Error token number */
#define YYTERROR        1
#define YYERRCODE       256



/* Enable debugging if requested.  */
#if YYDEBUG

# ifndef YYFPRINTF
#  include <stdio.h> /* INFRINGES ON USER NAME SPACE */
#  define YYFPRINTF fprintf
# endif

# define YYDPRINTF(Args)                        \
do {                                            \
  if (yydebug)                                  \
    YYFPRINTF Args;                             \
} while (0)

/* This macro is provided for backward compatibility. */
#ifndef YY_LOCATION_PRINT
# define YY_LOCATION_PRINT(File, Loc) ((void) 0)
#endif


# define YY_SYMBOL_PRINT(Title, Type, Value, Location)                    \
do {                                                                      \
  if (yydebug)                                                            \
    {                                                                     \
      YYFPRINTF (stderr, "%s ", Title);                                   \
      yy_symbol_print (stderr,                                            \
                  Type, Value); \
      YYFPRINTF (stderr, "\n");                                           \
    }                                                                     \
} while (0)


/*----------------------------------------.
| Print this symbol's value on YYOUTPUT.  |
`----------------------------------------*/

static void
yy_symbol_value_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  FILE *yyo = yyoutput;
  YYUSE (yyo);
  if (!yyvaluep)
    return;
# ifdef YYPRINT
  if (yytype < YYNTOKENS)
    YYPRINT (yyoutput, yytoknum[yytype], *yyvaluep);
# endif
  YYUSE (yytype);
}


/*--------------------------------.
| Print this symbol on YYOUTPUT.  |
`--------------------------------*/

static void
yy_symbol_print (FILE *yyoutput, int yytype, YYSTYPE const * const yyvaluep)
{
  YYFPRINTF (yyoutput, "%s %s (",
             yytype < YYNTOKENS ? "token" : "nterm", yytname[yytype]);

  yy_symbol_value_print (yyoutput, yytype, yyvaluep);
  YYFPRINTF (yyoutput, ")");
}

/*------------------------------------------------------------------.
| yy_stack_print -- Print the state stack from its BOTTOM up to its |
| TOP (included).                                                   |
`------------------------------------------------------------------*/

static void
yy_stack_print (yytype_int16 *yybottom, yytype_int16 *yytop)
{
  YYFPRINTF (stderr, "Stack now");
  for (; yybottom <= yytop; yybottom++)
    {
      int yybot = *yybottom;
      YYFPRINTF (stderr, " %d", yybot);
    }
  YYFPRINTF (stderr, "\n");
}

# define YY_STACK_PRINT(Bottom, Top)                            \
do {                                                            \
  if (yydebug)                                                  \
    yy_stack_print ((Bottom), (Top));                           \
} while (0)


/*------------------------------------------------.
| Report that the YYRULE is going to be reduced.  |
`------------------------------------------------*/

static void
yy_reduce_print (yytype_int16 *yyssp, YYSTYPE *yyvsp, int yyrule)
{
  unsigned long int yylno = yyrline[yyrule];
  int yynrhs = yyr2[yyrule];
  int yyi;
  YYFPRINTF (stderr, "Reducing stack by rule %d (line %lu):\n",
             yyrule - 1, yylno);
  /* The symbols being reduced.  */
  for (yyi = 0; yyi < yynrhs; yyi++)
    {
      YYFPRINTF (stderr, "   $%d = ", yyi + 1);
      yy_symbol_print (stderr,
                       yystos[yyssp[yyi + 1 - yynrhs]],
                       &(yyvsp[(yyi + 1) - (yynrhs)])
                                              );
      YYFPRINTF (stderr, "\n");
    }
}

# define YY_REDUCE_PRINT(Rule)          \
do {                                    \
  if (yydebug)                          \
    yy_reduce_print (yyssp, yyvsp, Rule); \
} while (0)

/* Nonzero means print parse trace.  It is left uninitialized so that
   multiple parsers can coexist.  */
int yydebug;
#else /* !YYDEBUG */
# define YYDPRINTF(Args)
# define YY_SYMBOL_PRINT(Title, Type, Value, Location)
# define YY_STACK_PRINT(Bottom, Top)
# define YY_REDUCE_PRINT(Rule)
#endif /* !YYDEBUG */


/* YYINITDEPTH -- initial size of the parser's stacks.  */
#ifndef YYINITDEPTH
# define YYINITDEPTH 200
#endif

/* YYMAXDEPTH -- maximum size the stacks can grow to (effective only
   if the built-in stack extension method is used).

   Do not make this value too large; the results are undefined if
   YYSTACK_ALLOC_MAXIMUM < YYSTACK_BYTES (YYMAXDEPTH)
   evaluated with infinite-precision integer arithmetic.  */

#ifndef YYMAXDEPTH
# define YYMAXDEPTH 10000
#endif


#if YYERROR_VERBOSE

# ifndef yystrlen
#  if defined __GLIBC__ && defined _STRING_H
#   define yystrlen strlen
#  else
/* Return the length of YYSTR.  */
static YYSIZE_T
yystrlen (const char *yystr)
{
  YYSIZE_T yylen;
  for (yylen = 0; yystr[yylen]; yylen++)
    continue;
  return yylen;
}
#  endif
# endif

# ifndef yystpcpy
#  if defined __GLIBC__ && defined _STRING_H && defined _GNU_SOURCE
#   define yystpcpy stpcpy
#  else
/* Copy YYSRC to YYDEST, returning the address of the terminating '\0' in
   YYDEST.  */
static char *
yystpcpy (char *yydest, const char *yysrc)
{
  char *yyd = yydest;
  const char *yys = yysrc;

  while ((*yyd++ = *yys++) != '\0')
    continue;

  return yyd - 1;
}
#  endif
# endif

# ifndef yytnamerr
/* Copy to YYRES the contents of YYSTR after stripping away unnecessary
   quotes and backslashes, so that it's suitable for yyerror.  The
   heuristic is that double-quoting is unnecessary unless the string
   contains an apostrophe, a comma, or backslash (other than
   backslash-backslash).  YYSTR is taken from yytname.  If YYRES is
   null, do not copy; instead, return the length of what the result
   would have been.  */
static YYSIZE_T
yytnamerr (char *yyres, const char *yystr)
{
  if (*yystr == '"')
    {
      YYSIZE_T yyn = 0;
      char const *yyp = yystr;

      for (;;)
        switch (*++yyp)
          {
          case '\'':
          case ',':
            goto do_not_strip_quotes;

          case '\\':
            if (*++yyp != '\\')
              goto do_not_strip_quotes;
            /* Fall through.  */
          default:
            if (yyres)
              yyres[yyn] = *yyp;
            yyn++;
            break;

          case '"':
            if (yyres)
              yyres[yyn] = '\0';
            return yyn;
          }
    do_not_strip_quotes: ;
    }

  if (! yyres)
    return yystrlen (yystr);

  return yystpcpy (yyres, yystr) - yyres;
}
# endif

/* Copy into *YYMSG, which is of size *YYMSG_ALLOC, an error message
   about the unexpected token YYTOKEN for the state stack whose top is
   YYSSP.

   Return 0 if *YYMSG was successfully written.  Return 1 if *YYMSG is
   not large enough to hold the message.  In that case, also set
   *YYMSG_ALLOC to the required number of bytes.  Return 2 if the
   required number of bytes is too large to store.  */
static int
yysyntax_error (YYSIZE_T *yymsg_alloc, char **yymsg,
                yytype_int16 *yyssp, int yytoken)
{
  YYSIZE_T yysize0 = yytnamerr (YY_NULLPTR, yytname[yytoken]);
  YYSIZE_T yysize = yysize0;
  enum { YYERROR_VERBOSE_ARGS_MAXIMUM = 5 };
  /* Internationalized format string. */
  const char *yyformat = YY_NULLPTR;
  /* Arguments of yyformat. */
  char const *yyarg[YYERROR_VERBOSE_ARGS_MAXIMUM];
  /* Number of reported tokens (one for the "unexpected", one per
     "expected"). */
  int yycount = 0;

  /* There are many possibilities here to consider:
     - If this state is a consistent state with a default action, then
       the only way this function was invoked is if the default action
       is an error action.  In that case, don't check for expected
       tokens because there are none.
     - The only way there can be no lookahead present (in yychar) is if
       this state is a consistent state with a default action.  Thus,
       detecting the absence of a lookahead is sufficient to determine
       that there is no unexpected or expected token to report.  In that
       case, just report a simple "syntax error".
     - Don't assume there isn't a lookahead just because this state is a
       consistent state with a default action.  There might have been a
       previous inconsistent state, consistent state with a non-default
       action, or user semantic action that manipulated yychar.
     - Of course, the expected token list depends on states to have
       correct lookahead information, and it depends on the parser not
       to perform extra reductions after fetching a lookahead from the
       scanner and before detecting a syntax error.  Thus, state merging
       (from LALR or IELR) and default reductions corrupt the expected
       token list.  However, the list is correct for canonical LR with
       one exception: it will still contain any token that will not be
       accepted due to an error action in a later state.
  */
  if (yytoken != YYEMPTY)
    {
      int yyn = yypact[*yyssp];
      yyarg[yycount++] = yytname[yytoken];
      if (!yypact_value_is_default (yyn))
        {
          /* Start YYX at -YYN if negative to avoid negative indexes in
             YYCHECK.  In other words, skip the first -YYN actions for
             this state because they are default actions.  */
          int yyxbegin = yyn < 0 ? -yyn : 0;
          /* Stay within bounds of both yycheck and yytname.  */
          int yychecklim = YYLAST - yyn + 1;
          int yyxend = yychecklim < YYNTOKENS ? yychecklim : YYNTOKENS;
          int yyx;

          for (yyx = yyxbegin; yyx < yyxend; ++yyx)
            if (yycheck[yyx + yyn] == yyx && yyx != YYTERROR
                && !yytable_value_is_error (yytable[yyx + yyn]))
              {
                if (yycount == YYERROR_VERBOSE_ARGS_MAXIMUM)
                  {
                    yycount = 1;
                    yysize = yysize0;
                    break;
                  }
                yyarg[yycount++] = yytname[yyx];
                {
                  YYSIZE_T yysize1 = yysize + yytnamerr (YY_NULLPTR, yytname[yyx]);
                  if (! (yysize <= yysize1
                         && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
                    return 2;
                  yysize = yysize1;
                }
              }
        }
    }

  switch (yycount)
    {
# define YYCASE_(N, S)                      \
      case N:                               \
        yyformat = S;                       \
      break
      YYCASE_(0, YY_("syntax error"));
      YYCASE_(1, YY_("syntax error, unexpected %s"));
      YYCASE_(2, YY_("syntax error, unexpected %s, expecting %s"));
      YYCASE_(3, YY_("syntax error, unexpected %s, expecting %s or %s"));
      YYCASE_(4, YY_("syntax error, unexpected %s, expecting %s or %s or %s"));
      YYCASE_(5, YY_("syntax error, unexpected %s, expecting %s or %s or %s or %s"));
# undef YYCASE_
    }

  {
    YYSIZE_T yysize1 = yysize + yystrlen (yyformat);
    if (! (yysize <= yysize1 && yysize1 <= YYSTACK_ALLOC_MAXIMUM))
      return 2;
    yysize = yysize1;
  }

  if (*yymsg_alloc < yysize)
    {
      *yymsg_alloc = 2 * yysize;
      if (! (yysize <= *yymsg_alloc
             && *yymsg_alloc <= YYSTACK_ALLOC_MAXIMUM))
        *yymsg_alloc = YYSTACK_ALLOC_MAXIMUM;
      return 1;
    }

  /* Avoid sprintf, as that infringes on the user's name space.
     Don't have undefined behavior even if the translation
     produced a string with the wrong number of "%s"s.  */
  {
    char *yyp = *yymsg;
    int yyi = 0;
    while ((*yyp = *yyformat) != '\0')
      if (*yyp == '%' && yyformat[1] == 's' && yyi < yycount)
        {
          yyp += yytnamerr (yyp, yyarg[yyi++]);
          yyformat += 2;
        }
      else
        {
          yyp++;
          yyformat++;
        }
  }
  return 0;
}
#endif /* YYERROR_VERBOSE */

/*-----------------------------------------------.
| Release the memory associated to this symbol.  |
`-----------------------------------------------*/

static void
yydestruct (const char *yymsg, int yytype, YYSTYPE *yyvaluep)
{
  YYUSE (yyvaluep);
  if (!yymsg)
    yymsg = "Deleting";
  YY_SYMBOL_PRINT (yymsg, yytype, yyvaluep, yylocationp);

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  YYUSE (yytype);
  YY_IGNORE_MAYBE_UNINITIALIZED_END
}




/* The lookahead symbol.  */
int yychar;

/* The semantic value of the lookahead symbol.  */
YYSTYPE yylval;
/* Number of syntax errors so far.  */
int yynerrs;


/*----------.
| yyparse.  |
`----------*/

int
yyparse (void)
{
    int yystate;
    /* Number of tokens to shift before error messages enabled.  */
    int yyerrstatus;

    /* The stacks and their tools:
       'yyss': related to states.
       'yyvs': related to semantic values.

       Refer to the stacks through separate pointers, to allow yyoverflow
       to reallocate them elsewhere.  */

    /* The state stack.  */
    yytype_int16 yyssa[YYINITDEPTH];
    yytype_int16 *yyss;
    yytype_int16 *yyssp;

    /* The semantic value stack.  */
    YYSTYPE yyvsa[YYINITDEPTH];
    YYSTYPE *yyvs;
    YYSTYPE *yyvsp;

    YYSIZE_T yystacksize;

  int yyn;
  int yyresult;
  /* Lookahead token as an internal (translated) token number.  */
  int yytoken = 0;
  /* The variables used to return semantic value and location from the
     action routines.  */
  YYSTYPE yyval;

#if YYERROR_VERBOSE
  /* Buffer for error messages, and its allocated size.  */
  char yymsgbuf[128];
  char *yymsg = yymsgbuf;
  YYSIZE_T yymsg_alloc = sizeof yymsgbuf;
#endif

#define YYPOPSTACK(N)   (yyvsp -= (N), yyssp -= (N))

  /* The number of symbols on the RHS of the reduced rule.
     Keep to zero when no symbol should be popped.  */
  int yylen = 0;

  yyssp = yyss = yyssa;
  yyvsp = yyvs = yyvsa;
  yystacksize = YYINITDEPTH;

  YYDPRINTF ((stderr, "Starting parse\n"));

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY; /* Cause a token to be read.  */
  goto yysetstate;

/*------------------------------------------------------------.
| yynewstate -- Push a new state, which is found in yystate.  |
`------------------------------------------------------------*/
 yynewstate:
  /* In all cases, when you get here, the value and location stacks
     have just been pushed.  So pushing a state here evens the stacks.  */
  yyssp++;

 yysetstate:
  *yyssp = yystate;

  if (yyss + yystacksize - 1 <= yyssp)
    {
      /* Get the current used size of the three stacks, in elements.  */
      YYSIZE_T yysize = yyssp - yyss + 1;

#ifdef yyoverflow
      {
        /* Give user a chance to reallocate the stack.  Use copies of
           these so that the &'s don't force the real ones into
           memory.  */
        YYSTYPE *yyvs1 = yyvs;
        yytype_int16 *yyss1 = yyss;

        /* Each stack pointer address is followed by the size of the
           data in use in that stack, in bytes.  This used to be a
           conditional around just the two extra args, but that might
           be undefined if yyoverflow is a macro.  */
        yyoverflow (YY_("memory exhausted"),
                    &yyss1, yysize * sizeof (*yyssp),
                    &yyvs1, yysize * sizeof (*yyvsp),
                    &yystacksize);

        yyss = yyss1;
        yyvs = yyvs1;
      }
#else /* no yyoverflow */
# ifndef YYSTACK_RELOCATE
      goto yyexhaustedlab;
# else
      /* Extend the stack our own way.  */
      if (YYMAXDEPTH <= yystacksize)
        goto yyexhaustedlab;
      yystacksize *= 2;
      if (YYMAXDEPTH < yystacksize)
        yystacksize = YYMAXDEPTH;

      {
        yytype_int16 *yyss1 = yyss;
        union yyalloc *yyptr =
          (union yyalloc *) YYSTACK_ALLOC (YYSTACK_BYTES (yystacksize));
        if (! yyptr)
          goto yyexhaustedlab;
        YYSTACK_RELOCATE (yyss_alloc, yyss);
        YYSTACK_RELOCATE (yyvs_alloc, yyvs);
#  undef YYSTACK_RELOCATE
        if (yyss1 != yyssa)
          YYSTACK_FREE (yyss1);
      }
# endif
#endif /* no yyoverflow */

      yyssp = yyss + yysize - 1;
      yyvsp = yyvs + yysize - 1;

      YYDPRINTF ((stderr, "Stack size increased to %lu\n",
                  (unsigned long int) yystacksize));

      if (yyss + yystacksize - 1 <= yyssp)
        YYABORT;
    }

  YYDPRINTF ((stderr, "Entering state %d\n", yystate));

  if (yystate == YYFINAL)
    YYACCEPT;

  goto yybackup;

/*-----------.
| yybackup.  |
`-----------*/
yybackup:

  /* Do appropriate processing given the current state.  Read a
     lookahead token if we need one and don't already have one.  */

  /* First try to decide what to do without reference to lookahead token.  */
  yyn = yypact[yystate];
  if (yypact_value_is_default (yyn))
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* YYCHAR is either YYEMPTY or YYEOF or a valid lookahead symbol.  */
  if (yychar == YYEMPTY)
    {
      YYDPRINTF ((stderr, "Reading a token: "));
      yychar = yylex ();
    }

  if (yychar <= YYEOF)
    {
      yychar = yytoken = YYEOF;
      YYDPRINTF ((stderr, "Now at end of input.\n"));
    }
  else
    {
      yytoken = YYTRANSLATE (yychar);
      YY_SYMBOL_PRINT ("Next token is", yytoken, &yylval, &yylloc);
    }

  /* If the proper action on seeing token YYTOKEN is to reduce or to
     detect an error, take that action.  */
  yyn += yytoken;
  if (yyn < 0 || YYLAST < yyn || yycheck[yyn] != yytoken)
    goto yydefault;
  yyn = yytable[yyn];
  if (yyn <= 0)
    {
      if (yytable_value_is_error (yyn))
        goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }

  /* Count tokens shifted since error; after three, turn off error
     status.  */
  if (yyerrstatus)
    yyerrstatus--;

  /* Shift the lookahead token.  */
  YY_SYMBOL_PRINT ("Shifting", yytoken, &yylval, &yylloc);

  /* Discard the shifted token.  */
  yychar = YYEMPTY;

  yystate = yyn;
  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END

  goto yynewstate;


/*-----------------------------------------------------------.
| yydefault -- do the default action for the current state.  |
`-----------------------------------------------------------*/
yydefault:
  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;
  goto yyreduce;


/*-----------------------------.
| yyreduce -- Do a reduction.  |
`-----------------------------*/
yyreduce:
  /* yyn is the number of a rule to reduce with.  */
  yylen = yyr2[yyn];

  /* If YYLEN is nonzero, implement the default value of the action:
     '$$ = $1'.

     Otherwise, the following line sets YYVAL to garbage.
     This behavior is undocumented and Bison
     users should not rely upon it.  Assigning to YYVAL
     unconditionally makes the parser a bit smaller, and it avoids a
     GCC warning that YYVAL may be used uninitialized.  */
  yyval = yyvsp[1-yylen];


  YY_REDUCE_PRINT (yyn);
  switch (yyn)
    {
        case 2:
#line 287 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"class");
	insertIntoList((yyval.List),(yyvsp[-4].string));
	insertIntoList((yyval.List),"{");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),"}");
}
#line 1695 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 3:
#line 297 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"class");
	insertIntoList((yyval.List),(yyvsp[-6].string));
	insertIntoList((yyval.List),"extends");
	insertIntoList((yyval.List),(yyvsp[-4].string));
	insertIntoList((yyval.List),"{");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),"}");
}
#line 1711 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 4:
#line 310 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"class");
	insertIntoList((yyval.List),(yyvsp[-15].string));
	insertIntoList((yyval.List),"{");
	insertIntoList((yyval.List),(yyvsp[-13].string));
	insertIntoList((yyval.List),"static");
	insertIntoList((yyval.List),"void");
	insertIntoList((yyval.List),"main");
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),"String");
	insertIntoList((yyval.List),"[]");
	insertIntoList((yyval.List),(yyvsp[-5].string));
	insertIntoList((yyval.List),"){");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"}");
	insertIntoList((yyval.List),"}");
}
#line 1734 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 5:
#line 329 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),",");
	insertIntoList((yyval.List),(yyvsp[0].string));
}
#line 1744 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 6:
#line 335 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)(malloc(sizeof(list)));//no more to do after allocating space
}
#line 1752 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 7:
#line 340 "P1.y" /* yacc.c:1646  */
    {
	(yyval.ListofList) = (yyvsp[-2].ListofList);
	if((yyval.ListofList) == NULL)
	{
		(yyval.ListofList) = (listoflist*)malloc(sizeof(listoflist));
		listnode* t = (listnode*)malloc(sizeof(listnode));
		t->val = (list*)malloc(sizeof(list));
		t->val->head = t->val->tail = (node*)malloc(sizeof(node));
		t->val->head->val = ",";
		listnode* t2 = (listnode*)malloc(sizeof(listnode));
		t2->val = (yyvsp[0].List);
		t->next = t2;
		(yyval.ListofList)->head = t;
		(yyval.ListofList)->tail = t2;
	}
	else
	{
		listnode* t1 = (listnode*)malloc(sizeof(listnode));
		listnode* t2 = (listnode*)malloc(sizeof(listnode));
		t1->val = (list*)malloc(sizeof(list));
		t1->val->head = t1->val->tail = (node*)malloc(sizeof(node));
		t1->val->head->val = ",";
		t1->next = t2;
		t2->val = (yyvsp[0].List);
		(yyval.ListofList)->tail->next = t1;
		(yyval.ListofList)->tail = t2;
	}
}
#line 1785 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 8:
#line 369 "P1.y" /* yacc.c:1646  */
    {
	(yyval.ListofList) = NULL;
}
#line 1793 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 9:
#line 373 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"if");
	insertIntoList((yyval.List),"(");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),")");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 1806 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 10:
#line 382 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"if");
	insertIntoList((yyval.List),"(");
	appendList(&(yyval.List),&(yyvsp[-4].List));
	insertIntoList((yyval.List),")");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"else");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 1821 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 11:
#line 394 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"{");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),"}");
}
#line 1832 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 12:
#line 401 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"System.out.print(");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),");");
}
#line 1843 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 13:
#line 408 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"System.out.println(");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),");");
}
#line 1854 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 14:
#line 415 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),(yyvsp[-3].string));
	insertIntoList((yyval.List),"=");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),";");
}
#line 1866 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 15:
#line 423 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),(yyvsp[-6].string));
	insertIntoList((yyval.List),"[");
	appendList(&(yyval.List),&(yyvsp[-4].List));
	insertIntoList((yyval.List),"]");
	insertIntoList((yyval.List),"=");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),";");
}
#line 1881 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 16:
#line 434 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 1890 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 17:
#line 439 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"while");
	insertIntoList((yyval.List),"(");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),")");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 1903 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 18:
#line 448 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));//now we've to test for syntax errors due to poor macro usage or wrong macro names
	//identify all the parameters of the call, and then proceed to try for a macro matching.
	listnode* t = (yyvsp[-2].ListofList) -> head;//head to a list of lists
	int cnt = 0;
	while(t != NULL)
	{
		if((t->val != NULL) && (t->val->head != NULL) && strcmp(t->val->head->val,",") == 0)
			cnt++;
		t = t->next;
	}
	//there are now cnt+1 function arguments that are possible
	list* arr[cnt+1];
	arr[0] = (yyvsp[-3].List);
	int i = 1;
	t = (yyvsp[-2].ListofList) -> head;
	while(t != NULL)
	{
		if(t->val != NULL && (t->val->head != NULL) && strcmp(t->val->head->val,",") != 0)
			arr[i++] = t->val;//new identifier syntax to be replaced
		 t = t->next;
	}
	list* ans = substitute(macro_table,(yyvsp[-5].string),arr,cnt+1);//check if we got a valid macro substitution now
	if(ans == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList(&(yyval.List),&ans);//store the result over here please!
}
#line 1938 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 19:
#line 479 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	list* an = substitute(macro_table,(yyvsp[-3].string),NULL,0);
	if(an == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList(&(yyval.List),&an);
}
#line 1953 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 20:
#line 490 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),";");
}
#line 1962 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 21:
#line 496 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-1].List));
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 1971 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 22:
#line 501 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
}
#line 1979 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 23:
#line 506 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	(yyval.List)->head = (yyval.List)->tail = (node*)(malloc(sizeof(node)));
	(yyval.List)->head->val = itoa((yyvsp[0].integer));
}
#line 1989 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 24:
#line 512 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	(yyval.List)->head = (yyval.List)->tail = (node*)malloc(sizeof(node));
	(yyval.List)->head->val = "true";
}
#line 1999 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 25:
#line 518 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	(yyval.List)->head = (yyval.List)->tail = (node*)malloc(sizeof(node));
	(yyval.List)->head->val = "false";
}
#line 2009 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 26:
#line 524 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	(yyval.List)->head = (yyval.List)->tail = (node*)malloc(sizeof(node));
	(yyval.List)->head->val = (yyvsp[0].string);
}
#line 2019 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 27:
#line 530 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	(yyval.List)->head = (yyval.List)->tail = (node*)malloc(sizeof(node));
	(yyval.List)->head->val = "this";
}
#line 2029 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 28:
#line 536 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"new");
	insertIntoList((yyval.List),(yyvsp[-3].string));
	insertIntoList((yyval.List),"[");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),"]");
}
#line 2042 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 29:
#line 545 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"new");
	insertIntoList((yyval.List),(yyvsp[-2].string));
	insertIntoList((yyval.List),"()");
}
#line 2053 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 30:
#line 552 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"!");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2063 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 31:
#line 558 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"(");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),")");
}
#line 2074 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 32:
#line 566 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"&&");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2085 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 33:
#line 573 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"||");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2096 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 34:
#line 580 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"!=");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2107 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 35:
#line 587 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"==");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2118 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 36:
#line 594 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),">");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2129 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 37:
#line 601 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"<");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2140 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 38:
#line 608 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"<=");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2151 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 39:
#line 615 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),">=");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2162 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 40:
#line 622 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"+");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2173 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 41:
#line 629 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"-");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2184 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 42:
#line 636 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"*");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2195 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 43:
#line 643 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"/");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2206 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 44:
#line 650 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),"%");
	appendList(&(yyval.List),&(yyvsp[0].List));
}
#line 2217 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 45:
#line 657 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-6].List));
	insertIntoList((yyval.List),".");
	insertIntoList((yyval.List),(yyvsp[-4].string));
	insertIntoList((yyval.List),"(");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	listnode* h = ((yyvsp[-1].ListofList) == NULL)?NULL:((yyvsp[-1].ListofList)->head);
	while(h != NULL)
	{
		appendList(&(yyval.List),&(h->val));
		h = h->next;
	}
	insertIntoList((yyval.List),")");
}
#line 2237 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 46:
#line 673 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));//now we've to test for syntax errors due to poor macro usage or wrong macro names
	//identify all the parameters of the call, and then proceed to try for a macro matching.
	listnode* t = (yyvsp[-1].ListofList) -> head;//head to a list of lists
	int cnt = 0;
	while(t != NULL)
	{
		if((t->val != NULL) && (t->val->head != NULL) && strcmp(t->val->head->val,",") == 0)
			cnt++;
		t = t->next;
	}
	//there are now cnt+1 function arguments that are possible
	list* arr[cnt+1];
	arr[0] = (yyvsp[-2].List);
	int i = 1;
	t = (yyvsp[-1].ListofList) -> head;
	while(t != NULL)
	{
		if(t->val != NULL && (t->val->head != NULL) && strcmp(t->val->head->val,",") != 0)
			arr[i++] = t->val;//new identifier syntax to be replaced
		 t = t->next;
	}
	list* ans = substitute(macro_table,(yyvsp[-4].string),arr,cnt+1);//check if we got a valid macro substitution now
	if(ans == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList(&(yyval.List),&ans);//store the result over here please!
}
#line 2272 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 47:
#line 704 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	list* an = substitute(macro_table,(yyvsp[-2].string),NULL,0);
	if(an == NULL)
	{
		printf("// Failed to parse macrojava code.");
		exit(0);
	}
	appendList(&(yyval.List),&an);
}
#line 2287 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 48:
#line 715 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-4].List));
	insertIntoList((yyval.List),".");
	insertIntoList((yyval.List),(yyvsp[-2].string));
	insertIntoList((yyval.List),"()");
}
#line 2299 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 49:
#line 723 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),".");
	insertIntoList((yyval.List),(yyvsp[0].string));
}
#line 2310 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 50:
#line 732 "P1.y" /* yacc.c:1646  */
    {
	//insert into the macro definition table
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"#define");
	insertIntoList((yyval.List),(yyvsp[-5].string));
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),(yyvsp[-3].string));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),")");
	appendList(&(yyval.List),&(yyvsp[0].List));
	list* var = (list*)malloc(sizeof(list));
	insertIntoList(var,(yyvsp[-3].string));
	int cnt = 1;
	node* h = ((yyvsp[-2].List) == NULL)?(NULL):((yyvsp[-2].List)->head);
	while(h != NULL)
	{
		if(strcmp(h->val,",") == 0)
		{
			cnt++;
			insertIntoList(var,h->next->val);
			h = h->next->next;
		}
	}
	add_to_table(macro_table,(yyvsp[-5].string),var,(yyvsp[0].List),cnt);

}
#line 2341 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 51:
#line 759 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"#define");
	insertIntoList((yyval.List),(yyvsp[-3].string));
	insertIntoList((yyval.List),"()");
	appendList(&(yyval.List),&(yyvsp[0].List));
	add_to_table(macro_table,(yyvsp[-3].string),NULL,(yyvsp[0].List),0);
}
#line 2354 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 52:
#line 769 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"#define");
	insertIntoList((yyval.List),(yyvsp[-5].string));
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),(yyvsp[-3].string));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),")");
	appendList(&(yyval.List),&(yyvsp[0].List));
	list* var = (list*)malloc(sizeof(list));
	insertIntoList(var,(yyvsp[-3].string));
	int cnt = 1;
	node* h = ((yyvsp[-2].List) == NULL)?(NULL):((yyvsp[-2].List)->head);
	while(h != NULL)
	{
		if(strcmp(h->val,",") == 0)
		{
			cnt++;
			insertIntoList(var,h->next->val);
			h = h->next->next;
		}
	}
	add_to_table(macro_table,(yyvsp[-5].string),var,(yyvsp[0].List),cnt);
}
#line 2383 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 53:
#line 794 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),"#define");
	insertIntoList((yyval.List),(yyvsp[-3].string));
	insertIntoList((yyval.List),"()");
	appendList(&(yyval.List),&(yyvsp[0].List));
	add_to_table(macro_table,(yyvsp[-3].string),NULL,(yyvsp[0].List),0);
}
#line 2396 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 54:
#line 804 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (yyvsp[0].List);	
}
#line 2404 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 55:
#line 808 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (yyvsp[0].List);
}
#line 2412 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 56:
#line 812 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-1].List));
}
#line 2420 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 57:
#line 816 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
}
#line 2428 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 58:
#line 820 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-1].List));
}
#line 2436 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 59:
#line 824 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
}
#line 2444 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 60:
#line 828 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-3].List));
	insertIntoList((yyval.List),(yyvsp[-2].string));
	insertIntoList((yyval.List),(yyvsp[-1].string));
	insertIntoList((yyval.List),";");
}
#line 2455 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 61:
#line 835 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
}
#line 2463 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 62:
#line 839 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-3].List));
	insertIntoList((yyval.List),",");
	insertIntoList((yyval.List),(yyvsp[-1].string));
	insertIntoList((yyval.List),(yyvsp[0].string));
}
#line 2474 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 63:
#line 846 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
}
#line 2482 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 64:
#line 850 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = "public";
}
#line 2490 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 65:
#line 853 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = "private";
}
#line 2498 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 66:
#line 856 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = "protected";
}
#line 2506 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 67:
#line 859 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = "private";
}
#line 2514 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 68:
#line 863 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),(yyvsp[-14].string));
	insertIntoList((yyval.List),(yyvsp[-13].string));
	insertIntoList((yyval.List),(yyvsp[-12].string));
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),(yyvsp[-10].string));
	insertIntoList((yyval.List),(yyvsp[-9].string));
	appendList(&(yyval.List),&(yyvsp[-8].List));
	insertIntoList((yyval.List),")");
	insertIntoList((yyval.List),"{");
	appendList(&(yyval.List),&(yyvsp[-5].List));
	appendList(&(yyval.List),&(yyvsp[-4].List));
	insertIntoList((yyval.List),"return");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),";");
	insertIntoList((yyval.List),"}");
}
#line 2537 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 69:
#line 882 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),(yyvsp[-11].string));
	insertIntoList((yyval.List),(yyvsp[-10].string));
	insertIntoList((yyval.List),(yyvsp[-9].string));
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),")");
	insertIntoList((yyval.List),"{");
	appendList(&(yyval.List),&(yyvsp[-5].List));
	appendList(&(yyval.List),&(yyvsp[-4].List));
	insertIntoList((yyval.List),"return");
	appendList(&(yyval.List),&(yyvsp[-2].List));
	insertIntoList((yyval.List),";");
	insertIntoList((yyval.List),"}");
}
#line 2557 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 70:
#line 898 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),(yyvsp[-10].string));
	insertIntoList((yyval.List),(yyvsp[-9].string));
	insertIntoList((yyval.List),(yyvsp[-8].string));
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),(yyvsp[-6].string));
	insertIntoList((yyval.List),(yyvsp[-5].string));
	appendList(&(yyval.List),&(yyvsp[-4].List));
	insertIntoList((yyval.List),")");
	insertIntoList((yyval.List),"return");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),";");
}
#line 2576 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 71:
#line 913 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	insertIntoList((yyval.List),(yyvsp[-7].string));
	insertIntoList((yyval.List),(yyvsp[-6].string));
	insertIntoList((yyval.List),(yyvsp[-5].string));
	insertIntoList((yyval.List),"(");
	insertIntoList((yyval.List),")");
	insertIntoList((yyval.List),"return");
	appendList(&(yyval.List),&(yyvsp[-1].List));
	insertIntoList((yyval.List),";");
}
#line 2592 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 72:
#line 926 "P1.y" /* yacc.c:1646  */
    {
	appendList(&(yyval.List),&(yyvsp[-1].List));
}
#line 2600 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 73:
#line 930 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
}
#line 2608 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 74:
#line 935 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = (char*)malloc(sizeof(char)*11);
	(yyval.string) = itoa((yyvsp[0].integer));//decimal number to be stored as a char*
}
#line 2617 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 75:
#line 940 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = "boolean";
}
#line 2625 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 76:
#line 944 "P1.y" /* yacc.c:1646  */
    {
	//array type
	(yyval.string) = malloc(sizeof(char) * 40);
	strcpy((yyval.string),(yyvsp[-2].string));
	strcat((yyval.string),"[]");
}
#line 2636 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 77:
#line 950 "P1.y" /* yacc.c:1646  */
    {
	(yyval.string) = (yyvsp[0].string);//simply copy the pointer!
}
#line 2644 "P1.tab.c" /* yacc.c:1646  */
    break;

  case 78:
#line 955 "P1.y" /* yacc.c:1646  */
    {
	(yyval.List) = (list*)malloc(sizeof(list));
	appendList(&(yyval.List),&(yyvsp[-2].List));
	appendList(&(yyval.List),&(yyvsp[-1].List));
	appendList(&(yyval.List),&(yyvsp[0].List));
	printListLine((yyval.List));
}
#line 2656 "P1.tab.c" /* yacc.c:1646  */
    break;


#line 2660 "P1.tab.c" /* yacc.c:1646  */
      default: break;
    }
  /* User semantic actions sometimes alter yychar, and that requires
     that yytoken be updated with the new translation.  We take the
     approach of translating immediately before every use of yytoken.
     One alternative is translating here after every semantic action,
     but that translation would be missed if the semantic action invokes
     YYABORT, YYACCEPT, or YYERROR immediately after altering yychar or
     if it invokes YYBACKUP.  In the case of YYABORT or YYACCEPT, an
     incorrect destructor might then be invoked immediately.  In the
     case of YYERROR or YYBACKUP, subsequent parser actions might lead
     to an incorrect destructor call or verbose syntax error message
     before the lookahead is translated.  */
  YY_SYMBOL_PRINT ("-> $$ =", yyr1[yyn], &yyval, &yyloc);

  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);

  *++yyvsp = yyval;

  /* Now 'shift' the result of the reduction.  Determine what state
     that goes to, based on the state we popped back to and the rule
     number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTOKENS] + *yyssp;
  if (0 <= yystate && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTOKENS];

  goto yynewstate;


/*--------------------------------------.
| yyerrlab -- here on detecting error.  |
`--------------------------------------*/
yyerrlab:
  /* Make sure we have latest lookahead translation.  See comments at
     user semantic actions for why this is necessary.  */
  yytoken = yychar == YYEMPTY ? YYEMPTY : YYTRANSLATE (yychar);

  /* If not already recovering from an error, report this error.  */
  if (!yyerrstatus)
    {
      ++yynerrs;
#if ! YYERROR_VERBOSE
      yyerror (YY_("syntax error"));
#else
# define YYSYNTAX_ERROR yysyntax_error (&yymsg_alloc, &yymsg, \
                                        yyssp, yytoken)
      {
        char const *yymsgp = YY_("syntax error");
        int yysyntax_error_status;
        yysyntax_error_status = YYSYNTAX_ERROR;
        if (yysyntax_error_status == 0)
          yymsgp = yymsg;
        else if (yysyntax_error_status == 1)
          {
            if (yymsg != yymsgbuf)
              YYSTACK_FREE (yymsg);
            yymsg = (char *) YYSTACK_ALLOC (yymsg_alloc);
            if (!yymsg)
              {
                yymsg = yymsgbuf;
                yymsg_alloc = sizeof yymsgbuf;
                yysyntax_error_status = 2;
              }
            else
              {
                yysyntax_error_status = YYSYNTAX_ERROR;
                yymsgp = yymsg;
              }
          }
        yyerror (yymsgp);
        if (yysyntax_error_status == 2)
          goto yyexhaustedlab;
      }
# undef YYSYNTAX_ERROR
#endif
    }



  if (yyerrstatus == 3)
    {
      /* If just tried and failed to reuse lookahead token after an
         error, discard it.  */

      if (yychar <= YYEOF)
        {
          /* Return failure if at end of input.  */
          if (yychar == YYEOF)
            YYABORT;
        }
      else
        {
          yydestruct ("Error: discarding",
                      yytoken, &yylval);
          yychar = YYEMPTY;
        }
    }

  /* Else will try to reuse lookahead token after shifting the error
     token.  */
  goto yyerrlab1;


/*---------------------------------------------------.
| yyerrorlab -- error raised explicitly by YYERROR.  |
`---------------------------------------------------*/
yyerrorlab:

  /* Pacify compilers like GCC when the user code never invokes
     YYERROR and the label yyerrorlab therefore never appears in user
     code.  */
  if (/*CONSTCOND*/ 0)
     goto yyerrorlab;

  /* Do not reclaim the symbols of the rule whose action triggered
     this YYERROR.  */
  YYPOPSTACK (yylen);
  yylen = 0;
  YY_STACK_PRINT (yyss, yyssp);
  yystate = *yyssp;
  goto yyerrlab1;


/*-------------------------------------------------------------.
| yyerrlab1 -- common code for both syntax error and YYERROR.  |
`-------------------------------------------------------------*/
yyerrlab1:
  yyerrstatus = 3;      /* Each real token shifted decrements this.  */

  for (;;)
    {
      yyn = yypact[yystate];
      if (!yypact_value_is_default (yyn))
        {
          yyn += YYTERROR;
          if (0 <= yyn && yyn <= YYLAST && yycheck[yyn] == YYTERROR)
            {
              yyn = yytable[yyn];
              if (0 < yyn)
                break;
            }
        }

      /* Pop the current state because it cannot handle the error token.  */
      if (yyssp == yyss)
        YYABORT;


      yydestruct ("Error: popping",
                  yystos[yystate], yyvsp);
      YYPOPSTACK (1);
      yystate = *yyssp;
      YY_STACK_PRINT (yyss, yyssp);
    }

  YY_IGNORE_MAYBE_UNINITIALIZED_BEGIN
  *++yyvsp = yylval;
  YY_IGNORE_MAYBE_UNINITIALIZED_END


  /* Shift the error token.  */
  YY_SYMBOL_PRINT ("Shifting", yystos[yyn], yyvsp, yylsp);

  yystate = yyn;
  goto yynewstate;


/*-------------------------------------.
| yyacceptlab -- YYACCEPT comes here.  |
`-------------------------------------*/
yyacceptlab:
  yyresult = 0;
  goto yyreturn;

/*-----------------------------------.
| yyabortlab -- YYABORT comes here.  |
`-----------------------------------*/
yyabortlab:
  yyresult = 1;
  goto yyreturn;

#if !defined yyoverflow || YYERROR_VERBOSE
/*-------------------------------------------------.
| yyexhaustedlab -- memory exhaustion comes here.  |
`-------------------------------------------------*/
yyexhaustedlab:
  yyerror (YY_("memory exhausted"));
  yyresult = 2;
  /* Fall through.  */
#endif

yyreturn:
  if (yychar != YYEMPTY)
    {
      /* Make sure we have latest lookahead translation.  See comments at
         user semantic actions for why this is necessary.  */
      yytoken = YYTRANSLATE (yychar);
      yydestruct ("Cleanup: discarding lookahead",
                  yytoken, &yylval);
    }
  /* Do not reclaim the symbols of the rule whose action triggered
     this YYABORT or YYACCEPT.  */
  YYPOPSTACK (yylen);
  YY_STACK_PRINT (yyss, yyssp);
  while (yyssp != yyss)
    {
      yydestruct ("Cleanup: popping",
                  yystos[*yyssp], yyvsp);
      YYPOPSTACK (1);
    }
#ifndef yyoverflow
  if (yyss != yyssa)
    YYSTACK_FREE (yyss);
#endif
#if YYERROR_VERBOSE
  if (yymsg != yymsgbuf)
    YYSTACK_FREE (yymsg);
#endif
  return yyresult;
}
#line 962 "P1.y" /* yacc.c:1906  */


int yyerror(char *s)
{
	printf ("%s ERROR\n",s);
	return 0;
  
}
int main ()
{
	macro_table = (table*)(malloc(sizeof(table)));
	yyparse();
	return 0;
}
