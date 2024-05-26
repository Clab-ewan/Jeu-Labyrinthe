#include "creerGrille.h"
#include "interface.h"
#include <stdio.h>
#include <time.h>

int main() {

  int largeur, hauteur; //initialise la largeur et la hauteur de la grille
  char **grille;// Déclare un pointeur vers un tableau à deux dimensions pour la grille du jeu


  int CordCibles[CIBLES][2];
  MurCible murHCible[CIBLES]; // structure pour stcocker les murs formant des angles droit autour de la cible
  MurCible murVCible[CIBLES];
  

  int *MurRandH = NULL; //Pointeurs pour stocker les positions des murs horizontaux et verticaux aléatoires
  int *MurRandV = NULL;

  srand(time(NULL));
  hauteur = rand() % 6 + 15; // Génère un nombre entre 15 et 20
  largeur = rand() % 6 + 15; // Génère un nombre entre 15 et 20
  printf("Le tableau contient %d lignes et %d colonnes\n", hauteur, largeur);

  MurRandH = (int *)malloc(4 * sizeof(int)); //Alloue la mémoire pour stocker les positions des 4 murs horizontaux
  if (MurRandH == NULL){
    printf("Erreur d'allocation memoire\n");
    exit(1);
  }
  MurRandV = (int *)malloc(4 * sizeof(int)); // Alloue la mémoire pour stocker les positions des 4 murs horizontaux 
  if (MurRandV == NULL){
    printf("Erreur d'allocation memoire\n");
    exit(1);
  }
  for (int i = 0; i < 4; i++) {//Génère aléatoirement les positions des 4 murs horizontaux et verticaux, en s'assurant qu'ils sont uniques. Affiche les positions des murs après les avoir définies.
    do {
      MurRandH[i] = rand() % (hauteur - 2) +
                    1; 
      MurRandV[i] = rand() % (largeur - 2) +
                    1;
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

  initialiserGrille(&grille, hauteur, largeur);//Initialise la grille avec les dimensions spécifiées

  placerCibles(grille, hauteur, largeur, CordCibles, murHCible, murVCible);//Place les cibles sur la grille,
  placerRobots(grille, hauteur, largeur); //Place les robots sur la grille,
  afficherGrille(grille, hauteur, largeur, MurRandH, MurRandV, murHCible,
                 murVCible);//affiche la grille avec les robots et les cibles ainsi que les murs de différentes couleurs.

  int nb_joueur = 1;// initialise le nombre de joueurs à 1
  int niveau_difficulte = 2;// initialise la difficulte à 2
  int *nmbMouv = NULL;// initialise le nombre de mouvements
  int duree_chrono = 0;// initialise la durée du chronometre 
  int direction;
  int joueurActuel = 0;//initalise le joueur qui vas jouer la manche 
  NombreJoueurs(&nb_joueur);// demande le nombre de joueurs
  int *pointsJoueurs = NULL; //initalise les points  
  Robot robot;
  Cible cible;

  pointsJoueurs = malloc(nb_joueur * sizeof(int));//Alloue de la mémoire pour stocker les points des joueurs et initialise ces points à zéro.
  if (pointsJoueurs == NULL) {
    printf("Erreur d'allocation mémoire\n");
    exit(1);
  }
  for (int i = 0; i < nb_joueur; i++) {
    pointsJoueurs[i] = 0;
  }
  
  printf("Début du jeu\n");
  for (int i = 0; i < 5; i++) { //Boucle principale du jeu qui itère sur 5 manches.
    printf("Manche %d\n", i + 1);
    choisirRobotCible(grille, hauteur, largeur, &robot, &cible);// choisit un robot et une cible aléatoirement sur la grille.
     duree_chrono = choixdifficulte(niveau_difficulte); //demande le niveau de difficulté et retourne le temps du chronomètre en fonction
    afficherGrille(grille, hauteur, largeur, MurRandH, MurRandV, murHCible,
                   murVCible);
     chronometrer(duree_chrono);//active le chronomètre pendant lequel les joueurs réfléchissent à leur nombres de mouvements
    choix_player(&nmbMouv, nb_joueur, grille, &robot, &cible, &joueurActuel); //Choisit le joueur avec le moins de mouvements et lui demande de jouer.
    printf("Le joueur %d va faire %d mouvements\n", joueurActuel + 1, nmbMouv[joueurActuel]);
     JoueurTour(grille,  hauteur,  largeur,  &robot,  &cible,  MurRandH,  MurRandV,  murHCible,  murVCible,  nmbMouv,  joueurActuel, pointsJoueurs);//tant que le nombre de mouvement n'est pas terminé, demande au joueur la direction et deplace le robot. Actualise le nombre de points 

    // Afficher les points après chaque manche
    printf("Points après la manche %d:\n", i + 1);
    for (int j = 0; j < nb_joueur; j++) {
      printf("Joueur %d: %d points\n", j + 1, pointsJoueurs[j]);
    }
  }

   AfficherGagnant(pointsJoueurs, nb_joueur);
  
  for (int i = 0; i < hauteur; i++) {//libère la mémoire 
    free(grille[i]);
  }
  free(grille);
  free(MurRandH);
  free(MurRandV);
  free(pointsJoueurs);
  free(nmbMouv);
  return 0;
}

