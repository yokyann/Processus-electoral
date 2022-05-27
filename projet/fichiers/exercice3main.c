#include "exercice3.h"

// fonction de TEST
int main(void)
{
    srand(time(NULL));

    printf("\nTEST : validation de la declaration, et des conversions\n\n");

    // Testing Init Keys
    Key *pKey = malloc(sizeof(Key));
    Key *sKey = malloc(sizeof(Key));
    init_pair_keys(pKey, sKey, 3, 7);
    printf("pKey: %lx, %lx\n", pKey->val, pKey->n);
    printf("sKey: %lx, %lx\n", sKey->val, sKey->n);

    // Testing Key Serialization
    char *chaine = key_to_str(pKey);
    printf("key to str: %s\n", chaine);
    Key *k = str_to_key(chaine);
    printf("str to key: %lx, %lx\n", k->val, k->n);

    // Testing signature
    // Candidate keys:
    Key *pKeyC = malloc(sizeof(Key));
    Key *sKeyC = malloc(sizeof(Key));
    init_pair_keys(pKeyC, sKeyC, 3, 7);
    // Declaration:
    char *mess = key_to_str(pKeyC);

    char *tmp1 = key_to_str(pKey), *tmp2;
    printf("%s vote pour %s \n", tmp1, mess);
    free(tmp1);

    Signature *sgn = sign(mess, sKey);
    printf("signature : ");
    print_long_vector(sgn->content, sgn->size);

    free(chaine);

    chaine = signature_to_str(sgn);
    printf("signature to str: %s\n", chaine);

    free(sgn->content);
    free(sgn);

    sgn = str_to_signature(chaine);
    printf("str to signature: ");
    print_long_vector(sgn->content, sgn->size);
    free(chaine);

    free(k);

    // Testing protected:
    Protected *pr = init_protected(pKey, mess, sgn);

    // Verification:
    if (verify(pr))
    {
        printf("Signature valide \n");
    }
    else
    {
        printf("Signature non valide \n");
    }

    chaine = protected_to_str(pr);
    printf("protected to str : %s\n", chaine);

    tmp1 = key_to_str(pr->pKey);
    tmp2 = signature_to_str(pr->sgn);

    free(pr);

    pr = str_to_protected(chaine);
    printf("str to protected : %s %s %s\n", tmp1, pr->mess, tmp2);

    // desallocation de tout

    // chaine de caractere
    free(tmp1);
    free(tmp2);
    free(chaine);
    free(mess);

    // Protected
    free(pr->pKey);
    free(pr->sgn->content);
    free(pr->sgn);
    free(pr->mess);
    free(pr);

    // signature
    free(sgn->content);
    free(sgn);
    free(pKey);
    free(sKey);
    free(pKeyC);
    free(sKeyC);

    return 0;
}
