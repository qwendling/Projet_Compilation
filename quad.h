#ifndef QUAD_H
#define QUAD_H
#include "table_symbole.h"

// enumeration des types de quad
typedef enum quad_op{
  //--- Sprint 1
  print_i,
  print_f,
  return_prog,
  create_string,
  create_main,

  //--- Sprint 2
  use_var,
  affectation,
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


#endif
