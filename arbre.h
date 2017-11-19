#ifndef ARBRE_H
#define ARBRE_H

// Enum des types de Noeuds dans l'AST
typedef enum arbre_type{
  ast_constant,
  ast_str,
  ast_printf,
  ast_printi,
  ast_return,
  ast_main
}arbre_type;

// Union definissant les valeurs possibles d'une feuille
typedef union tree_value{
  char* str;
  int constante;
}tree_value;

// Structure de l'AST
typedef struct str_arbre{
  arbre_type type;
  struct str_arbre* fils;
  struct str_arbre* freres;
  tree_value val;
} std_arbre,*Arbre;

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

//Affiche dans le terminal l'AST avec ses profondeurs 
void ast_print(Arbre a);

#endif
