#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

int minimum(int a, int b) {
    if (a < b) {
        return a;
    }
    return b;
}

int m(int s, int i, int *V) {
    //printf("s : %d\n", s);
    printf("i : %d\n", i);
    if (i == 0 || s < 0) {
        return INT_MAX;
    }
    if (s == 0) {
        return 0;
    }
    int withoutCurrent = m(s, i - 1, V);
    int withCurrent = m(s - V[i - 1], i, V);
    if (withCurrent != INT_MAX) {
        withCurrent += 1;
    }
    return minimum(withoutCurrent, withCurrent);
}

int main() {
    FILE *fichier;
    fichier = fopen("donnees.txt", "r");
    int ligne;
    fscanf(fichier, "%d", &ligne);
    int s = ligne;//151;
    fscanf(fichier, "%d", &ligne);
    int i = ligne;//3;
    int *V = (int *)malloc(i * sizeof(int));
    fscanf(fichier, "%d", &ligne);
    V[0] = ligne;
    printf("V[0] : %d\n", V[0]);
    fscanf(fichier, "%d", &ligne);
    V[1] = ligne;
    printf("V[1] : %d\n", V[1]);
    fscanf(fichier, "%d", &ligne);
    V[2] = ligne;
    printf("V[2] : %d\n", V[2]);
    printf("S : %d\n", s);
    printf("i : %d\n", i);
    printf("m(s, i) : %d\n", m(s, i, V));
    free(V); // Libérer la mémoire allouée
    fclose(fichier);
    return 0;
}
