#include "../include/lecturePPM.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

infoPPM* informations_PPM(FILE* f) {
    char magic[3];
    int largeur, hauteur, couleurMax;

    // 1. Lecture du Magic Number
    if (fscanf(f, "%2s", magic) != 1 || strcmp(magic, "P6") != 0) {
        fprintf(stderr, "Erreur : Fichier P6 invalide\n");
        return NULL;
    }

    // 2. Sauter les commentaires et espaces proprement
    int c;
    while ((c = fgetc(f)) != EOF) {
        if (c == '#') { 
            while ((c = fgetc(f)) != '\n' && c != EOF);
        } else if (!isspace(c)) { 
            ungetc(c, f); // On remet le chiffre trouvé
            break;
        }
    }

    // 3. Lecture Dimensions
    if (fscanf(f, "%d %d %d", &largeur, &hauteur, &couleurMax) != 3) {
        return NULL;
    }

    // 4. CORRECTION CRITIQUE DU SAUT DE LIGNE
    // On doit consommer exactement un caractère whitespace après le 255.
    c = fgetc(f);
    if (c == '\r') { // Cas Windows rare mais possible
        c = fgetc(f);
        if (c != '\n') ungetc(c, f);
    }
    // Si c'est \n ou espace, c'est consommé et on est calé au byte près.

    // 5. Lecture des données
    infoPPM* p = malloc(sizeof(infoPPM));
    p->largeur = largeur;
    p->hauteur = hauteur;
    p->couleurMax = couleurMax;
    p->pixels = malloc(largeur * hauteur * sizeof(pixel));
    
    if (fread(p->pixels, sizeof(pixel), largeur * hauteur, f) != (size_t)(largeur * hauteur)) {
        fprintf(stderr, "Erreur de lecture des pixels\n");
        free(p->pixels);
        free(p);
        return NULL;
    }

    return p;
}