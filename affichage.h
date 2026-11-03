#ifndef AFFICHAGE_H
#define AFFICHAGE_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : affichage.h
   Description: Prototypes des fonctions d'affichage en mode console
   ========================================================================= */

#include "structures.h"

void afficherPartie(const Partie *p, const char *messageInfo);
void afficherReglesDuJeu(void);
void afficherFinDePartie(const Partie *p);

#endif /* AFFICHAGE_H */
