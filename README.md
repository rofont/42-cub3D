# Cub3D

Ce projet est inspiré du jeu Wolfeinstein3D, considéré comme le premier FPS
jamais développé. Il permet d’explorer la technique du ray-casting. L'objectif est de faire une vue dynamique au sein d’un labyrinthe, dans lequel on devra trouver
notre chemin.

## Table des matières

- [Introduction](#introduction)
- [Avertissement](#avertissement-pour-la-partie-bonus)
- [Fonctionnalités](#fonctionnalités)
- [Installation](#installation)
- [Utilisation](#utilisation)
- [Contrôles](#contrôles)
- [Ressources](#ressources)

## Introduction

Cub3D est une opportunité pour plonger dans le monde de la programmation graphique. Vous apprendrez des techniques de rendu, la gestion des événements et la gestion de la boucle de jeu. Le but est de créer un jeu 3D basique en utilisant la bibliothèque MLX42.

## Avertissement (pour la partie Bonus)

**Avertissement pour les personnes épileptiques :**

Ce jeu peut contenir des effets visuels, des motifs lumineux clignotants ou des séquences de lumières clignotantes pouvant provoquer des crises d'épilepsie photosensible chez les individus sensibles. Si vous ou un membre de votre famille avez des antécédents d'épilepsie, veuillez consulter un médecin avant de jouer. Si vous ressentez des étourdissements, des troubles visuels, des contractions musculaires ou des pertes de conscience pendant le jeu, arrêtez immédiatement et consultez un médecin.



## Fonctionnalités

- Parsing de carte en 2D
- Raycasting pour le rendu 3D
- Mappage de textures
- Mécaniques de jeu basiques (déplacement, regard)
- Rendu simple de sprites

## Installation

### Prérequis

- [MLX42](https://github.com/codam-coding-college/MLX42) (inclus dans le projet)
- GCC (GNU Compiler Collection)
- Make

### Cloner le dépôt

```sh
git clone git@github.com:rofont/42-cub3D.git
```

### Construire le projet

```sh
make
```

## Utilisation

Pour lancer le jeu simplement :
```sh
./cub3D ./map/map_de_votre_choix.cub
```

Pour Lancer le jeu avec Bunus :
```sh
make bonus
./cub3D_bonus ./map/map_de_votre_choix.cub
```

## Ressources
- [sujet du projet Cub3D de 42](https://cdn.intra.42.fr/pdf/pdf/114785/fr.subject.pdf)
- [Github MLX42](https://github.com/codam-coding-college/MLX42)
- [Tutoriel sur le raycasting](https://lodev.org/cgtutor/raycasting.html)