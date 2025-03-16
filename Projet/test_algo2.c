#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

void algo2(int somme, int indice, int* valeurs, int** T, int* A) {
    for (int j = 0; j <= somme; j++)
        for (int k = 0; k <= indice; k++)
            T[j][k] = INT_MAX;
    
    for (int j = 0; j <= indice; j++)
        T[0][j] = 0;
    
    for (int j = 1; j <= somme; j++) {
        for (int k = 1; k <= indice; k++) {
            int min1 = (j - valeurs[k - 1] < 0) ? INT_MAX : T[j - valeurs[k - 1]][k] + 1;
            int min2 = T[j][k - 1];
            T[j][k] = minimum(min1, min2);
        }
    }
    
    int s1 = somme, i1 = indice;
    for (int j = 0; j < i1; j++) A[j] = 0;
    while (s1 != 0 && i1 != 0) {
        if (T[s1][i1] != T[s1][i1 - 1]) {
            A[i1 - 1]++;
            s1 -= valeurs[i1 - 1];
        } else {
            i1--;
        }
    }
}

void mesurer_temps(int somme, int taille, int* valeurs, double* temps) {
    clock_t debut, fin;
    debut = clock();
    int** T = (int**)malloc((somme + 1) * sizeof(int*));
    for (int j = 0; j <= somme; j++)
        T[j] = (int*)malloc((taille + 1) * sizeof(int));
    int* A = (int*)malloc(taille * sizeof(int));
    algo2(somme, taille, valeurs, T, A);
    fin = clock();
    *temps = ((double)(fin - debut)) / CLOCKS_PER_SEC;
    for (int j = 0; j <= somme; j++) free(T[j]);
    free(T);
    free(A);
}

int main() {
    int valeurs_d[] = {2, 3, 4};
    int valeurs_S[] = {20, 50, 100, 150, 200, 250, 300, 350, 400, 450, 500, 550, 600, 650, 700, 750, 800, 850, 900, 950, 1000};
    int valeurs_k[] = {10, 20, 30, 40, 50, 60};
    bool continuer = true;
    
    FILE *fichier = fopen("resultats2.txt", "w");
    fprintf(fichier, "d S k algo2_temps\n");
    
    for (int d = 0; d < 3; d++) {
        for (int ki = 0; ki < 6; ki++) {
            int k = valeurs_k[ki];
            int valeurs[k];
            for (int j = 0; j < k; j++) valeurs[j] = (int)pow(valeurs_d[d], j);
            for (int si = 0; si < 21; si++) {
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