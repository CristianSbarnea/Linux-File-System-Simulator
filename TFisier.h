#ifndef T_FISIER_
#define T_FISIER_
#include "TDirector.h"

typedef struct fisier {
   char* nume;
   struct director* parinte;
   struct fisier* st;
   struct fisier* dr;  
} TFisier;

TFisier* creeaza_fisier(TDirector** parinte, char* numeFisier);
int insereaza_fisier(TFisier** files, TFisier* fisier);
int touch(TDirector* d, char* numeFisier);
void afiseaza_fisiere(TFisier* fisier);
void distruge_fisiere(TFisier* fisier);
int cauta_fisier(TFisier* fisier, char* numeFisier);
int sterge_fisier(TFisier** fisier, char* numeFisier);
int rm(TDirector* director, char* numeFisier);
void distruge_fisier(TFisier** f);

#endif