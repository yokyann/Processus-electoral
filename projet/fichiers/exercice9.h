#ifndef exercice9_H
#define exercice9_H

#include <dirent.h>
#include "exercice8.h"

// ecriture de la declaration a la suite dans le fichier "Pending_votes.txt"
void submit_vote(Protected *p);

// creation dun block dans "Pending_block" et supprime "Pending_votes.txt" et l ajoute dans l'arbre
void create_block(CellTree **tree, Key *author, int d);

// ajoute le block : ./Blockchain/name si verifiee et supprime "Pending_block"
void add_block(int d, char *name);

// lecture des fichiers : ./Blockchain/* et renvoie sous forme d'arbre
CellTree *read_tree();

// renvoie la cle du candidat gagnant depuis une generation de donnee et depuis une blockchain
Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV);

#endif
