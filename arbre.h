#ifndef ARBRE_H
#define ARBRE_H

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
  ast_autoIncrementMoins
}arbre_type;

// Union definissant les valeurs possibles d'une feuille
typedef union tree_value{
  char* str;
  int constante;
  char op;
}tree_value;

// Structure de l'AST
typedef struct str_arbre{
  arbre_type type;
  struct str_arbre* fils;
  struct str_arbre* freres;
  tree_value val;
} std_arbre,*Arbre;

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


//------- All sprints -------
//Affiche dans le terminal l'AST général avec ses frères et fils
void ast_print(Arbre a);

//Affiche dans le terminal l'AST donné a une profondeur donné
void ast_print_aux(Arbre a,int profondeur);

#endif
