#include <stdlib.h>
#include "grille.h"

/*
Met toutes les cases de la grille de jeu a zero (aucune tuile)
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

/*
Recherche si un segment du serpent occupe la case (ligne, colonne)
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

/*
Compte les cases qui ne contiennent ni tuile ni segment du serpent
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

/*
Compte le nombre de tuiles numeriques presentes sur la grille
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

/*
Tire une puissance de 2 aleatoire entre 2 et 512 (hors 1024 et 2048)
*/
int tirerValeurTuileAleatoire(void)
{
    int tirage = rand() % 100;

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

/*
Place une tuile de valeur aleatoire sur une case libre choisie au hasard
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

/*
Genere une nouvelle tuile apres un deplacement reussi sans saturer le plateau
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

/*
Genere plusieurs tuiles aleatoires sur la grille au debut de la partie
*/
void genererTuilesInitiales(Partie *p)
{
    int nbInitial = (p->taille / 2) + 2;
    int i;

    for (i = 0; i < nbInitial; i++) {
        placerUneTuileAleatoire(p);
    }
}
