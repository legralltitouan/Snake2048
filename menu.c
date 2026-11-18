#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include "menu.h"

#define TOUCHE_ENTREE 13
#define TOUCHE_SPECIALE 224
#define FLECHE_HAUT 72
#define FLECHE_BAS 80

void afficherRegles(void)
{
    system("cls");
    printf("=== REGLES ===\n\n");
    printf("-Le serpent ne doit pas sortir de la grille\n-Le serpent ne doit pas repasser sur son corp\n");
    printf("\nAppuie sur une touche pour revenir au menu...");
    _getch();
}
