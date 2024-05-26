#ifndef Grille_h
#define Grille_h

#include "couleur.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define ROBOTS 4
#define CIBLES 18

typedef struct {
  int ligne;
  int col;
} MurInterdit;

typedef struct {
  int ligne;
  int col;
} MurCible;

void clearInputBuffer();

void initialiserGrille(char ***grille, int hauteur, int largeur);

void placerCibles(char **grille, int hauteur, int largeur, int CordCibles[][2],
                  MurCible murHCible[CIBLES], MurCible murVCible[CIBLES]);

void placerRobots(char **grille, int hauteur, int largeur);

void afficherGrille(char **grille, int hauteur, int largeur, int *MurRandH,
                    int *MurRandV, MurCible murHCible[CIBLES], MurCible murVCible[CIBLES]);

int estPositionValide(char **grille, int hauteur, int largeur, int ligne,
                      int col);

#endif
