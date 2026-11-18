# 🐍 Snake2048

Projet en langage C (Code::Blocks) combinant les mécaniques classiques du **Snake** et du **2048**.

---

## 🚀 Avant de vous répartir le code (À faire ensemble)

- [ ] Ouvrir `Snake2048.cbp` et vérifier que **Debug → Rebuild** (`Ctrl + F11`) compile sans ajouter de bibliothèque dans *Linker settings*.
- [ ] Se mettre d’accord sur les données partagées dans `structures.h` : `Segment`, `Serpent`, `Partie`, les directions et les états de fin.
- [ ] Conserver une **seule version de référence** du projet via Git (éviter les échanges d'archives `.zip` modifiées séparément).
- [ ] **Convention d'indexation :** `serpent.corps[0]` représente la **tête**, et les indices suivants vont vers la **queue**.

---

## 👥 Répartition des tâches

### 1. Titouan — Grille et démarrage d’une partie
**Fichiers principaux :** `grille.c`, `grille.h`, coordination de `structures.h`

- [ ] Vérifier que la taille choisie reste comprise entre `5 × 5` et `10 × 10` (`10 × 10` par défaut).
- [ ] Initialiser la grille vide.
- [ ] Placer le serpent au début d’une partie.
- [ ] Générer des tuiles aléatoires de valeurs `2, 4, 8, …, 512`, sans chevaucher le serpent ni une autre tuile.
- [ ] Vérifier que la génération s’arrête proprement si le plateau est plein ou atteint sa limite de tuiles.
- [ ] Tester les tailles minimale (`5 × 5`) et maximale (`10 × 10`), ainsi que l’initialisation d’une nouvelle partie.

> 🤝 **Coordination (avec Ulysse) :** Définir les fonctions de grille appelées lors des déplacements et des détections de collisions.

---

### 2. Ulysse — Serpent et règles du jeu
**Fichiers principaux :** `serpent.c`, `serpent.h`, `jeu.c`, `jeu.h`

- [ ] Calculer la prochaine position selon la direction.
- [ ] Empêcher le demi-tour direct vers le cou.
- [ ] Détecter les collisions avec les bords du plateau et avec le corps du serpent.
- [ ] Déplacer le serpent et traiter les tuiles mangées.
- [ ] Ajouter un segment lorsque le serpent mange une tuile.
- [ ] Fusionner les segments consécutifs de même valeur, y compris les **fusions en chaîne**.
- [ ] Mettre à jour le score, la longueur et la valeur maximale atteinte.
- [ ] Détecter la victoire (`2048`), les défaites et l’absence de déplacements possibles.
- [ ] Tester séparément les déplacements, les collisions et les fusions.

> 🤝 **Coordination (avec Adam) :** Valider les codes de direction et les actions clavier transmises au moteur de jeu.

---

### 3. Adam — Clavier, affichage et menus
**Fichiers principaux :** `console.c`, `console.h`, `affichage.c`, `affichage.h`, `menu.c`, `menu.h`

- [ ] Vérifier le décodage des flèches directionnelles Windows via `_getch()` et la détection non bloquante via `_kbhit()`.
- [ ] Afficher le plateau, les tuiles, le serpent et le HUD (score, longueur, valeur maximale).
- [ ] Afficher le temps écoulé.
- [ ] Gérer les menus : *Nouvelle partie*, *Chargement*, *Règles*, *Quitter*.
- [ ] Gérer le choix de la taille de grille et les écrans/messages de victoire, défaite et sauvegarde.
- [ ] Tester le rendu sur les grilles `5 × 5` et `10 × 10`.

| Touche | Action en jeu |
| :--- | :--- |
| **Flèches directionnelles** | Diriger le serpent |
| **`S`** | Sauvegarder la partie |
| **`P`** | Mettre en pause |
| **`Q`** | Revenir au menu principal |

---

### 4. Yassine — Sauvegarde, intégration et tests finaux
**Fichiers principaux :** `sauvegarde.c`, `sauvegarde.h` *(+ intégration finale sans modifier seul les règles du jeu)*

- [ ] Définir avec l’équipe le format texte de `sauvegarde.txt`.
- [ ] Implémenter la sauvegarde et le chargement de toutes les données : taille, grille, serpent, score, valeur maximale et temps.
- [ ] Gérer les cas d’erreur : fichier absent, incomplet ou corrompu.
- [ ] Intégrer l'ensemble des fichiers au projet Code::Blocks et vérifier la correspondance des prototypes `.h`.
- [ ] Lancer un **Rebuild** complet et corriger les éventuelles erreurs d’intégration.
- [ ] Réaliser le parcours de test complet et préparer l’archive finale.

---

## 🔄 Ordre d’intégration conseillé

1. **Toute l’équipe :** Valider `structures.h` et compiler le projet de départ.
2. **Titouan (P1) :** Initialisation et génération de la grille.
3. **Ulysse (P2) :** Déplacements, collisions et fusions.
4. **Adam (P3) :** Liaison clavier et affichage aux fonctions du jeu.
5. **Yassine (P4) :** Liaison chargement/sauvegarde et tests de bout en bout.
6. **Toute l’équipe :** Compilation complète finale et validation avant rendu.

---

## ✅ Checklist des tests et contraintes avant rendu

- [ ] Nouvelle partie fonctionnelle en `5 × 5` et en `10 × 10`.
- [ ] Apparition des tuiles uniquement sur des cases libres, avec une valeur maximale de `512`.
- [ ] Avancée automatique du serpent et réactivité aux flèches directionnelles.
- [ ] Blocage effectif du demi-tour immédiat vers le cou.
- [ ] Augmentation de la longueur lors de l'absorption d'une tuile et déclenchement correct des fusions simples et en chaîne.
- [ ] Fonctionnement de tous les cas de défaite et de la victoire à `2048`.
- [ ] Restauration exacte de l'état d'une partie sauvegardée après chargement.
- [ ] Compilation propre via `Ctrl + F11` puis exécution via `F9` sous Code::Blocks (sans `ncurses` ni bibliothèque externe).
- [ ] **Contraintes de code :** Encodage strictement **ASCII**, respect de la limite maximale de lignes par fonction et présence du commentaire d’en-tête obligatoire sur chaque fonction.
