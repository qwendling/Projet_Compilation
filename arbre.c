#include "arbre.h"
#include <stdlib.h>

Arbre newArbre(){
  return NULL;
}

Arbre new_const(int val){
  Arbre new = malloc(sizeof(std_arbre));
  new->type = ast_constant;
  new->val.constante = val;
  return new;
}

Arbre new_string(char* val){
  Arbre new = malloc(sizeof(std_arbre));
  new->type = ast_str;
  new->val.str = val;
  return new;
}
Arbre concat(Arbre a1,Arbre a2){
  Arbre tmp=a1;
  while(a1->freres != NULL){
    a1=a1->freres;
  }
  a1->freres=a2;
  return tmp;
}

Arbre ast_new_print(arbre_type type,Arbre feuille){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint->type = type;
  newprint->fils = feuille;
  return newprint;
}

Arbre ast_new_return(Arbre feuille){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint->type = ast_return;
  newprint->fils = feuille;
  return newprint;
}

Arbre ast_new_main(Arbre statement){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint->type = ast_main;
  newprint->fils = statement;
  return newprint;
}
