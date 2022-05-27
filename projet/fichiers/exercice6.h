#ifndef exercice6_H
#define exercice6_H

#include "exercice5.h"

typedef struct hashcell
{
    Key *key;
    int val; // 0 pas voté, 1 voté (si candidat : nombre de vote)
} HashCell;

typedef struct hashtable
{
    HashCell **tab;
    int size;
} HashTable;

// verification et supression de toutes les declarations non valide (si rien est valide liste est vide NULL)
void verify_cell_protected(CellProtected **c);

// Creation
HashCell *create_hashcell(Key *key);                  // creation de cellules
HashTable *create_hashtable(CellKey *keys, int size); // creation de table de hachage

// renvoie la cle
int hash_function(Key *key, int size); // s * u % size

// renvoie position de la cle dans la table
int find_position(HashTable *t, Key *key);

// ajoute dans la table de hachage la cle
void ajout_hashtable(HashTable *h, Key *key);

int est_dans_table(HashTable *t, Key *k); // 1 sil existe sinon 0
Key *le_plus_vote(HashTable *h);          // renvoie le candidat qui a le plus de vote parmi la table

// renvoie la cle du candidat gagnant depuis une generation de donnee
Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);

// desallocation
void delete_hashtable(HashTable *t);

#endif
