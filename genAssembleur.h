#ifndef GENASSEMBLEUR_H
#define GENASSEMBLEUR_H

#include "table_symbole.h"
#include "generationCI.h"
#include <stdio.h>

void genAssembleur(quad,Symbole[],FILE*);
void genAssembleur_header(ConstString,FILE* file);

#endif
