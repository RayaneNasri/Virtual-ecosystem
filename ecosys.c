#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ecosys.h"

/* Parametres globaux de l'ecosysteme (externes dans le ecosys.h)*/
float p_ch_dir = 0.01;
float p_reproduce_proie = 0.5;
float p_reproduce_predateur = 0.5;
int temps_repousse_herbe = -15;

/* PARTIE 1*/
/* Fourni: Part 1, exercice 4, question 2 */
Animal *creer_animal(int x, int y, float energie){
  
  // Ajout d'asserts vérifiants les valeurs passées en arguments :
  assert ((0 <= x) && (x < SIZE_X));
  assert ((0 <= y) && (y < SIZE_Y));
  assert (0 < energie);

  Animal *na = (Animal *)malloc(sizeof(Animal));
  assert(na);
  na->x = x;
  na->y = y;
  na->energie = energie;
  na->dir[0] = rand() % 3 - 1;
  na->dir[1] = rand() % 3 - 1;
  na->suivant = NULL;
  return na;
}


/* Fourni: Part 1, exercice 4, question 3 */
Animal *ajouter_en_tete_animal(Animal *liste, Animal *animal) {
  assert(animal);
  assert(!animal->suivant);
  animal->suivant = liste;
  return animal;
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_rec(Animal *la) {
  if (!la) return 0;
  return 1 + compte_animal_rec(la->suivant);
}

/* Fourni: part 1, exercice 4, question 4 */
unsigned int compte_animal_it(Animal *la) {
  int cpt=0;
  Animal* tmp = la;
  while (tmp){
    cpt++;
    tmp = tmp->suivant;
  }
  return cpt;
}

/* A faire. Part 1, exercice 6, question 2 */
void ajouter_animal(int x, int y, float energie, Animal** liste_animal){
  
  assert ((0 <= x) && (x < SIZE_X));
  assert ((0 <= y) && (y < SIZE_Y));
  assert (0 < energie);

  Animal* new = malloc(sizeof(Animal));
  assert(new);

  new -> x = x;
  new -> y = y;
  new -> dir[0] = rand() % 3 - 1;
  new -> dir[1] = rand() % 3 - 1;
  new -> energie = energie;

  new -> suivant = (*liste_animal);
  (*liste_animal) = new;
}

/* A Faire. Part 1, exercice 5, question 5 */
void enlever_animal(Animal** liste, Animal* animal) {
  Animal* tmp = (*liste);
  
  // Si c'est le premier :
  if (tmp == animal){
    (*liste) = (*liste) -> suivant;
    free(tmp);
    return;
  }
  // Si ce n'est pas le premier :
  while((tmp) && (tmp -> suivant != animal)){
    tmp = tmp -> suivant;
  }
  if ((tmp -> suivant) == animal)
    {
      tmp -> suivant = tmp -> suivant -> suivant;
      free(animal);
      return;
    }
  return;
}

/* A Faire. Part 1, exercice 6, question 7 */
Animal* liberer_liste_animaux(Animal* liste){
  Animal* tmp;
  while(liste){
    tmp = liste -> suivant;
    free(liste);
    liste = tmp;
  }
  return NULL;
}

/* Part 1. Exercice 5, question 1, ATTENTION, ce code est susceptible de contenir des erreurs */
void afficher_ecosys(Animal *liste_proie, Animal *liste_predateur){
  unsigned int i, j;
  char ecosys[SIZE_X][SIZE_Y];
  Animal *pa = NULL;

  /* On initialise le tableau */
  for (i = 0; i < SIZE_X; i++) {
    for (j = 0; j < SIZE_Y; j++) {
      ecosys[i][j]=' ';
    }
  }

  /* On ajoute les proies */
  pa = liste_proie;
  while (pa) {
    ecosys[pa->x][pa->y] = '*';
    pa = pa->suivant;
  }

  /* On ajoute les predateurs */
  pa = liste_predateur;
  while (pa) {
      if ((ecosys[pa->x][pa->y] == '@') || (ecosys[pa->x][pa->y] == '*')) { /* proies aussi present */
        ecosys[pa->x][pa->y] = '@';
      } else {
        ecosys[pa->x][pa->y] = 'O';
      }
    pa = pa->suivant;
  }

  /* on affiche le tableau */
  printf("+");
  for (j = 0; j < SIZE_Y; j++) {
    printf("-");
  }  
  printf("+\n");
  for (i = 0; i < SIZE_X; i++) {
    printf("|");
    for (j = 0; j < SIZE_Y; j++) {
      putchar(ecosys[i][j]);
    }
    printf("|\n");
  }
  printf("+");
  for (j = 0; j < SIZE_Y; j++) {
    printf("-");
  }
  printf("+\n");
  int nbproie=compte_animal_it(liste_proie);
  int nbpred=compte_animal_it(liste_predateur);
  
  printf("Nb proies : %5d\tNb predateurs : %5d\n", nbproie, nbpred);

}


void clear_screen() {
  printf("\x1b[2J\x1b[1;1H");  /* code ANSI X3.4 pour effacer l'ecran */
}

/* PARTIE 2*/

/* Part 2. Exercice 1, question 1 */
void ecrire_ecosys(const char* nom_fichier, Animal* liste_predateur, Animal* liste_proie){
  FILE* mon_fichier = fopen(nom_fichier, "w");
  assert(mon_fichier);

  // Ecriture de la liste des proies :
  fprintf(mon_fichier, "<proies>\n");
  while (liste_proie){
    fprintf(mon_fichier, "x=%d y=%d dir=[%d %d] e=%.2f\n", liste_proie -> x,
    liste_proie -> y, (liste_proie -> dir)[0], (liste_proie -> dir)[1],
    liste_proie -> energie);
    liste_proie = liste_proie -> suivant;
  }
  fprintf(mon_fichier, "</proies>\n");

  // Ecriture de la liste des predateurs :
  fprintf(mon_fichier, "<predateurs>\n");
  while (liste_predateur){
    fprintf(mon_fichier, "x=%d y=%d dir=[%d %d] e=%.2f\n", liste_predateur -> x,
    liste_predateur -> y, (liste_predateur -> dir)[0], (liste_predateur -> dir)[1],
    liste_predateur -> energie);
    liste_predateur = liste_predateur -> suivant;
  }
  fprintf(mon_fichier, "</predateurs>\n");
  fclose(mon_fichier);
}

/* Part 2. Exercice 1, question 2 */
void lire_ecosys(const char* nom_fichier, Animal** liste_predateur, Animal** liste_proie){
  // Ouverture du fichier :
  FILE* mon_fichier = fopen(nom_fichier, "r");
  assert(mon_fichier);

  // Indicateur de fin :
  int LMAX = 500;
  char buffer[LMAX];
  char* end = fgets(buffer, LMAX, mon_fichier);

  // Variables de stock :
  int x, y;
  int d[2];
  float energie;

  while(end){
    // Lecture des données des proies :
    if (!(strncmp(buffer, "<proies>\n", strlen("<proies>\n")))){
      end = fgets(buffer, LMAX, mon_fichier);   
      while(end && (strncmp(buffer, "</proies>\n", strlen("</proies>\n")))){
        sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x, &y, &(d[0]), &(d[1]), &energie);
        ajouter_animal(x, y, energie, liste_proie);
        // Modification des directions aleatoires :
        ((*liste_proie) -> dir)[0] = d[0];
        ((*liste_proie) -> dir)[1] = d[1];
        end = fgets(buffer, LMAX, mon_fichier);
      }
    }
    // Lecture des données des predateurs :
    if (!(strncmp(buffer, "<predateurs>\n", strlen("<predateurs>\n")))){
      end = fgets(buffer, LMAX, mon_fichier);
      while(end && (strncmp(buffer, "</predateurs>\n", strlen("</predateurs>\n")))){
        sscanf(buffer, "x=%d y=%d dir=[%d %d] e=%f\n", &x, &y, &(d[0]), &(d[1]), &energie);
        ajouter_animal(x, y, energie, liste_predateur);
        // Modification des directions aleatoires :
        ((*liste_predateur) -> dir)[0] = d[0];
        ((*liste_predateur) -> dir)[1] = d[1];
        end = fgets(buffer, LMAX, mon_fichier);
        }
      }
    end = fgets(buffer, LMAX, mon_fichier);
  }
  fclose(mon_fichier);
}
  

