#ifndef Interface_h
    #define Interface_h

    #include <stdlib.h>
    #include <stdio.h>
    #include <time.h>
    #include <unistd.h>
    
   int nb_joueur(int nb_joueur);
   int choisir_niveau_difficulte(); // Pour choisir le niveau
   void chronometrer(int duree_chrono); // Chronométrer
   void demanderMouvements(Grille *grille, Position *robot);

    
#endif
