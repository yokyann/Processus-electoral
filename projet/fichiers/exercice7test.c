#include"exercice7.h"
#include <unistd.h>

int main()
{

    srand(time(NULL));

    //________ TEST : Fonction de hachage ___________
    printf("\nTEST : SHA256 fonction");
    const char * s = "Rosetta code";
    unsigned char * sss = SHA256(s, strlen (s), 0) ;
    int i ;
    printf("\"Rosetta code\" encoded avec le code fourni : ");
    for(i = 0; i < SHA256_DIGEST_LENGTH ; i++)
    printf("%02x", sss[i]);
    putchar('\n');

    printf("\nAvec la fonction str_to_SHA256 : \n");
    char *sr="Rosetta code";
    unsigned char * ssr = str_to_SHA256(sr);
    printf("Decoded : %s\nEncoded : %s \n\n",sr,ssr);

    //________ TEST : Block valide ___________
    // initialisation d'un block
    printf("\nTEST : initialisation d'un block valide\n");
    generate_random_data(1, 1);

    Block *b = malloc(sizeof(Block));
    b->author = malloc(sizeof(Key));
    init_key(b->author, 2, 13);
    b->previous_hash = NULL;
    b->nonce = 0;
    b->votes = read_protected("./data/declarations.txt");
    b->hash = NULL;

    int d = 1;

    // initialisation de nonce pour le block
    compute_proof_of_work(b, d);

    char *aff = block_to_str(b);
    printf("\nblock :%s\n", aff);
    printf("valeur hache : %s\n",b->hash);

    // verifie que le block est bien valide
    if (verify_block(b, d))
    {
        printf("\nblock valide\n");
    }
    else
    {
        printf("\nblock invalide\n");
    }

    //______ TEST : ecriture lecture fichier ______

    printf("\nTEST : ecriture et lecture d'un fichier contenant un block\n");
    ecrire_fichier_block("./test/block_test.txt", b);
    Block *b2 = lecture_fichier_block("./test/block_test.txt");

    int ok=1;

    char *k2 = key_to_str(b2->author);
    char *k1 = key_to_str(b->author);

    // si auteur,valeur hachee, valeur precedemment hachee, ou la preuve n'est pas la meme
    if (strcmp(k2, k1) != 0 || strcmp(b->hash, b2->hash) != 0 || b->nonce != b2->nonce)
    {
        // Affichage erreur
        printf("erreur lecture/ecriture fichier, Affichage : %s %s %s %d\n", k2, b2->hash, b2->previous_hash, b->nonce);
        ok=0;
    }
    else
    {
        CellProtected *c1 = b->votes;
        CellProtected *c2 = b2->votes;

        // parcours des declarations de votes du block 1 et 2
        while (c1 != NULL || c2 != NULL)
        {
            char *pr1 = protected_to_str(c1->data);
            char *pr2 = protected_to_str(c2->data);
            // si l'une des declarations n'est pas la meme affiche erreur
            if (strcmp(pr1, pr2) != 0)
            {
                printf("erreur lecture/ecriture fichier, Affichage declaration : %s %s\n", pr1, pr2);
                ok=0;
                break;
            }
            c1 = c1->next;
            c2 = c2->next;

            free(pr1);
            free(pr2);
        }
    }

    if(ok){
        printf("\nl'ecriture du block et la lecture du fichier contenant ce block sont egaux, donc pas d'erreur.\n");
    }

    printf("\n\nContenu du fichier block_test.txt :\n\n");
    int status = system("cat ./test/block_test.txt");

    //_______ Tracage de la courbe temps ________
    //ecrire_temps_fichier("./courbetemps/proof_algo.txt",b,4);

    // Desallocation
    free(ssr);
    free(aff);
    free(k1);
    free(k2);
    delete_list_protected(&(b2->votes));
    free(b2->author);
    delete_block(b2);

    delete_list_protected(&(b->votes));
    free(b->author);
    delete_block(b);

    return 0;
}
