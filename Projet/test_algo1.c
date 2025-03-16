#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>

// fonction pour trouver le minimum entre deux nombres
int minimum(int a, int b) {
    return (a < b) ? a : b;
}

// algo1 pour trouver le nombre minimum d'elements pour atteindre une somme
int algo1(int somme, int indice, int *valeurs) {
    if (indice == 0 || somme < 0) return INT_MAX;
    if (somme == 0) return 0;
    int sansCourant = algo1(somme, indice - 1, valeurs);
    int avecCourant = algo1(somme - valeurs[indice - 1], indice, valeurs);
    if (avecCourant != INT_MAX) avecCourant += 1;
    return minimum(sansCourant, avecCourant);
}

// fonction pour mesurer le temps d'execution de algo1
void mesurer_temps(int somme, int taille, int* valeurs, double* temps) {
    clock_t debut, fin;
    if (*temps < 60.0) {
        debut = clock();
        algo1(somme, taille, valeurs);
        fin = clock();
        *temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    }
}

int main() {
    int valeurs_d[] = {2, 3, 4};
    int valeurs_S[] = {10, 25, 50, 75, 100, 125, 150, 175, 200, 225, 250, 275, 300, 325, 350, 375, 400, 425, 450, 475, 500};
    int valeurs_k[] = {5, 10, 15, 20, 25, 30};
    bool continuer = true;
    
    // ouvrir le fichier pour ecrire les resultats
    FILE *fichier = fopen("resultats1.txt", "w");
    fprintf(fichier, "d S k algo1_temps\n");
    
    // boucles pour tester differentes combinaisons de d, k et S
    for (int d = 0; d < 3; d++) {
        for (int ki = 0; ki < 6; ki++) {
            int k = valeurs_k[ki];
            int valeurs[k];
            for (int j = 0; j < k; j++) valeurs[j] = (int)pow(valeurs_d[d], j);
            for (int si = 0; si < 20; si++) {
                int S = valeurs_S[si];
                double temps = 0;
                mesurer_temps(S, k, valeurs, &temps);
                if (!continuer) break;
                fprintf(fichier, "%d %d %d %f\n", valeurs_d[d], S, k, temps);
            }
            if (!continuer) break;
        }
        if (!continuer) break;
    }
    fclose(fichier);
    return 0;
}