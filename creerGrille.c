#include "creerGrille.h"

#define CIBLES 18
#define ROBOTS 4

void clearInputBuffer() {
  int c;
  while ((c = getchar()) != '\n' && c != EOF)
    ;
}

// Fonction pour initialiser la grille
void initialiserGrille(char ***grille, int hauteur, int largeur) {
  *grille = (char **)malloc(hauteur * sizeof(char *));
  for (int i = 0; i < hauteur; i++) {
    (*grille)[i] = (char *)malloc(largeur * sizeof(char));
    for (int j = 0; j < largeur; j++) {
      (*grille)[i][j] = ' ';
    }
  }
}

// Fonction pour vérifier si une position est valide pour placer une cible ou un
// robot
int estPositionValide(char **grille, int hauteur, int largeur, int ligne,
                      int col) {
  if (ligne <= 0 || ligne >= hauteur - 1 || col <= 0 || col >= largeur - 1 ||
      grille[ligne][col] != ' ') {
    return 0;
  }
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (grille[ligne + i][col + j] != ' ') {
        return 0;
      }
    }
  }
  return 1;
}

// Fonction pour placer les cibles
void placerCibles(char **grille, int hauteur, int largeur, int CordCibles[][2],
                  MurCible murHCible[CIBLES], MurCible murVCible[CIBLES]) {
  for (int num = 0; num < CIBLES; num++) {
    int ligne = 0, col = 0;
    do {
      ligne = rand() % (hauteur - 2) + 1;
      col = rand() % (largeur - 2) + 1;
    } while (!estPositionValide(grille, hauteur, largeur, ligne, col));

    grille[ligne][col] = 'A' + num;
    CordCibles[num][0] = ligne;
    CordCibles[num][1] = col;

    int choix = rand() % 4;
    switch (choix) {
    case 0: // Haut Gauche
      murHCible[num].ligne = ligne;
      murHCible[num].col = col;
      murVCible[num].ligne = ligne;
      murVCible[num].col = col;
      break;
    case 1: // Haut Droite
      murHCible[num].ligne = ligne;
      murHCible[num].col = col;
      murVCible[num].ligne = ligne;
      murVCible[num].col = col + 1;
      break;
    case 2: // Bas Gauche
      murHCible[num].ligne = ligne + 1;
      murHCible[num].col = col;
      murVCible[num].ligne = ligne;
      murVCible[num].col = col;
      break;
    case 3: // Bas Droite
      murHCible[num].ligne = ligne + 1;
      murHCible[num].col = col;
      murVCible[num].ligne = ligne;
      murVCible[num].col = col + 1;
      break;
    default:
      printf("Erreur d'allocation MurCibles\n");
      break;
    }
  }
}

// Fonction pour placer les robots
void placerRobots(char **grille, int hauteur, int largeur) {
  for (int num = 0; num < ROBOTS; num++) {
    int ligne, col;
    do {
      ligne = rand() % (hauteur - 2) + 1;
      col = rand() % (largeur - 2) + 1;
    } while (!estPositionValide(grille, hauteur, largeur, ligne, col));
    grille[ligne][col] =
        '1' + num; // Utiliser des chiffres pour différencier les robots
  }
}

// Fonction pour afficher la grille
void afficherGrille(char **grille, int hauteur, int largeur, int *MurRandH,
                    int *MurRandV, MurCible murHCible[CIBLES],
                    MurCible murVCible[CIBLES]) {
  couleur("47");                                  // Fond blanc
  for (int ligne = 0; ligne < hauteur; ligne++) { // Correction ici
    // Afficher la bordure supérieure de chaque cellule
    for (int col = 0; col < largeur; col++) {
      if (ligne == 0) {
        couleur("31"); // Texte rouge pour la ligne supérieure
      } else {
        couleur("34"); // Texte bleu pour les lignes internes
      }
      if (col == 0 || col == largeur) {
        couleur("31"); // Texte rouge pour la bordure gauche et droite
      }
      printf("+");
      if (ligne == 0) {
        couleur("31"); // Texte rouge pour la ligne supérieure
      } else if (ligne == MurRandH[0] && col == 0 ||
                 ligne == MurRandH[1] && col == 0 ||
                 ligne == MurRandH[2] && col == largeur - 1 ||
                 ligne == MurRandH[3] && col == largeur - 1) {
        couleur("31"); // Texte rouge pour les 4 murs horizontaux Rand
      } else {
        couleur("34"); // Texte bleu pour les lignes internes
      }
      for (int i = 0; i < CIBLES; i++) {
        if (murHCible[i].ligne == ligne && murHCible[i].col == col) {
          couleur("31"); // Texte rouge pour murs cibles
        }
      }
      printf("---");
    }
    couleur("31"); // Texte rouge pour la ligne supérieure
    printf("+\n");

    // Afficher le contenu des cellules
    for (int col = 0; col < largeur; col++) {
      if (col == 0) {
        couleur("31"); // Texte rouge pour la bordure gauche et droite
      } else if (ligne == 0 && col == MurRandV[0] ||
                 ligne == 0 && col == MurRandV[1] ||
                 ligne == hauteur - 1 && col == MurRandV[2] ||
                 ligne == hauteur - 1 && col == MurRandV[3]) {
        couleur("31"); // Texte rouge pour les 4 murs verticaux Rand
      } else {
        couleur("30"); // Texte noir pour le contenu des cellules
      }
      for (int i = 0; i < CIBLES; i++) {
        if (murVCible[i].col == col && murVCible[i].ligne == ligne) {
          couleur("31"); // Texte rouge pour colonnes cibles
        }
      }
      printf("|");
      if (grille[ligne][col] == ' ') {
        printf("   "); // Espace pour les murs internes
      } else {
        couleur("31");
        printf(" %c ", grille[ligne][col]); // Contenu des cellules
      }
    }
    couleur("31"); // Texte rouge pour la bordure gauche et droite
    printf("|\n");
  }
  // Afficher la bordure inférieure de la grille
  for (int col = 0; col < largeur; col++) {
    couleur("31"); // Texte rouge pour la ligne inférieure
    printf("+---");
  }
  printf("+\n");
  couleur("0");
}



