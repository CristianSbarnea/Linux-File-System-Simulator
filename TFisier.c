/* Sbarnea Cristian-Stefan 314CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDirector.h"
#include "TFisier.h"


/*functie care imi creeaza un pointer la o structura de tip
TFisier, ii aloca memorie si initializeaza campurile */
TFisier* creeaza_fisier(TDirector** parinte, char* numeFisier) {
    TFisier* aux = (TFisier*)calloc(sizeof(TFisier), 1);
    if (!aux) {
        return NULL;
    }
    aux->nume = strdup(numeFisier);
    aux->parinte = *parinte;
    aux->st = NULL;
    aux->dr = NULL;
    return aux;
}

/*functie care insereaza un fisier in ordine lexicografica intr-un
arbore de fisiere*/
int insereaza_fisier(TFisier** files, TFisier* fisier) {
    if (!(*files)) {
        *files = fisier;
        return 1;
    }
    int directie; /*dreapta = 1, stanga = 0*/
    TFisier* p;
    TFisier* f = *files;
    while (f != NULL) {
        if (strcmp(f->nume, fisier->nume) == 0) {
            return 0;
        }
        if (strcmp(f->nume, fisier->nume) < 0) {
            p = f;
            f = f->dr;
            directie = 1; /*dreapta*/
        } else {
            p = f;
            f = f->st;
            directie = 0; /*stanga*/
        }
    }
    if (directie == 0) {
        p->st = fisier;  
    } else {
        p->dr = fisier;
    }
    return 1;
}

/*creeaza si insereaza un fisier*/
int touch(TDirector* d, char* numeFisier) {
    TFisier* aux = creeaza_fisier(&d, numeFisier);
    if (!aux) {
        return 0;
    }
    if (insereaza_fisier(&(d->fisiere), aux)) {
        return 1;
    } else {
        distruge_fisiere(aux); /*distrug fisierul creat daca inserarea esuaza*/
        return 0;
    }
}

/*functie care elibereaza memoria ocupata de un fisier*/
void distruge_fisiere(TFisier* fisier) {
    if (!fisier) {
        return;
    }
    distruge_fisiere(fisier->st);
    distruge_fisiere(fisier->dr);
    free(fisier->nume);
    free(fisier);
}

/*functie care cauta un fisier intr-un arbore de fisiere*/
int cauta_fisier(TFisier* fisier, char* numeFisier) {
    if (!fisier) {
        return 0;
    }
    while (fisier != NULL) {
        if (strcmp(fisier->nume, numeFisier) == 0) {
            return 1;
        }
        if (strcmp(fisier->nume, numeFisier) > 0) {
            fisier = fisier->st;
        } else {
            fisier = fisier->dr;
        }
    }
    return 0;
}

/*functie care sterge un fisier*/
void distruge_fisier(TFisier** f) {
    TFisier* p = *f;
    free(p->nume);
    free(p);
    *f = NULL;
}

/*functie care elimina un fisier dintr-un arbore*/
int sterge_fisier(TFisier** fisier, char* numeFisier) {
    if (!(*fisier)) {
        return 0;
    }
    if (cauta_fisier(*fisier, numeFisier) == 0) {
        return 0;
    }
    TFisier* f = *fisier;
    TFisier* p = NULL;
    int directie;
    while (f) {
        if (strcmp(f->nume, numeFisier) == 0) {
            break;
        }
        if (strcmp(f->nume, numeFisier) > 0) {
            p = f;
            f = f->st;
            directie = 0;
        } else {
            p = f;
            f = f->dr;
            directie = 1;
        }
    }
    if (f->dr == NULL && f->st == NULL) {
       if (directie == 0) {
           distruge_fisier(&p->st);
           p->st = NULL;
           return 1;
       } else if (directie == 1) {
           distruge_fisier(&p->dr);
           p->dr = NULL;
           return 1;
       } else if (p == NULL) {
           distruge_fisier(&f);
           f = NULL;
           return 1;
       }
    } else if (f->st == NULL || f->dr == NULL) {
        if (p == NULL) {
            if (f->st == NULL) {
                *fisier = f->dr;
                distruge_fisier(&f);
                f = NULL;
                return 1;
            } else if (f->dr == NULL) {
                *fisier = f->st;
                distruge_fisier(&f);
                f = NULL;
                return 1;
            }
        } else if (f->st == NULL) {
            if (strcmp(p->nume, f->nume) > 0) {
                p->st = f->dr;
            } else {
                p->dr = f->dr;
            }
            distruge_fisier(&f);
            f = NULL;
            return 1;
        } else if (f->dr == NULL) {
            if (strcmp(p->nume, f->nume) > 0) {
                p->st = f->st;
            } else {
                p->dr = f->st;
            }
            distruge_fisier(&f);
            f = NULL;
            return 1;
        }
    } else {
        TFisier* temp = f->st, *parinteTemp;
        parinteTemp = f;
        while (temp->dr) {
            parinteTemp = temp;
            temp = temp->dr;
        }
        if (temp == f->st) {
            free(f->nume);
            f->nume = strdup(temp->nume);
            distruge_fisier(&temp);
            f->st = NULL;
            temp = NULL;
            return 1;
        }
        free(f->nume);
        f->nume = strdup(temp->nume);
        parinteTemp->dr = temp->st;
        distruge_fisier(&temp);
        temp = NULL;
        return 1;
    }
    return 1;
}

/*stergere fisier*/
int rm(TDirector* director, char* numeFisier) {
    if (sterge_fisier(&(director->fisiere), numeFisier)) {
        return 1;
    } else {
        printf("File %s doesn't exist!\n", numeFisier);
        return 0;
    }
}