#include "exercice9.h"

int main()
{
    srand(time(NULL));

    printf("\nTEST : simulation d'un election avec une base decentralise\n");

    // Generation de donnee
    int sizeC = 5;
    int sizeV = 1000;
    generate_random_data(sizeV, sizeC);

    CellProtected *votes = read_protected("./data/declarations.txt");
    CellKey *candidates = read_public_keys("./data/candidates.txt");
    CellKey *voters = read_public_keys("./data/keys.txt");
    CellTree *tmp = NULL;

    int d = 0;
    int nbvotes = 0;
    CellProtected *decl = votes;

    printf("Soumission des votes ...\n");
    // Parcours de tous les declarations
    while (decl != NULL)
    {
        // soumission des votes dans "Pending_votes.txt"
        nbvotes++;
        submit_vote(decl->data);

        // tous les 10 votes creation dun block
        if (nbvotes % 10 == 0)
        {
            // nom du fichier qui sera dans la blockchain
            char *filename = malloc(sizeof(char) * 30);
            sprintf(filename, "Block%d.txt", (int)nbvotes / 10);

            printf("Creation d'un block de 10 votes ...\n");

            // creation du block "Pending_block" et de son ajout dans la blockchain
            create_block(&tmp, decl->data->pKey, d);
            add_block(d, filename);

            printf("Block ajouté dans ../Blockchain/%s !\n", filename);

            free(filename);
        }
        decl = decl->next;
    }

    printf("Fin des elections\n");
    printf("Debut des calculs ...\n");

    // Preparation de l'election (lecture de la blockchain)
    CellTree *tree = read_tree();
    // print_tree(tree);

    // Election : calcul des votes
    Key *winner = compute_winner_BT(tree, candidates, voters, sizeC, sizeV);
    char *str_winner = key_to_str(winner);
    printf("\nGagnant de l'election : %s\n", str_winner);

    // desallocation
    free(str_winner);

    delete_data(tmp);
    delete_CellTree(tmp);

    delete_data_decl_long(tree);
    delete_author(tree);
    delete_CellTree(tree);

    delete_list_keys(candidates);
    delete_list_keys(voters);
    delete_list_protected(&votes);

    return 0;
}
