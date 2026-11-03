#ifndef GRILLE_H
#define GRILLE_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : grille.h
   Description: Prototypes des fonctions de gestion de la grille et des tuiles
   ========================================================================= */

#include "structures.h"

void viderGrille(Partie *p);
int indiceSegmentSurCase(const Serpent *s, int ligne, int colonne);
int compterCasesVides(const Partie *p);
int compterTuilesSurGrille(const Partie *p);
int tirerValeurTuileAleatoire(void);
int placerUneTuileAleatoire(Partie *p);
void genererTuileApresDeplacement(Partie *p);
void genererTuilesInitiales(Partie *p);

#endif /* GRILLE_H */
