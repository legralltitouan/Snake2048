#ifndef MENU_H
#define MENU_H

#define NB_BOUTONS 4

typedef enum
{
    CHOIX_JOUER,
    CHOIX_CHARGER,
    CHOIX_REGLES,
    CHOIX_QUITTER
} ChoixMenu;

int menuPrincipal(void);
void afficherRegles(void);

#endif
