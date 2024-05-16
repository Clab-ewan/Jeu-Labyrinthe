#include <stdio.h>

#include <time.h>

#include "interface.h"
#include "creerGrille.h"




int main(){
    srand(time(NULL));
    int joueur = nb_joueur(joueur);
    
    creerGrille(grille);
    placerMursBords(grille);
    placerMursPerpendiculaires(grille);
    placerCibles(grille);
    placerRobots(grille);
    afficherGrille(grille);

    Position robot, cible;
    choisirRobotCible(grille, &robot, &cible);
   
    int niveau_difficulte = 2;
    int duree_chrono;
    switch (niveau_difficulte) {
        case 1:
            duree_chrono = 10;
            break;
        case 2:
            duree_chrono = 20;
            break;
        case 3:
            duree_chrono = 30;
            break;
        default:
            duree_chrono = 20;
    }
    chronometrer(duree_chrono);
    
    demanderMouvements(grille, &robot);

    freeGrille(grille);

    return 0;
}




    return 0;
}
