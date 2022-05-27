#include "exercice7.h"

void ecrire_fichier_block(char *nomfic, Block *b)
{
    FILE *f = fopen(nomfic, "w");

    // ecriture de la premiere ligne : cle, valeur hachee, valeur prec hachee, preuve travail
    char *strkey = key_to_str(b->author);
    fprintf(f, "%s %s %s %d\n", strkey, b->hash, b->previous_hash, b->nonce);
    free(strkey);

    // parcours des declarations
    CellProtected *v = b->votes;
    while (v != NULL)
    {
        // ecriture de la declaration dans le fichier
        char *strpro = protected_to_str(v->data);
        fprintf(f, "%s\n", strpro);
        v = v->next;
        free(strpro);
    }

    fclose(f);
}

Block *lecture_fichier_block(char *nomfic)
{
    FILE *f = fopen(nomfic, "r");

    // allocation
    char ligne[256];
    char *author = malloc(sizeof(char) * 20);
    char *hash = malloc(sizeof(char) * 65);
    char *previous_hash = malloc(sizeof(char) * 65);
    int nonce;

    Block *b = malloc(sizeof(Block));

    // lecture de la premiere ligne
    if (fgets(ligne, 256, f) != NULL)
    {
        if (sscanf(ligne, "%s %s %s %d\n", author, hash, previous_hash, &nonce) == 4)
        {
            // initialisation du block
            b->votes = NULL;
            b->author = str_to_key(author);
            b->hash = hash;
            if (strcmp(previous_hash, "(null)") == 0)
            {
                b->previous_hash = NULL;
                free(previous_hash);
            }
            else
            {
                b->previous_hash = previous_hash;
            }
            b->nonce = nonce;
        }
    }

    CellProtected *tmp = NULL;
    // lecture des lignes de declarations
    while (fgets(ligne, 256, f) != NULL)
    {
        // conversion de la chaine en declaration de vote type 'Protected'
        Protected *pr = str_to_protected(ligne);
        // Ajout en tete a la LCP
        ajout_tete_cell_protected(&tmp, pr);
    }

    // remet dans l'ordre les declarations
    while (tmp != NULL)
    {
        CellProtected *suppr = tmp;
        ajout_tete_cell_protected(&(b->votes), tmp->data);
        tmp = tmp->next;
        free(suppr);
    }

    // desallocation
    free(author);
    fclose(f);
    return b;
}

char *block_to_str(Block *block)
{
    // Duplication de l'auteur
    char *strkey = key_to_str(block->author);
    char *str = strdup(strkey);
    free(strkey);

    // Concatatenation de hash_previous avec le saut de ligne
    if (block->previous_hash)
    {
        str = realloc(str, strlen(str) + strlen(block->previous_hash) + 2);
        strcat(str, "\n");
        strcat(str, block->previous_hash);
    }

    // Concatenation de votes avec le saut de livre
    CellProtected *LCP = block->votes;
    while (LCP)
    {
        char *strpr = protected_to_str(LCP->data);
        str = realloc(str, strlen(str) + strlen(strpr) + 2);
        strcat(str, "\n");
        strcat(str, strpr);
        LCP = LCP->next;
        free(strpr);
    }

    // Concatenation de nonce avec le saut de ligne
    // un int a au plus 10 chiffres
    str = realloc(str, strlen(str) + 10 + 2);
    char *strnonce = malloc(256);
    strcat(str, "\n");
    sprintf(strnonce, "%d", block->nonce);
    strcat(str, strnonce);

    free(strnonce);

    return str;
}

unsigned char *str_to_SHA256(char *s)
{
    unsigned char *str = SHA256(s, strlen(s), 0);
    unsigned char *sha = (char *)malloc(1 + 2 * SHA256_DIGEST_LENGTH * sizeof(unsigned char));

    // Remplir le tableau de 0
    memset(sha, 0, 1 + 2 * SHA256_DIGEST_LENGTH);

    for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        // chaine en hexadecimal;
        unsigned char *val = malloc(3);
        sprintf(val, "%02x", str[i]);

        // concatenation
        strcat(sha, val);
        free(val);
    }

    return sha;
}

void compute_proof_of_work(Block *B, int d)
{
    // initialisation
    int nonce = 0;
    int i = 0;
    char nb_d[d + 1];

    // creer un tableau chaine de caractere qui a d '0'
    for (int i = 0; i < d; i++)
    {
        nb_d[i] = '0';
    }
    nb_d[d] = '\0';

    // hashage du block
    char *str = block_to_str(B);
    B->hash = str_to_SHA256(str);
    free(str);

    // jusqua obtenir une valeur hachee qui commence par d zeros successifs
    while (strncmp(B->hash, nb_d, d * sizeof(char)) != 0)
    {
        // hash le block et initialise
        free(B->hash);
        str = block_to_str(B);
        B->hash = str_to_SHA256(str);

        // incrementation de nonce
        B->nonce++;
        free(str);
    }
}

int verify_block(Block *b, int d)
{
    int i = 0;
    // tant qu'il y a des zeros
    while (i < d)
    {
        // si on a trouve un caractere different de 0 parmi les d premier caractere
        if (b->hash[i] != '0')
        {
            return 0; // faux
        }
        i++;
    }
    // vrai
    return 1;
}

void ecrire_temps_fichier(char *nomfic, Block *b, int max)
{
    FILE *f = fopen(nomfic, "w");

    for (int d = 0; d <= max; d++)
    {
        free(b->hash);
        // temps mis par la fonction 'compute_proof_of_work'
        temps_proof_init = clock();
        compute_proof_of_work(b, d);
        temps_proof_final = clock();
        temps_proof = ((double)(temps_proof_final - temps_proof_init)) / CLOCKS_PER_SEC;

        // ecriture dans un fichier
        fprintf(f, "%d %f\n", d, temps_proof);
    }
    fclose(f);
}

void delete_block(Block *b)
{
    // desallocation des valeurs hachées
    if (b->hash != NULL)
        free(b->hash);
    if (b->previous_hash != NULL)
        free(b->previous_hash);

    // desallocation des cellules declarations de votes
    if (b->votes != NULL)
    {
        CellProtected *cp = b->votes;
        while (cp != NULL)
        {
            CellProtected *tmp = cp->next;
            if (cp != NULL)
                free(cp);
            cp = tmp;
        }
    }
    free(b);
}
