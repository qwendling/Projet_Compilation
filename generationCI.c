#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
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

// Return le resultat d'un quad
Symbole quad_res(quad q){
	if(q == NULL){
		return NULL;
	}
	if(q->next == NULL){
		return q->res;
	}
	return quad_res(q->next);
}

//Affiche les quads sur le terminal
void print_quad(quad q){
  if(q == NULL)
    return;
  switch (q->op){
    case print_i:
      printf("print_i %s NULL NULL\n",q->arg1->name);
      break;
    case print_f:
      printf("print_f %s NULL NULL\n",q->arg1->name);
      break;
    case affectation:
      printf("affectation NULL NULL %s : %d\n",q->res->name,q->res->val.entier);
      break;
    case return_prog:
      printf("return %s NULL NULL\n",q->arg1->name);
      break;
    case affectation_var:
  		printf("WTFFF %s %p\n",q->arg1->name,q->res);
  		printf("affectation %s NULL %s\n",q->arg1->name,q->res->name);
  		break;
    case affectation_tab:
      printf("affectation_tab %s NULL %s\n",q->arg1->name,q->res->name);
      break;
    case q_add:
  		printf("add %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
  		break;
    case q_mul:
  		printf("mul %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
  		break;
    case q_div:
  		printf("div %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
  		break;
    case q_sub:
  		printf("sub %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
  		break;
  	case use_var:
  		printf("use NULL NULL %s\n",q->res->name);
  		break;
    case q_equal:
      printf("equal %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
      break;
    case q_nequal:
      printf("nequal %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
      break;
    case q_greater:
      printf("gt %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
      break;
    case q_greaterOrEqual:
      printf("gte %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
      break;
    case q_less:
      printf("lt %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
      break;
    case q_lessOrEqual:
      printf("lte %s %s %s\n",q->arg1->name,q->arg2->name,q->res->name);
      break;
    case q_create_label:
      printf("label NULL NULL %s\n",q->res->name);
      break;
    case q_goto:
      printf("goto NULL NULL %s\n",q->res->name);
      break;
    case q_empile:
      printf("empile NULL NULL %s\n",q->res->name);
      break;
    case q_depile:
      printf("depile NULL NULL %s\n",q->res->name);
      break;
    case q_fctRes:
      printf("fctRes NULL NULL %s\n",q->res->name);
      break;
    case q_returnFct:
      printf("returnFct %s NULL %s\n",q->arg1->name,q->res->name);
      break;

  }
  print_quad(q->next);
}


void quad_complete(quad q,Symbole s){
  if(q==NULL)
    return;
  q->res = s;
  quad_complete(q->nextBool,s);
}

void quad_complete_returnFct(quad q,Symbole s){
  if(q==NULL)
    return;
  if(q->op == q_returnFct){
    q->res = s;
  }

  quad_complete_returnFct(q->next,s);
}

quad add_bool(quad q1,quad q2){
  if(q1 == NULL)
    return q2;
  q1->nextBool = add_bool(q1->nextBool,q2);
  return q1;
}

//genere les quad des expressions boolean
quad genCodeRelop(quad_op relop,Arbre ast,Symbole sym_table[TAILLE_TABLE]){
  quad codegen=NULL,arg=NULL,arg2=NULL,tmpQuad=NULL,tmpQuad2=NULL;
  Symbole sym_arg1,sym_arg2;
  //operande gauche
  arg = genCode(ast->fils,sym_table);
  //operande droite
  arg2 = genCode(ast->fils->freres,sym_table);
  // symbole de l'operande gauche
  sym_arg1=quad_res(arg);
  // symbole de l'operande droite
  sym_arg2=quad_res(arg2);
  //ajout quad de l'operande gauche
  codegen=add_quad(codegen,arg);
  //ajout quad de l'operande droite
  codegen=add_quad(codegen,arg2);

  // hummmm
  tmpQuad = quad_add(NULL,relop,sym_arg1,sym_arg2,NULL);
  codegen=add_quad(codegen,tmpQuad);
  tmpQuad2 = quad_add(NULL,q_goto,NULL,NULL,NULL);
  codegen=add_quad(codegen,tmpQuad2);

  // quads de la liste si vrai
  ast->val.boolList.trueList = tmpQuad;
  tmpQuad->nextBool = NULL;
  // quads de la liste si faux
  ast->val.boolList.falseList = tmpQuad2;
  tmpQuad2->nextBool = NULL;
  return codegen;
}

quad declare_stencil(Arbre ast,Symbole sym_table[TAILLE_TABLE],Symbole* addr_stencil){
  if(ast == NULL)
    return NULL;
  quad codegen=NULL,tmp_quad=NULL;
  Symbole sym_arg1,sym_tmp,tmp;
  switch(ast->type){
    case ast_bloc:
      codegen = declare_stencil(ast->fils,sym_table,addr_stencil);
      break;
    default:
      tmp_quad = genCode(ast,sym_table);
      sym_arg1 = quad_res(tmp_quad);
      codegen = add_quad(codegen,tmp_quad);
      codegen = add_quad(codegen,quad_add(NULL,affectation_tab,sym_arg1,NULL,*addr_stencil));
      tmp = sym_new_tmp(sym_table);
      tmp->type = sym_const;
      tmp->val.entier = 4;

      sym_tmp = sym_new_tmp(sym_table);
      codegen = add_quad(codegen,quad_add(NULL,q_add,tmp,*addr_stencil,sym_tmp));
      *addr_stencil=sym_tmp;
      break;
  }
  codegen = add_quad(codegen,declare_stencil(ast->freres,sym_table,addr_stencil));
  return codegen;
}

int nbFreres(Arbre a){
  if(a== NULL)
    return 0;
  return 1+nbFreres(a->freres);
}

int produitDim(Dim d){
  if(d==NULL){
    return 1;
  }
  return d->size*produitDim(d->next);
}

quad genForStencil(Arbre indexTab,Dim dimTab,Symbole sym_sten,int profondeur,Symbole addrSten,Symbole addrTab,Symbole result,Symbole sym_table[TAILLE_TABLE]){
	Symbole sym_i,tmp1,tmp2,tmp3,tmp4,tmp5,sym_arg1,sym_idTab,sym_checkinf,sym_checksup;
	Symbole lbl_condition,lbl_debut,lbl_fin;
	quad codegen = NULL,arg=NULL;
	int n = sym_sten->val.stencil.voisin;

	sym_i=sym_new_tmp(sym_table);

	tmp1=sym_new_tmp(sym_table);
	tmp1->type=sym_const;
	tmp1->val.entier=-n;

	tmp2=sym_new_tmp(sym_table);
	tmp2->type=sym_const;
	tmp2->val.entier=n;

	lbl_condition = sym_new_lbl(sym_table);
	lbl_debut = sym_new_lbl(sym_table);
	lbl_fin = sym_new_lbl(sym_table);

	codegen = add_quad(codegen,quad_add(NULL,affectation_var,tmp1,NULL,sym_i));
	codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl_condition));
	codegen = add_quad(codegen,quad_add(NULL,q_lessOrEqual,sym_i,tmp2,lbl_debut));
	codegen = add_quad(codegen,quad_add(NULL,q_goto,NULL,NULL,lbl_fin));
	codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl_debut));

	tmp3=sym_new_tmp(sym_table);
	tmp3->type=sym_const;
	tmp3->val.entier=produitDim(dimTab->next)*4;




	arg = genCode(indexTab,sym_table);
	sym_arg1 = quad_res(arg);

	codegen = add_quad(codegen,arg);
	codegen = add_quad(codegen,quad_add(NULL,q_add,sym_i,sym_arg1,sym_new_tmp(sym_table)));
	sym_idTab = quad_res(codegen);

	sym_checkinf=sym_new_tmp(sym_table);
	sym_checkinf->type=sym_const;
	sym_checkinf->val.entier=0;

	sym_checksup=sym_new_tmp(sym_table);
	sym_checksup->type=sym_const;
	sym_checksup->val.entier=dimTab->size;

	dimTab = (dimTab)?dimTab->next:NULL;

	codegen = add_quad(codegen,quad_add(NULL,q_less,sym_idTab,sym_checkinf,lbl_condition));
	codegen = add_quad(codegen,quad_add(NULL,q_greaterOrEqual,sym_idTab,sym_checksup,lbl_fin));


	codegen = add_quad(codegen,quad_add(NULL,q_mul,tmp3,sym_idTab,sym_new_tmp(sym_table)));
	codegen = add_quad(codegen,quad_add(NULL,q_add,addrTab,quad_res(codegen),sym_new_tmp(sym_table)));
	addrTab = quad_res(codegen);

	tmp4=sym_new_tmp(sym_table);
	tmp4->type=sym_const;
	tmp4->val.entier=pow(2*sym_sten->val.stencil.voisin+1,sym_sten->val.stencil.dim-profondeur)*4;

	codegen = add_quad(codegen,quad_add(NULL,q_add,sym_i,tmp2,sym_new_tmp(sym_table)));
	codegen = add_quad(codegen,quad_add(NULL,q_mul,tmp4,quad_res(codegen),sym_new_tmp(sym_table)));
	codegen = add_quad(codegen,quad_add(NULL,q_add,addrSten,quad_res(codegen),sym_new_tmp(sym_table)));
	addrSten = quad_res(codegen);

	if(indexTab->freres == NULL){
		addrSten->type = sym_tabRes;
		addrTab->type = sym_tabRes;
		codegen = add_quad(codegen,quad_add(NULL,q_mul,addrSten,addrTab,sym_new_tmp(sym_table)));
		codegen = add_quad(codegen,quad_add(NULL,q_add,result,quad_res(codegen),result));
	}else{
		codegen = add_quad(codegen,genForStencil(indexTab->freres,dimTab,sym_sten,profondeur+1,addrSten,addrTab,result,sym_table));
	}

	tmp5=sym_new_tmp(sym_table);
	tmp5->type=sym_const;
	tmp5->val.entier=1;

	codegen = add_quad(codegen,quad_add(NULL,q_add,sym_i,tmp5,sym_i));

	codegen = add_quad(codegen,quad_add(NULL,q_goto,NULL,NULL,lbl_debut));
	codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl_fin));

	return codegen;
}

int isInQuad(Symbole s,quad q){
  if(q==NULL)
    return 0;
  return !strcmp(s->name,q->res->name) || isInQuad(s,q->next);
}

void genPile(quad code,quad* empile,quad* depile){
  if(code == NULL)
    return;

  if(code->res != NULL && code->res->type == sym_var && !isInQuad(code->res,*empile)){
    *empile =add_quad(*empile,quad_add(NULL,q_empile,NULL,NULL,code->res));
    *depile =add_quad(quad_add(NULL,q_depile,NULL,NULL,code->res),*depile);
  }
  genPile(code->next,empile,depile);
}

// genere les quads depuis l'AST en stockant dans la table des symboles
quad genCode(Arbre ast,Symbole sym_table[TAILLE_TABLE]){
  if(ast == NULL)
    return NULL;
  //nouveau symbole du quad
  Symbole tmp,tmp2,sym_arg1,sym_arg2,lbl,lbl2,lbl3,result;
  quad codegen = NULL,arg = NULL,arg2=NULL,arg3=NULL,arg4=NULL,tmpQuad=NULL,tmpQuad2=NULL;
  Arbre fils,tmp_sten,tmp_tab;
  //Suivant le type de l'AST le quad est différent
  switch(ast->type){
    case ast_constant:
  		  printf("CI cst\n");
        tmp = sym_new_tmp(sym_table);
        tmp->type = sym_const;
        tmp->val.entier = ast->val.constante;
        codegen = quad_add(codegen,affectation,NULL,NULL,tmp);
        break;
    case ast_str:
  		  printf("CI str\n");
        tmp = sym_new_tmp(sym_table);
        tmp->type = sym_string;
        tmp->val.str = strdup(ast->val.str);
        codegen = quad_add(codegen,create_string,NULL,NULL,tmp);
        break;
    case ast_printf:
  		  printf("CI printf\n");
        // on genere le quad de la constante a afficher
        arg = genCode(ast->fils,sym_table);
        codegen = arg;
        // on concatene le dernier quad (argument string) avec un quad printf
        codegen = add_quad(codegen,quad_add(NULL,print_f,quad_res(arg),NULL,NULL));
        break;
    case ast_printi:
  		  printf("CI printi\n");
        // on genere le quad de la constante a afficher
        arg = genCode(ast->fils,sym_table);
        codegen = arg;
        // on concatene le dernier quad (argument constant) avec un quad printi
        codegen = add_quad(codegen,quad_add(NULL,print_i,quad_res(arg),NULL,NULL));
        break;
    case ast_return:
  		  printf("CI return\n");
        // on genere le quad de la valeur a return
        arg = genCode(ast->fils,sym_table);
        codegen = arg;
        // on concatene le dernier quad (argument constant) avec un quad return
        codegen = add_quad(codegen,quad_add(NULL,return_prog,quad_res(arg),NULL,NULL));
        break;
    case ast_main:
  		  printf("CI main\n");
        codegen = quad_add(codegen,create_main,NULL,NULL,NULL);
        fils = ast->fils;
        // On parcoure l'AST pour générer tout les quads du main
        while(fils != NULL){
          codegen = add_quad(codegen,genCode(fils,sym_table));
          fils = fils->freres;
        }
        codegen = add_quad(codegen,genCode(ast->freres,sym_table));
        break;
    case ast_var:
  		printf("CI Var %s\n",ast->val.str);
      // On génère le quad de variable déja initialisé
  		codegen = quad_add(codegen,use_var,NULL,NULL,sym_find(ast->val.str,sym_table));
      break;
  	case ast_affectation:
  		printf("CI affecVar %s\n",ast->fils->val.str);
      arg2 = genCode(ast->fils,sym_table);
      printf("test arg2 affecVar\n");
  		arg = genCode(ast->fils->freres,sym_table);
  		printf("test arg : %s\n",quad_res(arg)->name);

      sym_arg1 = quad_res(arg);
      sym_arg2 = quad_res(arg2);

  		codegen = arg2;
      codegen = add_quad(codegen,arg);
      // On génère le quad d'affectation de variable
		  printf("\n\n############FIND %s %p\n\n",ast->fils->val.str,sym_find(ast->fils->val.str,sym_table));
      quad_op q_op= affectation_var;
      switch(ast->fils->type){
        case ast_tableau:
          q_op = affectation_tab;
          break;
        case ast_var:
          q_op = affectation_var;
          break;
      }
  		codegen = add_quad(codegen,quad_add(NULL,q_op,sym_arg1,NULL,sym_arg2));
  		break;
  	case ast_div:
  	  printf("CI /\n");
        // On génère les quad pour le calcul de la division
  		tmp = sym_new_tmp(sym_table);
      // quad pour coté gauche div
  		arg = genCode(ast->fils,sym_table);
      // quad pour coté droite div
  		arg2 = genCode(ast->fils->freres,sym_table);
      // resultat coté gauche stocké
  		sym_arg1 = quad_res(arg);
      // resultat coté droite stocké
  		sym_arg2 = quad_res(arg2);
  		codegen = add_quad(arg,arg2);
      // on concat les quad existant avec un nouveau de division et ses 2 operandes
  		codegen = add_quad(codegen,quad_add(NULL,q_div,sym_arg1,sym_arg2,tmp));
  		break;
  	case ast_fois:
  	  printf("CI *\n");
      // On génère les quad pour le calcul de la multiplication
  		tmp = sym_new_tmp(sym_table);
  		arg = genCode(ast->fils,sym_table);
  		arg2 = genCode(ast->fils->freres,sym_table);
  		sym_arg1 = quad_res(arg);
  		sym_arg2 = quad_res(arg2);
  		codegen = add_quad(arg,arg2);
  		codegen = add_quad(codegen,quad_add(NULL,q_mul,sym_arg1,sym_arg2,tmp));
  		break;
  	case ast_moins:
  	  printf("CI -\n");
      // On génère les quad pour le calcul de la soustraction
  		tmp = sym_new_tmp(sym_table);
  		arg = genCode(ast->fils,sym_table);
  		arg2 = genCode(ast->fils->freres,sym_table);
  		sym_arg1 = quad_res(arg);
  		sym_arg2 = quad_res(arg2);
  		codegen = add_quad(arg,arg2);
  		codegen = add_quad(codegen,quad_add(NULL,q_sub,sym_arg1,sym_arg2,tmp));
  		break;
  	case ast_plus:
  		printf("CI +\n");
      // On génère les quad pour le calcul de la somme
  		tmp = sym_new_tmp(sym_table);
  		arg = genCode(ast->fils,sym_table);
  		arg2 = genCode(ast->fils->freres,sym_table);
  		sym_arg1 = quad_res(arg);
  		sym_arg2 = quad_res(arg2);
  		codegen = add_quad(arg,arg2);
  		codegen = add_quad(codegen,quad_add(NULL,q_add,sym_arg1,sym_arg2,tmp));

  		break;
    case ast_autoIncrementPlus:
      // On génère les quad pour le calcul de l'autoIncremente
      // On cherche la valeur de la variable a incrémenter
      sym_arg1 = sym_find(ast->fils->val.str,sym_table);
      tmp = sym_new_tmp(sym_table);
      // On affecte a une variable temporaire la valeur de la variable recherché
      codegen = add_quad(codegen,quad_add(NULL,affectation_var,sym_arg1,NULL,tmp));
      // Incrementation = affectation de +1, creation de la constant entier 1
      tmp2 = sym_new_tmp(sym_table);
      tmp2->type = sym_const;
      tmp2->val.entier = 1;
      // On affecte la constante 1
      codegen = add_quad(codegen,quad_add(NULL,affectation,NULL,NULL,tmp2));
      // On genere le quad de somme var + 1
      codegen = add_quad(codegen,quad_add(NULL,q_add,tmp2,sym_arg1,sym_arg1));
      codegen = add_quad(codegen,quad_add(NULL,use_var,NULL,NULL,tmp));
      break;
    case ast_autoIncrementMoins:
      sym_arg1 = sym_find(ast->fils->val.str,sym_table);
      tmp = sym_new_tmp(sym_table);
      codegen = add_quad(codegen,quad_add(NULL,affectation_var,sym_arg1,NULL,tmp));
      tmp2 = sym_new_tmp(sym_table);
      tmp2->type = sym_const;
      tmp2->val.entier = 1;
      codegen = add_quad(codegen,quad_add(NULL,affectation,NULL,NULL,tmp2));
      codegen = add_quad(codegen,quad_add(NULL,q_sub,sym_arg1,tmp2,sym_arg1));
      codegen = add_quad(codegen,quad_add(NULL,use_var,NULL,NULL,tmp));
      break;
    case ast_and:
      // operande de gauche
      arg = genCode(ast->fils,sym_table);
      // operande de droite
      arg2 = genCode(ast->fils->freres,sym_table);
      lbl = sym_new_lbl(sym_table);
      //la true liste prene le label actuel
      quad_complete(ast->fils->val.boolList.trueList,lbl);
      // on ajoute tout les frères de la condtion dans la true liste, donc si condition verifié
      ast->val.boolList.trueList = ast->fils->freres->val.boolList.trueList;
      // on ajoute le else dans la false list
      ast->val.boolList.falseList = add_bool(ast->fils->val.boolList.falseList,ast->fils->freres->val.boolList.falseList);

      codegen = add_quad(codegen,arg);
      // mmmmh je bug la
      codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl));
      codegen = add_quad(codegen,arg2);
      break;
    case ast_or:
      arg = genCode(ast->fils,sym_table);
      arg2 = genCode(ast->fils->freres,sym_table);
      lbl = sym_new_lbl(sym_table);
      quad_complete(ast->fils->val.boolList.falseList,lbl);
      ast->val.boolList.falseList = ast->fils->freres->val.boolList.falseList;
      ast->val.boolList.trueList = add_bool(ast->fils->val.boolList.trueList,ast->fils->freres->val.boolList.trueList);
      codegen = add_quad(codegen,arg);
      codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl));
      codegen = add_quad(codegen,arg2);
      break;
    case ast_not:
      codegen = genCode(ast->fils,sym_table);
      ast->val.boolList.falseList = ast->fils->val.boolList.trueList;
      ast->val.boolList.trueList = ast->fils->val.boolList.falseList;
      break;
    case ast_equal:
      codegen = genCodeRelop(q_equal,ast,sym_table);
      break;
    case ast_nequal:
      codegen = genCodeRelop(q_nequal,ast,sym_table);
      break;
    case ast_greater:
      codegen = genCodeRelop(q_greater,ast,sym_table);
      break;
    case ast_greaterOrEqual:
      codegen = genCodeRelop(q_greaterOrEqual,ast,sym_table);
      break;
    case ast_less:
      codegen = genCodeRelop(q_less,ast,sym_table);
      break;
    case ast_lessOrEqual:
      codegen = genCodeRelop(q_lessOrEqual,ast,sym_table);
      break;
    case ast_if:
      arg = genCode(ast->fils,sym_table);
      arg2 = genCode(ast->fils->freres,sym_table);
      arg3 = genCode(ast->fils->freres->freres,sym_table);

      lbl = sym_new_lbl(sym_table);
      tmpQuad = quad_add(NULL,q_create_label,NULL,NULL,lbl);
      quad_complete(ast->fils->val.boolList.trueList,lbl);

      codegen = arg;
      codegen = add_quad(codegen,tmpQuad);
      codegen = add_quad(codegen,arg2);
      lbl2 = sym_new_lbl(sym_table);
      codegen = add_quad(codegen,quad_add(NULL,q_goto,NULL,NULL,lbl2));
      if(arg3 != NULL){
        lbl = sym_new_lbl(sym_table);
        tmpQuad = quad_add(NULL,q_create_label,NULL,NULL,lbl);
        quad_complete(ast->fils->val.boolList.falseList,lbl);
        codegen = add_quad(codegen,tmpQuad);
        codegen = add_quad(codegen,arg3);

      }else{
        quad_complete(ast->fils->val.boolList.falseList,lbl2);
      }

      codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl2));

      break;
    case ast_bloc:
      fils = ast->fils;
      // On parcoure l'AST pour générer tout les quads du main
      while(fils != NULL){
        codegen = add_quad(codegen,genCode(fils,sym_table));
        fils = fils->freres;
      }
      break;
  	case ast_while:
      //quad condition
  		arg=genCode(ast->fils,sym_table);
      //quad instructions
  		arg2 = genCode(ast->fils->freres,sym_table);
  		lbl = sym_new_lbl(sym_table);
  		lbl2 = sym_new_lbl(sym_table);
  		lbl3 = sym_new_lbl(sym_table);

      // quad quand condition vrai
  		quad_complete(ast->fils->val.boolList.trueList,lbl);
      //quad quand faux
  		quad_complete(ast->fils->val.boolList.falseList,lbl2);

      // hummm le lbl3 why ?
  		codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl3));
  		codegen= add_quad(codegen,arg);
  		codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl));
  		codegen = add_quad(codegen,arg2);
  		codegen = add_quad(codegen,quad_add(NULL,q_goto,NULL,NULL,lbl3));
  		codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl2));

  		break;
  	case ast_for:
      //quad inits
  		arg=genCode(ast->fils,sym_table);
      //quad condition
  		arg2=genCode(ast->fils->freres,sym_table);
      //quad increment
  		arg3=genCode(ast->fils->freres->freres,sym_table);
      //quad instructions
  		arg4=genCode(ast->fils->freres->freres->freres,sym_table);

  		lbl = sym_new_lbl(sym_table);
  		lbl2 = sym_new_lbl(sym_table);
  		lbl3 = sym_new_lbl(sym_table);

      // quad quand condition verifié
  		quad_complete(ast->fils->freres->val.boolList.trueList,lbl2);
      //quad quand fini boucle
  		quad_complete(ast->fils->freres->val.boolList.falseList,lbl3);

  		//Code Init
  		codegen = add_quad(codegen,arg);
  		//Label condition
  		codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl));
  		//Condition
  		codegen = add_quad(codegen,arg2);
  		//Label true
  		codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl2));
  		//Bloc de code
  		codegen = add_quad(codegen,arg4);
  		//iteration
  		codegen = add_quad(codegen,arg3);
  		//gotoCond
  		codegen = add_quad(codegen,quad_add(NULL,q_goto,NULL,NULL,lbl));
  		//label false
  		codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl3));

  		break;
    case ast_tableau:
      printf("GEN CI tab\n");
      sym_arg1 = sym_find(ast->val.str,sym_table);
      arg=genCode(ast->fils,sym_table);

      sym_arg2=quad_res(arg);
      codegen = add_quad(codegen,arg);

      Arbre parcours_dim = ast->fils->freres;
      Dim dim_tab = sym_arg1->val.dimension->next;
      int size_dim;

      while(parcours_dim != NULL && dim_tab != NULL){

        size_dim = dim_tab->size;
        dim_tab = dim_tab->next;

        tmp = sym_new_tmp(sym_table);
        tmp->type = sym_const;
        tmp->val.entier = size_dim;
        codegen = add_quad(codegen,quad_add(NULL,q_mul,quad_res(codegen),tmp,sym_new_tmp(sym_table)));
        sym_arg2=quad_res(codegen);
        arg=genCode(parcours_dim,sym_table);

        codegen = add_quad(codegen,arg);


        codegen = add_quad(codegen,quad_add(NULL,q_add,quad_res(codegen),sym_arg2,sym_new_tmp(sym_table)));

        parcours_dim = parcours_dim->freres;
      }
      tmp = sym_new_tmp(sym_table);
      tmp->type = sym_const;
      tmp->val.entier = 4;
      codegen = add_quad(codegen,quad_add(NULL,q_mul,tmp,quad_res(codegen),sym_new_tmp(sym_table)));

      tmp = sym_new_tmp(sym_table);
      tmp->type = sym_tabRes;
      codegen = add_quad(codegen,quad_add(NULL,q_add,sym_arg1,quad_res(codegen),tmp));

      printf("#######TAB######\n\n");
      print_quad(codegen);

      break;
    case ast_declaration:
      if(ast->fils->type == ast_stencil){
        sym_arg1 = sym_find(ast->fils->val.stencil.name,sym_table);
        codegen = declare_stencil(ast->fils->fils,sym_table,&sym_arg1);
      }
      if(ast->fils->type == ast_tableau && ast->fils->freres != NULL){
        sym_arg1 = sym_find(ast->fils->val.str,sym_table);
        codegen = declare_stencil(ast->fils->freres->fils,sym_table,&sym_arg1);
      }
      if(ast->fils->type == ast_fonction){
        sym_arg1 = sym_find(ast->fils->val.str,sym_table);
        codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,sym_arg1));
        arg = genCode(ast->fils->fils->freres,sym_table);
        genPile(arg,&arg2,&arg3);
        lbl = sym_new_lbl(sym_table);
        quad_complete_returnFct(arg,lbl);

        codegen = add_quad(codegen,quad_add(NULL,q_beginFct,NULL,NULL,NULL));
        codegen = add_quad(codegen,arg2);

        codegen = add_quad(codegen,arg);
        codegen = add_quad(codegen,quad_add(NULL,q_create_label,NULL,NULL,lbl));

        codegen = add_quad(codegen,arg3);
        codegen = add_quad(codegen,quad_add(NULL,q_endFct,NULL,NULL,NULL));

        codegen = add_quad(codegen,genCode(ast->freres,sym_table));
      }
      break;
    case ast_applyStencil:
      printf("CI apply stencil\n");
      if(ast->fils->type == ast_stencil){
        tmp_tab = ast->fils->freres;
        tmp_sten = ast->fils;
      }else{
        tmp_sten = ast->fils->freres;
        tmp_tab = ast->fils;
      }

      Symbole sym_sten = sym_find(tmp_sten->val.stencil.name,sym_table);
      Symbole addrTab = sym_find(tmp_tab->val.str,sym_table);
      Dim dimTab = addrTab->val.dimension;

      Arbre indexTab = tmp_tab->fils;

      result = sym_new_tmp(sym_table);
      printf("nb dim du tab = %d\n",nbFreres(indexTab));


      while(nbFreres(indexTab) > sym_sten->val.stencil.dim){
        printf("Ok test\n");
        arg = genCode(indexTab,sym_table);
        sym_arg1=quad_res(arg);

        codegen = add_quad(codegen,arg);

        tmp = sym_new_tmp(sym_table);
        tmp->type = sym_const;
        tmp->val.entier = produitDim(dimTab->next)*4;

        codegen = add_quad(codegen,quad_add(NULL,q_mul,sym_arg1,tmp,sym_new_tmp(sym_table)));
        codegen = add_quad(codegen,quad_add(NULL,q_add,addrTab,quad_res(codegen),sym_new_tmp(sym_table)));
        addrTab = quad_res(codegen);

        indexTab = indexTab->freres;
        dimTab = (dimTab)?dimTab->next:NULL;
      }

      codegen = add_quad(codegen,genForStencil(indexTab,dimTab,sym_sten,1,sym_sten,addrTab,result,sym_table));

      /*printf("#########PETITE VERIF CODEGEN\n");
      print_quad(codegen);
      printf("\n\n");*/

      codegen = add_quad(codegen,quad_add(NULL,use_var,NULL,NULL,result));
      break;
    case ast_fonction:
      sym_arg1 = sym_find(ast->val.str,sym_table);
      Arg list_arg = sym_arg1->val.arg_list;
      fils = ast->fils;
      //affectation des arguments
      while(list_arg != NULL){
        sym_arg2 = sym_find(list_arg->name,sym_table);
        arg = add_quad(arg,genCode(fils,sym_table));
        arg = add_quad(arg,quad_add(NULL,affectation_var,quad_res(arg),NULL,sym_arg2));
        arg2 = add_quad(arg2,quad_add(NULL,q_empile,NULL,NULL,sym_arg2));
        arg3 = add_quad(quad_add(NULL,q_depile,NULL,NULL,sym_arg2),arg3);
        list_arg = list_arg->next;
        fils = fils->freres;
      }
      codegen = add_quad(codegen,arg2);
      codegen = add_quad(codegen,arg);

      //appel de la Fonction

      codegen = add_quad(codegen,quad_add(NULL,q_goto,NULL,NULL,sym_arg1));
      codegen = add_quad(codegen,arg3);

      //recuperation du resultat
      codegen = add_quad(codegen,quad_add(NULL,q_fctRes,NULL,NULL,sym_new_tmp(sym_table)));
      break;
    case ast_returnFct:
      arg = genCode(ast->fils,sym_table);
      codegen = add_quad(codegen,arg);
      codegen = add_quad(codegen,quad_add(NULL,q_returnFct,quad_res(arg),NULL,NULL));
      break;
  }
  return codegen;
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
