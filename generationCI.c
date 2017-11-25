#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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
		printf("affectation %s NULL %s\n",q->arg1->name,q->res->name);
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
  }
  print_quad(q->next);
}

// genere les quads depuis l'AST en stockant dans la table des symboles et strings
quad genCode(Arbre ast,Symbole sym_table[TAILLE_TABLE]){
  //nouveau symbole du quad
  Symbole tmp,tmp2,sym_arg1,sym_arg2;
  quad codegen = NULL,arg = NULL,arg2=NULL;
  Arbre fils;
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
        codegen = add_quad(codegen,quad_add(NULL,print_f,quad_res(arg),NULL,NULL));
        break;
    case ast_printi:
  		printf("CI printi\n");
        // on genere le quad de la constante a afficher
        arg = genCode(ast->fils,sym_table);
        codegen = arg;
        codegen = add_quad(codegen,quad_add(NULL,print_i,quad_res(arg),NULL,NULL));
        break;
    case ast_return:
  		  printf("CI return\n");
        // on genere le quad de la valeur a return
        arg = genCode(ast->fils,sym_table);
        codegen = arg;
        codegen = add_quad(codegen,quad_add(NULL,return_prog,quad_res(arg),NULL,NULL));
        break;
    case ast_main:
  		printf("CI main\n");
        codegen = quad_add(codegen,create_main,NULL,NULL,NULL);
        fils = ast->fils;
        // On parcoure l'AST pour générer tout les quads
        while(fils != NULL){
          codegen = add_quad(codegen,genCode(fils,sym_table));
          fils = fils->freres;
        }
        break;
    case ast_var:
  		printf("CI Var\n");
  		codegen = quad_add(codegen,use_var,NULL,NULL,sym_find(ast->val.str,sym_table));
  		break;
  	case ast_affectation:
  		printf("CI affecVar %s\n",ast->fils->val.str);
  		arg = genCode(ast->fils->freres,sym_table);
  		printf("test arg : %s\n",quad_res(arg)->name);
  		codegen = arg;
  		codegen = add_quad(codegen,quad_add(NULL,affectation_var,quad_res(arg),NULL,sym_find(ast->fils->val.str,sym_table)));
  		break;
  	case ast_div:
  	  printf("CI /\n");
  		tmp = sym_new_tmp(sym_table);
  		arg = genCode(ast->fils,sym_table);
  		arg2 = genCode(ast->fils->freres,sym_table);
  		sym_arg1 = quad_res(arg);
  		sym_arg2 = quad_res(arg2);
  		codegen = add_quad(arg,arg2);
  		codegen = add_quad(codegen,quad_add(NULL,q_div,sym_arg1,sym_arg2,tmp));
  		break;
  	case ast_fois:
  	  printf("CI *\n");
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
  		tmp = sym_new_tmp(sym_table);
  		arg = genCode(ast->fils,sym_table);
  		arg2 = genCode(ast->fils->freres,sym_table);
  		sym_arg1 = quad_res(arg);
  		sym_arg2 = quad_res(arg2);
  		codegen = add_quad(arg,arg2);
  		codegen = add_quad(codegen,quad_add(NULL,q_add,sym_arg1,sym_arg2,tmp));

  		break;
    case ast_autoIncrementPlus:
      sym_arg1 = sym_find(ast->fils->val.str,sym_table);
      tmp = sym_new_tmp(sym_table);
      codegen = add_quad(codegen,quad_add(NULL,affectation_var,sym_arg1,NULL,tmp));
      tmp2 = sym_new_tmp(sym_table);
      tmp2->type = sym_const;
      tmp2->val.entier = 1;
      codegen = add_quad(codegen,quad_add(NULL,affectation,NULL,NULL,tmp2));
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
