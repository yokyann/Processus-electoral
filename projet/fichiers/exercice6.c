#include "exercice6.h"

void verify_cell_protected(CellProtected **c)
{

    CellProtected *prec = NULL;
    CellProtected *suiv;
    CellProtected *current = *c;

    // parcours de la liste chainee
    while (current != NULL)
    {
        suiv = current->next;

        // si declaration non valide
        if (verify(current->data) == 0)
        {
            // suppression de l'element
            delete_cell_protected(current);

            // si cetait le dernier element de la liste
            if (suiv == NULL)
            {
                // et etait le premier element de la liste
                if (prec == NULL)
                {
                    // liste devient vide, car declaration non valide et unique element
                    *c = NULL;
                }
                else // sinon contient plusieurs elements
                {
                    // element suivant vide
                    prec->next = NULL;
                }

                break;
            }

            // si l'element supprime etait le premier element de la liste
            if (prec == NULL)
            {
                // on change la tete de liste et on passe au suivant
                *c = suiv;
                current = suiv;
                continue;
            }

            // relie la liste chainee avec les elements suivant
            current = suiv;
            prec->next = suiv;
            continue;
        }

        prec = current;
        current = suiv;
    }
}

HashCell *create_hashcell(Key *key)
{
    HashCell *hc = malloc(sizeof(HashCell));
    hc->key = key;
    hc->val = 0;
    return hc;
}

int hash_function(Key *key, int size)
{
    // s * u % size
    return (key->val * key->n) % size;
}

int find_position(HashTable *t, Key *key)
{
    // position de la cle dans la table
    int pos = hash_function(key, t->size);
    int el = 0;

    // parcours de la table de hachage
    // sort des qu'on parcourt tous les elements
    // ou des qu'il y a un espace libre (NULL)
    // ou on l'a trouve
    while (t->tab[pos]->key != NULL && t->tab[pos]->key->val != key->val && t->tab[pos]->key->n != key->n && el < t->size)
    {
        el++;
        pos++;
        // si l'indice est size, retour a 0
        if (pos == t->size)
        {
            pos = 0;
            continue;
        }
    }
    return pos;
}

HashTable *create_hashtable(CellKey *keys, int size)
{
    // allocation
    HashTable *h = malloc(sizeof(HashTable));
    h->tab = malloc(sizeof(CellKey *) * size);
    h->size = size;

    // initialise a null les element de la table
    for (int i = 0; i < size; i++)
    {
        h->tab[i] = create_hashcell(NULL);
    }

    // parcours de la liste de cle
    while (keys != NULL)
    {
        // position ou devrait etre la cle
        int pos = find_position(h, keys->data);

        // on insere dans la table
        h->tab[pos]->key = keys->data;

        keys = keys->next;
    }
    return h;
}

void delete_hashtable(HashTable *t)
{

    for (int i = 0; i < t->size; i++)
    {
        // supprime la cellule
        free(t->tab[i]);
    }

    free(t->tab);
    free(t);
}

Key *compute_winner(CellProtected *decl, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{

    // la table de candidat
    HashTable *Hc = create_hashtable(candidates, sizeC);

    // la table des votants
    HashTable *Hv = create_hashtable(voters, sizeV);

    // les declarations sont suppose verifie

    printf("Comptage des declarations de votes ...\n");

    // parcours des declarations de votes
    while (decl != NULL)
    {

        // cle du candidat
        Key *mess = str_to_key(decl->data->mess);
        int vote = find_position(Hc, mess);

        // cle du citoyen
        int pos = find_position(Hv, decl->data->pKey);

        // si est dans la table de candidat
        if (est_dans_table(Hc, mess) == 1)
        {
            //si notre votant n'est pas un candidat
            if (est_dans_table(Hc, decl->data->pKey) == 0)
            {
                // si le votant na pas voté encore
                if (Hv->tab[pos]->val == 0)
                {
                    Hv->tab[pos]->val = 1;

                    //+1 vote pour le candidat
                    Hc->tab[vote]->val++;
                }
            }
        }
        free_Key(mess);
        decl = decl->next;
    }

    printf("\nAffichage de tous les candidats et de leur nombre de vote (en %%) : \n");

    int ind_max = 0;
    Key *Winner = Hc->tab[0]->key;

    // parcours de la table
    for (int i = 0; i < Hc->size; i++)
    {
        // si le candidat a un plus grand nombre de vote
        if (Hc->tab[i]->val > Hc->tab[ind_max]->val)
        {
            ind_max = i;

            //+ grand vote actuel
            Winner = Hc->tab[ind_max]->key;
        }
        char *strc = key_to_str(Hc->tab[i]->key);
        printf("%s : %.2f %%\n", strc, (float)(Hc->tab[i]->val * 100.0) / sizeV);

        free(strc);
    }

    // desallocation des table de hachage
    delete_hashtable(Hc);
    delete_hashtable(Hv);

    // retourne le gagnant;
    return Winner;
}

void ajout_hashtable(HashTable *h, Key *key)
{
    if (h == NULL)
        return;

    // insere la cle dans la table
    int pos = find_position(h, key);
    h->tab[pos]->key = key;
}

int est_dans_table(HashTable *t, Key *k)
{
    // si la cle existe bien dans la table
    int pos = find_position(t, k);
    if (t->tab[pos]->key->n == k->n && t->tab[pos]->key->val == k->val)
    {
        return 1;
    }
    else
    {
        return 0;
    }
}

Key *le_plus_vote(HashTable *h)
{
    // initialisation du gagnant (au premier candidat de la table)
    HashCell *Winner = h->tab[0];

    // parcours de la table
    for (int i = 1; i < h->size; i++)
    {
        // si le candidat a un plus grand nombre de vote
        if (h->tab[i]->val > Winner->val)
        {
            //+ grand vote actuel
            Winner = h->tab[i];
        }
    }
    return Winner->key;
}
