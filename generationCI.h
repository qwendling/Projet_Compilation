#ifndef GENERATIONCI_H
#define GENERATIONCI_H
#include "table_symbole.h"
#include "arbre.h"

typedef enum quad_op{
  print_i,
  print_f,
  affectation,
  return_prog
} quad_op;


typedef struct quad_struct {
  quad_op op; //operateur
  Symbole arg1; //1er argument
  Symbole arg2; //2eme argument
  Symbole res; // resultat
  struct quad_struct * next; //quad suivant
}std_quad , *quad;


quad quad_add(quad,quad_op,Symbole,Symbole,Symbole);
void quad_free(quad);
void print_quad(quad);

quad genCode(Arbre,Symbole[]);



#endif
