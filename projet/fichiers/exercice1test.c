#include "exercice1.h"

void affichage()
{
    printf("\nTEST : si le nombre est premier\n");
    printf("Choisissez un nombre :\n");
    printf("-1 pour quitter\n");
}

int main(int argc, char **argv)
{
    srand(time(NULL));
    int choix = 0;
    // Affichage en temps de la fonction is_prime_naive pour un nombre choisi
    while (1)
    {
        affichage();
        scanf(" %d", &choix);
        if (choix == -1)
        {
            break;
        }

        is_prime_naive_temps(choix);

        if (is_prime_naive(choix))
        {
            printf("is_prime_naive(%d) est premier\n", choix);
        }
        else
        {
            printf("is_prime_naive(%d) n'est pas premier\n", choix);
        }

        if (is_prime_miller(choix, 1))
        {
            printf("is_prime_miller(%d,1) est premier pour 1 test\n", choix);
        }
        else
        {
            printf("is_prime_miller(%d,1) n'est pas premier pour 1 test\n", choix);
        }

        if (is_prime_miller(choix, 200))
        {
            printf("is_prime_miller(%d,200) est premier pour 200 test\n", choix);
        }
        else
        {
            printf("is_prime_miller(%d,200) n'est pas premier pour 200 test\n", choix);
        }
    }

    // donne le temps des 2 algorithme dans un fichier
    modpow_calcul("./courbetemps/modpow_calcul.txt");

    printf("\n52^7 mod 7 naive:%ld, non naive:%d\n", modpow_naive(52, 7, 7), modpow(52, 7, 7));
    printf("nombre premier aleatoire de taille 3 a 7 avec 1 test : %ld \n", random_prime_number(3, 7, 1));
    printf("nombre premier aleatoire de taille 3 a 7 avec 120 test : %ld \n", random_prime_number(3, 7, 120));

    return 0;
}
