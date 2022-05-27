#include "exercice2.h"

// Fonction de TEST de generation de cle et cryptage et decryptage
int main()
{
    srand(time(NULL));

    printf("\nTEST : cryptage et decryptage de cles publiques et secretes generes \n\n");

    // Generation de cle :
    long p = random_prime_number(3, 7, 5000);
    long q = random_prime_number(3, 7, 5000);
    while (p == q)
    {
        q = random_prime_number(3, 7, 5000);
    }
    long n, s, u;
    generate_keys_values(p, q, &n, &s, &u);
    // Pour avoir des cles positives :
    if (u < 0)
    {
        long t = (p - 1) * (q - 1);
        u = u + t; // on aura toujours s*u mod t = 1
    }

    // Afichage des cles en hexadecimal
    printf("clepublique = (%lx,%lx)\n", s, n);
    printf("cleprivee = (%lx,%lx)\n", u, n);

    // Chiffrement:
    char mess[50] = "Les fonctions marchent.";
    int len = strlen(mess);
    long *crypted = encrypt(mess, s, n);

    printf("Initial message: %s\n", mess);
    printf("Encoded representation : \n");
    print_long_vector(crypted, len);

    // Dechiffrement
    char *decoded = decrypt(crypted, len, u, n);
    printf("Decoded : %s\n", decoded);

    free(decoded);
    free(crypted);

    return 0;
}
