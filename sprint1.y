%{
	#include <stdio.h>
	#include "arbre.h"
	extern Arbre ast;
	int yylex();
	void yyerror(const char*);
	extern return_value;
%}


%union {int nombre;char* string;Arbre ast;}
%token MAIN
%token RETURN
%token <nombre> NOMBRE
%token <string> STRING
%token PRINTF
%token PRINTI
%type <ast> B
%type <ast> Instruction
%type <ast> ListeInstr
%type <ast> fonction
%type <ast> program
%start program
%%
program: fonction {ast=$1;};

fonction: MAIN'('')''{'ListeInstr'}' {$$=ast_new_main($5);}
	;

ListeInstr: Instruction';'ListeInstr { $$=concat($1,$3);}
	| Instruction';' {$$=$1;}
	;

//Les différentes instructions possible
Instruction: RETURN B { $$=ast_new_return($2);}
	|PRINTF'('STRING')' { $$=ast_new_print(ast_printf,new_string($3));}
	|PRINTI'('B')' { $$=ast_new_print(ast_printi,$3); }
	;

B: NOMBRE {$$=new_const($1);};

%%
void yyerror(const char* s){
	fprintf(stderr,"erreur de syntaxe\n");
	return_value = 1;
}
