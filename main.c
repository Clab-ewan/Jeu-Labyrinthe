#include "creerGrille.h"
#include "interface.h"
#include <stdio.h>
#include <time.h>

int main() {

  int largeur, hauteur;
  char **grille;

  int CordCibles[CIBLES][2];
  MurCible murHCible[CIBLES];
  MurCible murVCible[CIBLES];
  int nombreMursInterdits = 0;

  int *MurRandH = NULL;
  int *MurRandV = NULL;

  srand(time(NULL));
  hauteur = rand() % 6 + 15; // Génère un nombre entre 15 et 20
  largeur = rand() % 6 + 15; // Génère un nombre entre 15 et 20
  printf("Le tableau contient %d lignes et %d colonnes\n", hauteur, largeur);

  MurRandH = (int *)malloc(4 * sizeof(int)); // alloc dynamique
  MurRandV = (int *)malloc(4 * sizeof(int)); // alloc dynamique

  for (int i = 0; i < 4; i++) {
    do {
      MurRandH[i] = rand() % (hauteur - 2) + 1;
      MurRandV[i] = rand() % (largeur - 2) + 1;
      int unique = 1;
      for (int j = 0; j < i; j++) {
        if (MurRandH[j] == MurRandH[i] || MurRandV[j] == MurRandV[i]) {
          unique = 0;
          break;
        }
      }
      if (unique) {
        break;
      }
    } while (1);

    printf("MurRandH[%d] = %d\n", i, MurRandH[i]);
    printf("MurRandV[%d] = %d\n", i, MurRandV[i]);
  }

  initialiserGrille(&grille, hauteur, largeur);

  placerCibles(grille, hauteur, largeur, CordCibles, murHCible, murVCible);
  placerRobots(grille, hauteur, largeur);
  afficherGrille(grille, hauteur, largeur, &MurRandH, &MurRandV, murHCible,
                 murVCible);
  // début du jeu Z'ESSTTT PARTIIII !!!
  int nb_joueur = 1;
  int niveau_difficulte = 2;
  int *nmbMouv = NULL;
  int duree_chrono = 0;
  int player = 0;
  int direction;
  NombreJoueurs(&nb_joueur);
  Robot robot;
  Cible cible;
  printf("Début du jeu\n");
  for (int i = 0; i < 5; i++) {
    printf("Manche %d\n", i + 1);
    choisirRobotCible(grille, hauteur, largeur, &robot, &cible);
    // duree_chrono = choixdifficulte(niveau_difficulte);
    afficherGrille(grille, hauteur, largeur, &MurRandH, &MurRandV, murHCible,
                   murVCible);
    // chronometrer(duree_chrono);
    choix_player(&nmbMouv, nb_joueur, grille, &robot, &cible, &player);
    printf("Le joueur %d va faire %d mouvements\n", player + 1,
           nmbMouv[player]);
    for (int i = 0; i < nmbMouv[player]; i++) {
      direction = choix_direction();

      deplacement(&robot, &cible, direction, MurRandH, MurRandV, murHCible,
                  murVCible, grille, hauteur, largeur);
      afficherGrille(grille, hauteur, largeur, &MurRandH, &MurRandV, murHCible,
                     murVCible);
    }
  }
  for (int i = 0; i < hauteur; i++) {
    free(grille[i]);
  }
  free(grille);
  free(MurRandH);
  free(MurRandV);

  return 0;
}
