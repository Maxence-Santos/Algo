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
    for (int j = 0; j < i; j++) {
        fscanf(fichier, "%d", &ligne);
        V[j] = ligne;

    }
    for (int j = 0; j < i; j++) {
        printf("V[%d] : %d\n", j, V[j]);
    }
    printf("S : %d\n", s);
    printf("i : %d\n", i);
    printf("m(s, i) : %d\n", m(s, i, V));
    free(V); // Libérer la mémoire allouée
    fclose(fichier);
    return 0;
}
