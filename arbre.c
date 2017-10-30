#include "arbre.h"
#include <stdlib.h>
#include <stdio.h>

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



void ast_print_aux(Arbre a,int profondeur){
  if(a==NULL)
    return;
  int i;
  for(i=0;i<profondeur;i++){
    printf("-");
  }
  switch(a->type){
    case ast_constant:
      printf("ast_constant\n");
      break;
    case ast_str:
      printf("ast_str\n");
      break;
    case ast_printf:
      printf("ast_printf\n");
      break;
    case ast_printi:
      printf("ast_printi\n");
      break;
    case ast_return:
      printf("ast_return\n");
      break;
    case ast_main:
      printf("ast_main\n");
      break;
  }

  ast_print_aux(a->fils,profondeur+1);
  ast_print_aux(a->freres,profondeur);

}

void ast_print(Arbre a){
  ast_print_aux(a,0);
}
