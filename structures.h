#ifndef STRUCTURES_H
#define STRUCTURES_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : structures.h
   Description: Constantes et structures de donnees principales du jeu
   ========================================================================= */

#include <time.h>

/* Dimensions de la grille (minimum 5x5, maximum 10x10, 10x10 par defaut) */
#define TAILLE_MIN        5
#define TAILLE_MAX        10
#define TAILLE_DEFAUT     10
#define MAX_SEGMENTS      (TAILLE_MAX * TAILLE_MAX)

/* Parametres du jeu */
#define OBJECTIF_VICTOIRE 2048
#define DELAI_PAS_MS      450
#define TRANCHE_MS        50
#define FICHIER_SAUVEGARDE "sauvegarde.txt"

/* Directions de deplacement du serpent */
#define DIR_HAUT          0
#define DIR_BAS           1
#define DIR_GAUCHE        2
#define DIR_DROITE        3

/* Commandes clavier reconnues en cours de partie */
#define CMD_AUCUNE        0
#define CMD_HAUT          1
#define CMD_BAS           2
#define CMD_GAUCHE        3
#define CMD_DROITE        4
#define CMD_SAUVEGARDER   5
#define CMD_PAUSE         6
#define CMD_QUITTER       7

/* Etats possibles d'une partie */
#define ETAT_EN_COURS       0
#define ETAT_VICTOIRE       1
#define ETAT_DEFAITE_BORD   2
#define ETAT_DEFAITE_CORPS  3
#define ETAT_DEFAITE_BLOQUE 4
#define ETAT_RETOUR_MENU    5

/* Paires de couleurs ncurses (inspirees du TD R1.01 ncurses) */
#define PAIRE_DEFAUT      1  /* Texte blanc sur fond noir             */
#define PAIRE_TETE        2  /* Case tete du serpent : fond VERT      */
#define PAIRE_CORPS       3  /* Case corps du serpent : fond CYAN     */
#define PAIRE_TUILE_2_4   4  /* Tuiles 2 et 4 : fond BLANC            */
#define PAIRE_TUILE_8_16  5  /* Tuiles 8 et 16 : fond JAUNE           */
#define PAIRE_TUILE_32    6  /* Tuiles 32 a 128 : fond MAGENTA        */
#define PAIRE_TUILE_MAX   7  /* Tuiles >= 256 et alertes : fond ROUGE */
#define PAIRE_TEXTE_JAUNE 8  /* Texte jaune sur fond noir (infos)     */
#define PAIRE_TEXTE_VERT  9  /* Texte vert sur fond noir (messages)   */
#define PAIRE_TEXTE_ROUGE 10 /* Texte rouge sur fond noir (erreurs)   */

/* Structure representant un segment du serpent sur la grille */
typedef struct {
    int ligne;
    int colonne;
    int valeur;
} Segment;

/* Structure representant le serpent complet */
typedef struct {
    Segment corps[MAX_SEGMENTS]; /* corps[0] correspond a la tete du serpent */
    int longueur;                /* Nombre actuel de segments du serpent     */
    int direction;               /* Direction courante (DIR_HAUT, etc.)      */
} Serpent;

/* Structure regroupant toutes les informations d'une partie */
typedef struct {
    int grille[TAILLE_MAX][TAILLE_MAX]; /* Tuiles sur le plateau (0 = vide) */
    int taille;                         /* Taille choisie (de 5 a 10)       */
    Serpent serpent;                    /* Le serpent dirige par le joueur  */
    int score;                          /* Score total de la partie         */
    int valeurMax;                      /* Plus grande valeur sur le serpent*/
    int etat;                           /* Etat courant (ETAT_EN_COURS...)  */
    time_t startTime;                   /* Temps de depart (TD Exercice 5)  */
    int secondesCumulees;               /* Temps deja ecoule avant reprise  */
} Partie;

#endif /* STRUCTURES_H */
