#include "exercice4.h"

void ecrire_citoyen_fichier(FILE *f, Key *pKey, Key *sKey)
{
    char *strpKey = key_to_str(pKey);
    char *strsKey = key_to_str(sKey);
    fprintf(f, "%s\n%s\n", strpKey, strsKey);
    free(strpKey);
    free(strsKey);
}

void ecrire_candidat_fichier(FILE *f, Key *pKey)
{
    char *strpKey = key_to_str(pKey);
    fprintf(f, "%s\n", strpKey);
    free(strpKey);
}

void ecrire_declaration_fichier(FILE *f, Protected *pr)
{
    char *strpr = protected_to_str(pr);
    fprintf(f, "%s\n", strpr);
    free(strpr);
}

void generate_random_data(int nv, int nc)
{
    // ouverture du flux des fichiers
    FILE *fkey = fopen("./data/keys.txt", "w");
    FILE *fcand = fopen("./data/candidates.txt", "w");
    FILE *fdec = fopen("./data/declarations.txt", "w");

    // allocations des citoyens, candidats et des votes
    Key **citoyens = malloc(sizeof(Key *) * 2 * nv);
    Key **candidats = malloc(sizeof(Key *) * nc);
    Protected **vote = malloc(sizeof(Protected *) * nv);

    printf("Generation aleatoire de %d cles publiques et prives dans 'keys.txt' ...\n", nv);

    // genere nv cle publique/secrete
    for (int i = 0; i < 2 * nv; i += 2)
    {
        Key *pKey = malloc(sizeof(Key));
        Key *sKey = malloc(sizeof(Key));

        init_pair_keys(pKey, sKey, 3, 7);
        // indice pair cle publique
        citoyens[i] = pKey;
        // indice impair cle secrete
        citoyens[i + 1] = sKey;
        ecrire_citoyen_fichier(fkey, pKey, sKey);
    }

    printf("Selection de %d candidats parmi les citoyens et ajoute dans 'candidates.txt' ...\n", nc);

    // selectionne nc citoyens qui seront candidats
    for (int i = 0; i < nc; i++)
    {
        candidats[i] = NULL;
        // On boucle jusqua avoir trouve un candidat
        while (candidats[i] == NULL)
        {

            long rd = 1;

            // on verifie que que c'est un nombre pair (pour pas tomber sur la cle privee) dans le tableau citoyens
            while (rd % 2 != 0)
            {
                rd = rand_long(0, 2 * nv - 1);
            }

            // on verifie que le citoyen choisi aleatoirement n'est pas deja un candidat
            int j = 0;
            while (j < i)
            {

                // candidat = citoyen, on arrete la boucle
                if (candidats[j] == citoyens[rd])
                {
                    break;
                }
                j++;
            }

            // si on a parcouru tout le tableau candidats et que le citoyen nest pas dedans
            if (j == i)
            {
                candidats[i] = citoyens[rd];
                ecrire_candidat_fichier(fcand, candidats[i]);
            }

            // sinon on recherche a nouveau un candidat
        }
    }

    printf("Generation de %d declarations de votes des citoyens dans 'declarations.txt' ...\n", nv);

    // genere des declarations de vote pour tous les citoyens
    for (int i = 0; i < nv; i++)
    {
        // Creation de la signature
        long rd = rand_long(0, nc - 1);
        char *pKey = key_to_str(candidats[rd]); // cle publique du candidat
        Signature *sgn = sign(pKey, citoyens[i * 2 + 1]);

        // vote du citoyen
        vote[i] = init_protected(citoyens[i * 2], pKey, sgn);

        // si vote valide
        if (verify(vote[i]))
        {

            ecrire_declaration_fichier(fdec, vote[i]);
        }
    }

    printf("Generation des donnees termines !\n");

    // desallocation de tout les elements alloues
    for (int i = 0; i < nv; i++)
    {
        free_Key(citoyens[i * 2 + 1]);
        free_Protected(vote[i]);
    }

    free(candidats);
    free(citoyens);
    free(vote);

    // fermeture des fichiers
    fclose(fkey);
    fclose(fcand);
    fclose(fdec);
}
