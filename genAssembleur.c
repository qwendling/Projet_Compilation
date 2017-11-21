#include "genAssembleur.h"
#include <string.h>
#include <stdlib.h>

//Genere le code assembleur en fonction des quads et Table des Symbole dans un fichier .s
void genAssembleur(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
  if(code == NULL)
    return;
  char* str_code = calloc(1024,sizeof(char));
  if(str_code == NULL)
    exit(1);
  printf("Debut gen \n");
  // Switch en fonction de l'operéation du quad
  switch(code->op){
    case print_i: // Assembleur pour le printi
      printf("gen printi\n\n");
      // On charge l'argument a print en cherchant avec son index
      snprintf(str_code,1024,"lw $a0 %s\n",code->arg1->name);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);
      // On affiche l'entier
      str_code = "li $v0 1\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      str_code = "syscall\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      break;
    case print_f: // Assembleur pour le printf
      printf("gen printf\n");
      // On charge l'argument a print en cherchant avec son index
      snprintf(str_code,1024,"la $a0 %s\n",code->arg1->name);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);
      // On affiche le string
      str_code = "li $v0 4\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      str_code = "syscall\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      break;
    case affectation: // Assembleur pour l'affectation'
      printf("gen affec\n");
      // On sauvgarde la valeur dans le registre t0
      snprintf(str_code,1024,"li $t0 %d\n",code->res->val.entier);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      printf("\n%d\n",code->res->index);
      // On sauvgarde t0 a l'adresse de l'index
      snprintf(str_code,1024,"sw $t0 %s\n",code->res->name);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);
      break;
      // WTFFFFFFFFFFFFFFFFFFFFFFFF ?????????????????
    case return_prog: // Assembleur pour le return du programme
      printf("gen return\n");
      snprintf(str_code,1024,"lw $a0 %s\n",code->arg1->name);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);
      str_code = "li $v0 17\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      str_code = "syscall\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      break;
      // WTFFFFFFFFFFFFFFFFFFFFFFFF ?????????????????
    case create_main:
      str_code = "main:\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
  }
  // On génére le code du quad suivant 
  genAssembleur(code->next,sym_table,file);
}

void gen_sym(Symbole s,FILE* file){
	if(s == NULL)
		return;
	char* str_code = calloc(1024,sizeof(char));	
	switch(s->type){
		case sym_var:
			snprintf(str_code,1024,"%s: .word 0\n",s->name);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			break;
		case sym_const:
			snprintf(str_code,1024,"%s: .word %d\n",s->name,s->val.entier);
			fwrite(str_code,sizeof(char),strlen(str_code),file);
			break;
		case sym_string:
			snprintf(str_code,1024,"%s: .asciiz %s\n",s->name,s->val.str);
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


