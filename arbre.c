#include "arbre.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

//------- SPRINT 1 -------

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

Arbre ast_new_bloc(Arbre feuille){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_bloc;
	new->fils = feuille;
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




//------- SPRINT 2 -------

//creation d'une feuille variable avec un ID donné
Arbre new_var(char* var){
	Arbre new = calloc(1,sizeof(std_arbre));
	printf("var : %s",var);
	new->type = ast_var;
	new->val.str = strdup(var);
	// On return une feuille de type ast_var
	return new;
}

//Ajout d'un noeud de declaration
Arbre ast_new_declaration(Arbre feuille){
  Arbre newdeclare = calloc(1,sizeof(std_arbre));
  newdeclare->type = ast_declaration;
  newdeclare->fils = feuille;
  return newdeclare;
}

//Ajout d'un noeud affectation
Arbre ast_new_affectation(Arbre id, Arbre expr){
  Arbre newaffec = calloc(1,sizeof(std_arbre));
  newaffec->type = ast_affectation;
  newaffec->fils = concat(id,expr);
  return newaffec;
}

//Ajout d'un noeud somme
Arbre ast_new_plus(Arbre operande1, Arbre operande2){
	 Arbre newplus = calloc(1,sizeof(std_arbre));
  newplus->type = ast_plus;
  newplus->fils = operande1;
  newplus->fils->freres = operande2;
  return newplus;
}

//Ajout d'un noeud soustraction
Arbre ast_new_moins(Arbre operande1, Arbre operande2){
		 Arbre newmoins = calloc(1,sizeof(std_arbre));
  newmoins->type = ast_moins;
  newmoins->fils = operande1;
  newmoins->fils->freres = operande2;
  return newmoins;
}

//Ajout d'un noeud division
Arbre ast_new_div(Arbre operande1, Arbre operande2){
	Arbre newdiv = calloc(1,sizeof(std_arbre));
  newdiv->type = ast_div;
  newdiv->fils = operande1;
  newdiv->fils->freres = operande2;
  return newdiv;
}

//Ajout d'un noeud produit
Arbre ast_new_fois(Arbre operande1, Arbre operande2){
	Arbre newfois = calloc(1,sizeof(std_arbre));
  newfois->type = ast_fois;
  newfois->fils = operande1;
  newfois->fils->freres = operande2;
  return newfois;
}

//Ajout d'un noeud AutoIncrementation +
Arbre ast_new_autoIncrement_plus(Arbre var){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_autoIncrementPlus;
	new->fils = var;
	// On return une feuille de type ast_autoIncrementPlus
	return new;
}

//Ajout d'un noeud AutoIncrementation -
Arbre ast_new_autoIncrement_moins(Arbre var){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_autoIncrementMoins;
	new->fils = var;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

//Libere la mémoire de l'AST en récursif
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


//------- Sprint 3 -------

Arbre ast_new_and(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_and;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_or(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_or;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_not(Arbre operande){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_not;
	new->fils = operande;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_equal(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_equal;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_nequal(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_nequal;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_greater(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_greater;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_greaterOrEqual(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_greaterOrEqual;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_less(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_less;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_lessOrEqual(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_lessOrEqual;
	new->fils = operande1;
  new->fils->freres = operande2;
	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

Arbre ast_new_if(Arbre ifCondition, Arbre ifInstructions, Arbre elseInstructions){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_if;
	new->fils = ifCondition;

  new->fils->freres = calloc(1,sizeof(std_arbre));
  new->fils->freres->type = ast_bloc;
  new->fils->freres->fils = ifInstructions;

  new->fils->freres->freres = calloc(1,sizeof(std_arbre));
  new->fils->freres->freres->type = ast_bloc;
  new->fils->freres->freres->fils = elseInstructions;

	// On return une feuille de type ast_autoIncrementMoins
	return new;
}

//------- SPRINT 4 -------

Arbre ast_new_for(Arbre inits,Arbre conditions,Arbre increments,Arbre instructions){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_for;
	new->fils = ast_new_bloc(inits);
	new->fils->freres = conditions;
	new->fils->freres->freres = ast_new_bloc(increments);
	new->fils->freres->freres->freres = ast_new_bloc(instructions);
	return new;
}


Arbre ast_new_while(Arbre conditions, Arbre instructions){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_while;
	new->fils = conditions;
	new->fils->freres = ast_new_bloc(instructions);
	return new;
}

//------- All sprints -------

//Affiche dans le terminal l'AST général avec ses frères et fils
void ast_print(Arbre a){
  ast_print_aux(a,0);
}

//Affiche dans le terminal l'AST donné a une profondeur donné
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
	case ast_autoIncrementPlus:
	printf("ast_autoIncrementPlus \n");
	break;
	case ast_autoIncrementMoins:
	printf("ast_autoIncrementMoins \n");
	break;
  case ast_and:
  printf("ast_and\n");
	break;
  case ast_or:
  printf("ast_or\n");
	break;
  case ast_not:
  printf("ast_not\n");
	break;
  case ast_equal:
  printf("ast_equal\n");
	break;
  case ast_nequal:
  printf("ast_nequal\n");
	break;
  case ast_greater:
  printf("ast_greater\n");
	break;
  case ast_greaterOrEqual:
  printf("ast_greaterOrEqual\n");
	break;
  case ast_less:
  printf("ast_less\n" );
	break;
  case ast_lessOrEqual:
  printf("ast_lessOrEqual\n");
	break;
  case ast_if:
  printf("ast_if\n" );
	break;
  case ast_bloc:
  printf("ast_bloc\n");
  break;
  case ast_for:
  printf("ast_for\n");
  break;
  case ast_while:
  printf("ast_while\n");
  break;
  }

  //Affiche de manière recursive et ajoute une profondeur si possède des fils
  ast_print_aux(a->fils,profondeur+1);
  ast_print_aux(a->freres,profondeur);

}

int ast_semantique(Arbre a,Symbole sym_table[TAILLE_TABLE]){
	if(a == NULL)
		return 0;
	char* name;
	switch(a->type){
		case ast_declaration:
			printf("declaration semantique\n");
			name = a->fils->val.str;
			printf("declaration de %s\n",name);
			if(sym_existe_table(sym_table,name))
				return 2;
			sym_add(name,sym_table);
			break;
		case ast_var:
			name = a->val.str;
			if(!sym_existe_table(sym_table,name))
				return 1;
			break;
	}
  int tmp = ast_semantique(a->fils,sym_table);
  int tmp2 = ast_semantique(a->freres,sym_table);
	return tmp && tmp2;
}
