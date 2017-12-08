#ifndef ARBRE_H
#define ARBRE_H

#include "table_symbole.h"
#include "quad.h"

// Enum des types de Noeuds dans l'AST
typedef enum arbre_type{
  //--- Sprint 1
  ast_constant,
  ast_str,
  ast_printf,
  ast_printi,
  ast_return,
  ast_main,

  //--- Sprint 2
  ast_var,
  ast_plus,
  ast_moins,
  ast_fois,
  ast_div,
  ast_affectation,
  ast_declaration,
  ast_autoIncrementPlus,
  ast_autoIncrementMoins,

  //--- Sprint 3
  ast_and,
  ast_or,
  ast_not,
  ast_equal,
  ast_nequal,
  ast_greater,
  ast_greaterOrEqual,
  ast_less,
  ast_lessOrEqual,
  ast_if,
  ast_bloc,

  //--- Sprint 4
  ast_while,
  ast_for,

	//--- Sprint 5
	ast_tableau,
	ast_listTableau,

  //--- Sprint 6
  ast_stencil,
  ast_applyStencil,

  ast_fonction,
  ast_args,
  ast_instruction

}arbre_type;

// Structure du stencil
typedef struct str_stencil{
	int profondeurs;
  int member;
  char* name;
} std_stencil, *Stencil;

// Union definissant les valeurs possibles d'une feuille
typedef union tree_value{
  char* str;
  int constante;
  char op;
  struct{
    quad trueList;
    quad falseList;
  } boolList;
  std_stencil stencil;
}tree_value;

// Structure de l'AST
typedef struct str_arbre{
  arbre_type type;
  struct str_arbre* fils;
  struct str_arbre* freres;
  tree_value val;
} std_arbre,*Arbre;

// Structure de la liste de Define
typedef struct str_define{
	char* id;
	int cst;
	struct str_define* next;
} std_define, *ListeDefine;

Arbre new_ast_instruction(Arbre instruction);
Arbre new_ast_args(Arbre args);
Arbre new_ast_fonction(char* id, Arbre args, Arbre fct);
int replaceIdMain(Arbre ast);

int replaceIdVarFct(char *id, Arbre ast);
int repaceIdInAST(Arbre ast);
//------- SPRINT 1 -------

//creation d'un arbre vide
Arbre newArbre();

//creation d'une feuille const
Arbre new_const(int val);

//creation d'une feuille string
Arbre new_string(char* str);

//ajout de a2 dans les frere de a1
Arbre concat(Arbre a1,Arbre a2);

//Ajout d'un noeud print
Arbre ast_new_print(arbre_type type,Arbre feuille);

//Ajout d'un noeud return
Arbre ast_new_return(Arbre feuille);

//Ajout un noeud main
Arbre ast_new_main(Arbre statement);


//------- SPRINT 2 -------

//creation d'une feuille variable avec un ID donné
Arbre new_var(char* var);

//Ajout d'un noeud de declaration
Arbre ast_new_declaration(Arbre feuille);

//Ajout d'un noeud affectation
Arbre ast_new_affectation(Arbre id, Arbre Expr);

//Ajout d'un noeud somme
Arbre ast_new_plus(Arbre operande1, Arbre operande2);

//Ajout d'un noeud soustraction
Arbre ast_new_moins(Arbre operande1, Arbre operande2);

//Ajout d'un noeud division
Arbre ast_new_div(Arbre operande1, Arbre operande2);

//Ajout d'un noeud produit
Arbre ast_new_fois(Arbre operande1, Arbre operande2);

//Ajout d'un noeud AutoIncrementation +
Arbre ast_new_autoIncrement_plus(Arbre var);

//Ajout d'un noeud AutoIncrementation -
Arbre ast_new_autoIncrement_moins(Arbre var);

//Libere la mémoire de l'AST
void ast_free(Arbre);


//------- SPRINT 3 -------

//Ajout d'un noeud &&
Arbre ast_new_and(Arbre operande1, Arbre operande2);

//Ajout d'un noeud ||
Arbre ast_new_or(Arbre operande1, Arbre operande2);

//Ajout d'un noeud !
Arbre ast_new_not(Arbre operande);

//Ajout d'un noeud ==
Arbre ast_new_equal(Arbre operande1, Arbre operande2);

//Ajout d'un noeud !=
Arbre ast_new_nequal(Arbre operande1, Arbre operande2);

//Ajout d'un noeud >
Arbre ast_new_greater(Arbre operande1, Arbre operande2);

//Ajout d'un noeud >=
Arbre ast_new_greaterOrEqual(Arbre operande1, Arbre operande2);

//Ajout d'un noeud <
Arbre ast_new_less(Arbre operande1, Arbre operande2);

//Ajout d'un noeud <=
Arbre ast_new_lessOrEqual(Arbre operande1, Arbre operande2);

//Ajout d'un noeud de condition IF
Arbre ast_new_if(Arbre ifCondition, Arbre ifInstructions, Arbre elseInstructions);


//------- SPRINT 4 -------

//Ajout d'un noeud de boucle for
Arbre ast_new_for(Arbre inits,Arbre conditions,Arbre increments,Arbre instructions);

//Ajout d'un noeud de boucle while
Arbre ast_new_while(Arbre conditions, Arbre instructions);


//------- SPRINT 5 -------
Arbre ast_new_tableauDeclare(char* id, Arbre dimension, Arbre affect);

Arbre ast_new_tableauAffec(char* id, Arbre dimension, Arbre affect);

Arbre new_tableau(char* id, Arbre dimension);

Arbre ast_new_blocTableau(Arbre a);

int verifTableau(Arbre Dim , Arbre tableau);


//------- SPRINT 6 -------

Arbre new_stencil(char* id);

Arbre ast_new_stencilDeclare(char* id,Arbre member,int n,int prof);

Arbre ast_new_blocStencil(Arbre a);

Arbre ast_new_applyStencilD(Arbre stencil, Arbre tableau);

Arbre ast_new_applyStencilG(Arbre tableau,Arbre stencil);

int verifStencil(Arbre astStencil, int member, int dim);


//------- All sprints -------
//Affiche dans le terminal l'AST général avec ses frères et fils
void ast_print(Arbre a);

//Affiche dans le terminal l'AST donné a une profondeur donné
void ast_print_aux(Arbre a,int profondeur);

//return 0 si l'analyse et bonne sinon ficher non semantiquement correct
int ast_semantique(Arbre a ,Symbole sym_table[TAILLE_TABLE]);


//------- DEFINE -------

ListeDefine newListeDefine();

ListeDefine new_define(char* id, int constante);

ListeDefine concat_define(ListeDefine d,ListeDefine r);

void replaceDefineInAST(Arbre ast,ListeDefine d);

ListeDefine findInDefine(ListeDefine d, char* id);

void print_define(ListeDefine d);




#endif
