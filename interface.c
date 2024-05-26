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

int MIN(int tab[], int taille) {
  int num = tab[0];
  for (int i = 1; i < taille; i++) {
    if (tab[i] < num) {
      num = tab[i];
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

  switch (direction) {
  case 1: // Nord
    while (robot->ligne > 0) {
      if (robot->ligne == MurRandH[0] && robot->col == 0 ||
          robot->ligne == MurRandH[1] && robot->col == 0 ||
          robot->ligne == MurRandH[2] && robot->col == largeur - 1 ||
          robot->ligne == MurRandH[3] && robot->col == largeur - 1) {
        obstacle = 1;
        break;
      }
      robot->ligne--;
      obstacle = 0;
      for (int i = 0; i < CIBLES; i++) { // déplacement MurH vers le Nord
        if (robot->ligne == murHCible[i].ligne &&
            robot->col == murHCible[i].col) {
          obstacle = 1;
          break;
        }
      }
      if (robot->ligne == MurRandH[0] && robot->col == 0 ||
          robot->ligne == MurRandH[1] && robot->col == 0 ||
          robot->ligne == MurRandH[2] && robot->col == largeur - 1 ||
          robot->ligne == MurRandH[3] && robot->col == largeur - 1) {
        obstacle = 1;
        break;
      }
      if (grille[robot->ligne][robot->col] == '1' ||
          grille[robot->ligne][robot->col] == '2' ||
          grille[robot->ligne][robot->col] == '3' ||
          grille[robot->ligne][robot->col] == '4') {
        obstacle = 1;
        robot->ligne++;
        break;
      }
      if (obstacle || grille[robot->ligne][robot->col] != ' ')
        break;
    }
    break;
  case 2: // Est
    while (robot->col < largeur - 1) {
      robot->col++;
      obstacle = 0;
      for (int i = 0; i < CIBLES; i++) { // déplacement pour murV vers l'Est
        if (robot->ligne == murVCible[i].ligne &&
            robot->col == murVCible[i].col) {
          obstacle = 1;
          robot->col--;
          break;
        }
      }
      if (robot->ligne == 0 && robot->col == MurRandV[0] ||
          robot->ligne == 0 && robot->col == MurRandV[1] ||
          robot->ligne == hauteur - 1 && robot->col == MurRandV[2] ||
          robot->ligne == hauteur - 1 && robot->col == MurRandV[3]) {
        obstacle = 1;
        robot->col--;
        break;
      }
      if (grille[robot->ligne][robot->col] == '1' ||
          grille[robot->ligne][robot->col] == '2' ||
          grille[robot->ligne][robot->col] == '3' ||
          grille[robot->ligne][robot->col] == '4') {
        obstacle = 1;
        robot->col--;
        break;
      }
      if (obstacle || grille[robot->ligne][robot->col] != ' ')
        break;
    }
    break;
  case 3: // Sud
    while (robot->ligne < hauteur - 1) {
      robot->ligne++;
      obstacle = 0;
      for (int i = 0; i < CIBLES; i++) { // déplacement MurH vers le Sud
        if (robot->ligne == murHCible[i].ligne &&
            robot->col == murHCible[i].col) {
          obstacle = 1;
          robot->ligne--;
          break;
        }
      }
      if (robot->ligne == MurRandH[0] && robot->col == 0 ||
          robot->ligne == MurRandH[1] && robot->col == 0 ||
          robot->ligne == MurRandH[2] && robot->col == largeur - 1 ||
          robot->ligne == MurRandH[3] && robot->col == largeur - 1) {
        obstacle = 1;
        robot->ligne--;
        break;
      }
      if (grille[robot->ligne][robot->col] == '1' ||
          grille[robot->ligne][robot->col] == '2' ||
          grille[robot->ligne][robot->col] == '3' ||
          grille[robot->ligne][robot->col] == '4') {
        obstacle = 1;
        robot->ligne--;
        break;
      }
      if (obstacle || grille[robot->ligne][robot->col] != ' ')
        break;
    }
    break;
  case 4: // Ouest
    while (robot->col > 0) {
      if (robot->ligne == 0 && robot->col == MurRandV[0] ||
          robot->ligne == 0 && robot->col == MurRandV[1] ||
          robot->ligne == hauteur - 1 && robot->col == MurRandV[2] ||
          robot->ligne == hauteur - 1 && robot->col == MurRandV[3]) {
        obstacle = 1;
        break;
      }
      robot->col--;
      obstacle = 0;
      for (int i = 0; i < CIBLES; i++) { // déplacement pour murV vers l'Ouest
        if (robot->ligne == murVCible[i].ligne &&
            robot->col == murVCible[i].col) {
          obstacle = 1;
          break;
        }
      }
      if (robot->ligne == 0 && robot->col == MurRandV[0] ||
          robot->ligne == 0 && robot->col == MurRandV[1] ||
          robot->ligne == hauteur - 1 && robot->col == MurRandV[2] ||
          robot->ligne == hauteur - 1 && robot->col == MurRandV[3]) {
        obstacle = 1;
        break;
      }
      if (grille[robot->ligne][robot->col] == '1' ||
          grille[robot->ligne][robot->col] == '2' ||
          grille[robot->ligne][robot->col] == '3' ||
          grille[robot->ligne][robot->col] == '4') {
        obstacle = 1;
        robot->col++;
        break;
      }
      if (obstacle || grille[robot->ligne][robot->col] != ' ')
        break;
    }
    break;
  default:
    printf("Erreur de déplacement\n");
    return;
  }
  // Sauvegarder le nouveau caractère initial de la position où le robot arrive
  robot->tampon = grille[robot->ligne][robot->col];

  // Placer le signe du robot sur la nouvelle position
  grille[robot->ligne][robot->col] = robot->signe;
}

void Points(int *pointsJoueurs, int nb_joueurs, int joueurActuel, int nb_deplacements, int nb_deplacements_effectues, int robotAtteintCible) {

    if (robotAtteintCible) { 
        if (nb_deplacements_effectues == nb_deplacements) {//si le joueur a atteint la cible avec le nombre de mouvements prévus
            pointsJoueurs[joueurActuel] += 2;
        } 
        else if (nb_deplacements_effectues < nb_deplacements) {//si le joueur a atteint la cible avec moins de mouvements que prévus
            pointsJoueurs[joueurActuel] -= 1;
        }
    } 
    else {
        for (int i = 0; i < nb_joueurs; i++) {//si le joueur n'atteint pas la cible avec le nombre de mouvements prévus
            if (i != joueurActuel) {
                pointsJoueurs[i] += 1;
            }
        }
    }
}

void JoueurTour(char **grille, int hauteur, int largeur, Robot *robot, Cible *cible, int *MurRandH, int *MurRandV, MurCible *murHCible, MurCible *murVCible, int *nmbMouv, int joueurActuel, int *pointsJoueurs)
{

  int direction;
  int deplacementsEffectues = 0;
  int robotAtteintCible = 0;
  while (deplacementsEffectues < nmbMouv[joueurActuel]) {//tant que le joueur n'a pas atteint le nombre de mouvements prévus
    direction = choix_direction(direction);//demande la direction
      deplacement(robot, cible, direction, MurRandH, MurRandV, murHCible, murVCible, grille,hauteur, largeur);//déplace le robot 
      deplacementsEffectues++;//incrémente le nombre de déplacements effectués

    if (robot->ligne == cible->ligne && robot->col == cible->col) {
      robotAtteintCible = 1;//si le robot a atteint la cible
      break;
    }
       afficherGrille(grille, hauteur, largeur, MurRandH, MurRandV, murHCible, murVCible);
  }

  Points(pointsJoueurs, 4, joueurActuel, nmbMouv[joueurActuel], deplacementsEffectues, robotAtteintCible);//actualise le nombre de points
  }

void AfficherGagnant(int *pointsJoueurs, int nb_joueurs) {
    int maxPoints = pointsJoueurs[0];
    int gagnant = 0;
    int egalite = 0;

    for (int i = 1; i < nb_joueurs; i++) {
        if (pointsJoueurs[i] > maxPoints) {
            maxPoints = pointsJoueurs[i];
            gagnant = i;
            egalite = 0;
        } else if (pointsJoueurs[i] == maxPoints) {
            egalite = 1;
        }
    }

    if (egalite) {
        printf("Il y a une égalité entre plusieurs joueurs !\n");
    } else {
        printf("Le gagnant est le joueur %d avec %d points !\n", gagnant + 1, maxPoints);
    }
}
 
  
 
