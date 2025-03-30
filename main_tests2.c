#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include "ecosys.h"

#define NbProie 5
#define NbPred 5

int main(){
    srand(time(NULL));
    // Création des 20 proies :
    Animal* proies = NULL;
    int x, y;
    float e;
    for(int i = 0; i < NbProie; i++){
        x = rand() % SIZE_X;
        y = rand() % SIZE_Y;
        e = rand() % 10 + 1;
        ajouter_animal(x, y, e, &proies);
    }
    // Création des 20 prédateurs :
    Animal* predateurs = NULL;
    for(int i = 0; i < NbPred; i++){
        x = rand() % SIZE_X;
        y = rand() % SIZE_Y;
        e = rand() % 10 + 1;
        ajouter_animal(x, y, e, &predateurs);
    }

    //assert(compte_animal_it(proies) == 5);
    //assert(compte_animal_it(predateurs) == 5);

    afficher_ecosys(proies, predateurs);

    ecrire_ecosys("Ecosysteme1.txt", predateurs, proies);
    //rafraichir_proies(&proies);
    ecrire_ecosys("Ecosysteme2.txt", predateurs, proies);

    /* Supression d'une proie au début et une autre au milieu :
    enlever_animal(&proies, proies);
    enlever_animal(&proies, proies -> suivant -> suivant -> suivant);

    // Supression d'un predateur au début et au autre au milieu :
    enlever_animal(&predateurs, predateurs);
    enlever_animal(&predateurs, predateurs -> suivant -> suivant -> suivant); */

    /* Reproduire des proies :*/
    reproduce(&proies, p_reproduce_proie); 

    // Deplacement des animaux :
    bouger_animaux(proies);
    bouger_animaux(predateurs); 

    afficher_ecosys(proies, predateurs);
    liberer_liste_animaux(proies);
    liberer_liste_animaux(predateurs);
}
