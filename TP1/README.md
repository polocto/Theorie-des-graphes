# Théorie des Graphes - TD/TP 1

Ce dépôt contient les exercices et les implémentations en C++ pour le TD/TP 1 sur la théorie des graphes. Ce travail couvre divers aspects de la modélisation et de la résolution de problèmes à l'aide de graphes.

## Table des Matières

1. [Introduction](#introduction)
2. [Exercices](#exercices)
3. [Implémentation en C++](#implémentation-en-c++)
4. [Instructions pour Compiler et Exécuter](#instructions-pour-compiler-et-exécuter)
5. [Crédits](#crédits)

## Introduction

Voir présentation du sujet [ici](../README.md).

## Exercices

### Exercice 1 : Amis en Commun
Montrer qu'il y a au moins deux personnes ayant le même nombre d'amis dans un groupe.

### Exercice 2 : Groupes de Travail
Déterminer le nombre de personnes nécessaires pour constituer 5 groupes de travail avec des contraintes spécifiques.

### Exercice 3 : Résolution de Sudoku
Formaliser le problème de Sudoku sous forme de graphe.

### Exercice 4 : Automate pour Notation Scientifique
Créer un automate reconnaissant les nombres en notation scientifique.

### Exercice 5 : Coloration de Cartes
Colorier une carte de sorte que deux pays frontaliers n'aient pas la même couleur.

### Exercice 6 : Allocation de Fréquences
Attribuer des fréquences à des stations émettrices en minimisant les interférences.

### Exercice 7 : Jeu des Allumettes
Modéliser le jeu des allumettes à l'aide d'un graphe d'états.

## Implémentation en C++

Les exercices sont implémentés en C++, en utilisant des structures de données comme les matrices d'adjacence et les listes d'adjacence. Les algorithmes de coloration, tels que l'algorithme de Welsh et Powell, sont également implémentés.

## Instructions pour Compiler et Exécuter

1. **Cloner le Dépôt** :
   ```bash
   git clone https://github.com/polocto/Theorie-des-graphes.git
   cd Theorie-des-graphes/TP1

2. **Compiler le code** :
    ```bash
    cd build
    cmake . .
    cmake --build .
    ```

3. **Lancer le code** :
    ```bash
    #Linux/MacOs
    ./TP1 [path/to/file]
    ```

## Crédits

Paul SADE