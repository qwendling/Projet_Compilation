%option nounput
%option noyywrap

%{
/* Declaration C */

/* fichier dans lequel est defini les macros constantes */
#include "sprint1.tab.h" 
#include <stdio.h>

union {int ival; char *sval; double fval;} yylval;

%}

/* Declaration Lex */

/* ###### SPRINT 1 ###### */

MAIN "int main"
NOMBRE [0-9]*
COMMENT \/\*.*\*\/
ENDLIGNE [\n]
STRING   \"([^\"\\]|\\.)*\"
RETURN return\ [0-9]* 

/* ##################### */




/* Regle syntaxique */
%%
{COMMENT}* ;
{ENDLIGNE}* ;

{MAIN} {return MAIN;}
{RETURN} {return RETURN;}
{NOMBRE} {yylval.ival=atoi(yytext); return NOMBRE;}
{STRING} {yylval.sval=strdup(yytext); return STRING;}


printf {return PRINTF;}
printi {return PRINTI;}

%%


/* Code C additionnel */
int main(int argc, char **argv )
{
	yylex();
	return 0;
}
