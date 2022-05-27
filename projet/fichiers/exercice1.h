#ifndef exercice1_H
#define exercice1_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


// calcul du temps pour l'algorithme 1
clock_t temps_initial;
clock_t temps_final;
double temps_cpu;

// calcul du temps pour l'algorithme 2
clock_t temps_initial2;
clock_t temps_final2;
double temps_cpu2;


// est premier
int is_prime_naive(long p);       // si oui renvoie 1 sinon 0 avec p impair
void is_prime_naive_temps(int p); // affiche le temps de is_prime_naive

// calcul : a^b mod n
long modpow_naive(long a, long m, long n);
int modpow(long a, long m, long n);
// donnes du temps de deux fonctions modpow dans un fichier
void modpow_calcul(char *fichier);

// Miller
int witness(long a, long b, long d, long p); // si 1 alors temoin de Miller, donc p pas premier pour la valeur a
long rand_long(long low, long up);           // renvoie un nombre aleatoire taille [low,up]
int is_prime_miller(long p, int k);          // renvoie 1 si p est premier pour un nombre k de tests sinon 0

// renvoie un nombre premier compris entre 2 taille [low,up] pour k test de miller
long random_prime_number(int low_size, int up_size, int k);

#endif