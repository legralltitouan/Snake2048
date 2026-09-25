# Tutoriel complet pour contribuer à `Snake2048`

Le fonctionnement sera :

```text
main
 ├── branche/alice
 ├── branche/bob
 └── branche/nom-du-contributeur
```

Chaque contributeur travaille uniquement sur sa branche, puis crée une **Pull Request** vers `main`. L’administrateur vérifie et fusionne.

Le dépôt contient actuellement un `README.md` et un `.gitignore`, mais aucun fichier indiquant une installation spécifique ou une dépendance particulière. Le setup ci-dessous installe donc Git et un éditeur de code ; les outils supplémentaires dépendront du code ajouté ensuite.

---

# 1. Installation du setup de développement

## Windows

Installer :

1. **Git** : [git-scm.com/download/win](https://git-scm.com/download/win)
2. **Visual Studio Code** : [code.visualstudio.com](https://code.visualstudio.com/)

Pendant l’installation de Git, les options par défaut conviennent généralement.

Ensuite, ouvrir **Git Bash**, PowerShell ou le terminal de VS Code.

Vérifier l’installation :

```bash
git --version
```

Configurer son identité Git :

```bash
git config --global user.name "Prénom Nom"
git config --global user.email "adresse@email.com"
```

Vérifier la configuration :

```bash
git config --global --list
```

L’adresse e-mail utilisée doit idéalement être liée au compte GitHub du contributeur.

---

# 2. Première récupération du projet

Le contributeur doit cloner le dépôt principal :

```bash
git clone https://github.com/legralltitouan/Snake2048.git
```

Entrer dans le dossier :

```bash
cd Snake2048
```

Vérifier les branches disponibles :

```bash
git branch -a
```

La branche principale doit apparaître :

```text
remotes/origin/main
```

Vérifier le dépôt distant :

```bash
git remote -v
```

Le résultat devrait ressembler à ceci :

```text
origin  https://github.com/legralltitouan/Snake2048.git (fetch)
origin  https://github.com/legralltitouan/Snake2048.git (push)
```

Le dépôt contient actuellement :

```text
README.md
.gitignore
```

Pour ouvrir le projet dans Visual Studio Code :

```bash
code .
```

Si la commande `code` n’est pas reconnue, ouvrir directement Visual Studio Code puis sélectionner :

```text
File → Open Folder → Snake2048
```

---

# 3. Créer sa propre branche

Un contributeur ne doit pas travailler directement sur `main`.

Avant de créer une branche, récupérer la dernière version de `main` :

```bash
git switch main
git pull origin main
```

Créer ensuite une branche personnelle :

```bash
git switch -c prenom-nom
```

Exemples :

```bash
git switch -c alice-interface
git switch -c bob-correction-score
git switch -c yanis-ajout-menu
```

Vérifier la branche actuelle :

```bash
git branch
```

L’étoile doit être devant la branche personnelle :

```text
  main
* alice-interface
```

La commande `git switch -c` crée la branche et s’y positionne immédiatement. Une branche permet de travailler séparément sans modifier directement la branche principale. [Writing code for a project](https://docs.github.com/en/pull-requests/concepts/writing-code-for-a-project)

---

# 4. Développer sur sa branche

Le contributeur peut maintenant modifier les fichiers du projet.

Pour vérifier les modifications :

```bash
git status
```

Pour voir précisément les changements :

```bash
git diff
```

Il est conseillé de faire des commits régulièrement, avec des messages explicites :

```bash
git add .
git commit -m "Ajout de l'écran principal"
```

Exemples de bons messages :

```bash
git commit -m "Ajout du déplacement du serpent"
git commit -m "Correction du calcul du score"
git commit -m "Création du menu principal"
git commit -m "Ajout de la gestion des collisions"
```

Éviter les messages trop vagues comme :

```text
modif
test
ça marche
```

Les commits doivent rester petits et concerner une modification cohérente. [Contributing to open source](https://docs.github.com/en/get-started/exploring-projects-on-github/contributing-to-open-source)

---

# 5. Envoyer sa branche sur GitHub

Lors du premier envoi, utiliser :

```bash
git push -u origin prenom-nom
```

Par exemple :

```bash
git push -u origin alice-interface
```

L’option `-u` associe la branche locale à la branche distante. Ensuite, les prochains envois pourront être faits simplement avec :

```bash
git push
```

Vérifier que la branche existe sur GitHub en allant dans :

```text
Code → Branches
```

La branche doit apparaître à côté de `main`.

---

# 6. Créer une Pull Request

Après le `git push`, GitHub proposera normalement un bouton :

```text
Compare & pull request
```

Cliquer dessus.

Si le bouton n’apparaît pas :

1. Aller dans le dépôt `legralltitouan/Snake2048`.
2. Cliquer sur **Pull requests**.
3. Cliquer sur **New pull request**.
4. Sélectionner les branches suivantes :

```text
base repository : legralltitouan/Snake2048
base branch     : main
compare branch  : prenom-nom
```

La configuration doit être équivalente à :

```text
legralltitouan/Snake2048:main
←
legralltitouan/Snake2048:prenom-nom
```

Donner un titre clair :

```text
Ajout du système de score
```

Dans la description, indiquer :

```text
## Modifications
- Ajout du système de score
- Affichage du score à l'écran

## Tests effectués
- Test du lancement du jeu
- Test de l'incrémentation du score
- Test après collision
```

Puis cliquer sur :

```text
Create pull request
```

Une Pull Request propose les changements d’une branche afin qu’ils soient examinés avant leur fusion dans la branche principale. [Quickstart for pull requests](https://docs.github.com/en/pull-requests/get-started/pull-request-quickstart)

---

# 7. Modifier une Pull Request après des remarques

Si l’administrateur demande des corrections, il ne faut pas créer une nouvelle Pull Request.

Le contributeur retourne sur sa branche :

```bash
git switch prenom-nom
```

Il modifie les fichiers, puis exécute :

```bash
git add .
git commit -m "Correction après revue"
git push
```

Les nouveaux commits seront automatiquement ajoutés à la Pull Request existante. [Quickstart for pull requests](https://docs.github.com/en/pull-requests/get-started/pull-request-quickstart)

---

# 8. Mettre sa branche à jour avec `main`

Si l’option **Require branches to be up to date before merging** est activée, le contributeur doit mettre sa branche à jour lorsque `main` a changé.

## Méthode recommandée avec `merge`

Récupérer la dernière version de `main` :

```bash
git fetch origin
```

Se placer sur sa branche :

```bash
git switch prenom-nom
```

Fusionner `main` dans sa branche :

```bash
git merge origin/main
```

S’il n’y a pas de conflit :

```bash
git push
```

Commandes complètes :

```bash
git fetch origin
git switch prenom-nom
git merge origin/main
git push
```

## En cas de conflit

Git indiquera les fichiers concernés :

```text
CONFLICT (content): Merge conflict in fichier.ext
```

Afficher les fichiers en conflit :

```bash
git status
```

Dans les fichiers concernés, Git affichera des marqueurs comme :

```text
<<<<<<< HEAD
Code de la branche du contributeur
=======
Code de main
>>>>>>> origin/main
```

Le contributeur doit :

1. Choisir le bon code ;
2. Supprimer les marqueurs `<<<<<<<`, `=======` et `>>>>>>>` ;
3. Enregistrer le fichier ;
4. Ajouter le fichier corrigé :

```bash
git add fichier.ext
```

5. Terminer la fusion :

```bash
git commit -m "Résolution des conflits avec main"
```

6. Envoyer la mise à jour :

```bash
git push
```

La Pull Request sera ensuite actualisée.

---

# 9. Vérifications avant de demander la fusion

Avant de demander la fusion, le contributeur doit vérifier :

```bash
git status
```

Puis vérifier qu’il est bien sur sa branche :

```bash
git branch --show-current
```

La commande doit afficher sa branche, par exemple :

```text
alice-interface
```

Il doit aussi vérifier que tous les changements ont été envoyés :

```bash
git log --oneline --max-count=5
git push
```

Enfin, il doit tester le projet localement.

Comme le dépôt ne contient actuellement pas encore de système de build ou de test identifié, chaque groupe devra ajouter dans le `README.md` les commandes propres au projet dès qu’elles seront définies.

---

# 10. Travail de l’administrateur

L’administrateur se rend dans :

```text
Pull requests
```

Puis ouvre la Pull Request concernée.

Il vérifie :

- le titre et la description ;
- les fichiers modifiés ;
- les commits ;
- les éventuels conflits ;
- les tests ;
- les commentaires ;
- la branche de destination.

Il peut consulter les changements dans l’onglet :

```text
Files changed
```

Si une correction est nécessaire, cliquer sur :

```text
Request changes
```

Si tout est correct, cliquer sur :

```text
Approve
```

Avec un ruleset configuré correctement, GitHub attendra les validations et conditions nécessaires avant d’autoriser la fusion.

---

# 11. Fusionner la Pull Request dans `main`

Lorsque les conditions sont remplies, l’administrateur peut cliquer sur :

```text
Merge pull request
```

Puis :

```text
Confirm merge
```

Je recommande d’utiliser :

```text
Squash and merge
```

Cela regroupe les commits de la branche dans un seul commit propre sur `main`.

Après la fusion, l’administrateur peut supprimer la branche distante avec :

```text
Delete branch
```

Cette suppression ne supprime pas la branche `main`.

Le processus officiel de création, de revue et de fusion d’une Pull Request est décrit dans la documentation GitHub. [Quickstart for pull requests](https://docs.github.com/en/pull-requests/get-started/pull-request-quickstart)

---

# 12. Mettre à jour le poste du contributeur après la fusion

Après la fusion dans `main`, le contributeur doit supprimer son ancienne branche locale et récupérer la nouvelle version :

```bash
git switch main
git pull origin main
```

Pour supprimer sa branche locale :

```bash
git branch -d prenom-nom
```

S’il souhaite recommencer une nouvelle tâche :

```bash
git switch -c nouvelle-tache
```

Exemple :

```bash
git switch -c ajout-ecran-game-over
```

---

# 13. Procédure complète résumée pour un contributeur

À utiliser pour chaque nouvelle tâche :

```bash
git switch main
git pull origin main
git switch -c ma-nouvelle-branche
```

Développer, puis :

```bash
git status
git add .
git commit -m "Description de la modification"
git push -u origin ma-nouvelle-branche
```

Créer ensuite une Pull Request :

```text
ma-nouvelle-branche → main
```

Si la Pull Request demande des modifications :

```bash
git add .
git commit -m "Correction après revue"
git push
```

Si `main` a changé :

```bash
git fetch origin
git merge origin/main
git push
```

---

# 14. Version avec GitHub CLI

L’installation de GitHub CLI est facultative : [GitHub CLI quickstart](https://docs.github.com/en/github-cli/github-cli/quickstart)

Se connecter :

```bash
gh auth login
```

Créer une Pull Request :

```bash
gh pr create
```

Créer directement une Pull Request en brouillon :

```bash
gh pr create --draft
```

Lister les Pull Requests :

```bash
gh pr list
```

Voir une Pull Request :

```bash
gh pr view
```

Fusionner une Pull Request avec squash :

```bash
gh pr merge --squash --delete-branch
```

L’administrateur peut aussi choisir la branche et le titre interactifs avec :

```bash
gh pr merge
```

---

# 15. Règles à respecter par tous

Chaque contributeur doit respecter ces règles :

```text
1. Ne jamais travailler directement sur main.
2. Créer une branche par fonctionnalité ou correction.
3. Utiliser des noms de branches explicites.
4. Faire des commits clairs.
5. Pousser sa branche sur GitHub.
6. Passer par une Pull Request.
7. Ne pas fusionner soi-même dans main.
8. Corriger les remarques sur la même Pull Request.
9. Mettre sa branche à jour si main a changé.
10. Ne jamais utiliser git push --force sur main.
```

Convention recommandée pour les branches :

```text
feature/nom-de-la-fonctionnalite
fix/nom-du-bug
docs/nom-de-la-documentation
refactor/nom-du-refactoring
```

Exemples :

```bash
git switch -c feature/menu-principal
git switch -c feature/systeme-score
git switch -c fix/collision-serpent
git switch -c docs/installation
```

Avec cette organisation, les collaborateurs restent des contributeurs avec accès au dépôt, mais leurs modifications passent par leurs branches et par une Pull Request avant d’arriver dans `main`.
