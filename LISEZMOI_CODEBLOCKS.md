# Projet Snake 2048 — Aligné sur le TD `R1.01 ncurses` & Cours Fichiers (BUT 1 Info S1)

Projet complet en **langage C** avec **`ncurses`**, intégralement réécrit pour reprendre **exactement les fonctions et conventions de tes supports de cours** (`R1_01_TD_Ncurses.pdf`, `LectureEcritureFichier.txt`, `Note sur ncurses dans codeblocks.pdf` et la playlist vidéo `ncurses`).

---

## 1. Lancer le projet dans Code::Blocks (Windows & Linux IUT)

Double-clique sur **`Snake2048.cbp`**, puis choisis la cible en haut de Code::Blocks (à côté de l'engrenage jaune) avant d'appuyer sur **`F9`** :

- **Sur ton PC Windows (avec MSYS2 `ucrt64`)** :
  - Utilise **`PDCurses_Windows`** *(recommandé sur `cmd.exe` Windows : rendu couleurs natif Windows Console sans aucune DLL externe !)* ou **`Debug`** (`ncursesw`).
- **Sur les PC Linux de l'IUT** (comme indiqué dans *Note sur ncurses dans codeblocks.pdf*) :
  - Sélectionne la cible **`Linux_IUT`** (qui utilise déjà `ncurses` dans *Linker settings*).

### Mettre ton nom dans les cartouches de fonctions
Dans Code::Blocks : **`Ctrl + Maj + R`** (*Replace in files*) $\rightarrow$ remplace `Etudiant BUT1` par ton `Nom Prénom`.

---

## 2. Correspondance directe avec tes documents de cours

### A. TD `R1_01_TD_Ncurses.pdf` & Playlist vidéo `ncurses`
- **Exercice 1 (`getmaxyx` & `mvprintw`)** : utilisé dans `affichage.c` et `menu.c` pour récupérer la taille de la console (`getmaxyx(stdscr, maxY, maxX)`) et centrer l'affichage.
- **Exercice 2 & Vidéos (`WINDOW *`, `newwin`, `box(..., ACS_VLINE, ACS_HLINE)`, `mvwprintw`, `wrefresh`)** :
  - Fenêtre encadrée pour le menu principal et le choix de la taille (`menu.c`) avec surbrillance `A_REVERSE` et navigation `keypad(fen, TRUE)` + `wgetch(fen)`.
  - Deux fenêtres encadrées en jeu (`affichage.c`) : `fenInfos` en haut (score, longueur, valeur max) et `fenPlateau` en dessous (grille de `5x5` à `10x10`).
- **Exercices 3 & 4 (`start_color`, `init_pair`, `bkgd`, cases à fond coloré)** :
  - Tête du serpent affichée sur **fond vert** (`PAIRE_TETE`), corps sur **fond cyan** (`PAIRE_CORPS`), et tuiles 2048 sur **fond blanc, jaune, magenta ou rouge** selon leur valeur (`mvwprintw`).
- **Exercice 5 (Chronomètre `MM:SS` en haut à droite)** :
  - Utilise `time_t startTime = time(NULL)` et `difftime(maintenant, p->startTime)` pour afficher le temps écoulé en haut à droite avec `mvprintw(0, COLS - 10, "%02d:%02d", minutes, secondes)`.

### B. Cours `LectureEcritureFichier.txt` (`sauvegarde.c`)
- Écriture et lecture dans `sauvegarde.txt` uniquement avec **`FILE *f`**, **`fopen(..., "w" / "r")`**, **`fprintf(f, "%d ...\n", ...)`**, **`fscanf(f, "%d ...", &...)`** et **`fclose(f)`**, exactement comme dans l'exemple du cours.

---

## 3. Découpage modulaire (toutes les fonctions `< 55 lignes`)

- **`structures.h`** : constantes et structures `Segment`, `Serpent`, `Partie`.
- **`main.c`** : `srand`, `initialiserNcurses()`, `lancerMenuPrincipal()`, `fermerNcurses()`.
- **`console.c` / `.h`** : configuration `ncurses`, paires de couleurs `init_pair`, lecture clavier `nodelay` + `getch`.
- **`menu.c` / `.h`** : fenêtres `WINDOW *` du menu principal et du choix de la taille (`10x10` par défaut, réglable de `5x5` à `10x10`).
- **`affichage.c` / `.h`** : fenêtres `WINDOW *` du jeu, cases colorées, chronomètre `MM:SS`, règles et bilan de fin.
- **`jeu.c` / `.h`** : boucle temps réel, déplacement d'un pas, pause (`[P]`), sauvegarde (`[S]`), victoire `2048` et défaites.
- **`serpent.c` / `.h`** : placement aléatoire, collisions, ingestion et fusions consécutives en chaîne (`2+2=4`, `4+4=8`...).
- **`grille.c` / `.h`** : gestion de la grille et génération des tuiles (`2` à `512`, hors `1024` et `2048`).
- **`sauvegarde.c` / `.h`** : sauvegarde et rechargement texte dans `sauvegarde.txt`.
