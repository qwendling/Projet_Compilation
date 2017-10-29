#ifndef TABLE_SYMBOLE_H
#define TABLE_SYMBOLE_H

typedef struct std_symbole{
  char* name;
  int index;
  struct std_symbole* next;
}std_symbole,*Symbole;

int sym_hach(const char* name);

void sym_add(Symbole* table);

int sym_find_index(Symbole* table,const char* name);




#endif
