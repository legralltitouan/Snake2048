#include "structures.h"
#include "console.h"

/**
Fonction   : initialiserNcurses
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Initialise ncurses, le clavier et les paires de couleurs (TD R1.01)
Retour     : Aucun (procedure)
*/
void initialiserNcurses(void)
{
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    curs_set(0);

    if (has_colors()) {
        start_color();
        init_pair(PAIRE_DEFAUT,      COLOR_WHITE,  COLOR_BLACK);
        init_pair(PAIRE_TETE,        COLOR_BLACK,  COLOR_GREEN);
        init_pair(PAIRE_CORPS,       COLOR_BLACK,  COLOR_CYAN);
        init_pair(PAIRE_TUILE_2_4,   COLOR_BLACK,  COLOR_WHITE);
        init_pair(PAIRE_TUILE_8_16,  COLOR_BLACK,  COLOR_YELLOW);
        init_pair(PAIRE_TUILE_32,    COLOR_WHITE,  COLOR_MAGENTA);
        init_pair(PAIRE_TUILE_MAX,   COLOR_WHITE,  COLOR_RED);
        init_pair(PAIRE_TEXTE_JAUNE, COLOR_YELLOW, COLOR_BLACK);
        init_pair(PAIRE_TEXTE_VERT,  COLOR_GREEN,  COLOR_BLACK);
        init_pair(PAIRE_TEXTE_ROUGE, COLOR_RED,    COLOR_BLACK);
        bkgd(COLOR_PAIR(PAIRE_DEFAUT));
    }
}

/**
Fonction   : fermerNcurses
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Restaure le curseur et quitte proprement ncurses avec endwin()
Retour     : Aucun (procedure)
*/
void fermerNcurses(void)
{
    curs_set(1);
    endwin();
}

/**
Fonction   : attendreMs
Auteur     : Etudiant BUT1
Param      : millisecondes (duree de la pause en millisecondes)
Traitement : Suspend temporairement l'execution via napms de ncurses
Retour     : Aucun (procedure)
*/
void attendreMs(int millisecondes)
{
    napms(millisecondes);
}

/**
Fonction   : estToucheEntree
Auteur     : Etudiant BUT1
Param      : touche (code renvoye par getch ou wgetch)
Traitement : Verifie si la touche pressee correspond a la touche Entree
Retour     : 1 si c'est Entree, 0 sinon
*/
int estToucheEntree(int touche)
{
    if (touche == '\n' || touche == '\r' || touche == KEY_ENTER) {
        return 1;
    }
    return 0;
}

/**
Fonction   : lireCommandeNonBloquante
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Lit sans bloquer une touche au clavier (fleches KEY_UP.. ou action)
Retour     : Code de la commande reconnue, ou CMD_AUCUNE si aucune touche
*/
int lireCommandeNonBloquante(void)
{
    int touche;

    nodelay(stdscr, TRUE);
    touche = getch();
    nodelay(stdscr, FALSE);

    if (touche == ERR)       return CMD_AUCUNE;
    if (touche == KEY_UP)    return CMD_HAUT;
    if (touche == KEY_DOWN)  return CMD_BAS;
    if (touche == KEY_LEFT)  return CMD_GAUCHE;
    if (touche == KEY_RIGHT) return CMD_DROITE;

    if (touche == 's' || touche == 'S') return CMD_SAUVEGARDER;
    if (touche == 'p' || touche == 'P') return CMD_PAUSE;
    if (touche == 'q' || touche == 'Q' || touche == 27) return CMD_QUITTER;

    return CMD_AUCUNE;
}

/**
Fonction   : attendreCommandeDepart
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Attend une touche au lancement de la partie et detecte une fleche
Retour     : CMD_HAUT..CMD_DROITE si fleche pressee, CMD_QUITTER ou CMD_AUCUNE
*/
int attendreCommandeDepart(void)
{
    int touche;

    flushinp();
    nodelay(stdscr, FALSE);
    touche = getch();

    if (touche == KEY_UP)    return CMD_HAUT;
    if (touche == KEY_DOWN)  return CMD_BAS;
    if (touche == KEY_LEFT)  return CMD_GAUCHE;
    if (touche == KEY_RIGHT) return CMD_DROITE;
    if (touche == 'q' || touche == 'Q' || touche == 27) return CMD_QUITTER;

    return CMD_AUCUNE;
}

/**
Fonction   : attendreAppuiTouche
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Vide le tampon clavier puis attend un appui avec getch()
Retour     : Aucun (procedure)
*/
void attendreAppuiTouche(void)
{
    flushinp();
    nodelay(stdscr, FALSE);
    getch();
}
