#include "exercice3.h"

void init_key(Key *key, long val, long n)
{
    if (key == NULL)
    {
        key = malloc(sizeof(Key));
    }

    // initialisation des valeurs de la cle
    key->n = n;
    key->val = val;
}

void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size)
{
    // p 1er nombre premier
    long p = random_prime_number(low_size, up_size, 5000);
    long q = p;

    // q 2e nombre premier different de r1
    while (q == p)
    {
        q = random_prime_number(low_size, up_size, 5000);
    }

    // generer une cle avec les 2 nombres premiers
    long u, s, n;
    generate_keys_values(p, q, &n, &s, &u);

    // initialisation de la cle publique pKey et secrete sKey
    init_key(pKey, s, n);
    init_key(sKey, u, n);
}

char *key_to_str(Key *key)
{
    char *str = malloc(sizeof(char) * 50);

    // met dans la chaine de caractere les valeurs de la cle
    sprintf(str, "(%lx,%lx)", key->val, key->n);

    str = realloc(str, sizeof(char) * (strlen(str) + 1));

    return str;
}

Key *str_to_key(char *str)
{
    Key *key = malloc(sizeof(Key));

    // s'il existe bel et bien 2 elements dans le bon format
    long val, n;
    if (sscanf(str, " (%lx,%lx)", &val, &n) == 2)
    {
        // initialisation de la cle
        init_key(key, val, n);
    }
    return key;
}

Signature *init_signature(long *content, int size)
{
    Signature *sig = malloc(sizeof(Signature));
    sig->size = size;
    sig->content = content;
    return sig;
}

Signature *sign(char *mess, Key *sKey)
{
    // initialise la signature avec le message scryptee de la cle prive
    return init_signature(encrypt(mess, sKey->val, sKey->n), strlen(mess));
}

// fonction donnee
char *signature_to_str(Signature *sgn)
{
    char *result = malloc(10 * sgn->size * sizeof(char));
    result[0] = '#';
    int pos = 1;
    char buffer[156];
    for (int i = 0; i < sgn->size; i++)
    {
        sprintf(buffer, "%lx", sgn->content[i]);
        for (int j = 0; j < strlen(buffer); j++)
        {
            result[pos] = buffer[j];
            pos = pos + 1;
        }
        result[pos] = '#';
        pos = pos + 1;
    }
    result[pos] = '\0';
    result = realloc(result, (pos + 1) * sizeof(char));
    return result;
}

Signature *str_to_signature(char *str)
{
    int len = strlen(str);
    long *content = (long *)malloc(sizeof(long) * len);
    int num = 0;
    char buffer[256];
    int pos = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] != '#')
        {
            buffer[pos] = str[i];
            pos = pos + 1;
        }
        else
        {
            if (pos != 0)
            {
                buffer[pos] = '\0';
                sscanf(buffer, "%lx", &(content[num]));
                num = num + 1;
                pos = 0;
            }
        }
    }
    content = realloc(content, num * sizeof(long));
    return init_signature(content, num);
}

Protected *init_protected(Key *pKey, char *mess, Signature *sgn)
{
    Protected *p = malloc(sizeof(Protected));
    p->pKey = pKey;
    p->mess = mess;
    p->sgn = sgn;
    return p;
}

int verify(Protected *pr)
{

    // cle public du candidat en char* : contenu decrypte de la signature avec la cle publique
    char *sgn_content = decrypt(pr->sgn->content, pr->sgn->size, pr->pKey->val, pr->pKey->n);

    // verification que la cle contenu dans pr est egale a la cle dans mess (comparaison de chaine de caractere)
    if (strcmp(pr->mess, sgn_content) != 0)
    {
        // non valide
        free(sgn_content);
        return 0;
    }

    free(sgn_content);
    return 1;
}

char *protected_to_str(Protected *pr)
{
    // Conversion de cle publique en chaine de caractere
    char *strKey = key_to_str(pr->pKey);

    // Conversion de la signature en chaine de caractere
    char *sgn = signature_to_str(pr->sgn);

    // allocation de la chaine de protected
    int size = strlen(strKey) + strlen(sgn) + strlen(pr->mess) + 3;
    char *str = malloc(sizeof(char) * size);

    // initialise la chaine de protected
    sprintf(str, "%s %s %s", strKey, pr->mess, sgn);
    str[strlen(str)] = '\0';

    // Desalloue les chaines
    free(sgn);
    free(strKey);

    return str;
}

Protected *str_to_protected(char *str)
{
    Protected *pt = NULL;

    // variable pour : cle, signature, vote
    char strkey[256], strsgn[256], *mess = malloc(sizeof(char) * 50);
    Key *pkey;
    Signature *sgn;

    // si la chaine de caractere contient bien 3 chaine de caractere separe
    if (sscanf(str, "%s %s %s\n", strkey, mess, strsgn) == 3)
    {

        // initialise les elements de la declaration
        pkey = str_to_key(strkey);
        sgn = str_to_signature(strsgn);
        mess = realloc(mess, sizeof(char) * (strlen(mess) + 1));
        pt = init_protected(pkey, mess, sgn);
    }
    else
    {
        free(mess);
    }

    return pt;
}

void free_Key(Key *k)
{
    if (k == NULL)
        return;
    free(k);
}

void free_Signature(Signature *sgn)
{
    if (sgn == NULL)
        return;

    free(sgn->content);
    free(sgn);
}
void free_Protected(Protected *p)
{
    if (p == NULL)
        return;

    free(p->mess);
    free_Key(p->pKey);
    free_Signature(p->sgn);
    free(p);
}
