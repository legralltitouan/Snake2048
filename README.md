---

# Snake2048 - Guide de Contribution Git

Ce guide explique la procédure pas à pas pour récupérer le projet, travailler sur une nouvelle fonctionnalité et proposer vos modifications sur le dépôt GitHub.

---

## 1. Prérequis

* **Git** installé sur votre machine.
* **Visual Studio Community** (avec le composant *Développement Desktop en C++*).

---

## 2. Cloner le dépôt localement

Ouvrez un terminal (CMD, PowerShell ou le terminal de Visual Studio) et lancez la commande suivante :

```bash
git clone https://github.com/legralltitouan/Snake2048.git
cd Snake2048

```

* **Vérification :** Tapez `dir` (sous Windows) ou `ls` pour vérifier que la solution `Snake2048.slnx` (ou `.sln`) et le dossier `Snake2048` sont bien présents.

---

## 3. Créer une nouvelle branche de travail

Il est recommandé de ne pas travailler directement sur la branche `main`. Créez une branche dédiée à votre fonctionnalité ou correction :

```bash
git checkout -b nom_de_votre_branche

```

> **Exemple :** `git checkout -b ajout-score` ou `git checkout -b nom_dev`

* **Vérification :** Tapez `git branch`. Une étoile `*` doit apparaître à côté de votre nouvelle branche.

---

## 4. Effectuer des modifications et les valider (Commit)

1. Ouvrez le projet dans Visual Studio et apportez vos modifications dans le code.
2. Une fois vos changements enregistrés et testés, retournez dans le terminal.
3. Vérifiez les fichiers modifiés :
```bash
git status

```


4. Ajoutez les fichiers au suivi Git :
```bash
git add .

```


5. Enregistrez vos modifications avec un message explicite :
```bash
git commit -m "Description claire de vos modifications"

```



* **Vérification :** Un message de Git confirme la création du commit avec le nombre de fichiers modifiés.

---

## 5. Publier la branche sur GitHub (Push)

Pour envoyer votre nouvelle branche et vos commits sur le dépôt distant :

```bash
git push -u origin nom_de_votre_branche

```

* **Vérification :** Allez sur la page GitHub du projet (`[https://github.com/legralltitouan/Snake2048.git](https://github.com/legralltitouan/Snake2048.git)`). Votre nouvelle branche doit apparaître dans le menu déroulant des branches.

---

## 6. Mettre à jour sa branche avec `main` (Optionnel)

Si des modifications ont été apportées sur la branche `main` pendant que vous travailliez, récupérez-les sur votre branche locale :

```bash
git checkout main
git pull origin main
git checkout nom_de_votre_branche
git merge main

```

* **Vérification :** Git indique `Already up to date` ou valide la fusion des modifications.
