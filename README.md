# Projet Scolaire en C

## Description
Projet FISA S5

## Structure du Projet
TODO

## Prérequis
- Un compilateur C (`gcc`)
- `make` pour faciliter la compilation ou le développement.

## Compilation et Exécution

1. Compiler et éxecuter avec Make :
    ```sh
    make all
    ```

1. Compiler sans make :
    ```sh
    gcc -Iinclude -o output src/analyseur.c src/main.c
    ```

2. Exécuter le programme avec la commande :
    ```sh
    ./output
    ```

## Développement
### Lancer les Tests Unitaires
Certaines méthodes du projet sont testés via le framework Unity, pour lancer les TU :

1. Spécifier dans `TEST_SRC` les fichiers sources à tester.
2. Lancer les TU avec make:
    ```sh
    make test
    ```

2. Lancer les TU sans make:
    ```sh
    gcc -Iinclude -o test_output tests/*.c src/unity.c src/analyseur.c
    ```
3. Exécuter le programme si compilé sans make :
    ```sh
    ./output
    ```
    
## Auteurs
- [**Mathéo NGUYEN**](https://github.com/LiberiBg)
- **Alexandre RABOUIN**
- **Gabriel PIERRET**


## Licence
TODO