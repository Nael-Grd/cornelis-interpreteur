#include "../include/pile.h"
#include "../include/bloc.h"
#include "../include/couleur.h"
#include "../include/lecturePPM.h"
#include <stdlib.h> 
#include <string.h>
#include <stdio.h>


void lire_entier(stack s) {
    char buf[100];
    int val;
    printf("Entrez un entier : "); 
    while (1) {
        if (!fgets(buf, 100, stdin)) return;
        if (sscanf(buf, "%d", &val) == 1) {
            push(s, val);
            break;
        }
    }
}

void lire_char(stack s) {
    char buf[100];
    char c;
    printf("Entrez un caractere : ");
    if (fgets(buf, 100, stdin) && sscanf(buf, "%c", &c) == 1) {
        push(s, (int)c);
    }
}

int main(int argc, char* argv[]) {
    if (argc != 2) { printf("Usage: %s <file>\n", argv[0]); exit(1); }

    FILE* file = fopen(argv[1], "r");
    if (!file) { perror("Erreur ouverture"); exit(1); }

    infoPPM* info = informations_PPM(file);
    if (!info) exit(1);

    stack s = new();
    int h = info->hauteur, l = info->largeur;
    
    // Matrice de traitement
    int** traite = malloc(h * sizeof(int*));
    for (int i = 0; i < h; i++) traite[i] = calloc(l, sizeof(int));

    // État initial
    direction d = EST;
    bord b = BABORD;
    
    int x = 0, y = 0; // position courante
    couleur c_cur = nom_couleur(info->pixels[0]);
    couleur c_next;
    
    // Initialisation premier bloc
    traitement(info, c_cur, x, y, traite);
    Point p_sortie = pixel_suivant(traite, d, b, h, l);

    int bloquants = 0;
    int gliss_blanc = 0;

    while (bloquants < 8) {
        int next_x = p_sortie.x + (d == EST) - (d == OUEST);
        int next_y = p_sortie.y + (d == SUD) - (d == NORD);

        int est_mur = 0;
        if (next_x < 0 || next_x >= l || next_y < 0 || next_y >= h) {
            est_mur = 1;
            c_next = autre;
        } else {
            c_next = nom_couleur(info->pixels[next_y * l + next_x]);
            if (c_next == autre) est_mur = 1;
            if (!gliss_blanc && c_next == c_cur) est_mur = 1;
        }

        if (est_mur) {
            bloquants++;
            if (bloquants % 2 == 1) b = changer_bord(b);
            else d = changer_direction(d);
            
            if (gliss_blanc) {
                p_sortie.x = x; 
                p_sortie.y = y;
            } else {
                p_sortie = pixel_suivant(traite, d, b, h, l);
            }
        } 
        else if (estPassante(info->pixels[next_y * l + next_x])) {
            bloquants = 0;
            if (!gliss_blanc) gliss_blanc = 1;
            
            x = next_x; y = next_y;   
            c_cur = c_next;        
            p_sortie.x = x; p_sortie.y = y; 
        } 
        else {
            bloquants = 0;
            
            if (!gliss_blanc) {
                int dc = dif_couleur(c_cur, c_next);
                int dl = dif_luminosite(c_cur, c_next);
                if (dc==0 && dl==1) push(s, taille_bloc(traite, l, h));
                else if (dc==0 && dl==2 && stack_size(s)>=1) pop(s);
                else if (dc==1 && stack_size(s)>=2) {
                    if (dl==0) somme(s); else if (dl==1) difference(s); else if (dl==2) produit(s);
                }
                else if (dc==2) {
                    if (stack_size(s)>=1 && dl==2) zero(s);
                    else if (stack_size(s)>=2) { if (dl==0) division(s); else if (dl==1) reste(s); }
                }
                else if (dc==3) {
                    if (dl==0 && stack_size(s)>=2) plusgrand(s);
                    else if (stack_size(s)>=1) {
                        int val = peek(s); pop(s);
                        if (dl==1) { int n=(val%4+4)%4; for(int k=0;k<n;k++) d=changer_direction(d); }
                        else if (dl==2) { int n=(val%2+2)%2; for(int k=0;k<n;k++) b=changer_bord(b); }
                    }
                }
                else if (dc==4) {
                    if (dl==0 && stack_size(s)>=1) duplique(s);
                    else if (dl==1 && stack_size(s)>=2) tourne(s);
                    else if (dl==2) lire_entier(s);
                }
                else if (dc==5) {
                    if (dl==0) lire_char(s);
                    else if (stack_size(s)>=1) {
                        int val = peek(s); pop(s);
                        if (dl==1) printf("%d", val);
                        else if (dl==2) printf("%c", (char)val);
                        fflush(stdout);
                    }
                }
            }

            gliss_blanc = 0;
            x = next_x; y = next_y;
            c_cur = c_next;

            for(int i=0; i<h; i++) memset(traite[i], 0, l*sizeof(int));
            traitement(info, c_cur, x, y, traite);
            p_sortie = pixel_suivant(traite, d, b, h, l);
        }
    }

    for(int i=0; i<h; i++) free(traite[i]);
    free(traite);
    free(info->pixels);
    free(info);
    fclose(file);
    return 0;
}