#include <stdlib.h>
#include <stdio.h>
#include "generationCI.h"

// Ajoute un quad dans la liste q
quad quad_add(quad q,quad_op op,Symbole s1,Symbole s2,Symbole s3){
  quad new= malloc(sizeof(std_quad));
  new->op=op;
  new->arg1=s1;
  new->arg2=s2;
  new->res=s3;
  new->next=q;
  return new;
}

// Concatène deux liste de quad
quad add_quad(quad q1,quad q2){
  if(q1 == NULL){
      return q2;
  }
  q1->next = add_quad(q1->next,q2);

  return q1;
}

// Supprime la liste quad
void quad_free(quad q){
  if(q == NULL)
    return;
  quad_free(q->next);
  free(q);
}

// genere les quads depuis l'AST en stockant dans la table des symboles et strings
quad genCode(Arbre ast,Symbole sym_table[TAILLE_TABLE],ConstString* string_table){
  //nouveau symbole du quad
  Symbole tmp;
  quad codegen = NULL,arg = NULL;
  Arbre fils;
  //Suivant le type de l'AST le quad est différent
  switch(ast->type){
    case ast_constant:
      tmp = sym_new_tmp(sym_table);
      tmp->type = sym_const;
      tmp->val.entier = ast->val.constante;
      codegen = quad_add(codegen,affectation,NULL,NULL,tmp);
      break;
    case ast_str:
      tmp = sym_new_tmp(sym_table);
      tmp->type = sym_string;
      tmp->val.str = ast->val.str;
      codegen = quad_add(codegen,create_string,NULL,NULL,tmp);

      // Si string alors on l'ajoute aussi dans la liste ConstString
      ConstString newConst = malloc(sizeof(std_string));
      newConst->next = *string_table;
      newConst->name = tmp->name+1;
      newConst->val = ast->val.str;
      *string_table = newConst;
      break;
    case ast_printf:
      // on genere le quad de la constante a afficher
      arg = genCode(ast->fils,sym_table,string_table);
      codegen = arg;
      codegen = add_quad(codegen,quad_add(NULL,print_f,arg->res,NULL,NULL));
      break;
    case ast_printi:
      // on genere le quad de la constante a afficher
      arg = genCode(ast->fils,sym_table,string_table);
      codegen = arg;
      codegen = add_quad(codegen,quad_add(NULL,print_i,arg->res,NULL,NULL));
      break;
    case ast_return:
      // on genere le quad de la valeur a return
      arg = genCode(ast->fils,sym_table,string_table);
      codegen = arg;
      codegen = add_quad(codegen,quad_add(NULL,return_prog,arg->res,NULL,NULL));
      break;
    case ast_main:
      codegen = quad_add(codegen,create_main,NULL,NULL,NULL);
      fils = ast->fils;
      // On parcoure l'AST pour générer tout les quads
      while(fils != NULL){
        codegen = add_quad(codegen,genCode(fils,sym_table,string_table));
        fils = fils->freres;
      }
      break;

  }
  return codegen;
}

//Affiche les quads sur le terminal
void print_quad(quad q){
  if(q == NULL)
    return;
  switch (q->op){
    case print_i:
      printf("print_i %s\n",q->arg1->name);
      break;
    case print_f:
      printf("print_f %s\n",q->arg1->name);
      break;
    case affectation:
      printf("affectation %s\n",q->res->name);
      break;
    case return_prog:
      printf("return %s\n",q->arg1->name);
      break;
  }
  print_quad(q->next);
}


// Affiche les strings sur le terminal
void print_const(ConstString s){
  if(s == NULL){
    return;
  }
  printf("%s val : %s\n",s->name,s->val);
  print_const(s->next);
}

// Supprime ConstString
void constString_free(ConstString conststring){
  if(conststring == NULL)
    return;
  constString_free(conststring->next);
  free(conststring);
}
