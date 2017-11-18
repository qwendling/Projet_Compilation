#include "genAssembleur.h"
#include <string.h>
#include <stdlib.h>

void genAssembleur(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
  if(code == NULL)
    return;
  char* str_code = calloc(1024,sizeof(char));
  if(str_code == NULL)
    exit(1);
  printf("Debut gen \n");
  switch(code->op){
    case print_i:
      printf("gen printi\n\n");
      snprintf(str_code,1024,"lw $a0 %d($sp)\n",4*code->arg1->index);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);

      str_code = "li $v0 1\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      str_code = "syscall\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      break;
    case print_f:
      printf("gen printf\n");
      snprintf(str_code,1024,"la $a0 %s\n",code->arg1->name + 1);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);

      str_code = "li $v0 4\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      str_code = "syscall\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      break;
    case affectation:
      printf("gen affec\n");
      snprintf(str_code,1024,"li $t0 %d\n",code->res->val.entier);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      printf("\n%d\n",code->res->index);
      snprintf(str_code,1024,"sw $t0 %d($sp)\n",4*code->res->index);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);
      break;
    case return_prog:
      printf("gen return\n");
      snprintf(str_code,1024,"lw $a0 %d($sp)\n",code->arg1->index);
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      free(str_code);
      str_code = "li $v0 17\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      str_code = "syscall\n";
      fwrite(str_code,sizeof(char),strlen(str_code),file);
      break;
  }
  genAssembleur(code->next,sym_table,file);
}
