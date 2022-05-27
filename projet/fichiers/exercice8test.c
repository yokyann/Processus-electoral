#include "exercice8.h"

int main()
{

    srand(time(NULL));

    printf("\nTEST : affichage d'un arbre de block\n");
    int d = 2;
    Block *b4 = malloc(sizeof(Block));
    b4->author = malloc(sizeof(Key));
    init_key(b4->author, 5, 14);
    b4->previous_hash = NULL;
    b4->nonce = 0;
    b4->votes = read_protected("./test/declarations4.txt");
    b4->hash = NULL;
    compute_proof_of_work(b4, d);
    // ecrire_fichier_block("block_test.txt4", b4);

    Block *b5 = malloc(sizeof(Block));
    b5->author = malloc(sizeof(Key));
    init_key(b5->author, 13, 13);
    b5->previous_hash = NULL;
    b5->nonce = 0;
    b5->votes = read_protected("./test/declarations5.txt");
    b5->hash = NULL;
    compute_proof_of_work(b5, d);
    // ecrire_fichier_block("block_test5.txt", b5);

    Block *b6 = malloc(sizeof(Block));
    b6->author = malloc(sizeof(Key));
    init_key(b6->author, 13, 5);
    b6->previous_hash = NULL;
    b6->nonce = 0;
    b6->votes = read_protected("./test/declarations6.txt");
    b6->hash = NULL;
    compute_proof_of_work(b6, d);
    // ecrire_fichier_block("block_test5.txt", b6);

    // Creation et initialisation de 6 block
    Block *b0 = lecture_fichier_block("./test/block_test.txt");
    Block *b1 = lecture_fichier_block("./test/block_test1.txt");
    Block *b2 = lecture_fichier_block("./test/block_test2.txt");
    Block *b3 = lecture_fichier_block("./test/block_test3.txt");

    // creation de l'arbre et de ses fils
    CellTree *ct = create_node(b0);
    CellTree *bb = create_node(b1);
    add_child(ct, create_node(b2));
    add_child(ct, bb);
    CellTree *bbt = create_node(b4);
    add_child(bbt, create_node(b3));
    add_child(bbt, create_node(b5));
    add_child(bbt, create_node(b6));
    add_child(bb, bbt);

    // Affichage
    printf("\nAffichage de l'arbre avec ses 6 fils : \n");
    print_tree(ct);

    printf("\nAffichage de l'arbre du plus grand fils de la racine :\n");
    print_tree(highest_child(ct));

    printf("\nAffichage du dernier noeud :\n");
    print_tree(last_node(ct));

    // ____________TEST : Fusion____________
    printf("\n\n TEST : FUSION de listes de declarations");
    printf("\n Résultat souhaité : ");

    printf("\nb0 : ");
    print_list_protected(ct->block->votes);
    printf("\nb1 : ");
    print_list_protected(ct->firstChild->nextBro->block->votes);
    printf("\nb4 : ");
    print_list_protected(ct->firstChild->nextBro->firstChild->block->votes);
    printf("\nb3 : ");
    print_list_protected(ct->firstChild->nextBro->firstChild->firstChild->block->votes);

    printf("\n FUSION AVEC ALGO \n");
    CellProtected *fus = decl_longue_chaine(&ct);
    print_list_protected(fus);

    // desallocation
    delete_author(ct);
    delete_data_decl_long(ct);
    delete_CellTree(ct);

    return 0;
}
