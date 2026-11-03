#include <stdlib.h>
#include <time.h>
#include "console.h"
#include "menu.h"

/**
Fonction   : main
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Initialise l'aleatoire et ncurses, lance le jeu puis ferme ncurses
Retour     : 0 (EXIT_SUCCESS) a la fermeture normale de l'application
*/
int main(void)
{
    srand((unsigned int)time(NULL));
    initialiserNcurses();
    lancerMenuPrincipal();
    fermerNcurses();
    return EXIT_SUCCESS;
}
