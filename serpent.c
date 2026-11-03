#include <stdlib.h>
#include "serpent.h"

/**
Fonction   : placerSerpentAleatoire
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie a initialiser)
Traitement : Place aleatoirement le serpent au debut de la partie loin des bords
Retour     : Aucun (procedure)
*/
void placerSerpentAleatoire(Partie *p)
{
    int lig = 1 + (rand() % (p->taille - 2));
    int col = 1 + (rand() % (p->taille - 2));

    p->serpent.longueur = 1;
    p->serpent.corps[0].ligne = lig;
    p->serpent.corps[0].colonne = col;
    p->serpent.corps[0].valeur = 2;

    /* Choix d'une direction initiale vers le cote le plus degage */
    if (rand() % 2 == 0) {
        p->serpent.direction = (col < p->taille / 2) ? DIR_DROITE : DIR_GAUCHE;
    } else {
        p->serpent.direction = (lig < p->taille / 2) ? DIR_BAS : DIR_HAUT;
    }

    p->valeurMax = 2;
}

/**
Fonction   : calculerProchainePosition
Auteur     : Etudiant BUT1
Param      : lig, col (position actuelle), direction, nouvLig, nouvCol (pointeurs resultat)
Traitement : Calcule les coordonnees de la case suivante selon la direction donnee
Retour     : Aucun (procedure modifiant nouvLig et nouvCol par adresse)
*/
void calculerProchainePosition(int lig, int col, int direction, int *nouvLig, int *nouvCol)
{
    *nouvLig = lig;
    *nouvCol = col;

    if (direction == DIR_HAUT) {
        (*nouvLig)--;
    } else if (direction == DIR_BAS) {
        (*nouvLig)++;
    } else if (direction == DIR_GAUCHE) {
        (*nouvCol)--;
    } else if (direction == DIR_DROITE) {
        (*nouvCol)++;
    }
}

/**
Fonction   : estDirectionValide
Auteur     : Etudiant BUT1
Param      : s (pointeur constant vers le Serpent), nouvelleDirection (direction souhaitee)
Traitement : Verifie que la direction existe et n'effectue pas un demi-tour sur le cou
Retour     : 1 si le changement de direction est valide, 0 sinon
*/
int estDirectionValide(const Serpent *s, int nouvelleDirection)
{
    int testLig;
    int testCol;

    if (nouvelleDirection < DIR_HAUT || nouvelleDirection > DIR_DROITE) {
        return 0;
    }

    if (s->longueur >= 2) {
        calculerProchainePosition(s->corps[0].ligne, s->corps[0].colonne,
                                  nouvelleDirection, &testLig, &testCol);
        if (testLig == s->corps[1].ligne && testCol == s->corps[1].colonne) {
            return 0;
        }
    }
    return 1;
}

/**
Fonction   : estCollisionBord
Auteur     : Etudiant BUT1
Param      : ligne, colonne (coordonnees a tester), taille (dimension de la grille)
Traitement : Verifie si les coordonnees sortent des limites de la grille de jeu
Retour     : 1 s'il y a collision avec un bord, 0 sinon
*/
int estCollisionBord(int ligne, int colonne, int taille)
{
    if (ligne < 0 || ligne >= taille || colonne < 0 || colonne >= taille) {
        return 1;
    }
    return 0;
}

/**
Fonction   : estCollisionCorps
Auteur     : Etudiant BUT1
Param      : s (pointeur Serpent), ligne, colonne, ignorerQueue (1 si la queue avance)
Traitement : Verifie si la case (ligne, colonne) percute un segment du serpent
Retour     : 1 s'il y a collision avec le corps du serpent, 0 sinon
*/
int estCollisionCorps(const Serpent *s, int ligne, int colonne, int ignorerQueue)
{
    int limite = s->longueur;
    int i;

    if (ignorerQueue != 0 && s->longueur > 0) {
        limite = s->longueur - 1;
    }

    for (i = 0; i < limite; i++) {
        if (s->corps[i].ligne == ligne && s->corps[i].colonne == colonne) {
            return 1;
        }
    }
    return 0;
}