/* Part 2. Exercice 4, question 1 */
void bouger_animaux(Animal *la){
    while (la){
      // Changement probable de direction :
      if((((float)rand()) / RAND_MAX) < p_ch_dir){
          (la -> dir)[0] = rand() % 3 - 1;
          (la -> dir)[1] = rand() % 3 - 1;
      }
      // Deplacement :
      la -> x = abs(la -> x + la -> dir[0]) % SIZE_X;
      la -> y = abs(la -> y + la -> dir[1]) % SIZE_Y;

      la = la -> suivant;
    }
}
//
/* Part 2. Exercice 4, question 3 */
void reproduce(Animal **liste_animal, float p_reproduce){
   Animal* tmp = (*liste_animal);
   while(tmp){
   // Reproduction si energie > 1  
    if((((float)rand()) / RAND_MAX) <= p_reproduce && (tmp -> energie > 1)){
    ajouter_animal(tmp -> x, tmp -> y, (tmp -> energie)/2, liste_animal);
    tmp -> energie /= 2;
   }
   tmp = tmp -> suivant;
  }
}

/* Part 2. Exercice 6, question 1 */
void rafraichir_proies(Animal** liste_proie, int monde[SIZE_X][SIZE_Y]){
  
  // faire bouger les proies :
  bouger_animaux(*liste_proie);

  // baisser l'enregie :
  Animal* tmp = *liste_proie;
  while(tmp){
    if( 0 >= --(tmp -> energie)){
      Animal* _tmp = tmp -> suivant;
      enlever_animal(liste_proie, tmp);
      tmp = _tmp;
      continue;
    }
    // manger probablement l'herbe :
    if(monde[tmp -> x][tmp -> y] >= 0){
      tmp -> energie += monde[tmp -> x][tmp -> y];
      monde[tmp -> x][tmp -> y] = temps_repousse_herbe;
    }
    tmp = tmp -> suivant;
 
  }

  // faire appel à reproduce :
  reproduce(liste_proie, p_reproduce_proie);
}

