#ifndef exercice3_H
#define exercice3_H

#include "exercice2.h"

typedef struct key
{
    long val;
    long n;
} Key;

typedef struct signature
{
    int size;
    long *content;
} Signature;

typedef struct protected
{
    Key *pKey;      // cle publique de l electeur
    char *mess;     // cle du candidat C
    Signature *sgn; // signature obtenu fonction 'sign' depuis la cle prive de l electeur
}
Protected;

// initialisation
void init_key(Key *key, long val, long n);                              // cle avec les valeurs en parametre
void init_pair_keys(Key *pKey, Key *sKey, long low_size, long up_size); // cles publique et prive
Signature *init_signature(long *content, int size);                     // content deja initialisé
Protected *init_protected(Key *pKey, char *mess, Signature *sgn);       // pas de dupplication des valeurs

// conversion
char *key_to_str(Key *key); // cle -> une chaine de caractere '(x,y)'
Key *str_to_key(char *str); // une chaine de caractere -> cle

char *signature_to_str(Signature *sgn); // conversion en "#x1#x2#x3#x4#...#"
Signature *str_to_signature(char *str); // x1,...xn sont les elements du tableau dans signature

char *protected_to_str(Protected *pr); // format : "cle messsage signature"
Protected *str_to_protected(char *str);

// signature depuis la cle du candidat C a laide de la cle prive
Signature *sign(char *mess, Key *sKey);

// verification
int verify(Protected *pr); // declaration authentique renvoie 1 sinon 0

// fonction de desallocation
void free_Protected(Protected *p);
void free_Signature(Signature *sgn);
void free_Key(Key *k);

#endif