/**
Fonction   : ajouterSegmentSerpent
Auteur     : Etudiant BUT1
Param      : s (pointeur vers le Serpent), ligne, colonne (position), valeur (tuile)
Traitement : Ajoute un nouveau segment a la queue du serpent apres ingestion d'une tuile
Retour     : Aucun (procedure)
*/
void ajouterSegmentSerpent(Serpent *s, int ligne, int colonne, int valeur)
{
    if (s->longueur < MAX_SEGMENTS) {
        s->corps[s->longueur].ligne = ligne;
        s->corps[s->longueur].colonne = colonne;
        s->corps[s->longueur].valeur = valeur;
        s->longueur++;
    }
}

/**
Fonction   : trouverIndiceFusion
Auteur     : Etudiant BUT1
Param      : s (pointeur constant vers le Serpent)
Traitement : Recherche deux segments consecutifs possedant la meme valeur numerique
Retour     : Indice du premier des deux segments a fusionner, ou -1 si aucune fusion
*/
int trouverIndiceFusion(const Serpent *s)
{
    int i;

    for (i = s->longueur - 2; i >= 0; i--) {
        if (s->corps[i].valeur == s->corps[i + 1].valeur) {
            return i;
        }
    }
    return -1;
}

/**
Fonction   : mettreAJourValeurMax
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie en cours)
Traitement : Parcourt le serpent pour actualiser la valeur maximale obtenue
Retour     : Aucun (procedure)
*/
void mettreAJourValeurMax(Partie *p)
{
    int i;

    for (i = 0; i < p->serpent.longueur; i++) {
        if (p->serpent.corps[i].valeur > p->valeurMax) {
            p->valeurMax = p->serpent.corps[i].valeur;
        }
    }
}

/**
Fonction   : fusionnerSegmentsConsecutifs
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie a mettre a jour)
Traitement : Realise toutes les fusions automatiques en chaine des segments identiques
Retour     : Nombre total de fusions effectuees lors de cet appel
*/
int fusionnerSegmentsConsecutifs(Partie *p)
{
    Serpent *s = &p->serpent;
    int idx;
    int j;
    int nbFusions = 0;

    idx = trouverIndiceFusion(s);
    while (idx != -1) {
        /* Doublement de la valeur du segment et ajout au score */
        s->corps[idx].valeur = s->corps[idx].valeur * 2;
        p->score += s->corps[idx].valeur;

        /* Decalage des valeurs suivantes pour garder un corps continu */
        for (j = idx + 1; j < s->longueur - 1; j++) {
            s->corps[j].valeur = s->corps[j + 1].valeur;
        }
        s->longueur--;
        nbFusions++;

        idx = trouverIndiceFusion(s);
    }

    mettreAJourValeurMax(p);
    return nbFusions;
}

/**
Fonction   : aucunDeplacementPossible
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie en cours)
Traitement : Teste les 4 directions autour de la tete pour savoir si le serpent est bloque
Retour     : 1 si aucun deplacement valide sans collision n'existe, 0 sinon
*/
int aucunDeplacementPossible(const Partie *p)
{
    int dir;
    int testLig;
    int testCol;
    int ignorerQueue;

    for (dir = DIR_HAUT; dir <= DIR_DROITE; dir++) {
        if (estDirectionValide(&p->serpent, dir)) {
            calculerProchainePosition(p->serpent.corps[0].ligne,
                                      p->serpent.corps[0].colonne,
                                      dir, &testLig, &testCol);
            if (!estCollisionBord(testLig, testCol, p->taille)) {
                ignorerQueue = (p->grille[testLig][testCol] == 0) ? 1 : 0;
                if (!estCollisionCorps(&p->serpent, testLig, testCol, ignorerQueue)) {
                    return 0;
                }
            }
        }
    }
    return 1;
}
