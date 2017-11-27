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

INCREMENTPLUS "++"
INCREMENTMOINS "--"

/* --------- SPRINT 3 --------- */

IF "if"
ELSE "else"
EQUAL "=="
SUPP ">"
INF "<"
SUPPEQU ">="
INFEQU "<="
DIFFERENCE "!="
NOT "!"
AND "&&"
OR "||"

/* --------- SPRINT 4 --------- */

WHILE "while"
FOR "for"


/*###################################*/
/*####### REGLE SYNTAXIQUE ##########*/
/*###################################*/
%%
{IF} { return IF; }
{ELSE} { return ELSE;}

{WHILE} {printf("debut while \n");return WHILE;}
{FOR} {printf("debut for \n");return FOR;}

{COMMENT} {}
{MAIN} {return MAIN;}
{RETURN} {return RETURN;}
{NOMBRE} {yylval.nombre=atoi(yytext); return NOMBRE;}
{STRING} {yylval.string=strdup(yytext); return STRING;}

printf {return PRINTF;}
printi {return PRINTI;}

[\{\}\(\)\;] {return yytext[0];}
=		{return yytext[0];}
[+-/*] {return yytext[0];}




{INT}	{return INT;}
{ID}	{yylval.string=strdup(yytext); return ID;}
{ID}{INCREMENTMOINS} {yytext[strlen(yytext)-2]='\0';
                      yylval.string=strdup(yytext);
                      return INCREMENTMOINSAFTER;}
{INCREMENTMOINS}{ID} {yylval.string=strdup(yytext+2);return INCREMENTMOINSBEFORE;}
{ID}{INCREMENTPLUS}  {yytext[strlen(yytext)-2]='\0';
                      yylval.string=strdup(yytext);
                      return INCREMENTPLUSAFTER;}
{INCREMENTPLUS}{ID}  {yylval.string=strdup(yytext+2);return INCREMENTPLUSBEFORE;}



{EQUAL} {return EQUAL;}
{SUPP} {return SUPP;}
{INF} {return INF;}
{SUPPEQU} {return SUPPEQU;}
{INFEQU} {return INFEQU;}
{DIFFERENCE} {return DIFFERENCE;}
{NOT} {return NOT;}
{AND} {return AND;}
{OR} {return OR;}





. {;}
%%


//###################################
//##### CODE ADDITIONNEL C	#########
//###################################

// Free the memory allocated for Lex when we are done.
void lex_free() {
  yy_delete_buffer(YY_CURRENT_BUFFER);
  free(yy_buffer_stack);
}

int main(int argc, char **argv )
{
	// Ouverture du fichier
	yyin = fopen(argv[1],"r");
	yyparse();
	fclose(yyin);
  if(return_value)
    return_value;

	printf("\n########## AST ##########\n\n");
	ast_print(ast);

	if(ast_semantique(ast,sym_Table)){
		printf("erreur semantique \n");
		return 1;
	}

	// Generation de quad aprés remplissage de l'AST et des constantes String
	quad code = genCode(ast,sym_Table);

	ast_free(ast);
	printf("\n########## QUADS ##########\n\n");
	print_quad(code);

	printf("\n########## MIPS ##########\n\n");
	// Generation du code assembleur dans le fichier test.s
	FILE* file = fopen("test.s","w");
	// 1.Header
	genAssembleur_header(sym_Table,file);
	// 2.Generation a partir des quads
	genAssembleur(code,sym_Table,file);

  // Liberation de la memoire utilise
	quad_free(code);
	sym_delete_table(sym_Table);
	lex_free();

	fclose(file);

	return return_value;
}
