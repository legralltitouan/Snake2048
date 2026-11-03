#include "structures.h"
#include "menu.h"
#include "jeu.h"
#include "sauvegarde.h"
#include "affichage.h"
#include "console.h"

/**
Fonction   : dessinerFenetreTaille
Auteur     : Etudiant BUT1
Param      : fen (pointeur WINDOW), tailleCourante (taille entre 5 et 10)
Traitement : Dessine le contenu de la fenetre de choix de taille avec mvwprintw
Retour     : Aucun (procedure)
*/
static void dessinerFenetreTaille(WINDOW *fen, int tailleCourante)
{
    werase(fen);
    box(fen, ACS_VLINE, ACS_HLINE);

    wattron(fen, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvwprintw(fen, 1, 14, "TAILLE DE LA GRILLE DE JEU");
    wattroff(fen, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);

    mvwprintw(fen, 3, 4, "Grille de 5x5 a 10x10 (10x10 par defaut) :");

    wattron(fen, COLOR_PAIR(PAIRE_TETE) | A_BOLD);
    mvwprintw(fen, 5, 21, " < %2d x %-2d > ", tailleCourante, tailleCourante);
    wattroff(fen, COLOR_PAIR(PAIRE_TETE) | A_BOLD);

    if (tailleCourante == TAILLE_DEFAUT) {
        wattron(fen, COLOR_PAIR(PAIRE_TEXTE_VERT));
        mvwprintw(fen, 7, 18, "(Taille par defaut)");
        wattroff(fen, COLOR_PAIR(PAIRE_TEXTE_VERT));
    }

    mvwprintw(fen, 9, 4, "[Fleches Gauche / Droite] : Modifier (5 a 10)");
    mvwprintw(fen, 10, 4, "[Entree]                  : Lancer la partie");
    wrefresh(fen);
}

/**
Fonction   : choisirTailleGrille
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Ouvre une fenetre ncurses permettant de choisir la taille (5 a 10)
Retour     : Taille de la grille retenue (entier entre 5 et 10)
*/
int choisirTailleGrille(void)
{
    int maxY, maxX, posX;
    int tailleChoisie = TAILLE_DEFAUT;
    int touche = 0;
    WINDOW *fenTaille;

    getmaxyx(stdscr, maxY, maxX);
    (void)maxY;
    posX = (maxX > 58) ? (maxX - 56) / 2 : 1;

    erase();
    refresh();

    fenTaille = newwin(13, 56, 4, posX);
    keypad(fenTaille, TRUE);
    flushinp();

    while (!estToucheEntree(touche)) {
        dessinerFenetreTaille(fenTaille, tailleChoisie);
        touche = wgetch(fenTaille);

        if ((touche == KEY_LEFT || touche == KEY_DOWN) && tailleChoisie > TAILLE_MIN) {
            tailleChoisie--;
        } else if ((touche == KEY_RIGHT || touche == KEY_UP) && tailleChoisie < TAILLE_MAX) {
            tailleChoisie++;
        } else if (touche >= '5' && touche <= '9') {
            tailleChoisie = touche - '0';
        } else if (touche == '0') {
            tailleChoisie = 10;
        }
    }

    delwin(fenTaille);
    return tailleChoisie;
}

/**
Fonction   : dessinerFenetreMenu
Auteur     : Etudiant BUT1
Param      : fen (pointeur WINDOW), selection (option surlignee de 1 a 4)
Traitement : Affiche le menu dans une fenetre ncurses avec A_REVERSE (style TD)
Retour     : Aucun (procedure)
*/
static void dessinerFenetreMenu(WINDOW *fen, int selection)
{
    const char *options[4] = {
        " 1. Commencer une nouvelle partie                  ",
        " 2. Charger une partie sauvegardee (sauvegarde.txt)",
        " 3. Afficher les regles du jeu                     ",
        " 4. Quitter l'application                          "
    };
    int i;

    werase(fen);
    box(fen, ACS_VLINE, ACS_HLINE);

    wattron(fen, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvwprintw(fen, 1, 16, "S N A K E   2 0 4 8");
    wattroff(fen, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvwprintw(fen, 2, 12, "SAE 1.01 / 1.02 - BUT 1 Info");

    for (i = 0; i < 4; i++) {
        if (selection == i + 1) {
            wattron(fen, A_REVERSE | A_BOLD);
        }
        mvwprintw(fen, 4 + i * 2, 4, "%s", options[i]);
        if (selection == i + 1) {
            wattroff(fen, A_REVERSE | A_BOLD);
        }
    }

    wattron(fen, COLOR_PAIR(PAIRE_TEXTE_VERT));
    mvwprintw(fen, 13, 4, "[Fleches Haut/Bas] + [Entree] ou touches [1]-[4]");
    wattroff(fen, COLOR_PAIR(PAIRE_TEXTE_VERT));
    wrefresh(fen);
}

/**
Fonction   : afficherMenuPrincipal
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Gere la navigation clavier dans la fenetre ncurses du menu principal
Retour     : Numero de l'option choisie (1 a 4)
*/
int afficherMenuPrincipal(void)
{
    int maxY, maxX, posX;
    int selection = 1;
    int touche;
    WINDOW *fenMenu;

    getmaxyx(stdscr, maxY, maxX);
    (void)maxY;
    posX = (maxX > 62) ? (maxX - 60) / 2 : 1;

    erase();
    refresh();

    fenMenu = newwin(15, 60, 3, posX);
    keypad(fenMenu, TRUE);
    flushinp();

    while (1) {
        dessinerFenetreMenu(fenMenu, selection);
        touche = wgetch(fenMenu);

        if (touche == KEY_UP && selection > 1) {
            selection--;
        } else if (touche == KEY_DOWN && selection < 4) {
            selection++;
        } else if (touche >= '1' && touche <= '4') {
            delwin(fenMenu);
            return touche - '0';
        } else if (estToucheEntree(touche)) {
            delwin(fenMenu);
            return selection;
        }
    }
}

/**
Fonction   : afficherErreurChargement
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Affiche une fenetre d'alerte si le fichier sauvegarde.txt est absent
Retour     : Aucun (procedure)
*/
static void afficherErreurChargement(void)
{
    int maxY, maxX, posX;
    WINDOW *fenErr;

    getmaxyx(stdscr, maxY, maxX);
    (void)maxY;
    posX = (maxX > 62) ? (maxX - 60) / 2 : 1;

    erase();
    refresh();

    fenErr = newwin(9, 60, 6, posX);
    box(fenErr, ACS_VLINE, ACS_HLINE);

    wattron(fenErr, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
    mvwprintw(fenErr, 2, 5, "Aucune sauvegarde valide dans '%s' !", FICHIER_SAUVEGARDE);
    wattroff(fenErr, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);

    mvwprintw(fenErr, 4, 5, "Appuyez sur [S] pendant une partie pour sauvegarder.");
    mvwprintw(fenErr, 6, 10, "Appuyez sur une touche pour continuer...");

    wrefresh(fenErr);
    delwin(fenErr);
    attendreAppuiTouche();
}

/**
Fonction   : lancerMenuPrincipal
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Boucle principale reliant le menu aux differentes actions du jeu
Retour     : Aucun (procedure)
*/
void lancerMenuPrincipal(void)
{
    Partie partie;
    int choix = 0;
    int taille;

    while (choix != 4) {
        choix = afficherMenuPrincipal();

        if (choix == 1) {
            taille = choisirTailleGrille();
            initialiserNouvellePartie(&partie, taille);
            jouerPartie(&partie);
        } else if (choix == 2) {
            if (chargerPartie(&partie, FICHIER_SAUVEGARDE)) {
                jouerPartie(&partie);
            } else {
                afficherErreurChargement();
            }
        } else if (choix == 3) {
            afficherReglesDuJeu();
        }
    }
}
