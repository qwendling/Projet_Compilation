#ifndef TABLE_SYMBOLE_H
#define TABLE_SYMBOLE_H

// Taille de la table des symboles
#define TAILLE_TABLE 4096

typedef struct std_dim{
	int size;
	struct std_dim* next;
}std_dim,*Dim;

// Enumeration des types de symboles
typedef enum sym_type{
  sym_var, // symbole
  sym_const,
  sym_string,
  sym_label,
  sym_tab,
	sym_tabRes,
	sym_stencil,
} sym_type;

// Structure des symboles
typedef struct std_symbole{
  char* name;
  int index; //index dans la table
  union{
    int entier;
    char* str;
    Dim dimension;
		struct {
			int voisin;
			int dim;
			int size;
		} stencil;
  } val;
  sym_type type; // type du symbole
  struct std_symbole* next;
}std_symbole,*Symbole;


// Donne le hach pour un nom donné
int sym_hach(char* name);

// Verifie qu'un symbole existe et le renvoie
Symbole sym_existe(Symbole s,char* name);

// Ajoute un symbole au hach donné
Symbole sym_add_aux(Symbole s,char* name,int h);

// Ajoute un symbole de nom donné dans la table
void sym_add(char* name,Symbole[]);

// Trouve l'index du symbole de nom donné
int sym_find_index(char* name,Symbole[]);

// Trouve le symbole de nom donné
Symbole sym_find(char* name,Symbole sym_Table[TAILLE_TABLE]);

// Supprime un symbole
void sym_delete(Symbole s);

// SUpprime la table de symbole
void sym_delete_table(Symbole[]);

// AJoute un nouveau symbole temporaire dans la table
Symbole sym_new_tmp(Symbole[]);

//Ajoute un label dans la table
Symbole sym_new_lbl(Symbole[]);

int sym_existe_table(Symbole table[],char* name);

#endif
