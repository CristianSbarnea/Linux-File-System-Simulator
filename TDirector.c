/* Sbarnea Cristian-Stefan 314CB */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TFisier.h"
#include "TDirector.h"

/*functie care initializeaza directorul root*/
TDirector* init_root(void) {
    TDirector* aux = (TDirector*)calloc(sizeof(TDirector), 1);
    if (!aux) {
        return NULL;
    }
    aux->nume = strdup("root");
    aux->parinte = NULL;
    aux->fisiere = NULL;
    aux->directoare = NULL;
    aux->st = NULL;
    aux->dr = NULL;
    return aux;
}

/*functie care creeaza un director*/
TDirector* creeaza_director(TDirector** parinte, char* numeDirector) {
    TDirector* aux = (TDirector*)calloc(sizeof(TDirector), 1);
    if (!aux) {
        return NULL;
    }
    aux->nume = strdup(numeDirector);
    aux->parinte = *parinte;
    aux->directoare = NULL;
    aux->st = NULL;
    aux->fisiere = NULL;
    aux->dr = NULL;
    return aux;
}

/*functie care insereaza un director in ordine lexicografica intr-un
arbore de directoare*/
int insereaza_director(TDirector** dir, TDirector* director) {
    if (!(*dir)) {
        *dir = director;
        return 1;
    }
    int directie;
    TDirector* p;
    TDirector* d = *dir;
    while (d != NULL) {
        if (strcmp(d->nume, director->nume) == 0) {
            return 0;
        }
        if (strcmp(d->nume, director->nume) < 0) {
            p = d;
            d = d->dr;
            directie = 1;
        } else {
            p = d;
            d = d->st;
            directie = 0;
        }
    }
    if (directie == 0) {
        p->st = director;
    } else {
        p->dr = director;
    }
    return 1;
}

/*creeaza si insereaza un director*/
int mkdir(TDirector* d, char* numeDirector) {
    TDirector* aux = creeaza_director(&d, numeDirector);
    if (!aux) {
        return 0;
    }
    if (insereaza_director(&(d->directoare), aux)) {
        return 1;
    } else {
        distruge_un_director(&aux);
        free(aux); /*distrug directorul creat daca esueaza inserarea*/
        return 0;
    }
}

/*functie care afiseaza directoarele lexicografic*/
void afiseaza_directoare(TDirector* director) {
    if (!director) {
        return;
    }
    afiseaza_directoare(director->st);
    printf("%s ", director->nume);
    afiseaza_directoare(director->dr);
}

/*functie care afiseaza fisierele lexicografic*/
void afiseaza_fisiere(TFisier* fisier) {
    if (fisier == NULL) {
        return;
    }
    afiseaza_fisiere(fisier->st);
    printf("%s ", fisier->nume);
    afiseaza_fisiere(fisier->dr);
}

/*functie care afiseaza fisierele si directoarele*/
void afiseaza_director_curent(TDirector* root) {
    if (!root) {
        return;
    }
    afiseaza_directoare(root->directoare);
    afiseaza_fisiere(root->fisiere);
    printf("\n");
}

/*functie care elibereaza memoria ocupata de un director*/
void distruge_directoare(TDirector* root) {
    if (!root) {
        return;
    }
    distruge_directoare(root->st);
    distruge_directoare(root->dr);
    free(root->nume);
    distruge_fisiere(root->fisiere);
    free(root);
}

/*functie care elibereaza memoria ocupata de fisierele si subdirectoarele
unui director*/
void distruge_director(TDirector* root) {
    if (!root) {
        return;
    }
    distruge_director(root->st);
    distruge_director(root->dr);
    free(root->nume);
    distruge_fisiere(root->fisiere);
    distruge_directoare(root->directoare);
    free(root);
}

/*functie care cauta un director intr-un arbore de directoare*/
int cauta_director(TDirector* root, char* numeDirector) {
    if (!root) {
        return 0;
    }
    while (root) {
        if (strcmp(root->nume, numeDirector) == 0) {
            return 1;
        }
        if (strcmp(root->nume, numeDirector) > 0) {
            root = root->st;
        } else {
            root = root->dr;
        }
    }
    return 0;
}

