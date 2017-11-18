#include "genAssembleur.h"

void genAssembleur(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file){
  if(quad == NULL)
    return;
  char string[1024];
  switch(code->op){
    case print_i:
      snprintf(string,1024,"lw $a0 %d($sp)\n",4*code->arg1->index);
      fwrite(string,sizeof(char),strlen(string),file);
      string = "li $v0 1\n";
      fwrite(string,sizeof(char),strlen(string),file);
      string "syscall\n";
      fwrite(string,sizeof(char),strlen(string),file);
      break;
    case print_f:
      snprintf(string,1024,"la $a0 %s\n",code->arg1->name + 1);
      fwrite(string,sizeof(char),strlen(string),file);
      string = "li $v0 4\n";
      fwrite(string,sizeof(char),strlen(string),file);
      string "syscall\n";
      fwrite(string,sizeof(char),strlen(string),file);
      break;
    case affectation:
      snprintf(string,1024,"li $t0 %d\n",code->res->val.entier);
      fwrite(string,sizeof(char),strlen(string),file);
      snprintf(string,1024,"sw $t0 %d($sp)\n",4*code->arg1->index);
      fwrite(string,sizeof(char),strlen(string),file);
      break;
    case return_prog:
      snprintf(string,1024,"li $a0 %d\n",code->arg1->val.entier);
      fwrite(string,sizeof(char),strlen(string),file);
      string = "li $v0 17\n";
      fwrite(string,sizeof(char),strlen(string),file);
      string "syscall\n";
      fwrite(string,sizeof(char),strlen(string),file);
      break;
  }
  genAssembleur(code->next,sym_table,file);
}
