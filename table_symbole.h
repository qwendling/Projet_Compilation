#ifndef TABLE_SYMBOLE_H
#define TABLE_SYMBOLE_H
#define TAILLE_TABLE 4096

typedef enum sym_type{
  sym_var,
  sym_const
} sym_type;

typedef struct std_symbole{
  char* name;
  int index;
  union{
    int entier;
    char* string;
  } val;
  sym_type type;
  struct std_symbole* next;
}std_symbole,*Symbole;

Symbole sym_Table[TAILLE_TABLE];

int sym_hach(char* name);

void sym_add(char* name);

int sym_find_index(char* name);

void sym_delete_table();

Symbole sym_new_tmp();

#endif