/*functie care cauta numele unui director/fisier in arborele de fisiere
si arborele de subdirectoare ale unui director*/
int cauta(TDirector* root, char* nume) {
    if (cauta_director(root->directoare, nume)) {
        printf("Directory %s already exists!\n", nume);
        return 1;
    } else if (cauta_fisier(root->fisiere, nume)) {
        printf("File %s already exists!\n", nume);
        return 1;
    }
    return 0;
}

/*functie care sterge un director dintr-un arbore de directoare*/
int sterge_director(TDirector** director, char* numeDirector) {
    if (!(*director)) {
        return 0;
    }
    if (cauta_director(*director, numeDirector) == 0) {
        return 0;
    }
    TDirector* d = *director;
    TDirector* p = NULL;
    int directie;
    while (d) {
        if (strcmp(d->nume, numeDirector) == 0) {
            break;
        }
        if (strcmp(d->nume, numeDirector) > 0) {
            p = d;
            d = d->st;
            directie = 0;
        } else {
            p = d;
            d = d->dr;
            directie = 1;
        }
    }
    if (d->dr == NULL && d->st == NULL) {
        if (directie == 0) {
            distruge_un_director(&p->st);
            p->st = NULL;
            return 1;
        } else if (directie == 1) {
            distruge_un_director(&p->dr);
            p->dr = NULL;
            return 1;
        } else if (p == NULL) {
            distruge_un_director(&d);
            *director = NULL;
            d = NULL;
            return 1;
        }
    } else if ((d->st == NULL) || (d->dr == NULL)) {
        if (p == NULL) {
            if (d->st == NULL) {
                *director = d->dr;
                distruge_un_director(&d);
                d = NULL;
                return 1;
            } else if (d->dr == NULL) {
                *director = d->st;
                distruge_un_director(&d);
                d = NULL;
                return 1;
            }
        } else if (d->st == NULL) {
            if (strcmp(p->nume, d->nume) > 0) {
                p->st = d->dr;
            } else {
                p->dr = d->dr;
            }
            distruge_un_director(&d);
            d = NULL;
            return 1;
        } else if (d->dr == NULL) {
            if (strcmp(p->nume, d->nume) > 0) {
                p->st = d->st;
            } else {
                p->dr = d->st;
            }
            distruge_un_director(&d);
            d = NULL;
            return 1;
        }  
    } else {
        TDirector* temp = d->st, *parinteTemp;
        parinteTemp = d;
        while (temp->dr) {
            parinteTemp = temp;
            temp = temp->dr;
        }
        if (temp == d->st) {
            free(d->nume);
            d->nume = strdup(temp->nume);
            distruge_un_director(&temp);
            temp = NULL;
            d->st = NULL;
            return 1;
        }
        free(d->nume);
        d->nume = strdup(temp->nume);
        parinteTemp->dr = temp->st;
        distruge_un_director(&temp);
        temp = NULL;
        return 1;
    }
    return 1;
}

/*functie care elibereaza un director dintr-un arbore*/
void distruge_un_director(TDirector** root) {
    TDirector* p = *root;
    distruge_fisiere(p->fisiere);
    p->fisiere = NULL;
    free(p->nume);
    free(p);
    p = NULL;
}

/*rmdir*/
int rmdir(TDirector* director, char* numeDirector) {
    if (sterge_director(&(director->directoare), numeDirector)) {
        return 1;
    } else {
        printf("Directory %s doesn't exist!\n", numeDirector);
        return 0;
    }
}

/*functie care cauta un director intr-un arbore si intoarce un pointer la el*/
TDirector* cauta_dir(TDirector* p, char* numeDirector) {
    if (!p) {
        return NULL;
    }
    TDirector* temp = p;
    while (temp) {
        if (strcmp(temp->nume, numeDirector) == 0) {
            return temp;
        } else if (strcmp(temp->nume, numeDirector) > 0) {
            temp = temp->st;
        } else {
            temp = temp->dr;
        }
    }   
    return NULL;
}

/*cd*/
TDirector* cd(TDirector* root, char* numeDirector) {
    TDirector* p = cauta_dir(root->directoare, numeDirector);
    if (p != NULL) {
        return p;
    } else {
        printf("Directory not found!\n");
        return root;
    }
}