#ifndef exercice7_H
#define exercice7_H

#include <openssl/sha.h>
#include "exercice6.h"

typedef struct block
{
    Key *author;                  // cle publique de l'auteur
    CellProtected *votes;         // declarations de vote
    unsigned char *hash;          // valeur hachee obtenu par compute_proof_of_work
    unsigned char *previous_hash; // valeur hache du block precedent
    int nonce;                    // preuve de travail
} Block;

clock_t temps_proof_init;
clock_t temps_proof_final;
double temps_proof;

// Fichiers lecture/ecriture
/* Format :
author hash previous_hash nonce
premier vote
deuxieme vote
etc.
*/
void ecrire_fichier_block(char *nomfic, Block *b);
Block *lecture_fichier_block(char *nomfic);

// temps de la fonction compute_proof_of_work en fonction de d (nombre de 0)
void ecrire_temps_fichier(char *nomfic, Block *b, int max);

// conversion
unsigned char *str_to_SHA256(char *s); // chaine de caractere hachee avec l'algorithme SHA256
// Format : auteur previous_hash
//  decl
//  nonce
char *block_to_str(Block *block);

// initialisation de nonce et de la valeur hachee du block
void compute_proof_of_work(Block *B, int d);

// verification
int verify_block(Block *b, int d);

// suppression d'un block
void delete_block(Block *b); // desallocation des valeurs hachee, des valeurs prec hachees celulles de declarations de votes

#endif
