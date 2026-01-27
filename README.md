# Cornelis interpreter

## *FR* Documentation du Projet (English below)

Le but de ce projet est d'implémenter un interpréteur pour le langage de programmation Cornelis, fortement inspiré du langage [Piet](https://www.dangermouse.net/esoteric/piet.html).
En Cornelis comme en Piet, les programmes sont donnés sous la forme d'image en deux dimensions.

# Comportement attendu des programmes :
Vous trouverez dans le repretoire /tests un certains nombres de fichiers d'entrées (exemple.ppm).

- adder.ppm : prend en entrée deux entiers et affiche leur somme

- alpha.ppm : affiche les lettres de a à z

- cowsay.ppm : prend en entrée une ligne de texte et affiche une vache qui répète cette ligne

- euclide.ppm : prend en entrée deux entiers et affiche leur PGCD

- fact.ppm : prend en entrée un entier et affiche sa factorielle

- hw2.ppm : affiche "Hello, world!"

- hw3.ppm : affiche "Hello, world!"

- hw4.ppm : affiche "Hello, world!"

- mondrian.ppm : affiche "Hello, world!"

- Piet_hello.ppm : affiche "Hello, world!" (sans retour à la ligne)

- pietquest.ppm : propose un petit jeu

- pi.ppm : calcul une valeur approximative de pi

- power.ppm : prend en entrée deux entiers et affiche le premier à la puissance le second

- tetris.ppm : affiche "Tetris" sans retour à la ligne. (À noter : les blocs ont tous une forme de pièce en Tetris.)

###  Compilation et Exécution

Toutes les commandes s'exécutent depuis le répertoire racine du projet.

1.  **Compiler le projet :**
    ```bash
    make
    ```

2.  **Exécuter le programme :**
    Essayer les fichiers tests

    ```bash
    ./cornelis tests/alpha.ppm
    ```

3.  **Nettoyage des fichiers objets :**
    ```bash
    make clean
    ```


---

## *ENG* Project Documentation 
The goal of this project is to implement an interpreter for the Cornelis programming language, which is heavily inspired by the [Piet](https://www.dangermouse.net/esoteric/piet.html) language.
In Cornelis, as in Piet, programs are given in the form of two-dimensional images.

# Expected behavior of programs :
You will find a number of input files (example.ppm) in the /tests directory.

- adder.ppm : takes two integers as input and displays their sum

- alpha.ppm : displays the letters from a to z

- cowsay.ppm : takes a line of text as input and displays a cow that repeats that line

- euclide.ppm : takes two integers as input and displays their GCD

- fact.ppm : takes an integer as input and displays its factorial

- hw2.ppm : display “Hello, world!”

- hw3.ppm : display “Hello, world!”

- hw4.ppm : display “Hello, world!”

- mondrian.ppm : display “Hello, world!”

- Piet_hello.ppm : display “Hello, world!” (without line break)

- pietquest.ppm : suggests a little game

- pi.ppm : calculate an approximate value of pi

- power.ppm : takes two integers as input and displays the first raised to the power of the second

- tetris.ppm : displays “Tetris” without line breaks. (Note: the blocks are all shaped like Tetris pieces.)

###  Compilation et Exécution

1.  **Compile the project :**
    ```bash
    make
    ```

2.  **Run the program :**
    Try the test files

    ```bash
    ./cornelis tests/alpha.ppm
    ```

3.  **Cleaning up object files :**
    ```bash
    make clean
    ```
