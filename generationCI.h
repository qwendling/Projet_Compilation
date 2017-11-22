#ifndef GENERATIONCI_H
#define GENERATIONCI_H
#include "table_symbole.h"
#include "arbre.h"

// Structure de la liste chainé stockant les strings
typedef struct const_string {
  char* name;
  char* val;
  struct const_string * next;
}std_string, *ConstString;

// enumeration des types de quad
typedef enum quad_op{
  print_i,
  print_f,
  affectation,
  return_prog,
  create_string,
  create_main,
  use_var,
  affectation_var,
  q_add,
  q_sub,
  q_mul,
  q_div
} quad_op;

// structure des quads
typedef struct quad_struct {
  quad_op op; //operateur
  Symbole arg1; //1er argument
  Symbole arg2; //2eme argument
  Symbole res; // resultat
  struct quad_struct * next; //quad suivant
}std_quad , *quad;


// Ajoute un quad dans la liste
quad quad_add(quad,quad_op,Symbole,Symbole,Symbole);

// Concatène deux liste de quad
quad add_quad(quad q1,quad q2);

// Supprime la liste quad
void quad_free(quad);

//Affiche les quads sur le terminal
void print_quad(quad);

// genere les quads depuis l'AST en stockant dans la table des symboles et strings
quad genCode(Arbre,Symbole[]);

// Affiche les strings sur le terminal
void print_const(ConstString s);

// Ajoute un string dans ConstString
ConstString constString_add(char*);

// Supprime ConstString
void constString_free(ConstString);

#endif
