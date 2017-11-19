#ifndef GENASSEMBLEUR_H
#define GENASSEMBLEUR_H

#include "table_symbole.h"
#include "generationCI.h"
#include <stdio.h>


//Genere le code assembleur en fonction des quads et Table des Symbole dans un fichier
void genAssembleur(quad,Symbole[],FILE*);

// Genere le head du fichier assembleur : .data .text .globl main
void genAssembleur_header(ConstString,FILE* file);

#endif
