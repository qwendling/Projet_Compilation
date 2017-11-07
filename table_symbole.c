#include "table_symbole.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int sym_hach(char* name){
  unsigned int i;
  int hach=0;

  int sizeName = strlen(name);
  for(i=0;i<sizeName;i++){
    hach+=name[i]<<i;
  }

  return hach%TAILLE_TABLE;
}

Symbole sym_existe(Symbole s,char* name){
  if(s==NULL){
    return NULL;
  }
  if(strcmp(s->name,name)==0){
    return s;
  }
  return sym_existe(s->next,name);
}

Symbole sym_add_aux(Symbole s,char* name){
  Symbole e=sym_existe(s,name);
  if(e!=NULL){
    return s;
  }
  int id = 0;
  if(s!=NULL)
    id = s->index+1;

  Symbole new=malloc(sizeof(std_symbole));
  new->name=name;
  new->index=id;
  new->next = s;
  new->type=sym_var;
  return new;
}

void sym_add(char* name){
  int h = sym_hach(name);
  Symbole e = sym_Table[h];
  if(e==NULL){
    sym_Table[h]=sym_add_aux(sym_Table[h],name);
  }
}

int sym_find_index(char* name){
  int h = sym_hach(name);
  Symbole e = sym_existe(sym_Table[h],name);
  if(e==NULL)
    return -1;
  return e->index*4096+h;
}

void sym_delete(Symbole s){
  if(s==NULL){
    return;
  }
  Symbole tmp = s->next;
  free(s->name);
  free(s);
  sym_delete(tmp);
}

void sym_delete_table(){
  int i=0;
  for(;i<TAILLE_TABLE;i++){
    sym_delete(sym_Table[i]);
  }
}

Symbole sym_new_tmp(){
  static int nb_tmp=0;

  char name[1024];
  snprintf(name,1024,"tmp%d",nb_tmp);

  char* name_tmp=malloc(strlen(name));

  strncpy(name_tmp,name,strlen(name));

  nb_tmp++;

  int h=sym_hach(name_tmp);

  Symbole new_tmp;

  if(sym_existe(sym_Table[h],name_tmp)!=NULL){
    free(name_tmp);
    new_tmp=sym_new_tmp();
    return new_tmp;
  }

  sym_add(name_tmp);
  new_tmp=sym_existe(sym_Table[h],name_tmp);

  return new_tmp;

}
