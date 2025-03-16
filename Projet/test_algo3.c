#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <limits.h>
#include <time.h>
#include <math.h>

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int algo1(int somme, int indice, int *valeurs) {
    if (indice == 0 || somme < 0) return INT_MAX;
    if (somme == 0) return 0;
    int sansCourant = algo1(somme, indice - 1, valeurs);
    int avecCourant = algo1(somme - valeurs[indice - 1], indice, valeurs);
    if (avecCourant != INT_MAX) avecCourant += 1;
    return minimum(sansCourant, avecCourant);
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

int algo_glouton(int somme, int taille, int* valeurs) {
    int A[taille], somme_glouton = 0, s1 = somme, i = taille - 1;
    for (int j = 0; j < taille; j++) A[j] = 0;
    while (s1 > 0) {
        A[i] = s1 / valeurs[i];
        somme_glouton += A[i];
        s1 -= A[i] * valeurs[i];
        i--;
    }
    return somme_glouton;
}

void mesurer_temps(int somme, int taille, int* valeurs, double* t3) {
    clock_t debut, fin;

    debut = clock();
    algo_glouton(somme, taille, valeurs);
    fin = clock();
    *t3 = ((double)(fin - debut)) / CLOCKS_PER_SEC;
}

int main() {
    int valeurs_d[] = {2, 3, 4};
    int valeurs_S[] = {500000, 3000000, 5500000, 8000000, 10500000, 13000000, 15500000, 18000000, 20500000, 23000000, 25500000, 28000000, 30500000, 33000000, 35500000, 38000000, 40500000, 43000000, 45500000, 48000000};
    int valeurs_k[] = {5000, 20000, 35000, 50000, 65000, 80000};
    bool continuer = true;
    
    FILE *fichier = fopen("resultats3.txt", "w");
    fprintf(fichier, "d S k algo3_temps\n");
    
    for (int d = 0; d < 3; d++) {
        for (int ki = 0; ki < 6; ki++) {
            int k = valeurs_k[ki];
            int valeurs[k];
            for (int j = 0; j < k; j++) valeurs[j] = (int)pow(valeurs_d[d], j);
            for (int si = 0; si < 21; si++) {
                int S = valeurs_S[si];
                double t3 = 0;
                mesurer_temps(S, k, valeurs, &t3);
                if (!continuer) break;
                fprintf(fichier, "%d %d %d %f\n", valeurs_d[d], S, k, t3);
            }
            if (!continuer) break;
        }
        if (!continuer) break;
    }
    fclose(fichier);
    return 0;
}