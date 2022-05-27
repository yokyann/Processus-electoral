#include "exercice8.h"

CellTree *create_node(Block *b)
{
    CellTree *ct = malloc(sizeof(CellTree));
    ct->block = b;
    ct->height = 0;
    ct->father = NULL;
    ct->firstChild = NULL;
    ct->nextBro = NULL;
    return ct;
}

int update_height(CellTree *father, CellTree *child)
{
    // pere null, child racine
    if (father == NULL)
        return 0;

    // fils modifie a la meme taille que le pere
    if (child->height + 1 == father->height)
    {
        return 0;
    }
    else
    {
        // mise a jour de la hauteur de l'arbre
        father->height = child->height + 1;
        update_height(father->father, father);
        return 1;
    }
}

void add_child(CellTree *father, CellTree *child)
{
    // Cas de base : le pere n'a pas de fils
    if (father->firstChild == NULL)
    {
        father->firstChild = child;
        child->father = father;
    }
    else // sinon
    {
        // ajoute le fils comme le dernier frere du 1er fils du pere
        CellTree *c = father->firstChild;
        while (c->nextBro != NULL)
        {
            c = c->nextBro;
        }
        c->nextBro = child;
        child->father = father;
    }
    // mis a jour de la taille
    update_height(father, child);
}

void print_tree(CellTree *tree)
{
    // si null pas daffichage
    if (tree == NULL)
        return;

    // affichage de la hauteur de l'arbre et de la valeur hachee
    printf("%d %s\n", tree->height, tree->block->hash);

    // parcours de l'arbre
    print_tree(tree->nextBro);
    print_tree(tree->firstChild);
}

void delete_node(CellTree *node)
{
    // supprime le block
    delete_block(node->block);
    free(node);
}

void delete_CellTree(CellTree *tree)
{
    // arbre vide
    if (tree == NULL)
        return;

    // parcours de l'arbre
    delete_CellTree(tree->firstChild);
    delete_CellTree(tree->nextBro);

    // supprime le noeud
    delete_node(tree);
}

CellTree *highest_child(CellTree *cell)
{
    // arbre vide
    if (cell == NULL)
        return NULL;

    CellTree *fils = cell->firstChild;
    CellTree *hc = fils;

    // pas de fils
    if (fils == NULL)
    {
        return NULL;
    }

    // parcours de tous les fils
    while (fils != NULL)
    {
        // on a trouve un fils avec une hauteur superieur
        if (hc->height < fils->height)
        {
            hc = fils;
        }

        fils = fils->nextBro;
    }

    return hc;
}

CellTree *last_node(CellTree *tree)
{
    // arbre vide
    if (tree == NULL)
        return NULL;

    // feuille
    if (tree->firstChild == NULL)
        return tree;

    // le fils qui a la plus grand hauteur
    CellTree *ln = highest_child(tree);

    // parcours des fils qui a la plus grande hauteur jusqua arrivé a une feuille
    while (ln->height != 0)
    {
        ln = highest_child(ln);
    }

    // parcours de ses freres jusqua arrivé au dernier frere
    while (ln->nextBro != NULL)
    {
        ln = ln->nextBro;
    }

    return ln;
}

void fusion_LDP(CellProtected **l1, CellProtected *l2)
{
    if (l2 == NULL)
        return;

    CellProtected *l2t = l2;

    while (l2t != NULL)
    {
        // ajout de cellule dans la liste
        ajout_tete_cell_protected(l1, l2t->data);
        l2t = l2t->next;
    }
}

CellProtected *decl_longue_chaine(CellTree **tree)
{
    if (*tree == NULL)
        return NULL;

    CellTree *fils = highest_child(*tree);

    // fusionne toutes les declarations en parcourant la plus longue chaine
    fusion_LDP(&((*tree)->block->votes), decl_longue_chaine(&fils));

    return ((*tree)->block->votes);
}

void delete_author(CellTree *tree)
{

    if (tree == NULL)
        return;
    delete_author(tree->firstChild);
    delete_author(tree->nextBro);
    free(tree->block->author);
}

void delete_data_decl_long(CellTree *tree)
{

    if (tree == NULL)
        return;

    delete_data_decl_long(tree->firstChild);
    delete_data_decl_long(tree->nextBro);
    CellProtected *votes = tree->block->votes;
    while (votes != NULL)
    {
        if (votes->data != NULL && highest_child(tree->father) != tree)
        {
            free_Protected(votes->data);
            votes->data = NULL;
        }

        votes = votes->next;
    }
}

void delete_data(CellTree *tree)
{

    if (tree == NULL)
        return;

    delete_data(tree->firstChild);
    delete_data(tree->nextBro);
    CellProtected *votes = tree->block->votes;
    while (votes != NULL)
    {
        if (votes->data != NULL)
        {
            free_Protected(votes->data);
            votes->data = NULL;
        }

        votes = votes->next;
    }
}
