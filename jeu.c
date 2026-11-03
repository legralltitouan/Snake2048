#include <string.h>
#include <time.h>
#include "jeu.h"
#include "grille.h"
#include "serpent.h"
#include "affichage.h"
#include "sauvegarde.h"
#include "console.h"

/**
Fonction   : initialiserNouvellePartie
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie), taille (dimension de la grille 5 a 10)
Traitement : Prepare une nouvelle partie avec grille, serpent, tuiles et chrono
Retour     : Aucun (procedure)
*/
void initialiserNouvellePartie(Partie *p, int taille)
{
    if (taille < TAILLE_MIN || taille > TAILLE_MAX) {
        taille = TAILLE_DEFAUT;
    }

    p->taille = taille;
    p->score = 0;
    p->valeurMax = 2;
    p->etat = ETAT_EN_COURS;
    p->secondesCumulees = 0;
    p->startTime = time(NULL);

    viderGrille(p);
    placerSerpentAleatoire(p);
    genererTuilesInitiales(p);
}

/**
Fonction   : verifierVictoire
Auteur     : Etudiant BUT1
Param      : p (pointeur constant vers la Partie en cours)
Traitement : Verifie si le joueur a obtenu un segment de valeur 2048
Retour     : 1 si le joueur a gagne, 0 sinon
*/
int verifierVictoire(const Partie *p)
{
    if (p->valeurMax >= OBJECTIF_VICTOIRE) {
        return 1;
    }
    return 0;
}

/**
Fonction   : convertirCommandeEnDirection
Auteur     : Etudiant BUT1
Param      : commande (code commande clavier CMD_HAUT..CMD_DROITE)
Traitement : Traduit une commande de fleche clavier en constante de direction
Retour     : Direction correspondante (DIR_HAUT..DIR_DROITE) ou -1
*/
static int convertirCommandeEnDirection(int commande)
{
    if (commande == CMD_HAUT)   return DIR_HAUT;
    if (commande == CMD_BAS)    return DIR_BAS;
    if (commande == CMD_GAUCHE) return DIR_GAUCHE;
    if (commande == CMD_DROITE) return DIR_DROITE;
    return -1;
}

/**
Fonction   : deplacerSerpentUnPas
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie a faire evoluer d'un pas)
Traitement : Gere le deplacement, les collisions, l'ingestion, les fusions et la fin
Retour     : Aucun (procedure)
*/
void deplacerSerpentUnPas(Partie *p)
{
    Serpent *s = &p->serpent;
    int nouvLig, nouvCol;
    int ancQueueLig, ancQueueCol;
    int valTuile;
    int i;

    calculerProchainePosition(s->corps[0].ligne, s->corps[0].colonne,
                              s->direction, &nouvLig, &nouvCol);

    if (estCollisionBord(nouvLig, nouvCol, p->taille)) {
        p->etat = ETAT_DEFAITE_BORD;
        return;
    }

    valTuile = p->grille[nouvLig][nouvCol];
    if (estCollisionCorps(s, nouvLig, nouvCol, (valTuile == 0) ? 1 : 0)) {
        p->etat = ETAT_DEFAITE_CORPS;
        return;
    }

    ancQueueLig = s->corps[s->longueur - 1].ligne;
    ancQueueCol = s->corps[s->longueur - 1].colonne;

    for (i = s->longueur - 1; i >= 1; i--) {
        s->corps[i].ligne = s->corps[i - 1].ligne;
        s->corps[i].colonne = s->corps[i - 1].colonne;
    }
    s->corps[0].ligne = nouvLig;
    s->corps[0].colonne = nouvCol;

    if (valTuile > 0) {
        p->grille[nouvLig][nouvCol] = 0;
        p->score += valTuile;
        ajouterSegmentSerpent(s, ancQueueLig, ancQueueCol, valTuile);
        fusionnerSegmentsConsecutifs(p);
    }

    genererTuileApresDeplacement(p);

    if (verifierVictoire(p)) {
        p->etat = ETAT_VICTOIRE;
    } else if (aucunDeplacementPossible(p)) {
        p->etat = ETAT_DEFAITE_BLOQUE;
    }
}

