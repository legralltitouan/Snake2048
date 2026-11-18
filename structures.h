#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <time.h>

#define TAILLE_MIN        5
#define TAILLE_MAX        10
#define TAILLE_DEFAUT     10
#define MAX_SEGMENTS      (TAILLE_MAX * TAILLE_MAX)

#define OBJECTIF_VICTOIRE 2048
#define DELAI_PAS_MS      450
#define TRANCHE_MS        50
#define FICHIER_SAUVEGARDE "sauvegarde.txt"

#define DIR_HAUT          0
#define DIR_BAS           1
#define DIR_GAUCHE        2
#define DIR_DROITE        3

#define CMD_AUCUNE        0
#define CMD_HAUT          1
#define CMD_BAS           2
#define CMD_GAUCHE        3
#define CMD_DROITE        4
#define CMD_SAUVEGARDER   5
#define CMD_PAUSE         6
#define CMD_QUITTER       7

#define ETAT_EN_COURS       0
#define ETAT_VICTOIRE       1
#define ETAT_DEFAITE_BORD   2
#define ETAT_DEFAITE_CORPS  3
#define ETAT_DEFAITE_BLOQUE 4
#define ETAT_RETOUR_MENU    5

typedef struct {
    int ligne;
    int colonne;
    int valeur;
} Segment;

typedef struct {
    Segment corps[MAX_SEGMENTS];
    int longueur;
    int direction;
} Serpent;

typedef struct {
    int grille[TAILLE_MAX][TAILLE_MAX];
    int taille;
    Serpent serpent;
    int score;
    int valeurMax;
    int etat;
    time_t startTime;
    int secondesCumulees;
} Partie;

#endif
