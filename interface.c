#include "interface.h"
#include "creerGrille.h"

void NombreJoueurs(int *nb_joueur) { // demande le nombre de joueur
  printf("Veuillez saisir un nombre de joueur entre 1 et 4 : \n");
  if (scanf("%d", &(*nb_joueur)) != 1) {
    printf("Erreur \n");
    exit(1);
  }
  while (*nb_joueur <= 1 && *nb_joueur > 4) {
    printf("Le nombre de joueur doit etre compris entre 1 et 4 \n");

    if (scanf("%d", &(*nb_joueur)) != 1) {
      printf("Erreur \n");
      exit(1);
    }
  }
}

int choixdifficulte(int niveau_difficulte) {
  int duree_chrono = 0;
  printf("\nVeuillez choisir le niveau de difficulté :\nniv 1 = 30\nniv 2 = "
         "20\nniv 3 = 10\n");
  if (scanf("%d", &niveau_difficulte) != 1) {
    printf("Erreurr \n");
    exit(1);
  }
  while (niveau_difficulte < 1 || niveau_difficulte > 3) {
    printf("Le niveau de difficulte doit etre compris entre 1 et 3 \n");
    if (scanf("%d", &niveau_difficulte) != 1) {
      printf("Erreurr \n");
      exit(1);
    }
  }
  switch (niveau_difficulte) {
  case 1:
    duree_chrono = 30;
    break;
  case 2:
    duree_chrono = 20;
    break;
  case 3:
    duree_chrono = 10;
    break;
  default:
    duree_chrono = 20;
  }
  return duree_chrono;
}

void choisirRobotCible(char **grille, int hauteur, int largeur, Robot *robot,
                       Cible *cible) {
  int robotTrouve = 0;
  int cibleTrouvee = 0;

  // Choisir un robot aléatoire
  while (!robotTrouve) {
    robot->ligne = rand() % hauteur;
    robot->col = rand() % largeur;
    if (grille[robot->ligne][robot->col] >= '1' &&
        grille[robot->ligne][robot->col] <= '4') {
      robot->signe = grille[robot->ligne][robot->col];
      robotTrouve = 1;
    }
  }

  // Choisir une cible aléatoire
  while (!cibleTrouvee) {
    cible->ligne = rand() % hauteur;
    cible->col = rand() % largeur;
    if (grille[cible->ligne][cible->col] >= 'A' &&
        grille[cible->ligne][cible->col] <= 'R') {
      cible->signe = grille[cible->ligne][cible->col];
      cibleTrouvee = 1;
    }
  }

  printf("\nRobot sélectionné : %c\n", robot->signe);
  printf("Cible sélectionnée : %c\n", cible->signe);
}

void chronometrer(int secondes) {
  printf("Temps de réflexion : %d secondes\n", secondes);
  for (int i = secondes; i > 0; i--) {
    printf("%d\n", i);
    sleep(1);
    printf("\033[F\033[J");
  }
  clrscr();
  clrscr();
  clrscr();
  printf("Temps écoulé \n");
}
int MIN(int My_array[], int len) {
  int num = My_array[0];
  for (int i = 1; i < len; i++) {
    if (My_array[i] < num) {
      num = My_array[i];
    }
  }
  return num;
}

void choix_player(int **nmbMouv, int nb_Joueur, char **grille, Robot *robot,
                  Cible *cible, int *player) {
  *nmbMouv = malloc(nb_Joueur * sizeof(int *));
  for (int i = 0; i < nb_Joueur; i++) {
    printf("Combien de mouvement voulez vous faire joueur %d ?\n", i + 1);
    if (scanf("%d", &(*nmbMouv)[i]) != 1) {
      printf("Erreur de saisie. Veuillez saisir un entier.\n");
      exit(1);
    }
  }
  for (int i = 0; i < nb_Joueur; i++) {
    if ((*nmbMouv)[i] == MIN(*nmbMouv, nb_Joueur)) {
      *player = i;
      printf("Joueur %d à toi de jouer\n", i + 1);
    }
  }
}

int choix_direction(int direction) {
  int result;

  do {
    printf("Veuillez entrer une direction (NORD=1, EST=2, SUD=3, OUEST=4):\n");
    result = scanf("%d", &direction);

    if (result != 1) {
      printf("Entrée invalide. Veuillez entrer un nombre entier.\n");
      clearInputBuffer(); // Vider le buffer d'entrée
    } else if (direction < 1 || direction > 4) {
      printf("Entrée hors limites. Veuillez entrer un nombre entre 1 et 4.\n");
      clearInputBuffer(); // Vider le buffer d'entrée
    } else {
      break; // Entrée valide
    }
  } while (1);

  printf("La direction est %d\n", direction);
  return direction;
}

