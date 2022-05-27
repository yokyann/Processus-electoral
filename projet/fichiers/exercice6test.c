#include "exercice6.h"

int main()
{
srand(time(NULL));

    //________TEST : vérification de la fonction qui verifie les declarations_______*/
    // ouverture et allocation

    printf("\nTEST : verification de d'une liste de fausse declarations\n");

    CellProtected *cp = read_protected("./test/fakedeclarations.txt");
    CellProtected *cp2 = read_protected("./test/fakedeclarations2.txt");
    printf("\ndeclarations du fichier : fakedeclarations.txt (seulement 1 correct) \n\n");

    // Affichage des declaration du fichier
    printf("LCP : \n");
    print_list_protected(cp);

    // verification des declaration et suppression des fausses declarations
    verify_cell_protected(&cp);

    // Affichage apres verification et suppression des fausses declarations
    printf("\nLCP verifiee : \n");
    print_list_protected(cp);

    printf("\ndeclarations du fichier : fakedeclarations2.txt (tous fausses) \n\n");

    // Affichage des declaration du fichier     
    printf("LCP : \n");
    print_list_protected(cp2);

    // verification des declaration et suppression des fausses declarations
    verify_cell_protected(&cp2);

    // Affichage apres verification et suppression des fausses declarations
    printf("\nLCP verifiee : \n");
    print_list_protected(cp2);

    // desallocation et fermeture de fichier
    delete_list_protected(&cp2);
    delete_list_protected(&cp);


    //_________TEST : election et gagnant____________
    // initialisation des candidats/citoyens/declarations

    printf("\nTEST : simulation d'un election avec une base centralisee\n");
    printf("\nDebut de l'election avec 500 citoyens et 5 candidats\n");

    // generation des donnees
    int nv = 500;
    int nc = 5;
    generate_random_data(nv, nc);

    CellKey *candidats = read_public_keys("./data/candidates.txt");
    CellKey *citoyens = read_public_keys("./data/keys.txt");
    CellProtected *decl = read_protected("./data/declarations.txt");
    printf("Fin de l'election\n");

    // election a la recherche du gagnant
    Key *key = compute_winner(decl, candidats, citoyens, nc, nv);
    char *winner = key_to_str(key);
    printf("\nGagnant de l'election : %s\n", winner);

    // desallocation
    free(winner);
    delete_list_keys(candidats);
    delete_list_keys(citoyens);
    delete_list_protected(&decl);

    return 0;
}
