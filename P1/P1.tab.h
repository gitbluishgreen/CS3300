/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

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
#line 272 "P1.y" /* yacc.c:1909  */

    int integer;
    char character;
    char* string;
    struct list* List;
    struct listoflist* ListofList;

#line 116 "P1.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_P1_TAB_H_INCLUDED  */
