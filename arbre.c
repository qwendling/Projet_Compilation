#include "arbre.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

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

//creation d'un noeud bloc pour différencier les blocs d'instruction dans les boucles ou conditions
Arbre ast_new_bloc(Arbre feuille){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_bloc;
	new->fils = feuille;
	return new;
}


//ajout de a2 dans les frere de a1
Arbre concat(Arbre a1,Arbre a2){
  Arbre tmp ;
  if(a1 == NULL){
    tmp = a2;
    return tmp;
  }else{
    tmp = a1;
  }

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

//Ajout d'un noeud &&
Arbre ast_new_and(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_and;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud ||
Arbre ast_new_or(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_or;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud !
Arbre ast_new_not(Arbre operande){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_not;
	new->fils = operande;
	return new;
}

//Ajout d'un noeud ==
Arbre ast_new_equal(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_equal;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud !=
Arbre ast_new_nequal(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_nequal;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud >
Arbre ast_new_greater(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_greater;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud >=
Arbre ast_new_greaterOrEqual(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_greaterOrEqual;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud <
Arbre ast_new_less(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_less;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud <=
Arbre ast_new_lessOrEqual(Arbre operande1, Arbre operande2){
  Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_lessOrEqual;
	new->fils = operande1;
  new->fils->freres = operande2;
	return new;
}

//Ajout d'un noeud de condition IF
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

	return new;
}

//------- SPRINT 4 -------

//Ajout d'un noeud de boucle for
Arbre ast_new_for(Arbre inits,Arbre conditions,Arbre increments,Arbre instructions){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_for;
  // fils 1 initialiseurs
	new->fils = ast_new_bloc(inits);
  // fils 2 conditon
	new->fils->freres = conditions;
  // fils 3 incrementation
	new->fils->freres->freres = ast_new_bloc(increments);
  // fils 4 bloc d'instruction
	new->fils->freres->freres->freres = ast_new_bloc(instructions);
	return new;
}

//Ajout d'un noeud de boucle while
Arbre ast_new_while(Arbre conditions, Arbre instructions){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_while;
	new->fils = conditions;
	new->fils->freres = ast_new_bloc(instructions);
	return new;
}


//------- SPRINT 5 -------
Arbre ast_new_tableauDeclare(char* id, Arbre dimension, Arbre affect){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_declaration;
	new->fils =  calloc(1,sizeof(std_arbre));
	new->fils->type = ast_tableau;
	new->fils->val.str = strdup(id);
	new->fils->fils = dimension;

	if(affect!=NULL){
		new->fils->freres = calloc(1,sizeof(std_arbre));
		new->fils->freres->type = ast_listTableau;
		new->fils->freres->fils = affect;
	}

	return new;

}

Arbre ast_new_tableauAffec(char* id, Arbre dimension, Arbre affect){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_affectation;
	new->fils =  calloc(1,sizeof(std_arbre));
	new->fils->type = ast_tableau;
	new->fils->val.str = strdup(id);
	new->fils->fils = dimension;
	new->fils->freres = affect;
	return new;
}

Arbre new_tableau(char* id, Arbre dimension){
	Arbre new = calloc(1,sizeof(std_arbre));
  new->type = ast_tableau;
  new->val.str = strdup(id);
	new->fils = dimension;
	return new;

}

Arbre ast_new_blocTableau(Arbre a){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_bloc;
	new->fils = a;
	return new;
}

//Verifie que pour l'arbre donné et la dimension donné on a le meme nombre d'élément attendu
int verifDimTab(int dim,Arbre list){
	int nbElem = dim;
  Arbre listTmp = list;

  // Verifie les frères
  for(int i=0;i<nbElem;i++){
  //Si moins que prevu renvoie faux
    if(listTmp == NULL){
      return 1;
    }
  //Si bloc alors qu'on est dans la verif de membre renvoie faux
    if(listTmp->type == ast_bloc){
      return 1;
    }
    listTmp = listTmp->freres;
  }
  // Si un frère en plus est la on renvoie faux
  if(listTmp != NULL){
    return 1;
  }

	return 0;
}

int verifTableau(Arbre Dim, Arbre Bloctableau){
  if(Bloctableau == NULL){
    return 1;
  }
  int nbrMember = Dim->val.constante;
  Arbre tmpBloctableau = Bloctableau;
  Arbre nextDim = Dim->freres;
  //si on est dans un bloc de membre on verifie son contenu
  if(tmpBloctableau->type != ast_bloc){
    // Ca doit etre la derniere ou seul dimension sinon c'est faux
    if(nextDim == NULL){
      if(verifDimTab(nbrMember,tmpBloctableau) == 1){
        return 1;
      }
    }
    else return 1;
  }
  //Verifie de manière recursive les blocs
  if(tmpBloctableau->type == ast_bloc){
    //permet de tester le nombre attendu
    for(int i=0;i<nbrMember;i++){
      //si null alors on a pas le bon nombre de freres
      if(tmpBloctableau == NULL){
        return 1;
      }
      //verifie en recursif
      if(verifTableau(nextDim,tmpBloctableau->fils) == 1){
        return 1;
      }
      tmpBloctableau = tmpBloctableau->freres;
    }
    // si on a un frere de trop ca bug
    if(tmpBloctableau != NULL){
      return 1;
    }
  }

  return 0;
}



// ------ DEFINE -----

ListeDefine newListeDefine(){
	return NULL;
}

ListeDefine new_define(char* id, int constante){
	ListeDefine new = calloc(1,sizeof(std_define));
	new->id = strdup(id);
	new->cst = constante;
	return new;
}

ListeDefine concat_define(ListeDefine d,ListeDefine r){
  ListeDefine tmp=d;
  while(d->next != NULL){
    d=d->next;
  }
  d->next=r;
  return tmp;
}

ListeDefine findInDefine(ListeDefine d, char* id){
	ListeDefine tmp=d;
  while(tmp != NULL){
		if(strcmp(tmp->id,id)==0)
			return tmp;
		tmp=tmp->next;
  }

	return NULL;
}

void replaceDefineInAST(Arbre a,ListeDefine d){
	if(a==NULL)
    return;

	if(a->type == ast_var){
		ListeDefine define = findInDefine(d,a->val.str);
		if(define != NULL){
			int cst = define->cst;
		  a->type = ast_constant;
		  a->val.constante = cst;
		}
	}
	replaceDefineInAST(a->freres,d);
	replaceDefineInAST(a->fils,d);
}

void print_define(ListeDefine d){
	if(d == NULL)
		return;

	printf("Define %s %d \n",d->id,d->cst);
	print_define(d->next);
}


//------- Sprint 6 -------

Arbre new_stencil(char* id){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_stencil;
	new->val.stencil.name = strdup(id);
}

Arbre ast_new_blocStencil(Arbre a){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_bloc;
	new->fils = a;
	return new;
}


Arbre ast_new_stencilDeclare(char* id,Arbre member,int n,int prof){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_declaration;
	new->fils =  calloc(1,sizeof(std_arbre));
  new->fils->type = ast_stencil;
  new->fils->val.stencil.name = strdup(id);
	new->fils->fils = member;


	//Stencil qui sert a l'analyse semeantique
  new->fils->val.stencil.profondeurs = prof;
	new->fils->val.stencil.member = n;

	return new;
}


int verifStencilDim(Arbre ast,int dim){
	Arbre tmp = ast;
	int cptdim = 0;
	while(tmp->type == ast_bloc){
		tmp=tmp->fils;
		cptdim++;
	}

	if(cptdim == dim-1){
		return 0;
	}

	return 1;
}

int verifStencilMember(Arbre ast, int member){
	Arbre tmp = ast;
	int cptmember = 0;
	while (tmp != NULL){
		tmp = tmp->freres;
		cptmember++;
	}

	if(cptmember==member){
		return 0;
	}
	return 1;
}

int verifStencilMemberRecu(Arbre astStencil, int member){
	if(astStencil == NULL){
		return 0;
	}

	int res1;
	int res2;
	int membre;
	switch(astStencil->type){
		case ast_bloc:
			res1 = verifStencilMemberRecu(astStencil->fils,member);
			res2 = verifStencilMemberRecu(astStencil->freres,member);
			return !(!res1 && !res2);
		break;

		default :
			membre = verifStencilMember(astStencil, 2*member+1);
			return membre;
		break;
	}

	return 0;
}

int verifStencilFrere(Arbre ast,int frere){
	Arbre tmp = ast;
	int cptfreres = 0;
	while (tmp != NULL) {
		tmp = tmp->freres;
		cptfreres++;
	}

	if(cptfreres==frere){
		return 0;
	}
	return 1;
}

int verifStencilFrereRecu(Arbre astStencil, int member){
	int res1;
	int res2;
	switch(astStencil->type){
		case ast_bloc:
			res1 = verifStencilFrere(astStencil,member);
			if(astStencil->fils->type==ast_bloc){
				 res2 = verifStencilFrereRecu(astStencil->fils,member);
				return !(!res2 && !res1);
			}

			return res1;
		break;
	}

	return 0;
}

int verifStencil(Arbre astStencil, int member, int dim){

	int resMember = verifStencilMemberRecu(astStencil,member);
	int resFrere = verifStencilFrereRecu(astStencil,2*member+1);
	int resDim = verifStencilDim(astStencil,dim);

	return !(!resMember && !resFrere && !resDim);
}


Arbre ast_new_applyStencilD(Arbre stencil, Arbre tableau){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_applyStencil;
	new->fils = stencil;
	new->fils->freres = tableau;

	return new;
}

Arbre ast_new_applyStencilG(Arbre tableau,Arbre stencil){
	Arbre new = calloc(1,sizeof(std_arbre));
	new->type = ast_applyStencil;
	new->fils = tableau;
	new->fils->freres = stencil;

	return new;
}


//------- Sprint 7 -------

Arbre ast_new_fonction(char* id, Arbre args, Arbre instruction){
  printf("%s\n", id);
  Arbre new = calloc(1,sizeof(std_arbre));
  new->type = ast_fonction;
  new->val.str = id;
  new->fils = ast_new_bloc(args);
  new->fils->freres = ast_new_bloc(instruction);
  return new;
}

Arbre ast_new_appelFonction(char* id, Arbre args){
  Arbre new = calloc(1,sizeof(std_arbre));
  new->type = ast_fonction;
  new->val.str = id;
  new->fils = args;
}

void ast_changeReturnFct(Arbre a){
  if(a==NULL)
    return;
  if(a->type == ast_return)
    a->type = ast_returnFct;
  ast_changeReturnFct(a->fils);
  ast_changeReturnFct(a->freres);
}

int replaceIdVarFct(char *id, Arbre ast){
  if (ast == NULL){
    return 0;
  }

  if(ast->type == ast_var){
    ast->val.str = strcat(ast->val.str,id);
  }
  if(ast->type == ast_stencil){
    ast->val.stencil.name = strcat(ast->val.stencil.name,id);
  }
  if(ast->type == ast_tableau){
    ast->val.str = strcat(ast->val.str,id);
  }
  if(ast->type == ast_fonction){
    ast->val.str = strcat(ast->val.str,"FCT");
  }

  if(ast->fils != NULL){
      replaceIdVarFct(id,ast->fils);
  }

  if(ast->freres != NULL){
      replaceIdVarFct(id,ast->freres);
  }

  return 0;
}

int repaceIdInAST(Arbre ast){
  Arbre astRacine = ast;

  while(ast != NULL){
    if(ast->type == ast_declaration){
      if(ast->fils->type == ast_fonction){
        replaceIdVarFct(ast->fils->val.str,ast->fils->fils);
        ast_changeReturnFct(ast->fils);
      }
    }
    if(ast->type == ast_main){
      replaceIdMain(ast->fils);
    }
    ast = ast->freres;
  }

  ast = astRacine;
  return 0;
}

int replaceIdMain(Arbre ast){
  if (ast == NULL){
    return 0;
  }

  if(ast->type == ast_var){
    ast->val.str = strcat(ast->val.str,"MAINFCT");
  }
  if(ast->type == ast_stencil){
    ast->val.stencil.name = strcat(ast->val.stencil.name,"MAINFCT");
  }
  if(ast->type == ast_tableau){
    ast->val.str = strcat(ast->val.str,"MAINFCT");
  }
  if(ast->type == ast_fonction){
    ast->val.str = strcat(ast->val.str,"FCT");
  }

  if(ast->fils != NULL){
      replaceIdMain(ast->fils);
  }

  if(ast->freres != NULL){
      replaceIdMain(ast->freres);
  }

  return 0;
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
	case ast_tableau:
	printf("ast_tableau  %s\n",a->val.str);
	break;
	case ast_stencil:
	printf("ast_stencil : %s {%d,%d}\n",a->val.stencil.name,a->val.stencil.member,a->val.stencil.profondeurs);
	break;
	case ast_applyStencil:
	printf("ast_applyStencil\n");
	break;
	case ast_listTableau:
	printf("ast_listTableau\n");
	break;
  case ast_fonction:
  printf("ast_fonction : %s\n",a->val.str);
  break;
  case ast_args:
  printf("ast_args \n");
  break;
  case ast_instruction:
  printf("ast_instruction \n");
  break;
  case ast_returnFct:
  printf("ast_returnFct\n");
  break;
  }

  //Affiche de manière recursive et ajoute une profondeur si possède des fils
  ast_print_aux(a->fils,profondeur+1);
  ast_print_aux(a->freres,profondeur);

}

Dim add_dim(Dim d,int size){
  if(d == NULL){
    Dim tmp=calloc(1,sizeof(std_dim));
    tmp->size=size;
    tmp->next = NULL;
    return tmp;
  }
  d->next = add_dim(d->next,size);
  return d;
}

void create_tab(Arbre a,Symbole s){
	Arbre tmp = a->fils;
  s->val.dimension=NULL;
  while(tmp != NULL){
    s->val.dimension=add_dim(s->val.dimension,tmp->val.constante);
    tmp = tmp->freres;
  }
}

void print_tab(Symbole s){
  Dim tmp = s->val.dimension;
  while(tmp != NULL){
    printf("%d ",tmp->size);
    tmp = tmp->next;
  }
  printf("\n");
}

Arg create_argList(Arbre a){
  if(a==NULL)
    return NULL;
  if(a->type == ast_declaration){
    Arg new_arg =calloc(1,sizeof(std_arg));
    new_arg->name =strdup(a->fils->val.str);
    new_arg->next =create_argList(a->freres);
    return new_arg;
  }
  return NULL;
}



// Repère si il y'a une erreur de sArbre verifStencil(Arbre list, Arbre dim)émantique dans le programme
int ast_semantique(Arbre a,Symbole sym_table[TAILLE_TABLE]){
	if(a == NULL){
		return 0;
	}
	char* name;
	Symbole s;
	switch(a->type){
		case ast_declaration:
			if(a->fils->type == ast_stencil)
				name = a->fils->val.stencil.name;
			else
				name = a->fils->val.str;
			if(sym_existe_table(sym_table,name)){
        printf("%s deja defini\n",name);
				return 2;
			}
			sym_add(name,sym_table);
			s=sym_find(name,sym_table);
			switch(a->fils->type){
				case ast_var:
					s->type = sym_var;
					break;
				case ast_tableau:
					printf("declaration tab\n");
					s->type = sym_tab;
				  create_tab(a->fils,s);
				  print_tab(s);
					if(a->fils->freres != NULL){
						if(a->fils->freres->type == ast_listTableau){
              //on donne ll'arbre des constantes de DIM et l'arbre de la liste
							if(verifTableau(a->fils->fils,a->fils->freres->fils)==1){
								printf("Liste d'affectation de tableau fausse \n");
								return 4;
							}
						}
						else{
							printf("Tableau mal défini, mauvaise type d'affecctation\n");
							return 4;
						}
					}
					break;
				case ast_stencil:
				printf("Declaration stencil\n" );
				if(verifStencil(a->fils->fils,a->fils->val.stencil.member,a->fils->val.stencil.profondeurs)){
					printf("Stencil mal definie !\n");
					return 3;
				}
				s->type = sym_stencil;
				s->val.stencil.size = pow(a->fils->val.stencil.member*2+1,a->fils->val.stencil.profondeurs);
				s->val.stencil.voisin = a->fils->val.stencil.member;
				s->val.stencil.dim = a->fils->val.stencil.profondeurs;
				break;
        case ast_fonction:
          //ICI le check semantique des fonctions

          s->type = sym_fonction;
          s->val.arg_list = create_argList(a->fils->fils->fils);
        break;
			}
			break;
		case ast_var:
			name = a->val.str;
			s = sym_find(name,sym_table);
			if(s == NULL || s->type != sym_var){
	        printf("%s pas ast_var\n",name );
					return 1;
				}
			break;
		case ast_tableau:
			printf("sem ast_tableau\n");
			name = a->val.str;
			s = sym_find(name,sym_table);
			if(s == NULL || s->type != sym_tab){
        printf("%s pas ast_tableau\n",name );
				return 1;
			}

        printf("%s ast_tableau\n",name );
			break;
		case ast_stencil:
			name = a->val.stencil.name;
			s = sym_find(name,sym_table);
			if(s == NULL || s->type != sym_stencil){
				printf("%s pas ast_stencil\n",name );
				return 1;
			}
			break;
	}
  int tmp = ast_semantique(a->fils,sym_table);
  int tmp2 = ast_semantique(a->freres,sym_table);
	return !(!tmp && !tmp2);
}
