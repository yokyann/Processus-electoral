#ifndef exercice2_H
#define exercice2_H

#include "exercice1.h"

// retourne pgcd
long extended_gcd(long s, long t, long *u, long *v);

// genere les valeurs de la cle publique (s,u) et secrete (u,n)
void generate_keys_values(long p, long q, long *n, long *s, long *u);

// cryptage/decryptage
long *encrypt(char *chaine, long s, long n);            // cryptage du message avec la cle publique
char *decrypt(long *crypted, int size, long u, long n); // decryptage a partir des valeurs de la cle secrete

// affichage
void print_long_vector(long *result, int size);

#endif