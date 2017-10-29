%{
	#include <stdio.h>
	#include "arbre.h"
%}


%union {int nombre;char* string;}
%token MAIN
%token RETURN
%token <nombre> NOMBRE
%token <string> STRING
%token PRINTF
%token PRINTI
%type <nombre> B
%start program
%%
program: fonction;

fonction: MAIN'('')''{'ListeInstr'}';

ListeInstr: | Instruction';'ListeInstr ;

//Les différentes instructions possible
Instruction: RETURN B { printf("return %d\n",$2);return $2;}
	|PRINTF'('STRING')' { printf("printf : %s\n",$3) ;}
	|PRINTI'('B')' { printf("%d\n",$3); }
	;

B: NOMBRE {$$=$1;};

%%
int yyerror(void){
	fprintf(stderr,"erreur de syntaxe\n");return 1;
}
