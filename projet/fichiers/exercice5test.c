#include "exercice5.h"

int main()
{
    srand(time(NULL));
    generate_random_data(10, 2);

    printf("\nTEST : lecture et affichage des cles et des declarations\n");
    printf("\npour 10 citoyens et 2 candidats\n");

    // TEST : affichage
    //  Affichage des cles publique du fichiers 'keys.txt'
    printf("lecture du fichier : keys.txt\n");
    CellKey *ck = read_public_keys("./data/keys.txt");
    printf("Affichage des cles : \n");
    printf("LCK : \n");
    print_list_keys(ck);
    delete_list_keys(ck);

    // Affichage des declarations du fichiers 'declarations.txt'
    printf("lecture du fichier : declarations.txt\n");
    CellProtected *cp = read_protected("./data/declarations.txt");
    printf("Affichage des cles : \n");
    printf("LCP : \n");
    print_list_protected(cp);
    delete_list_protected(&cp);

    return 0;
}
