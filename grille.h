#ifndef GRILLE_H
#define GRILLE_H
#include "structures.h"

void viderGrille(Partie *p);
int indiceSegmentSurCase(const Serpent *s, int ligne, int colonne);
int compterCasesVides(const Partie *p);
int compterTuilesSurGrille(const Partie *p);
int tirerValeurTuileAleatoire(void);
int placerUneTuileAleatoire(Partie *p);
void genererTuileApresDeplacement(Partie *p);
void genererTuilesInitiales(Partie *p);

#endif
