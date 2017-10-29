#ifndef GENERATIONCI_H
#define GENERATIONCI_H

typedef union symbol {
  char* str;
  int cst;
}symbol;


typedef struct quad {
  char op; //operateur
  symbol* arg1; //1er argument
  symbol* arg12; //2eme argument
  symbol* res; // resultat
  struct quad* next; //quad suivant
}quad, *quad;




#endif
