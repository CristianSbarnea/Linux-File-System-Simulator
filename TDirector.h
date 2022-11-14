#include "TFisier.h"
#ifndef T_DIRECTOR_
#define T_DIRECTOR_

/*structura director*/
typedef struct director {
    char* nume;
    struct director* parinte;
    struct fisier* fisiere;
    struct director* directoare;
    struct director* st;
    struct director* dr;
} TDirector;

/*functii*/
TDirector* init_root(void);
TDirector* creeaza_director(TDirector** parinte, char* numeDirector);
int insereaza_director(TDirector** dir, TDirector* director);
int mkdir(TDirector* d, char* numeDirector);
void afiseaza_directoare(TDirector* director);
void afiseaza_director_curent(TDirector* root);
void distruge_director(TDirector* root);
void distruge_directoare(TDirector* root);
int cauta_director(TDirector* root, char* numeDirector);
int cauta(TDirector* root, char* nume);
void distruge_un_director(TDirector** root);
int sterge_director(TDirector** director, char* numeDirector);
int rmdir(TDirector* director, char* numeDirector);
TDirector* cd(TDirector* root, char* numeDirector);
TDirector* cauta_dir(TDirector* p, char* numeDirector);

#endif