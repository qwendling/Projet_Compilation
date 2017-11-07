%option nounput
%option noyywrap

%{
/* Declaration C */

/* fichier dans lequel est defini les macros constantes */
#include "arbre.h"
#include "table_symbole.h"
#include "generationCI.h"
#include "sprint1.tab.h"
#include <stdio.h>

Arbre ast;
%}

/* Declaration Lex */

/* ###### SPRINT 1 ###### */

MAIN "int main"
NOMBRE [0-9]*
COMMENT \/\*.*\*\/|([^\\]\/\/.*[\n])
STRING   \"([^\"\\]|\\.)*\"
RETURN return

/* ##################### */




/* Regle syntaxique */
%%
{COMMENT} {printf(" Commentaire %s\n",yytext);}
{MAIN} {printf("main reconnu\n");return MAIN;}
{RETURN} {printf("return reconnu\n");return RETURN;}
{NOMBRE} {printf("entier lu\n");yylval.nombre=atoi(yytext); return NOMBRE;}
{STRING} {yylval.string=strdup(yytext); return STRING;}


printf {return PRINTF;}
printi {return PRINTI;}

[{}();] {printf("Envoie de : %s\n",yytext); return yytext[0];}
. {printf("caractere ignoré: %s\n",yytext);}

%%


/* Code C additionnel */
int main(int argc, char **argv )
{
	yyin = fopen(argv[1],"r");
	yyparse();
	fclose(yyin);

	ast_print(ast);

	return 0;
}
