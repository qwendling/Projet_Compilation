#include "arbre.h"
#include <stdlib.h>

Arbre newArbre(){
  return NULL;
}

Arbre new_const(int val){
  Arbre new = malloc(sizeof(std_arbre));
  new->type = ast_constant;
  new->val = val;
  return new;
}

Arbre new_string(char* val){
  Arbre new = malloc(sizeof(std_arbre));
  new->type = ast_str;
  new->val = val;
  return new;
}
Arbre concat(Abre a1,Arbre a2){
  Arbre tmp=a1;
  while(a1->freres != NULL){
    a1=a1->freres;
  }
  a1->freres=a2;
  return tmp;
}

Arbre ast_new_print(arbre_type type,Arbre feuille){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint.type = type;
  newprint.fils = feuille;
  return newprint;
}

Arbre ast_new_return(arbre_type type,Arbre feuille){
  Arbre newprint = malloc(sizeof(std_arbre));
  newprint.type = type;
  newprint.fils = feuille;
  return newprint;
}
