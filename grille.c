#include <stdlib.h>
#include "grille.h"

/**
Fonction   : viderGrille
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la structure Partie a initialiser)
Traitement : Met toutes les cases de la grille de jeu a zero (aucune tuile)
Retour     : Aucun (procedure)
*/
void viderGrille(Partie *p)
{
    int lig;
    int col;

    for (lig = 0; lig < TAILLE_MAX; lig++) {
        for (col = 0; col < TAILLE_MAX; col++) {
            p->grille[lig][col] = 0;
        }
    }
}

/**
Fonction   : indiceSegmentSurCase
Auteur     : Etudiant BUT1
Param      : s (pointeur constant vers le Serpent), ligne, colonne (coordonnees)
Traitement : Recherche si un segment du serpent occupe la case (ligne, colonne)
Retour     : Indice du segment (0 = tete, >=1 = corps), ou -1 si la case est libre
*/
int indiceSegmentSurCase(const Serpent *s, int ligne, int colonne)
{
    int i;

    for (i = 0; i < s->longueur; i++) {
        if (s->corps[i].ligne == ligne && s->corps[i].colonne == colonne) {
            return i;
        }
    }
    return -1;
}

/**
Fonction   : compterCasesVides
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie en cours)
Traitement : Compte les cases qui ne contiennent ni tuile ni segment du serpent
Retour     : Nombre total de cases completement libres sur la grille
*/
int compterCasesVides(const Partie *p)
{
    int lig;
    int col;
    int compteur = 0;

    for (lig = 0; lig < p->taille; lig++) {
        for (col = 0; col < p->taille; col++) {
            if (p->grille[lig][col] == 0 &&
                indiceSegmentSurCase(&p->serpent, lig, col) == -1) {
                compteur++;
            }
        }
    }
    return compteur;
}

/**
Fonction   : compterTuilesSurGrille
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie en cours)
Traitement : Compte le nombre de tuiles numeriques presentes sur la grille
Retour     : Nombre de tuiles actuellement posees sur le plateau
*/
int compterTuilesSurGrille(const Partie *p)
{
    int lig;
    int col;
    int nbTuiles = 0;

    for (lig = 0; lig < p->taille; lig++) {
        for (col = 0; col < p->taille; col++) {
            if (p->grille[lig][col] > 0) {
                nbTuiles++;
            }
        }
    }
    return nbTuiles;
}

/**
Fonction   : tirerValeurTuileAleatoire
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Tire une puissance de 2 aleatoire entre 2 et 512 (hors 1024 et 2048)
Retour     : Valeur numerique de la nouvelle tuile (2, 4, 8, ..., 512)
*/
int tirerValeurTuileAleatoire(void)
{
    int tirage = rand() % 100;

    /* Toutes les puissances de 2 sont possibles sauf 1024 et 2048 */
    if (tirage < 40) return 2;
    if (tirage < 68) return 4;
    if (tirage < 82) return 8;
    if (tirage < 90) return 16;
    if (tirage < 94) return 32;
    if (tirage < 97) return 64;
    if (tirage < 98) return 128;
    if (tirage < 99) return 256;
    return 512;
}

/**
Fonction   : placerUneTuileAleatoire
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie a modifier)
Traitement : Place une tuile de valeur aleatoire sur une case libre choisie au hasard
Retour     : 1 si la tuile a pu etre placee, 0 s'il n'y a plus de case libre
*/
int placerUneTuileAleatoire(Partie *p)
{
    int nbVides = compterCasesVides(p);
    int choixCase;
    int indexCourant = 0;
    int lig;
    int col;

    if (nbVides <= 0) {
        return 0;
    }

    choixCase = rand() % nbVides;

    for (lig = 0; lig < p->taille; lig++) {
        for (col = 0; col < p->taille; col++) {
            if (p->grille[lig][col] == 0 &&
                indiceSegmentSurCase(&p->serpent, lig, col) == -1) {
                if (indexCourant == choixCase) {
                    p->grille[lig][col] = tirerValeurTuileAleatoire();
                    return 1;
                }
                indexCourant++;
            }
        }
    }
    return 0;
}

/**
Fonction   : genererTuileApresDeplacement
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie en cours)
Traitement : Genere une nouvelle tuile apres un deplacement reussi sans saturer le plateau
Retour     : Aucun (procedure)
*/
void genererTuileApresDeplacement(Partie *p)
{
    int maxTuilesSimultanees = (p->taille * p->taille) / 3;

    if (maxTuilesSimultanees < 4) {
        maxTuilesSimultanees = 4;
    }

    if (compterTuilesSurGrille(p) < maxTuilesSimultanees) {
        placerUneTuileAleatoire(p);
    }
}

/**
Fonction   : genererTuilesInitiales
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie en cours d'initialisation)
Traitement : Genere plusieurs tuiles aleatoires sur la grille au debut de la partie
Retour     : Aucun (procedure)
*/
void genererTuilesInitiales(Partie *p)
{
    int nbInitial = (p->taille / 2) + 2;
    int i;

    for (i = 0; i < nbInitial; i++) {
        placerUneTuileAleatoire(p);
    }
}
