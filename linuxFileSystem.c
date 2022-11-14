#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "TDirector.h"
#include "TFisier.h"
#define MAX 256

int main(void) {
    TDirector* root = init_root(); /*initializare root*/
    if (!root) {
        return -1;
    }
    char* line = calloc(MAX, 1); /*alocare linie*/
    if (!line) {
        distruge_director(root);
        return -1;
    }
    
    while(fgets(line, MAX, stdin)) {
        char* token = strtok(line, " \n");
        if (!(strcmp(token, "touch"))) {
            char* p = strtok(0, " \n");
            if (cauta(root, p)) {
                continue;
            } else {
                touch(root, p);
            }
        } else if (!strcmp(token, "mkdir")) {
            char* p = strtok(0, " \n");
            if (cauta(root, p)) {
                continue;
            }
            mkdir(root, p);
        } else if (!strcmp(token, "ls")) {
            afiseaza_director_curent(root);
        } else if (!strcmp(token, "rm")){
            char* p = strtok(0, " \n");
            if (rm(root, p)) {
                continue;
            }
        } else if (!strcmp(token, "rmdir")) {
            char* p = strtok(0, " \n");
            if (rmdir(root, p)) {
                continue;
            }
        } else if (!(strcmp(token, "cd"))) {
            char* p = strtok(0, " \n");
            if (strcmp(p, "..") == 0) {
                if (root->parinte != NULL) {
                    root = root->parinte;
                    continue;
                }
            }
            root = cd(root, p);
        } else if (!strcmp(token, "quit")) {
            free(line);
            while(root->parinte) {
                root = root->parinte;
            }
            distruge_director(root);
            return 0;
        }
    }
    free(line);
    distruge_director(root);
    return 0;
}