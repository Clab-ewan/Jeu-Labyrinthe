#ifndef Interface_h
#define Interface_h

#include "couleur.h"

#include "creerGrille.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

typedef struct {
  int ligne;
  int col;
  char signe;
} Robot;

typedef struct {
  int ligne;
  int col;
  char signe;
} Cible;

void NombreJoueurs(int *nb_joueur);
void choisirRobotCible(char **grille, int hauteur, int largeur, Robot *robot,
                       Cible *cible);
void chronometrer(int duree_chrono);
int choixdifficulte(int niveau_difficulte);
void choix_player(int **nmbMouv, int m_bJoueur, char **grille, Robot *robot,
                  Cible *cible, int *player);
int MIN(int My_array[], int len);

void deplacement(Robot *robot, Cible *cible, int direction, int *MurRandH, int *MurRandV, MurCible *murHCible, MurCible *murVCible, char **grille, int hauteur, int largeur);

int choix_direction();

#endif



