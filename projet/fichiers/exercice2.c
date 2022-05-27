#include "exercice2.h"

long extended_gcd(long s, long t, long *u, long *v)
{
    if (s == 0)
    {
        *u = 0;
        *v = 1;
        return t;
    }

    long uPrim, vPrim;
    long gcd = extended_gcd(t % s, s, &uPrim, &vPrim);
    *u = vPrim - (t / s) * uPrim;
    *v = uPrim;

    return gcd;
}

void generate_keys_values(long p, long q, long *n, long *s, long *u)
{
    *n = p * q;
    long t = (p - 1) * (q - 1);
    long v;

    // boucle jusqua que s*u % t= 1 et le pgcd(s,t)=1
    do
    {
        // s : nombre aleatoire
        *s = rand_long(2, t - 1);
    } while (extended_gcd(*s, t, u, &v) != 1 || modpow((*s) * (*u), 1, t) != 1); // || *s == *u);
}

long *encrypt(char *chaine, long s, long n)
{
    long *crypt = malloc(strlen(chaine) * sizeof(long));
    int i = 0;
    // parcours de la chaine
    while (chaine[i] != '\0')
    {
        // c = m^s mod n, ou m est le caractere de 'chaine' en int
        crypt[i] = modpow((long)chaine[i], s, n);
        i++;
    }
    return crypt;
}

char *decrypt(long *crypted, int size, long u, long n)
{
    char *chaine = malloc(sizeof(char) * (size + 1));

    // parcours du tableau crypte
    for (int i = 0; i < size; i++)
    {
        // m = c^u mod n, ou c est un element du tableau
        chaine[i] = (char)modpow(crypted[i], u, n);
    }

    chaine[size] = '\0';

    return chaine;
}

void print_long_vector(long *result, int size)
{
    printf("Vector: [ ");
    for (int i = 0; i < size; i++)
    {
        printf("%lx\t", result[i]);
    }
    printf("]\n");
}
