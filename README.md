# Projet Scolaire en C

## Description
TODO

## Structure du Projet
TODO

## Prérequis
- Un compilateur C (`gcc`)
- `make` pour faciliter la compilation ou le développement.

## Compilation et Exécution

1. Compiler avec Make :
    ```sh
    make
    ```

1. Compiler sans make :
    ```sh
    gcc -Iinclude -o output src/*.c
    ```

2. Exécuter le programme avec la commande :
    ```sh
    ./output
    ```

## Développement
### Lancer les Tests Unitaires
Certaines méthodes du projet sont testés via le framework Unity, pour lancer les TU :

1. Spécifier dans `TEST_SRC` les fichiers sources à tester.
2. Lancer les TU :
    ```sh
    make test
    ```

## Auteurs
- [**Mathéo NGUYEN**](https://github.com/LiberiBg)
- **Alexandre RABOUIN**
- **Gabriel PIERRET**


## Licence
TODO