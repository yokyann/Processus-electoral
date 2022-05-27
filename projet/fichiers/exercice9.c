#include "exercice9.h"

void submit_vote(Protected *p)
{
    FILE *f = fopen("./Pending_votes.txt", "a");

    // ecriture de la declaration dans le fichier
    char *vote = protected_to_str(p);
    fprintf(f, "%s\n", vote);

    free(vote);
    fclose(f);
}

void create_block(CellTree **tree, Key *author, int d)
{

    // dernier noeud de l'arbre
    CellTree *last = last_node(*tree);

    Block *b = malloc(sizeof(Block));
    b->author = author;
    // liste des declarations des votes : "Pending_votes.txt"
    b->votes = read_protected("./Pending_votes.txt");
    b->hash = NULL;

    // si on a un dernier noeud
    if (last)
    {
        // valeur hache precedent est celui du de la valeur hache du dernier noeud
        b->previous_hash = strdup(last->block->hash);
    }
    else
    {
        b->previous_hash = NULL;
    }
    b->nonce = 0;

    // On valide la preuve de travail
    compute_proof_of_work(b, d);

    // supprime le fichier
    remove("./Pending_votes.txt");

    // ecriture du block dans : "Pending_block"
    ecrire_fichier_block("./Pending_block", b);

    // On crée le noeud du bloc
    CellTree *node = create_node(b);

    // On l'ajoute dans l'arbre
    if (last == NULL)
    {
        // s'il n'y avait pas de dernier noeud (pas de racine)
        // le noeud de notre block devient la racine
        *tree = node;
    }
    else
    {
        // Sinon c'est le fils du dernier noeud
        add_child(last, node);
    }
}

void add_block(int d, char *name)
{
    Block *b = lecture_fichier_block("./Pending_block");

    // Si verifie
    if (verify_block(b, d) == 1)
    {
        // nom du fichier avec le repertoire
        char *filename = malloc(sizeof(char) * (strlen("./Blockchain/") + strlen(name) + 1));
        sprintf(filename, "./Blockchain/%s", name);

        // ecriture du block dans le fichier
        ecrire_fichier_block(filename, b);
        free(filename);
    }

    // supprime le fichier
    remove("./Pending_block");

    // desallocation
    CellTree *tmp = create_node(b);
    delete_data(tmp);
    delete_author(tmp);
    delete_node(tmp);
}

CellTree *read_tree()
{
    // ouverture du repertoire
    DIR *rep = opendir("./Blockchain/");
    if (rep != NULL)
    {
        // nombre de fichiers
        int size = 0;

        struct dirent *dir;
        while ((dir = readdir(rep)) != NULL)
        {
            // si cest un fichier
            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                size++;
            }
        }

        rewinddir(rep);

        CellTree **T = malloc(sizeof(CellTree *) * (size));
        int ind = 0;
        while ((dir = readdir(rep)) != NULL)
        {

            if (strcmp(dir->d_name, ".") != 0 && strcmp(dir->d_name, "..") != 0)
            {
                // nom du fichier avec repertoire
                char *filename = malloc(sizeof(char) * (strlen("./Blockchain/") + strlen(dir->d_name) + 3));
                sprintf(filename, "./Blockchain/%s", dir->d_name);

                // lecture du fichier
                Block *b = lecture_fichier_block(filename);


                // creation du noeud dans T
                T[ind] = create_node(b);
                ind++;

                free(filename);
            }
        }

        closedir(rep);

        // parcours de T
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                // si le block il a une valeur hachee precedente
                if ((T[j])->block->previous_hash != NULL)
                {
                    // la valeur hache precedente T[j] et valeur hache T[i] dans le tableau correpond
                    if (strcmp((T[i])->block->hash, (T[j])->block->previous_hash) == 0)
                    {
                        // T[j] devient le fils de T[j]
                        add_child(T[i], T[j]);
                    }
                }
            }
        }

        // parcours T
        for (int i = 0; i < size; i++)
        {
            // si on a un noeud qui n'a pas pere
            if (T[i]->father == NULL)
            {
                // retourne la racine
                CellTree *racine = T[i];
                free(T);
                return racine;
            }
        }
        free(T);
    }

    return NULL;
}

Key *compute_winner_BT(CellTree *tree, CellKey *candidates, CellKey *voters, int sizeC, int sizeV)
{
    CellProtected *decl = decl_longue_chaine(&tree);
    verify_cell_protected(&decl);
    Key *winner = compute_winner(decl, candidates, voters, sizeC, sizeV);
    return winner;
}
