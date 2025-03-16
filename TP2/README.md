# Théorie des Graphes - TD/TP 2

Ce dépôt contient les exercices et implémentations en C++ pour le TD/TP 2 sur la théorie des graphes. Ce travail couvre les parcours de graphes (BFS et DFS), la recherche des composantes connexes, et les chaînes et cycles eulériens.

## Table des Matières

1. [Introduction](#introduction)
2. [Exercices](#exercices)
3. [Implémentation en C++](#implémentation-en-c++)
4. [Instructions pour Compiler et Exécuter](#instructions-pour-compiler-et-exécuter)
5. [Crédits](#crédits)

## Introduction

Voir présentation du sujet [ici](../README.md).

## Exercices

### Parcours de Graphes

- **BFS (Breadth-First Search)** : Effectuer un parcours en largeur à partir d'un sommet donné et déterminer l'ordre de découverte des sommets.
- **DFS (Depth-First Search)** : Effectuer des parcours en profondeur en utilisant une pile et comparer les arborescences obtenues.

### Composantes Connexes

- **Recherche des Composantes Connexes** : Ajouter une méthode pour rechercher et afficher les composantes connexes d'un graphe non orienté.

### Chaînes et Cycles Eulériens

- **Recherche de Chaînes ou Cycles Eulériens** : Déterminer et afficher si un graphe non orienté admet un cycle ou une chaîne eulérienne.

## Implémentation en C++

Les exercices sont implémentés en C++. Le programme est capable de :

- Charger un graphe à partir d'un fichier texte.
- Afficher le graphe en console.
- Effectuer des parcours BFS et DFS.
- Rechercher et afficher les composantes connexes.
- Déterminer et afficher les chaînes ou cycles eulériens.

## Instructions pour Compiler et Exécuter

1. **Cloner le Dépôt** :
   ```bash
   git clone https://github.com/polocto/Theorie-des-graphes.git
   cd Theorie-des-graphes/TP2

2. **Compiler le code** :
    ```bash
    cd build
    cmake . .
    cmake --build .
    ```

3. **Lancer le code** :
    ```bash
    #Linux/MacOs
    ./TP2 [path/to/file]
    ```

## Crédits

Paul SADE
