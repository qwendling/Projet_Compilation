#ifndef GENERATIONCI_H
#define GENERATIONCI_H

typedef union symbol {
  char* str;
  int cst;
}symbol;


typedef struct quad_struct {
  char op; //operateur
  symbol* arg1; //1er argument
  symbol* arg12; //2eme argument
  symbol* res; // resultat
  struct quad_struct * next; //quad suivant
}quad_struct , *quad;




#endif
