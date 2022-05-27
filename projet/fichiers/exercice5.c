#include "exercice5.h"

CellKey *create_cell_key(Key *key)
{
    CellKey *c = malloc(sizeof(CellKey));
    c->data = key;
    c->next = NULL;
    return c;
}

void ajout_tete_cell_key(CellKey **c, Key *key)
{
    // key n'a pas de valeur, il se passe rien
    if (key == NULL)
        return;

    CellKey *tete = create_cell_key(key);
    tete->next = *c;

    // changement de l'en tete de la liste
    *c = tete;
}

CellKey *read_public_keys(char *nomfic)
{
    FILE *f = fopen(nomfic, "r");
    char ligne[100], *strkey;

    // valeur des cle trouve dans le fichier
    Key *key = NULL;
    Key *prec_key = NULL;

    // notre LCK
    CellKey *c = NULL;

    // lecture d'une ligne du fichier a chaque iteration
    while (fgets(ligne, 100, f) != NULL)
    {

        strkey = malloc(sizeof(char) * 100);

        // si la ligne contient bien une chaine de caractere
        if (sscanf(ligne, "%s\n", strkey) == 1)
        {
            // conversion de la chaine en cle
            key = str_to_key(strkey);

            // dans le cas du fichier 'keys.txt' qui contient des cle prives
            // on a un pointeur temporaire pour comparer
            if (prec_key == NULL)
            {
                ajout_tete_cell_key(&c, key);
                free(strkey);
                prec_key = key;

                // passe a literation suivante
                continue;
            }

            // si la cle a la meme valeur n que la cle ajoute precedemment
            if (prec_key->n == key->n)
            {
                // desalloue la cle cree a partir de la chaine
                free(key);
                free(strkey);

                // passe a literation suivante
                continue;
            }

            // ajout en tete de la cle dans LCK
            ajout_tete_cell_key(&c, key);
            prec_key = key;
        }
        free(strkey);
    }
    fclose(f);
    return c;
}

void print_list_keys(CellKey *LCK)
{
    char *key;
    printf("[\n");

    // parcours de la LCK (liste chainee de cles)
    while (LCK != NULL)
    {
        // affichage des cle
        key = key_to_str(LCK->data);
        printf("%s\n", key);

        free(key);
        LCK = LCK->next;
    }
    printf("]\n");
}

void delete_cell_key(CellKey *c)
{
    // la liste est vide
    if (c == NULL)
        return;

    // suppression du premier element
    free_Key(c->data);
    free(c);
    c = NULL;
}

void delete_list_keys(CellKey *LCK)
{
    // la liste est vide
    if (LCK == NULL)
        return;

    CellKey *temp = NULL;

    // parcours de la liste jusqua lavant dernier element
    while (LCK->next != NULL)
    {
        temp = LCK;
        LCK = LCK->next;

        // supprime lelement
        delete_cell_key(temp);
    }

    // supprime le dernier element
    delete_cell_key(LCK);
}

CellProtected *create_cell_protected(Protected *pr)
{
    CellProtected *c = malloc(sizeof(CellProtected));
    c->data = pr;
    c->next = NULL;
    return c;
}

void ajout_tete_cell_protected(CellProtected **c, Protected *pr)
{
    // si la declaration est vide
    if (pr == NULL)
        return;

    CellProtected *tete = create_cell_protected(pr);
    tete->next = *c;
    *c = tete;
}

CellProtected *read_protected(char *nomfic)
{
    FILE *f = fopen(nomfic, "r");
    char *ligne = malloc(sizeof(char) * 500);
    CellProtected *c = NULL;
    Protected *pr = NULL;
    char cle[30], mess[30], sgn[100];
    // lecture dune ligne a chaque tour de boucle
    while (fgets(ligne, 500, f) != NULL)
    {
        // conversion de la chaine en declaration de vote type 'Protected'
        if (sscanf(ligne, "%s %s %s\n", cle, mess, sgn) == 3)
        {
            pr = str_to_protected(ligne);
        }
        // Ajout en tete a la LCP
        ajout_tete_cell_protected(&c, pr);
    }

    free(ligne);
    fclose(f);
    return c;
}

void print_list_protected(CellProtected *LCP)
{
    printf("[\n");

    // parcours de la la liste de declaration
    while (LCP != NULL)
    {
        // affichage de la declaration
        char *pr = protected_to_str(LCP->data);
        printf("%s\n", pr);

        free(pr);
        LCP = LCP->next;
    }
    printf("]\n");
}

void delete_cell_protected(CellProtected *c)
{
    // la liste est vide
    if (c == NULL)
        return;

    // supprime lelement
    if (c->data != NULL)
        free_Protected(c->data);

    free(c);
}

void delete_list_protected(CellProtected **LCP)
{
    // la liste est vide
    if (*LCP == NULL)
        return;

    CellProtected *temp = NULL;

    // parcours de la liste
    while ((*LCP) != NULL)
    {
        temp = *LCP;
        (*LCP) = (*LCP)->next;

        // supprime element
        delete_cell_protected(temp);
    }

    // change l'en tete en NULL
    *LCP = NULL;
}
