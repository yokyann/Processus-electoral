#ifndef exercice5_H
#define exercice5_H

#include "exercice4.h"

// liste chainee de cles
typedef struct cellKey
{
    Key *data;
    struct cellKey *next;
} CellKey;

// liste chainee de declarations
typedef struct cellProtected
{
    Protected *data;
    struct cellProtected *next;

} CellProtected;

// allocation et initialisation
CellKey *create_cell_key(Key *key);
CellProtected *create_cell_protected(Protected *pr);

// ajout en tete
void ajout_tete_cell_key(CellKey **c, Key *key);
void ajout_tete_cell_protected(CellProtected **c, Protected *pr);

// lecture de fichiers et renvoie une liste chainee
CellKey *read_public_keys(char *nomfic);     // fichiers :  'keys.txt' ou 'candidates.txt'
CellProtected *read_protected(char *nomfic); // fichier : 'declarations.txt'

// Affichage des listes chainees
void print_list_keys(CellKey *LCK);
void print_list_protected(CellProtected *LCP);

// DESALLOCATION

// desallocation d'une cellule (la derniere cellule de la liste)
void delete_cell_key(CellKey *c);
void delete_cell_protected(CellProtected *c);

// desallocation de la liste entiere
void delete_list_protected(CellProtected **LCP);
void delete_list_keys(CellKey *LCK);

#endif
