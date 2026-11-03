#ifndef CONSOLE_H
#define CONSOLE_H

/* =========================================================================
   Projet     : Snake 2048 (SAE 1.01 / SAE 1.02 - BUT 1 Informatique S1)
   Fichier    : console.h
   Description: Inclusion portable de ncurses et prototypes clavier/couleurs
   ========================================================================= */

#if defined(USE_PDCURSES)
  #if defined(__has_include)
    #if __has_include(<pdcurses.h>)
      #include <pdcurses.h>
    #elif __has_include(<pdcurses/curses.h>)
      #include <pdcurses/curses.h>
    #else
      #include <curses.h>
    #endif
  #else
    #include <curses.h>
  #endif
#elif defined(__has_include)
  #if __has_include(<ncurses.h>)
    #include <ncurses.h>
  #elif __has_include(<ncurses/ncurses.h>)
    #include <ncurses/ncurses.h>
  #elif __has_include(<ncursesw/ncurses.h>)
    #include <ncursesw/ncurses.h>
  #elif __has_include(<pdcurses.h>)
    #include <pdcurses.h>
  #else
    #include <curses.h>
  #endif
#else
  #include <ncurses.h>
#endif

void initialiserNcurses(void);
void fermerNcurses(void);
void attendreMs(int millisecondes);
int estToucheEntree(int touche);
int lireCommandeNonBloquante(void);
int attendreCommandeDepart(void);
void attendreAppuiTouche(void);

#endif /* CONSOLE_H */
