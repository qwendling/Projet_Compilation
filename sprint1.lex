%option nounput
%option noyywrap

%{
//###################################
//####### 	DECLARATION C ###########
//###################################

/* fichier dans lequel est defini les macros constantes */
#include "arbre.h"
#include "table_symbole.h"
#include "generationCI.h"
#include "genAssembleur.h"
#include "sprint1.tab.h"
#include <stdio.h>

/*----------- Variables globales --------------*/
Arbre ast;
Symbole sym_Table[TAILLE_TABLE];
//Liste chainé stockant les strings
ConstString string_const = NULL;


int return_value = 0;
%}

/*###################################
/*####### DECLARATION LEX	###########
/*###################################

/* --------- SPRINT 1 --------- */

MAIN "int main"
NOMBRE [0-9]*
COMMENT \/\*.*\*\/|([^\\]\/\/.*[\n])
STRING   \"([^\"\\]|\\.)*\"
RETURN return

/* --------- SPRINT 2 --------- */

ID [a-zA-Z_][a-zA-Z0-9_]*
INT "int"


/*###################################*/
/*####### REGLE SYNTAXIQUE ##########*/
/*###################################*/
%%
{COMMENT} {printf(" Commentaire %s\n",yytext);}
{MAIN} {printf("main reconnu\n");return MAIN;}
{RETURN} {printf("return reconnu\n");return RETURN;}
{NOMBRE} {printf("entier lu\n");yylval.nombre=atoi(yytext); return NOMBRE;}
{STRING} {yylval.string=strdup(yytext); return STRING;}

printf {return PRINTF;}
printi {return PRINTI;}

[{}();] {printf("Envoie de : %s\n",yytext); return yytext[0];}
=		{return yytext[0];}
[+-/*] {printf("Envoie Expression Math de  : %s\n",yytext);yylval.ope = yytext[0]; return OPE;}

. {printf("caractere ignoré: %s\n",yytext);}

{INT} {printf("type reconnu : %s \n",yytext); return INT;}
{ID}	{printf("id reconnu : %s \n",yytext); return ID;}

%%


//###################################
//##### CODE ADDITIONNEL C	#########
//###################################

int main(int argc, char **argv )
{
	// Ouverture du fichier
	yyin = fopen(argv[1],"r");
	yyparse();
	fclose(yyin);

	printf("\n########## AST ##########\n\n");
	ast_print(ast);

	// Generation de quad aprés remplissage de l'AST et des constantes String
	quad code = genCode(ast,sym_Table,&string_const);
	printf("\n########## QUADS ##########\n\n");
	print_quad(code);

	printf("\n###### CONST STRING ######\n\n");
	print_const(string_const);

	// Generation du code assembleur dans le fichier test.s
	FILE* file = fopen("test.s","w");
	// 1.Header
	genAssembleur_header(string_const,file);
	// 2.Generation a partir des quads
	genAssembleur(code,sym_Table,file);

	return return_value;
}
