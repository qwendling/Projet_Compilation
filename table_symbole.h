#ifndef TABLE_SYMBOLE_H
#define TABLE_SYMBOLE_H
#define TAILLE_TABLE 4096

typedef enum sym_type{
  sym_var,
  sym_const,
  sym_string
} sym_type;

typedef struct std_symbole{
  char* name;
  int index;
  union{
    int entier;
    char* str;
  } val;
  sym_type type;
  struct std_symbole* next;
}std_symbole,*Symbole;



int sym_hach(char* name);
Symbole sym_add(char* name,Symbole[]);

int sym_find_index(char* name,Symbole[]);

Symbole sym_find(char* name,Symbole sym_Table[TAILLE_TABLE]);

void sym_delete_table(Symbole[]);

Symbole sym_new_tmp(Symbole[]);

#endif
