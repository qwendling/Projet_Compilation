#ifndef TABLE_SYMBOLE_H
#define TABLE_SYMBOLE_H
#define TAILLE_TABLE 4096

typedef struct std_symbole{
  char* name;
  int index;
  struct std_symbole* next;
}std_symbole,*Symbole;

Symbole sym_Table[TAILLE_TABLE];

int sym_hach(char* name);

void sym_add(char* name);

int sym_find_index(char* name);

void sym_delete_table();


#endif
