#ifndef GENERATIONCI_H
#define GENERATIONCI_H
#include "table_symbole.h"
#include "arbre.h"
#include "quad.h"

// Structure de la liste chainé stockant les strings
typedef struct const_string {
  char* name;
  char* val;
  struct const_string * next;
}std_string, *ConstString;



// Ajoute un quad dans la liste
quad quad_add(quad,quad_op,Symbole,Symbole,Symbole);

// Concatène deux liste de quad
quad add_quad(quad q1,quad q2);

// Supprime la liste quad
void quad_free(quad);

//Affiche les quads sur le terminal
void print_quad(quad);

// genere les quads depuis l'AST en stockant dans la table des symboles
quad genCode(Arbre,Symbole[]);

// Affiche les strings sur le terminal
void print_const(ConstString s);

// Ajoute un string dans ConstString
ConstString constString_add(char*);

// Supprime ConstString
void constString_free(ConstString);

// Return le resultat d'un quad
Symbole quad_res(quad q);

#endif
