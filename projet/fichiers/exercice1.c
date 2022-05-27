#include "exercice1.h"

int is_prime_naive(long p)
{
    // p non compris entre 3 et +8
    if (p < 3)
    {
        return 0;
    }
    int i = 2;
    while (i < p)
    {
        // si p est divisible par i tel que i<p, alors p non premier
        if (p % i == 0)
        {
            return 0;
        }
        i++;
    }

    // sinon premier
    return 1;
}

// is_prime_naive affichage temps
void is_prime_naive_temps(int p)
{
    // temps calcul pour is_prime_naive
    temps_initial = clock();
    is_prime_naive(p);
    temps_final = clock();
    temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

    printf("p=%d temps=%.4f\n", p, temps_cpu);
}

long modpow_naive(long a, long m, long n)
{
    long am = 1;
    for (int i = 0; i < m; i++)
    {
        am = (am * a) % n;
    }
    return am;
}

int modpow(long a, long m, long n)
{
    // cas de base
    if (m == 0)
    {
        return 1;
    }

    // m est pair
    if (m % 2 == 0)
    {
        int b = modpow(a, m / 2, n);
        return (b * b) % n;
    }
    else // m est impair
    {
        int b = modpow(a, floor(m / 2), n);
        return (a * b * b) % n;
    }
}

// temps calcul modpow
void modpow_calcul(char *fichier)
{
    FILE *f = fopen(fichier, "w");

    for (int i = 1; i <= 5000; i++)
    {

        // temps pour modpow_naive
        temps_initial = clock();
        modpow_naive(2, i, 13);
        temps_final = clock();
        temps_cpu = ((double)(temps_final - temps_initial)) / CLOCKS_PER_SEC;

        // temps pour modpow
        temps_initial2 = clock();
        modpow(2, i, 13);
        temps_final2 = clock();
        temps_cpu2 = ((double)(temps_final2 - temps_initial2)) / CLOCKS_PER_SEC;

        fprintf(f, "%d %f %f\n", i, temps_cpu, temps_cpu2);
    }

    fclose(f);
}

int witness(long a, long b, long d, long p)
{
    long x = modpow(a, d, p);
    if (x == 1)
    {
        return 0;
    }
    for (long i = 0; i < b; i++)
    {
        if (x == p - 1)
        {
            return 0;
        }
        x = modpow(x, 2, p);
    }
    return 1;
}

long rand_long(long low, long up)
{
    return rand() % (up - low + 1) + low;
}

int is_prime_miller(long p, int k)
{
    if (p == 2)
    {
        return 1;
    }
    if (!(p & 1) || p <= 1)
    { // on verifie que p est impair et different de 1
        return 0;
    }
    // on determine b et d :
    long b = 0;
    long d = p - 1;
    while (!(d & 1))
    { // tant que d n’est pas impair
        d = d / 2;
        b = b + 1;
    }
    // On genere k valeurs pour a, et on teste si c’est un temoin :
    long a;
    int i;
    for (i = 0; i < k; i++)
    {
        a = rand_long(2, p - 1);
        if (witness(a, b, d, p))
        {
            return 0;
        }
    }
    return 1;
}

long random_prime_number(int low_size, int up_size, int k)
{
    // nombre decimal pour la taille donne en parametre
    int ls = (int)pow(2, low_size - 1);
    int us = (int)pow(2, up_size) - 1;

    long rd = rand_long(ls, us);

    // itere jusqua que le nombre soit premier
    while (is_prime_miller(rd, k) != 1)
    {
        rd = rand_long(ls, us);
    }

    return rd;
}