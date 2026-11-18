Avant de vous répartir le code — à faire ensemble
Ouvrez Snake2048.cbp et vérifiez que Debug → Rebuild compile sans ajouter de bibliothèque dans Linker settings.
Mettez-vous d’accord sur les données partagées dans structures.h : Segment, Serpent, Partie, les directions et les états de fin.
Gardez une seule version de référence du projet. Idéalement, utilisez Git ; sinon, désignez une personne qui rassemble les fichiers et évitez de vous envoyer chacun une archive complète modifiée.
Convenez que serpent.corps[0] est la tête et que les indices suivants vont vers la queue.
Titouan — grille et démarrage d’une partie
Fichiers principaux : grille.c, grille.h, et coordination de structures.h.

À faire dans cet ordre :

Vérifier que la taille choisie reste entre 5 × 5 et 10 × 10, avec 10 × 10 par défaut.
Initialiser la grille vide.
Placer le serpent au début d’une partie.
Générer des tuiles aléatoires de valeurs 2, 4, 8, …, 512, sans placer de tuile sur le serpent ou sur une autre tuile.
Vérifier que la génération de tuiles s’arrête correctement si le plateau est plein ou atteint sa limite de tuiles.
Tester les tailles minimale et maximale, ainsi que l’initialisation d’une nouvelle partie.
À coordonner avec la personne 2 : les fonctions de grille appelées par les déplacements et les collisions.

Ulysse — serpent et règles du jeu
Fichiers principaux : serpent.c, serpent.h, jeu.c, jeu.h.

À faire dans cet ordre :

Calculer la prochaine position selon la direction.
Empêcher le demi-tour direct vers le cou.
Détecter les collisions avec les bords et avec le corps.
Déplacer le serpent et traiter les tuiles mangées.
Ajouter un segment quand le serpent mange une tuile.
Fusionner les segments consécutifs de même valeur, y compris les fusions en chaîne.
Mettre à jour le score, la longueur et la valeur maximale.
Détecter victoire, défaites et absence de déplacements possibles.
Tester séparément les déplacements, collisions et fusions.
À coordonner avec la personne 3 : les codes de direction et les actions clavier que le jeu reçoit.

Adam — clavier, affichage et menus
Fichiers principaux : console.c, console.h, affichage.c, affichage.h, menu.c, menu.h.

À faire dans cet ordre :

Vérifier que les flèches Windows sont bien décodées par _getch() et que le jeu détecte les touches sans bloquer avec _kbhit().
Afficher le plateau, les tuiles, le serpent et le HUD : score, longueur et valeur maximale.
Afficher le temps écoulé.
Gérer les menus : nouvelle partie, chargement, règles, quitter.
Gérer le choix de taille et les messages de victoire, défaite et sauvegarde.
Tester l’affichage sur les grilles 5 × 5 et 10 × 10.
Commandes prévues en jeu : flèches pour diriger, S pour sauvegarder, P pour pause, Q pour revenir au menu.

Yassine — sauvegarde, intégration et tests finaux
Fichiers principaux : sauvegarde.c, sauvegarde.h. Elle ou il s’occupe aussi de l’intégration finale, mais ne modifie pas seul les règles du jeu.

À faire dans cet ordre :

Définir avec l’équipe le contenu texte de sauvegarde.txt.
Sauvegarder et recharger toutes les informations nécessaires : taille, grille, serpent, score, valeur maximale et temps.
Vérifier le cas où le fichier est absent, incomplet ou invalide.
Intégrer les fichiers au projet Code::Blocks et vérifier que les noms de fonctions correspondent aux prototypes .h.
Lancer une Rebuild complète et corriger les erreurs d’intégration.
Faire le parcours de test complet et préparer l’archive finale.
Ordre d’intégration conseillé
Toute l’équipe : valider les structures et compiler le projet de départ.
Personne 1 : initialisation et génération de la grille.
Personne 2 : déplacements, collisions et fusions.
Personne 3 : relier clavier et affichage aux fonctions du jeu.
Personne 4 : relier le chargement et la sauvegarde, puis faire les tests de bout en bout.
Toute l’équipe : refaire une compilation complète et tester avant de rendre.
Tests à ne pas oublier
Nouvelle partie en 5 × 5 et en 10 × 10.
Les tuiles apparaissent sur des cases libres et ne dépassent pas 512.
Le serpent avance automatiquement et répond aux flèches.
Pas de demi-tour immédiat vers le cou.
Une tuile mangée augmente la longueur et peut déclencher une ou plusieurs fusions.
Chaque type de défaite et la victoire à 2048 fonctionnent.
Une partie sauvegardée peut être chargée avec le même état.
Ctrl+F11 puis F9 fonctionne sous Code::Blocks sans ncurses et sans bibliothèque externe.
Le code reste en ASCII, les fonctions respectent la limite de lignes demandée et chaque fonction possède son commentaire d’en-tête obligatoire.