/* Part 2. Exercice 7, question 1 */
Animal* animal_en_XY(Animal* l, int x, int y){
  while(l){
    if((l -> x == x) && (l -> y == y)){
      return l;
    }
    l = l -> suivant;
  }
  return NULL;
} 

/* Part 2. Exercice 7, question 2 */
void rafraichir_predateurs(Animal** liste_predateur, Animal** liste_proie){
  // faire bouger les predateurs :
  bouger_animaux(*liste_predateur);

  // baisser l'enregie :
  Animal* tmp = *liste_predateur;
  Animal* p = NULL;
  while(tmp){
    if( 0 >= --(tmp -> energie)){
      Animal* _tmp = tmp -> suivant;
      enlever_animal(liste_predateur, tmp);
      tmp = _tmp;
      continue;
    }
    
    // manger probablement la proie :
    p = animal_en_XY(*liste_proie, tmp -> x, tmp -> y);
    if(p){
      tmp -> energie += 2.5*p -> energie; // /!\ le predateur recupere 2.5 fois energie de la proie
      enlever_animal(liste_proie, p);
    }
    tmp = tmp-> suivant;
  }

  // faire appel à reproduce :
  reproduce(liste_predateur, p_reproduce_predateur);
}


/* Part 2. Exercice 5, question 2 */
void rafraichir_monde(int monde[SIZE_X][SIZE_Y]){
  for(int i = 0; i < SIZE_X; i++){
    for(int j = 0; j < SIZE_Y; j++){
      monde[i][j]++;
    }
  }
}


