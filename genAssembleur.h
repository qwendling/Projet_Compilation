#ifndef GENASSEMBLEUR_H
#define GENASSEMBLEUR_H

#include "table_symbole.h"
#include "generationCI.h"
#include <stdio.h>

// FOnction de generation de printf
void gen_printf(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de printi
void gen_printi(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de l'affectation
void gen_affectation(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation du return
void gen_return(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation du main
void gen_main(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de l'affectation de variable
void gen_affecVar(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de la somme
void gen_add(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de la soustraction
void gen_sub(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de la multiplication
void gen_mul(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// FOnction de generation de la division
void gen_div(quad code,Symbole sym_table[TAILLE_TABLE],FILE* file);

// Ajout de tout les symboles dans le .data
void gen_sym(Symbole s,FILE* file);
void gen_sym_table(Symbole sym_table[TAILLE_TABLE],FILE* file);

//Genere le code assembleur en fonction des quads et Table des Symbole dans un fichier
void genAssembleur(quad,Symbole[],FILE*);

// Genere le head du fichier assembleur : .data .text .globl main
void genAssembleur_header(Symbole[],FILE* file);

#endif
