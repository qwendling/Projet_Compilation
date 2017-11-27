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

// ---- Sprint 1 Tokens
%token MAIN
%token RETURN
%token <nombre> NOMBRE
%token <string> STRING
%token PRINTF
%token PRINTI

// ---- Sprint 2 Tokens
%token <string> ID
%token INT
%token <string> INCREMENTPLUSBEFORE
%token <string> INCREMENTPLUSAFTER
%token <string> INCREMENTMOINSAFTER
%token <string> INCREMENTMOINSBEFORE

// ---- Sprint 3 Tokens
%token EQUAL
%token SUPP
%token INF
%token SUPPEQU
%token INFEQU
%token DIFFERENCE
%token NOT
%token AND
%token OR
%token IF
%token ELSE

// ---- Sprint 4 Tokens
%token WHILE
%token FOR

// ---- AST
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
%type <ast> Condition
%type <ast> ExprBoolean
%type <ast> ListeCondition
%type <ast> Boucle
%type <ast> ListeInit
%type <ast> ListeIncrement
%type <ast> InitMember

// ---- Gestion de la priorite
%left NOT
%left AND
%left OR
%left '+' '-'
%left '*' '/'
%left UMOINS
%left AUTOINCR


%start program


%%
//###################################
//####### REGLE TRADUCTION ##########
//###################################


//---------- STRUCTURE PROGRAMME -------------//
// Le program est une fonction qu'on considère comme un arbre ast
program: fonction {ast=$1;};

// La fonction main prend comme valeur la liste des instructions
fonction: MAIN'('')''{'ListeInstr'}' {$$=ast_new_main($5);}
	;

// Une liste d'instruction est une  succession d'instruction se terminant par ;
ListeInstr: Instruction';'ListeInstr { $$=concat($1,$3);}
	| Instruction';' {$$=$1;}
	| Condition ListeInstr {$$=concat($1,$2);}
	| Condition {$$=$1;}
	| Boucle  ListeInstr {$$=concat($1,$2);}
	| Boucle {$$=$1;}
	;

// Les différentes instructions possible
Instruction: RETURN Expression { $$=ast_new_return($2);}
	|PRINTF'('STRING')' { $$=ast_new_print(ast_printf,new_string($3));}
	|PRINTI'('Expression')' { $$=ast_new_print(ast_printi,$3); }
	|Declaration { $$=$1;}
	|Affectation { $$=$1;}
	|AutoIncremente {$$=$1;}
	;

//---------- DECLARATION VARIABLE -------------//
// Declaration de variable soit par une affectation de valeur soit vide
Declaration: INT Affectation{$$=ast_new_declaration(new_var($2->fils->val.str)); $$->freres = $2;}
	| INT ID {$$=ast_new_declaration(new_var($2));}
	;

//---------- AFFECTATION VARIABLE -------------//
// Une affectation correspond a un ID prenant comme valeur une expression
Affectation: ID '=' Expression {$$=ast_new_affectation(new_var($1),$3);}
	;

//---------- EXPRESSION ARITHMETIQUE -------------//
// Expressions arithmétiques + -, avec respect de la priorité
Expression: Expression'+'Terme {$$ = ast_new_plus($1,$3);}
	|	Expression'-'Terme {$$ = ast_new_moins($1,$3);}
	|	Terme {$$ = $1;}
	;

// Expressions arithmétiques * /, avec respect de la priorité
Terme: Terme'*'Facteur {$$ = ast_new_fois($1,$3);}
	| Terme'/'Facteur {$$ = ast_new_div($1,$3);}
	|	Facteur {$$ = $1;}
	;

// Priorité maximal dans une expression arithmétiques, - unaire et parenthèse
Facteur: '('Expression')' {$$ = $2;}
	| '-''('Expression')' {$$ = ast_new_fois(new_const(-1),$3);} %prec UMOINS
	| B {$$ = $1;}
	| '-'B {$$ = ast_new_fois(new_const(-1),$2);} %prec UMOINS
	;

//---------- AUTO INCREMENTATION -------------//
// Gestion de l'AutoIncrementation avant (BEFORE) et aprés (AFTER) la variable a incrémenter
AutoIncremente:	INCREMENTPLUSAFTER {$$=ast_new_autoIncrement_plus(new_var($1));} %prec AUTOINCR
	| INCREMENTMOINSAFTER {$$=ast_new_autoIncrement_moins(new_var($1));;} %prec AUTOINCR
	| INCREMENTMOINSBEFORE {$$=ast_new_affectation(new_var($1),ast_new_moins(new_var($1),new_const(1)));} %prec AUTOINCR
	| INCREMENTPLUSBEFORE {$$=ast_new_affectation(new_var($1),ast_new_plus(new_var($1),new_const(1)));} %prec AUTOINCR
	;

//---------- ETAT TERMINAL -------------//
// Etat terminal qui peut etre soit un nombre, un variable ou une incrementation de variable
B: NOMBRE {$$=new_const($1);}
	| ID { $$ = new_var($1);}
	| AutoIncremente {$$ = $1;}
	;


//---------- CONDITIONS -------------//
// Gestion des IF types possible
Condition: IF '('ListeCondition')''{' ListeInstr '}' ELSE '{' ListeInstr '}' {$$=ast_new_if($3,$6,$10);}
	| IF '('ListeCondition')''{' ListeInstr '}' {$$=ast_new_if($3,$6,NULL);}
	| IF '('ListeCondition')' Instruction ';' {$$=ast_new_if($3,$5,NULL);}
	;

// Liste des conditions multiples possibles
ListeCondition: ListeCondition AND ListeCondition {$$=ast_new_and($1,$3);}
	| ListeCondition OR ListeCondition {$$=ast_new_or($1,$3);}
	| NOT ListeCondition {$$=ast_new_not($2);}
	| '('ListeCondition')' {$$=$2;}
	| ExprBoolean {$$=$1;}
	;

// Expression boolean possible
ExprBoolean: B EQUAL B {$$=ast_new_equal($1,$3);}
	| B SUPP B {$$=ast_new_greater($1,$3);}
	| B INF B {$$=ast_new_less($1,$3);}
	| B SUPPEQU B {$$=ast_new_greaterOrEqual($1,$3);}
	| B INFEQU B {$$=ast_new_lessOrEqual($1,$3);}
	| B DIFFERENCE B {$$=ast_new_nequal($1,$3);}
	;


//---------- BOUCLES -------------//
//Gestion des boucles type possible
Boucle: FOR'('ListeInit';'ListeCondition';'ListeIncrement')''{'ListeInstr'}' {$$=ast_new_for($3,$5,$7,$10);}
	| WHILE'('ListeCondition')''{'ListeInstr'}' {$$=ast_new_while($3,$6);}
	;

//Liste des initialiseurs dans la boucle for
ListeInit:InitMember','ListeInit {$$=concat($1,$3);}
	|InitMember {$$=$1;}
	;

// Initialiseurs possible
InitMember: Affectation {$$=$1;}
	| Declaration {$$=$1;}
	| {$$=NULL;}
	;

// Liste des Incrementations dans la boucle for
ListeIncrement: AutoIncremente',' ListeIncrement {$$=concat($1,$3);}
	| AutoIncremente {$$=$1;}
	;

%%

// Fonction pour signaler une erreur
void yyerror(const char* s){
	fprintf(stderr,"erreur de syntaxe\n");
	return_value = 1;
}
