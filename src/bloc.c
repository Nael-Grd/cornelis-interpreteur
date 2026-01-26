#include "../include/bloc.h"
#include <string.h>
#include <stdlib.h>

void explorer_bloc(infoPPM* info, couleur init, int x, int y, int** traite) {
    if (x < 0 || x >= info->largeur || y < 0 || y >= info->hauteur) return;

    if (traite[y][x] == 1) return; 
    if (nom_couleur(info->pixels[y * info->largeur + x]) != init) return;

    traite[y][x] = 1; // marqué

    explorer_bloc(info, init, x + 1, y, traite);
    explorer_bloc(info, init, x - 1, y, traite);
    explorer_bloc(info, init, x, y + 1, traite);
    explorer_bloc(info, init, x, y - 1, traite);
}

int** traitement(infoPPM* info, couleur init, int x, int y, int** traite) {
    explorer_bloc(info, init, x, y, traite);
    return traite;
}

bord changer_bord(bord b) {
    return (b == BABORD) ? TRIBORD : BABORD;
}

direction changer_direction(direction d) {
    switch(d) {
        case EST: return SUD;
        case SUD: return OUEST;
        case OUEST: return NORD;
        case NORD: return EST;
        default: return d;
    }
}

int taille_bloc(int** bloc, int largeur, int hauteur) {
    int cpt=0;
    for (int i=0; i<hauteur; i++) {
        for (int j=0; j<largeur; j++) {
            if (bloc[i][j] == 1) cpt++;
        }
    }
    return cpt;
}

Point pixel_suivant(int** bloc, direction d, bord b, int hauteur, int largeur) {
    Point res = {0, 0};
    int frontiere = -1;

    switch (d) {
        case EST: // max x
            for (int x = largeur - 1; x >= 0; x--) {
                for (int y = 0; y < hauteur; y++) {
                    if (bloc[y][x] == 1) { frontiere = x; goto found; }
                }
            }
            break;
        case OUEST: // min x
            for (int x = 0; x < largeur; x++) {
                for (int y = 0; y < hauteur; y++) {
                    if (bloc[y][x] == 1) { frontiere = x; goto found; }
                }
            }
            break;
        case SUD: // max y
            for (int y = hauteur - 1; y >= 0; y--) {
                for (int x = 0; x < largeur; x++) {
                    if (bloc[y][x] == 1) { frontiere = y; goto found; }
                }
            }
            break;
        case NORD: // min y
            for (int y = 0; y < hauteur; y++) {
                for (int x = 0; x < largeur; x++) {
                    if (bloc[y][x] == 1) { frontiere = y; goto found; }
                }
            }
            break;
    }

found:
    if (frontiere == -1) return res;

    switch (d) {
        case EST:
            res.x = frontiere;
            if (b == BABORD) {   // haut
                for (int y = 0; y < hauteur; y++) if (bloc[y][frontiere] == 1) { res.y = y; break; }
            } else {   // bas
                for (int y = hauteur - 1; y >= 0; y--) if (bloc[y][frontiere] == 1) { res.y = y; break; }
            }
            break;
        case OUEST:
            res.x = frontiere;
            if (b == BABORD) {   // bas
                for (int y = hauteur - 1; y >= 0; y--) if (bloc[y][frontiere] == 1) { res.y = y; break; }
            } else {   // haut
                for (int y = 0; y < hauteur; y++) if (bloc[y][frontiere] == 1) { res.y = y; break; }
            }
            break;
        case SUD:
            res.y = frontiere;
            if (b == BABORD) {   // droite
                for (int x = largeur - 1; x >= 0; x--) if (bloc[frontiere][x] == 1) { res.x = x; break; }
            } else {   // gauche
                for (int x = 0; x < largeur; x++) if (bloc[frontiere][x] == 1) { res.x = x; break; }
            }
            break;
        case NORD:
            res.y = frontiere;
            if (b == BABORD) {   // gauche
                for (int x = 0; x < largeur; x++) if (bloc[frontiere][x] == 1) { res.x = x; break; }
            } else {   // droite
                for (int x = largeur - 1; x >= 0; x--) if (bloc[frontiere][x] == 1) { res.x = x; break; }
            }
            break;
    }
    return res;
}