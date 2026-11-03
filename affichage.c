#include <stddef.h>
#include <time.h>
#include "affichage.h"
#include "console.h"
#include "grille.h"

/**
Fonction   : couleurPourTuile
Auteur     : Etudiant BUT1
Param      : valeur (valeur numerique de la tuile sur la grille)
Traitement : Choisit la paire de couleurs de fond ncurses selon la valeur 2048
Retour     : Identifiant de la paire de couleurs (PAIRE_TUILE_2_4 a PAIRE_TUILE_MAX)
*/
static int couleurPourTuile(int valeur)
{
    if (valeur <= 4)   return PAIRE_TUILE_2_4;
    if (valeur <= 16)  return PAIRE_TUILE_8_16;
    if (valeur <= 128) return PAIRE_TUILE_32;
    return PAIRE_TUILE_MAX;
}

/**
Fonction   : afficherChronometre
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie en cours)
Traitement : Calcule le temps avec difftime et l'affiche en haut a droite (TD Ex. 5)
Retour     : Aucun (procedure)
*/
static void afficherChronometre(const Partie *p)
{
    time_t maintenant = time(NULL);
    int totalSec = p->secondesCumulees + (int)difftime(maintenant, p->startTime);
    int minutes = totalSec / 60;
    int secondes = totalSec % 60;

    attron(COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvprintw(0, COLS - 10, "%02d:%02d", minutes, secondes);
    attroff(COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
}

/**
Fonction   : dessinerFenetreInfos
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie), posX (colonne de depart)
Traitement : Cree et affiche la fenetre du haut avec score, longueur et valeur max
Retour     : Aucun (procedure)
*/
static void dessinerFenetreInfos(const Partie *p, int posX)
{
    WINDOW *fenInfos = newwin(4, 73, 1, posX);

    box(fenInfos, ACS_VLINE, ACS_HLINE);
    wattron(fenInfos, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvwprintw(fenInfos, 1, 2,
              "Score : %-7d | Longueur du serpent : %-3d | Valeur max : %-4d",
              p->score, p->serpent.longueur, p->valeurMax);
    wattroff(fenInfos, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);

    mvwprintw(fenInfos, 2, 2, "Legende : ");
    wattron(fenInfos, COLOR_PAIR(PAIRE_TETE) | A_BOLD);
    mvwprintw(fenInfos, 2, 12, "<  n>");
    wattroff(fenInfos, COLOR_PAIR(PAIRE_TETE) | A_BOLD);
    mvwprintw(fenInfos, 2, 18, "Tete  ");

    wattron(fenInfos, COLOR_PAIR(PAIRE_CORPS) | A_BOLD);
    mvwprintw(fenInfos, 2, 24, "[  n]");
    wattroff(fenInfos, COLOR_PAIR(PAIRE_CORPS) | A_BOLD);
    mvwprintw(fenInfos, 2, 30, "Corps  ");

    wattron(fenInfos, COLOR_PAIR(PAIRE_TUILE_8_16));
    mvwprintw(fenInfos, 2, 37, "   n ");
    wattroff(fenInfos, COLOR_PAIR(PAIRE_TUILE_8_16));
    mvwprintw(fenInfos, 2, 43, "Tuile (%dx%d)", p->taille, p->taille);

    wrefresh(fenInfos);
    delwin(fenInfos);
}

/**
Fonction   : dessinerCaseGrille
Auteur     : Etudiant BUT1
Param      : fen (pointeur WINDOW), p (pointeur Partie), lig, col (coordonnees)
Traitement : Affiche une case coloree sur la fenetre du plateau avec mvwprintw
Retour     : Aucun (procedure)
*/
static void dessinerCaseGrille(WINDOW *fen, const Partie *p, int lig, int col)
{
    int idx = indiceSegmentSurCase(&p->serpent, lig, col);
    int y = lig + 1;
    int x = 2 + col * 7;
    int val, paire;

    if (idx == 0) {
        val = p->serpent.corps[0].valeur;
        wattron(fen, COLOR_PAIR(PAIRE_TETE) | A_BOLD);
        mvwprintw(fen, y, x, "<%4d>", val);
        wattroff(fen, COLOR_PAIR(PAIRE_TETE) | A_BOLD);
    } else if (idx > 0) {
        val = p->serpent.corps[idx].valeur;
        wattron(fen, COLOR_PAIR(PAIRE_CORPS) | A_BOLD);
        mvwprintw(fen, y, x, "[%4d]", val);
        wattroff(fen, COLOR_PAIR(PAIRE_CORPS) | A_BOLD);
    } else if (p->grille[lig][col] > 0) {
        val = p->grille[lig][col];
        paire = couleurPourTuile(val);
        wattron(fen, COLOR_PAIR(paire) | A_BOLD);
        mvwprintw(fen, y, x, " %4d ", val);
        wattroff(fen, COLOR_PAIR(paire) | A_BOLD);
    } else {
        mvwprintw(fen, y, x, "  .   ");
    }
}

/**
Fonction   : afficherPartie
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie), messageInfo (message d'etat)
Traitement : Affiche tout l'ecran de jeu avec fenetres ncurses, couleurs et chrono
Retour     : Aucun (procedure)
*/
void afficherPartie(const Partie *p, const char *messageInfo)
{
    int maxY, maxX, posX, largPlateau, posXPlateau, lig, col;
    WINDOW *fenPlateau;

    getmaxyx(stdscr, maxY, maxX);
    (void)maxY;
    posX = (maxX > 75) ? (maxX - 73) / 2 : 1;

    erase();
    attron(A_BOLD);
    mvprintw(0, posX, "SNAKE 2048 - Mode Console ncurses");
    attroff(A_BOLD);
    afficherChronometre(p);
    mvprintw(5 + p->taille + 2, posX,
             "[Fleches] Diriger   [S] Sauvegarder   [P] Pause   [Q] Menu");

    if (messageInfo != NULL && messageInfo[0] != '\0') {
        attron(COLOR_PAIR(PAIRE_TEXTE_VERT) | A_BOLD);
        mvprintw(5 + p->taille + 3, posX, "%s", messageInfo);
        attroff(COLOR_PAIR(PAIRE_TEXTE_VERT) | A_BOLD);
    }
    refresh();

    dessinerFenetreInfos(p, posX);

    largPlateau = p->taille * 7 + 3;
    posXPlateau = posX + (73 - largPlateau) / 2;
    fenPlateau = newwin(p->taille + 2, largPlateau, 5, posXPlateau);
    box(fenPlateau, ACS_VLINE, ACS_HLINE);
    for (lig = 0; lig < p->taille; lig++) {
        for (col = 0; col < p->taille; col++) {
            dessinerCaseGrille(fenPlateau, p, lig, col);
        }
    }
    wrefresh(fenPlateau);
    delwin(fenPlateau);
}

/**
Fonction   : afficherReglesDuJeu
Auteur     : Etudiant BUT1
Param      : Aucun
Traitement : Affiche une fenetre encadree contenant les regles de Snake 2048
Retour     : Aucun (procedure)
*/
void afficherReglesDuJeu(void)
{
    int maxY, maxX, posX;
    WINDOW *fenRegles;

    getmaxyx(stdscr, maxY, maxX);
    (void)maxY;
    posX = (maxX > 75) ? (maxX - 73) / 2 : 1;

    erase();
    refresh();

    fenRegles = newwin(19, 73, 2, posX);
    box(fenRegles, ACS_VLINE, ACS_HLINE);

    wattron(fenRegles, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvwprintw(fenRegles, 1, 22, "REGLES DU JEU - SNAKE 2048");
    wattroff(fenRegles, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);

    mvwprintw(fenRegles, 3, 2, "1. Dirigez le serpent avec les FLECHES sur une grille 5x5 a 10x10.");
    mvwprintw(fenRegles, 4, 2, "   Le serpent se deplace en permanence.");
    mvwprintw(fenRegles, 6, 2, "2. Manger une tuile (2, 4, 8...) l'ajoute au corps du serpent.");
    mvwprintw(fenRegles, 7, 2, "   Deux segments consecutifs de meme valeur fusionnent aussitot");
    mvwprintw(fenRegles, 8, 2, "   pour doubler de valeur : 2+2=4, 4+4=8, 8+8=16...");
    mvwprintw(fenRegles, 10, 2, "3. VICTOIRE : obtenir la valeur 2048 dans le serpent.");
    mvwprintw(fenRegles, 11, 2, "4. DEFAITE  : collision bord, collision corps ou serpent bloque.");
    mvwprintw(fenRegles, 13, 2, "5. SAUVEGARDE : touche [S] en jeu pour enregistrer la partie.");

    wattron(fenRegles, COLOR_PAIR(PAIRE_TEXTE_VERT) | A_BOLD);
    mvwprintw(fenRegles, 16, 12, "Appuyez sur une touche pour revenir au menu...");
    wattroff(fenRegles, COLOR_PAIR(PAIRE_TEXTE_VERT) | A_BOLD);

    wrefresh(fenRegles);
    delwin(fenRegles);
    attendreAppuiTouche();
}

/**
Fonction   : afficherFinDePartie
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie terminee)
Traitement : Montre le plateau final puis une fenetre encadree du bilan de fin
Retour     : Aucun (procedure)
*/
void afficherFinDePartie(const Partie *p)
{
    int maxY, maxX, posX;
    WINDOW *fenFin;

    afficherPartie(p, "Partie terminee ! Appuyez sur une touche pour voir le bilan...");
    attendreAppuiTouche();

    getmaxyx(stdscr, maxY, maxX);
    (void)maxY;
    posX = (maxX > 70) ? (maxX - 68) / 2 : 1;

    erase();
    refresh();

    fenFin = newwin(14, 68, 4, posX);
    box(fenFin, ACS_VLINE, ACS_HLINE);

    if (p->etat == ETAT_VICTOIRE) {
        wattron(fenFin, COLOR_PAIR(PAIRE_TEXTE_VERT) | A_BOLD);
        mvwprintw(fenFin, 2, 10, "FELICITATIONS ! TUILE 2048 OBTENUE : VICTOIRE !");
        wattroff(fenFin, COLOR_PAIR(PAIRE_TEXTE_VERT) | A_BOLD);
    } else if (p->etat == ETAT_DEFAITE_BORD) {
        wattron(fenFin, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
        mvwprintw(fenFin, 2, 12, "DEFAITE : Collision avec un bord de la grille !");
        wattroff(fenFin, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
    } else if (p->etat == ETAT_DEFAITE_CORPS) {
        wattron(fenFin, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
        mvwprintw(fenFin, 2, 12, "DEFAITE : Collision avec votre propre corps !");
        wattroff(fenFin, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
    } else if (p->etat == ETAT_DEFAITE_BLOQUE) {
        wattron(fenFin, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
        mvwprintw(fenFin, 2, 9, "DEFAITE : Impossibilite de se deplacer (bloque) !");
        wattroff(fenFin, COLOR_PAIR(PAIRE_TEXTE_ROUGE) | A_BOLD);
    } else {
        wattron(fenFin, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
        mvwprintw(fenFin, 2, 18, "Partie interrompue par le joueur.");
        wattroff(fenFin, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    }

    mvwprintw(fenFin, 5, 16, "- Score final obtenu       : %d", p->score);
    mvwprintw(fenFin, 6, 16, "- Longueur finale serpent  : %d", p->serpent.longueur);
    mvwprintw(fenFin, 7, 16, "- Valeur maximale atteinte : %d", p->valeurMax);

    wattron(fenFin, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);
    mvwprintw(fenFin, 11, 11, "Appuyez sur une touche pour revenir au menu...");
    wattroff(fenFin, COLOR_PAIR(PAIRE_TEXTE_JAUNE) | A_BOLD);

    wrefresh(fenFin);
    delwin(fenFin);
    attendreAppuiTouche();
}
