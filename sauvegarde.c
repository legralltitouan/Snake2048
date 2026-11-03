#include <stdio.h>
#include <time.h>
#include "sauvegarde.h"
#include "grille.h"

/**
Fonction   : sauvegarderPartie
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie), nomFichier (nom du fichier texte)
Traitement : Ecrit les donnees de la partie en cours dans un fichier avec fprintf
Retour     : 1 si la sauvegarde a reussi, 0 si l'ouverture du fichier a echoue
*/
int sauvegarderPartie(const Partie *p, const char *nomFichier)
{
    FILE *f;
    int tempsTotal;
    int i, lig, col;

    f = fopen(nomFichier, "w");
    if (f == NULL) {
        return 0;
    }

    tempsTotal = p->secondesCumulees + (int)difftime(time(NULL), p->startTime);

    /* Ecriture des parametres principaux de la partie */
    fprintf(f, "%d %d %d %d %d %d\n",
            p->taille, p->score, p->valeurMax,
            p->serpent.direction, p->serpent.longueur, tempsTotal);

    /* Ecriture des segments du serpent (ligne colonne valeur) */
    for (i = 0; i < p->serpent.longueur; i++) {
        fprintf(f, "%d %d %d\n",
                p->serpent.corps[i].ligne,
                p->serpent.corps[i].colonne,
                p->serpent.corps[i].valeur);
    }

    /* Ecriture de la grille des tuiles */
    for (lig = 0; lig < p->taille; lig++) {
        for (col = 0; col < p->taille; col++) {
            fprintf(f, "%d ", p->grille[lig][col]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
    return 1;
}

/**
Fonction   : chargerPartie
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie a remplir), nomFichier (nom du fichier texte)
Traitement : Recharge une partie sauvegardee depuis le fichier texte avec fscanf
Retour     : 1 si le chargement est valide, 0 si le fichier est absent ou incorrect
*/
int chargerPartie(Partie *p, const char *nomFichier)
{
    FILE *f;
    int i, lig, col;

    f = fopen(nomFichier, "r");
    if (f == NULL) {
        return 0;
    }

    viderGrille(p);

    if (fscanf(f, "%d %d %d %d %d %d",
               &p->taille, &p->score, &p->valeurMax,
               &p->serpent.direction, &p->serpent.longueur,
               &p->secondesCumulees) != 6) {
        fclose(f);
        return 0;
    }

    if (p->taille < TAILLE_MIN || p->taille > TAILLE_MAX ||
        p->serpent.longueur < 1 || p->serpent.longueur > (p->taille * p->taille)) {
        fclose(f);
        return 0;
    }

    for (i = 0; i < p->serpent.longueur; i++) {
        if (fscanf(f, "%d %d %d",
                   &p->serpent.corps[i].ligne,
                   &p->serpent.corps[i].colonne,
                   &p->serpent.corps[i].valeur) != 3) {
            fclose(f);
            return 0;
        }
    }

    for (lig = 0; lig < p->taille; lig++) {
        for (col = 0; col < p->taille; col++) {
            if (fscanf(f, "%d", &p->grille[lig][col]) != 1) {
                fclose(f);
                return 0;
            }
        }
    }

    p->startTime = time(NULL);
    p->etat = ETAT_EN_COURS;
    fclose(f);
    return 1;
}
