#ifndef SERPENT_H
#define SERPENT_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : serpent.h
   Description: Prototypes des fonctions liees au serpent, collisions et fusions
   ========================================================================= */

#include "structures.h"

void placerSerpentAleatoire(Partie *p);
void calculerProchainePosition(int lig, int col, int direction, int *nouvLig, int *nouvCol);
int estDirectionValide(const Serpent *s, int nouvelleDirection);
int estCollisionBord(int ligne, int colonne, int taille);
int estCollisionCorps(const Serpent *s, int ligne, int colonne, int ignorerQueue);
void ajouterSegmentSerpent(Serpent *s, int ligne, int colonne, int valeur);
int trouverIndiceFusion(const Serpent *s);
int fusionnerSegmentsConsecutifs(Partie *p);
void mettreAJourValeurMax(Partie *p);
int aucunDeplacementPossible(const Partie *p);

#endif /* SERPENT_H */