/**
Fonction   : mettreEnPausePartie
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie), messageInfo (tampon texte d'information)
Traitement : Suspend la partie et fige le chronometre jusqu'a la reprise clavier
Retour     : Aucun (procedure)
*/
static void mettreEnPausePartie(Partie *p, char *messageInfo)
{
    p->secondesCumulees += (int)difftime(time(NULL), p->startTime);
    p->startTime = time(NULL);

    afficherPartie(p, "JEU EN PAUSE - Appuyez sur une touche pour reprendre...");
    attendreAppuiTouche();

    p->startTime = time(NULL);
    strcpy(messageInfo, "Partie reprise.");
    afficherPartie(p, messageInfo);
}

/**
Fonction   : attendreEtLireActionJoueur
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie), messageInfo (tampon texte d'information)
Traitement : Attend le prochain pas tout en lisant les touches ncurses sans bloquer
Retour     : Aucun (procedure)
*/
static void attendreEtLireActionJoueur(Partie *p, char *messageInfo)
{
    int tempsEcoule = 0;
    int prochaineDir = p->serpent.direction;
    int cmd, dirCandidate;

    while (tempsEcoule < DELAI_PAS_MS && p->etat == ETAT_EN_COURS) {
        cmd = lireCommandeNonBloquante();
        dirCandidate = convertirCommandeEnDirection(cmd);

        if (dirCandidate != -1) {
            if (estDirectionValide(&p->serpent, dirCandidate)) {
                prochaineDir = dirCandidate;
            }
        } else if (cmd == CMD_SAUVEGARDER) {
            if (sauvegarderPartie(p, FICHIER_SAUVEGARDE)) {
                strcpy(messageInfo, "Sauvegarde reussie dans sauvegarde.txt !");
            } else {
                strcpy(messageInfo, "Erreur : impossible de sauvegarder.");
            }
            afficherPartie(p, messageInfo);
        } else if (cmd == CMD_PAUSE) {
            mettreEnPausePartie(p, messageInfo);
        } else if (cmd == CMD_QUITTER) {
            p->etat = ETAT_RETOUR_MENU;
            return;
        }

        attendreMs(TRANCHE_MS);
        tempsEcoule += TRANCHE_MS;
    }

    p->serpent.direction = prochaineDir;
}

/**
Fonction   : jouerPartie
Auteur     : Etudiant BUT1
Param      : p (pointeur vers la Partie deja initialisee ou chargee)
Traitement : Execute la boucle temps reel ncurses jusqu'a victoire, defaite ou sortie
Retour     : Aucun (procedure)
*/
void jouerPartie(Partie *p)
{
    char messageInfo[80] = "";
    int cmdDepart, dirDepart;

    p->startTime = time(NULL);
    afficherPartie(p, "Pret ? Appuyez sur une fleche (ou Entree) pour demarrer...");
    cmdDepart = attendreCommandeDepart();
    p->startTime = time(NULL);

    dirDepart = convertirCommandeEnDirection(cmdDepart);
    if (dirDepart != -1 && estDirectionValide(&p->serpent, dirDepart)) {
        p->serpent.direction = dirDepart;
    } else if (cmdDepart == CMD_QUITTER) {
        p->etat = ETAT_RETOUR_MENU;
    }

    if (p->etat == ETAT_EN_COURS && verifierVictoire(p)) {
        p->etat = ETAT_VICTOIRE;
    } else if (p->etat == ETAT_EN_COURS && aucunDeplacementPossible(p)) {
        p->etat = ETAT_DEFAITE_BLOQUE;
    }

    while (p->etat == ETAT_EN_COURS) {
        afficherPartie(p, messageInfo);
        messageInfo[0] = '\0';
        attendreEtLireActionJoueur(p, messageInfo);

        if (p->etat == ETAT_EN_COURS) {
            deplacerSerpentUnPas(p);
        }
    }

    p->secondesCumulees += (int)difftime(time(NULL), p->startTime);
    p->startTime = time(NULL);
    afficherFinDePartie(p);
}
