#include "genAssembleur.h"
#include <string.h>
#include <stdlib.h>

void load_var(const char* registre,const Symbole s,FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	switch(s->type){
		case sym_tabRes:
			snprintf(str_code,1024,"lw %s %s\n",registre,s->name);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			snprintf(str_code,1024,"lw %s (%s)\n",registre,registre);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			free(str_code);
			break;
		case sym_var:
			snprintf(str_code,1024,"lw %s %s\n",registre,s->name);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			free(str_code);
			break;
		case sym_const:
			snprintf(str_code,1024,"li %s %d\n",registre,s->val.entier);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			free(str_code);
			break;
		case sym_string:
		case sym_stencil:
		case sym_tab:
			snprintf(str_code,1024,"la %s %s\n",registre,s->name);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			free(str_code);
			break;
	}
}

// FOnction de generation de
void gen_printf(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On charge l'argument a print en cherchant avec son index
	load_var("$a0",code->arg1,file);
	free(str_code);

	// On affiche le string
	str_code = "li $v0 4\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	str_code = "syscall\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
}

// FOnction de generation de printi
void gen_printi(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On charge l'argument a print en cherchant avec son index
	load_var("$a0",code->arg1,file);
	free(str_code);


	// On affiche l'entier
	str_code = "li $v0 1\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	str_code = "syscall\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
}

// FOnction de generation de l'affectation
void gen_affectation(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	/*char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	printf("gen affec\n");
	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"li $t0 %d\n",code->res->val.entier);
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	printf("\n%d\n",code->res->index);
	// On sauvgarde t0 a l'adresse de l'index
	snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	free(str_code);*/
}

// FOnction de generation du return
void gen_return(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	load_var("$a0",code->arg1,file);
	free(str_code);

	str_code = "li $v0 17\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	str_code = "syscall\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
}

// FOnction de generation du main
void gen_main(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code;

	str_code = "main:\n";
	fwrite(str_code,sizeof(char),strlen(str_code),file);
}

// FOnction de generation de l'affectation de variable
void gen_affecVar(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0

	load_var("$t0",code->arg1,file);

	// On sauvgarde t0 a l'adresse de l'index
	snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	free(str_code);
}

// FOnction de generation de l'affectation de tableau
void gen_affecTab(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	if(code->res->type == sym_stencil){
		snprintf(str_code,1024,"la $t1 %s\n",code->res->name);
		fwrite(str_code,sizeof(char),strlen(str_code),file);
	}
	else{
		snprintf(str_code,1024,"lw $t1 %s\n",code->res->name);
		fwrite(str_code,sizeof(char),strlen(str_code),file);
	}

	snprintf(str_code,1024,"sw $t0 ($t1)\n");
	fwrite(str_code,sizeof(char),strlen(str_code),file);
	free(str_code);
}

// FOnction de generation de la somme
void gen_add(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"add $t0 $t0 $t1\n");
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

// FOnction de generation de la soustraction
void gen_sub(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"sub $t0 $t0 $t1\n");
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

// FOnction de generation de la multiplication
void gen_mul(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"mul $t0 $t0 $t1\n");
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

// FOnction de generation de la division
void gen_div(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"div $t0 $t0 $t1\n");
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}


void gen_equal(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"beq $t0 $t1 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_nequal(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"bne $t0 $t1 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_greater(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"bgt $t0 $t1 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_greaterOrEqual(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"bge $t0 $t1 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_less(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"blt $t0 $t1 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_lessOrEqual(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	load_var("$t0",code->arg1,file);

	// On sauvgarde la valeur dans le registre t1
	load_var("$t1",code->arg2,file);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"ble $t0 $t1 %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_label(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"%s:\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

void gen_goto(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
	char* str_code = calloc(1024,sizeof(char));
	if(str_code == NULL)
		exit(1);

	// On sauvgarde la valeur dans le registre t0
	snprintf(str_code,1024,"b %s\n",code->res->name);
	fwrite(str_code,sizeof(char),strlen(str_code),file);

	free(str_code);
}

//Genere le code assembleur en fonction des quads et Table des Symbole dans un fichier .s
void genAssembleur(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
  if(code == NULL)
    return;
  // Switch en fonction de l'operéation du quad
  switch(code->op){
    case print_i: // Assembleur pour le printi
      gen_printi(code,sym_table,file);
      break;
    case print_f: // Assembleur pour le printf
      gen_printf(code,sym_table,file);
      break;
    case affectation: // Assembleur pour l'affectation'
      gen_affectation(code,sym_table,file);
      break;
    case return_prog: // Assembleur pour le return du programme
      gen_return(code,sym_table,file);
      break;
    case create_main:
	  	gen_main(code,sym_table,file);
			break;
		case affectation_var:
			gen_affecVar(code,sym_table,file);
			break;
		case affectation_tab:
			gen_affecTab(code,sym_table,file);
			break;
		case q_add:
			gen_add(code,sym_table,file);
			break;
		case q_sub:
			gen_sub(code,sym_table,file);
			break;
		case q_mul:
			gen_mul(code,sym_table,file);
			break;
		case q_div:
			gen_div(code,sym_table,file);
			break;
		case q_equal:
			gen_equal(code,sym_table,file);
			break;
		case q_nequal:
			gen_nequal(code,sym_table,file);
			break;
		case q_greater:
			gen_greater(code,sym_table,file);
			break;
		case q_greaterOrEqual:
			gen_greaterOrEqual(code,sym_table,file);
			break;
		case q_less:
			gen_less(code,sym_table,file);
			break;
		case q_lessOrEqual:
			gen_lessOrEqual(code,sym_table,file);
			break;
		case q_create_label:
			gen_label(code,sym_table,file);
			break;
		case q_goto:
			gen_goto(code,sym_table,file);
			break;

  }
  // On génére le code du quad suivant
  genAssembleur(code->next,sym_table,file);
}

int sizeTab(Symbole s){
	Dim tmpDim = s->val.dimension;
	int size=1;
	do{
		size *= tmpDim->size;
		tmpDim = tmpDim->next;
	}while(tmpDim != NULL);

	return size;
}

// Ajout de tout les symboles dans le .data
void gen_sym(Symbole s,FILE* file){
	if(s == NULL)
		return;
	char* str_code = calloc(1024,sizeof(char));
	switch(s->type){
		case sym_tabRes:
		case sym_var:
			snprintf(str_code,1024,"%s: .word 0\n",s->name);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			break;
		case sym_string:
			snprintf(str_code,1024,"%s: .asciiz %s\n",s->name,s->val.str);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			break;
		case sym_tab:
			snprintf(str_code,1024,"%s: .space %d\n",s->name,sizeTab(s)*4);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			break;
		case sym_stencil:
			printf("Size stencil : %d\n",s->val.stencil.size);
			snprintf(str_code,1024,"%s: .space %d\n",s->name,s->val.stencil.size*4);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			break;
	}
	free(str_code);
	gen_sym(s->next,file);
}


void gen_sym_table(Symbole sym_table[TAILLE_TABLE],FILE* file){
	for(int i=0;i<TAILLE_TABLE;i++){
		gen_sym(sym_table[i],file);
	}
}

// Genere le head du fichier assembleur
// Avec les .data .asciiz
// .text .globl main
void genAssembleur_header(Symbole sym_table[TAILLE_TABLE],FILE* file){
  char* str_code = ".data\n";
  fwrite(str_code,sizeof(char),strlen(str_code),file);

  gen_sym_table(sym_table,file);

  str_code = ".text\n.globl main\n";
  fwrite(str_code,sizeof(char),strlen(str_code),file);
}
