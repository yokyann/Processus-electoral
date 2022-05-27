#ifndef exercice8_H
#define exercice8_H

#include "exercice7.h"

typedef struct block_tree_cell
{
    Block *block;
    struct block_tree_cell *father;     // pere
    struct block_tree_cell *firstChild; // fils
    struct block_tree_cell *nextBro;    // frere (noeud de meme niveau)
    int height;                         // hauteur
} CellTree;

// creation et initialisation d'un noeud
CellTree *create_node(Block *b);

// mise a jour de la taille du pere
int update_height(CellTree *father, CellTree *child); // 1 si modifie 0 sinon
void add_child(CellTree *father, CellTree *child);
void fusion_LDP(CellProtected **l1, CellProtected *l2);

// affichage de l'arbre
void print_tree(CellTree *tree);

// desallocation
void delete_node(CellTree *node);
void delete_CellTree(CellTree *tree);

CellTree *highest_child(CellTree *cell); // fils avec lhauteur max
CellTree *last_node(CellTree *tree);     // fils au plus bas et dernier frere

// fusion des declarations avec la plus long chaine de l'arbre
CellProtected *decl_longue_chaine(CellTree **tree);

// suppression
void delete_author(CellTree *tree); // des auteurs de l'arbre
void delete_data(CellTree *tree);   // des donnees des block dans larbre
void delete_data_decl_long(CellTree *tree);   // des donnees des block dans larbre si on a utilise decl_longue_chaine


#endif
