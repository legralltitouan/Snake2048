#ifndef JEU_H
#define JEU_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : jeu.h
   Description: Prototypes du moteur principal d'une partie de Snake 2048
   ========================================================================= */

#include "structures.h"

void initialiserNouvellePartie(Partie *p, int taille);
int verifierVictoire(const Partie *p);
void deplacerSerpentUnPas(Partie *p);
void jouerPartie(Partie *p);

#endif /* JEU_H */
