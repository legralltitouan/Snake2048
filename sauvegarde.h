#ifndef SAUVEGARDE_H
#define SAUVEGARDE_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : sauvegarde.h
   Description: Prototypes des fonctions de sauvegarde et chargement texte
   ========================================================================= */

#include "structures.h"

int sauvegarderPartie(const Partie *p, const char *nomFichier);
int chargerPartie(Partie *p, const char *nomFichier);

#endif /* SAUVEGARDE_H */