void deplacement(Robot *robot, Cible *cible, int direction, int *MurRandH,
                 int *MurRandV, MurCible *murHCible, MurCible *murVCible,
                 char **grille, int hauteur, int largeur) {
  int exligne = robot->ligne;
  int excol = robot->col;
  int obstacle = 0;

  switch (direction) {
  case 1: // Nord
    while (robot->ligne > 0) {
      robot->ligne--;
      obstacle = 0;
      for (int i = 0; i < 18; i++) {
        if ((robot->ligne == murHCible[i].ligne &&
             robot->col == murHCible[i].col) ||
            (robot->ligne == murVCible[i].ligne &&
             robot->col == murVCible[i].col)) {
          obstacle = 1;
          break;
        }
      }
      for (int i = 0; i < 4; i++) {
        if ((robot->ligne == MurRandH[i] && robot->col == 0) ||
          (robot->ligne == MurRandH[i] && robot->col == largeur - 1) ||
            (robot->col == MurRandV[i] && robot->ligne == 0) ||
          (robot->col == MurRandV[i] && robot->ligne == hauteur - 1)) {
          obstacle = 1;
          break;
        }
      }
      if (obstacle)
        break;
    }
    break;
  case 2: // Est
    while (robot->col < largeur - 1) {
      robot->col++;
      obstacle = 0;
      for (int i = 0; i < 18; i++) {
        if ((robot->ligne == murHCible[i].ligne &&
             robot->col == murHCible[i].col) ||
            (robot->ligne == murVCible[i].ligne &&
             robot->col == murVCible[i].col)) {
          obstacle = 1;
          break;
        }
      }
      for (int i = 0; i < 4; i++) {
          if ((robot->ligne == MurRandH[i] && robot->col == 0) ||
            (robot->ligne == MurRandH[i] && robot->col == largeur - 1) ||
              (robot->col == MurRandV[i] && robot->ligne == 0) ||
            (robot->col == MurRandV[i] && robot->ligne == hauteur - 1)) {
          obstacle = 1;
          break;
        }
      }
      if (obstacle)
        break;
    }
    break;
  case 3: // Sud
    while (robot->ligne < hauteur - 1) {
      robot->ligne++;
      obstacle = 0;
      for (int i = 0; i < 18; i++) {
        if ((robot->ligne == murHCible[i].ligne &&
             robot->col == murHCible[i].col) ||
            (robot->ligne == murVCible[i].ligne &&
             robot->col == murVCible[i].col)) {
          obstacle = 1;
          break;
        }
      }
      for (int i = 0; i < 4; i++) {
          if ((robot->ligne == MurRandH[i] - 1 && robot->col == 0) ||
            (robot->ligne == MurRandH[i] - 1 && robot->col == largeur - 1) ||
              (robot->col == MurRandV[i] && robot->ligne == 0) ||
            (robot->col == MurRandV[i] && robot->ligne == hauteur - 1)) {
          obstacle = 1;
          break;
        }
      }
      if (obstacle)
        break;
    }
    break;
  case 4: // Ouest
    while (robot->col > 0) {
      robot->col--;
      obstacle = 0;
      for (int i = 0; i < 18; i++) {
        if ((robot->ligne == murHCible[i].ligne &&
             robot->col == murHCible[i].col) ||
            (robot->ligne == murVCible[i].ligne &&
             robot->col == murVCible[i].col)) {
          obstacle = 1;
          break;
        }
      }
      for (int i = 0; i < 4; i++) {
          if ((robot->ligne == MurRandH[i] && robot->col == 0) ||
            (robot->ligne == MurRandH[i] && robot->col == largeur - 1) ||
              (robot->col == MurRandV[i] + 1 && robot->ligne == 0) ||
            (robot->col == MurRandV[i] + 1 && robot->ligne == hauteur - 1)) {
          obstacle = 1;
          break;
        }
      }
      if (obstacle)
        break;
    }
    break;
  default:
    printf("Erreur de déplacement\n");
    return;
  }

  // Mettre à jour la grille
  grille[exligne][excol] = ' '; // Vider l'ancienne position
  grille[robot->ligne][robot->col] =
      robot->signe; // Mettre le robot à la nouvelle position
}
