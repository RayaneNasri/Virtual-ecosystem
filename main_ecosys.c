#include <assert.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <strings.h>
#include "ecosys.h"
/* /!\ Le nb de proies doit etre le double du nb de predateurs */
#define NB_PROIES 160
#define NB_PREDATEURS 80
#define T_WAIT 40000

int main(void){
  Srand(time(NULL));
  // Declaration et initialisation du monde :
  int monde[SIZE_X][SIZE_Y];
  for(int i = 0; i < SIZE_X; i++){
    for(int j = 0; j < SIZE_Y; j++){
      monde[i][j] = 0;
    }
  }
 
  // Création des 20 proies :
  Animal* proies = NULL;
  int x, y;
  float e;
  for(int i = 0; i < NB_PROIES; i++){
      x = rand() % SIZE_X;
      y = rand() % SIZE_Y;
      e = rand() % 10 + 1;
      ajouter_animal(x, y, e, &proies);
  }
  // Création des 20 prédateurs :
  Animal* predateurs = NULL;
  for(int i = 0; i < NB_PREDATEURS; i++){
      x = rand() % SIZE_X;
      y = rand() % SIZE_Y;
      e = rand() % 20 + 1;
      ajouter_animal(x, y, e, &predateurs);
  }

  FILE* mon_fichier = fopen("Evol_Pop.txt", "w");

  int IMAX = 500;
  fprintf(mon_fichier, "%d %d %d\n", 200 - IMAX, compte_animal_rec(proies), compte_animal_rec(predateurs));
  while(proies && IMAX){
    rafraichir_monde(monde);
    rafraichir_proies(&proies, monde);
    rafraichir_predateurs(&predateurs, &proies);
    fprintf(mon_fichier, "%d %d %d\n", 200 - IMAX + 1, compte_animal_rec(proies), compte_animal_rec(predateurs));
    //afficher_ecosys(proies, predateurs);
    //usleep(500000);
    IMAX--;
  }
  fclose(mon_fichier);
  liberer_liste_animaux(proies);
  liberer_liste_animaux(predateurs);
  return 0;
}

