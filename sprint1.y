%{
	//###################################
	//####### 	DECLARATION C ###########
	//###################################

	#include <stdio.h>
	#include "arbre.h"
	extern Arbre ast;
	int yylex();
	void yyerror(const char*);
	extern int return_value;
%}

/*--------- Declaration tokens et récuperation regex LEX---------*/
%union {int nombre;char* string;char ope; Arbre ast;}
%token MAIN
%token RETURN
%token <nombre> NOMBRE
%token <string> STRING
%token PRINTF
%token PRINTI
%token <string> ID
%token INT
%token <string> INCREMENTPLUSBEFORE
%token <string> INCREMENTPLUSAFTER
%token <string> INCREMENTMOINSAFTER
%token <string> INCREMENTMOINSBEFORE
%type <ast> B
%type <ast> Instruction
%type <ast> ListeInstr
%type <ast> fonction
%type <ast> program
%type <ast> Declaration
%type <ast> Expression
%type <ast> Affectation
%type <ast> Facteur
%type <ast> Terme
%type <ast> AutoIncremente


%left '+' '-'
%left '*' '/'
%left UMOINS
%left AUTOINCR

%start program


%%
//###################################
//####### REGLE TRADUCTION ##########
//###################################

// Le program est une fonction qu'on considère comme un arbre ast
program: fonction {ast=$1;};

// La fonction main prend comme valeur la liste des instructions
fonction: MAIN'('')''{'ListeInstr'}' {$$=ast_new_main($5);}
	;

// Une liste d'instruction est une  succession d'instruction se terminant par ;
ListeInstr: Instruction';'ListeInstr { $$=concat($1,$3);}
	| Instruction';' {$$=$1;}
	;

// Les différentes instructions possible
Instruction: RETURN Expression { $$=ast_new_return($2);}
	|PRINTF'('STRING')' { $$=ast_new_print(ast_printf,new_string($3));}
	|PRINTI'('Expression')' { $$=ast_new_print(ast_printi,$3); }
	|Declaration { $$=$1;}
	|Affectation { $$=$1;}
	|AutoIncremente {$$=$1;}
	;



//---- NATHAN SPRINT 2

Declaration: INT Affectation{$$=ast_new_declaration(new_var($2->fils->val.str)); $$->freres = $2;}
	| INT ID {$$=ast_new_declaration(new_var($2));}
	;

Affectation: ID '=' Expression {$$=ast_new_affectation(new_var($1),$3);}
	;

// Les différents expressions arithmétiques possibles
Expression: Expression'+'Terme {$$ = ast_new_plus($1,$3);}
	|	Expression'-'Terme {$$ = ast_new_moins($1,$3);}
	|	Terme {$$ = $1;}
	;

Terme: Terme'*'Facteur {$$ = ast_new_fois($1,$3);}
	| Terme'/'Facteur {$$ = ast_new_div($1,$3);}
	|	Facteur {$$ = $1;}
	;

Facteur: '('Expression')' {$$ = $2;}
	| '-''('Expression')' {$$ = ast_new_fois(new_const(-1),$3);} %prec UMOINS
	| B {$$ = $1;}
	| '-'B {$$ = ast_new_fois(new_const(-1),$2);} %prec UMOINS
	;

AutoIncremente:	INCREMENTPLUSAFTER {$$=ast_new_autoIncrement_plus(new_var($1));} %prec AUTOINCR
	| INCREMENTMOINSAFTER {$$=ast_new_autoIncrement_moins(new_var($1));;} %prec AUTOINCR
	| INCREMENTMOINSBEFORE {$$=ast_new_affectation(new_var($1),ast_new_moins(new_var($1),new_const(1)));} %prec AUTOINCR
	| INCREMENTPLUSBEFORE {$$=ast_new_affectation(new_var($1),ast_new_plus(new_var($1),new_const(1)));} %prec AUTOINCR
	;

B: NOMBRE {$$=new_const($1);}
	| ID { $$ = new_var($1);}
	| AutoIncremente {$$ = $1;}
	;

%%

// Fonction pour signaler une erreur
void yyerror(const char* s){
	fprintf(stderr,"erreur de syntaxe\n");
	return_value = 1;
}
