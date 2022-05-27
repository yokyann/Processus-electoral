#ifndef exercice4_H
#define exercice4_H

#include "exercice3.h"

//genere des données dans les fichiers 
// "keys.txt" (Ensemble de tout les cles et cle a chaque ligne) 
// "candidates.txt" (Ensemble de tout les cle publique des candidats)
// "declarations.txt" (Ensemble de tout les declarations de votes des citoyens // format :cle mess sgn
void generate_random_data(int nv, int nc);


//Ecriture des elements dans le fichier avec le flux dentree
void ecrire_citoyen_fichier(FILE *f, Key *pKey, Key *sKey);
void ecrire_candidat_fichier(FILE *f, Key *pKey);
void ecrire_declaration_fichier(FILE *f, Protected *pr);

#endif