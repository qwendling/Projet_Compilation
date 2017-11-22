#include "arbre.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


Arbre new_var(char* var){
	Arbre new = calloc(1,sizeof(std_arbre));	
	printf("var : %s",var);
	new->type = ast_var;
	new->val.str = strdup(var);
	// On return une feuille de type ast_var
	return new;
}

Arbre new_op(arbre_type type, char op){
	Arbre new = calloc(1,sizeof(std_arbre));		
	new->type = type;
	new->val.op = op;
	// On return une feuille de type ast_op_OP
	return new;
}

Arbre ast_new_affectation(Arbre id, Arbre expr){
  Arbre newaffec = calloc(1,sizeof(std_arbre));
  newaffec->type = ast_affectation;
  newaffec->fils = concat(id,expr);
  return newaffec;
}

Arbre ast_new_declaration(Arbre feuille){
  Arbre newdeclare = calloc(1,sizeof(std_arbre));
  newdeclare->type = ast_declaration;
  newdeclare->fils = feuille;
  return newdeclare;
}

Arbre ast_new_plus(Arbre operande1, Arbre operande2){
	 Arbre newplus = calloc(1,sizeof(std_arbre));
  newplus->type = ast_plus;
  newplus->fils = operande1;
  newplus->fils->freres = operande2;
  return newplus;
}

Arbre ast_new_moins(Arbre operande1, Arbre operande2){
		 Arbre newmoins = calloc(1,sizeof(std_arbre));
  newmoins->type = ast_moins;
  newmoins->fils = operande1;
  newmoins->fils->freres = operande2;
  return newmoins;
}

Arbre ast_new_div(Arbre operande1, Arbre operande2){
	Arbre newdiv = calloc(1,sizeof(std_arbre));
  newdiv->type = ast_div;
  newdiv->fils = operande1;
  newdiv->fils->freres = operande2;
  return newdiv;
}

Arbre ast_new_fois(Arbre operande1, Arbre operande2){
	Arbre newfois = calloc(1,sizeof(std_arbre));
  newfois->type = ast_fois;
  newfois->fils = operande1;
  newfois->fils->freres = operande2;
  return newfois;
}

//creation d'un arbre vide
Arbre newArbre(){
  return NULL;
}

//creation d'une feuille const
Arbre new_const(int val){
  Arbre new = calloc(1,sizeof(std_arbre));
  new->type = ast_constant;
  new->val.constante = val;
  // On return une feuille de type ast_constant
  return new;
}

//creation d'une feuille string
Arbre new_string(char* val){
  Arbre new = calloc(1,sizeof(std_arbre));
  new->type = ast_str;
  new->val.str = val;
  // On return une feuille de type ast_str
  return new;
}

//ajout de a2 dans les frere de a1
Arbre concat(Arbre a1,Arbre a2){
  Arbre tmp=a1;
  while(a1->freres != NULL){
    a1=a1->freres;
  }
  a1->freres=a2;
  return tmp;
}

//Ajout d'un noeud printi ou printf suivant le type
Arbre ast_new_print(arbre_type type,Arbre feuille){
  Arbre newprint = calloc(1,sizeof(std_arbre));
  newprint->type = type;
  newprint->fils = feuille;
  return newprint;
}

//Ajout d'un noeud return
Arbre ast_new_return(Arbre feuille){
  Arbre newprint = calloc(1,sizeof(std_arbre));
  newprint->type = ast_return;
  newprint->fils = feuille;
  return newprint;
}

//Ajout un noeud main, noeud le plus haut en profondeurs
Arbre ast_new_main(Arbre statement){
  Arbre newprint = calloc(1,sizeof(std_arbre));
  newprint->type = ast_main;
  newprint->fils = statement;
  return newprint;
}

//Affiche dans le terminal l'AST avec ses profondeurs
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
    case ast_affectation:
      printf("ast_affectation\n");
      break;
	case ast_var:
		printf("ast_var %s\n",a->val.str);
		break;
	case ast_plus:
		printf("ast_plus \n");
		break;
	case ast_moins:
		printf("ast_moins \n");
		break;
	case ast_fois:
		printf("ast_fois \n");
		break;
	case ast_div:
		printf("ast_div \n");
		break;
	case ast_declaration:
	printf("ast_declaration \n");
	break;
	break;
  }

  //Affiche de manière recursive et ajoute une profondeur si possède des fils
  ast_print_aux(a->fils,profondeur+1);
  ast_print_aux(a->freres,profondeur);

}

void ast_print(Arbre a){
  ast_print_aux(a,0);
}

void ast_free(Arbre a){
	if(a == NULL)
		return;
	ast_free(a->freres);
	ast_free(a->fils);
	if(a->type == ast_str || a->type == ast_var){
		if(a->val.str != NULL)
			free(a->val.str);
	}
		
	free(a);
}



