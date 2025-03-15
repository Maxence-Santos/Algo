#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <limits.h>

int minimum(int a, int b) {
    if (a<b) {
        return a;
    }
    return b;
}

int main() {
    FILE *fichier;
    fichier = fopen("donnees.txt", "r");
    int ligne;
    fscanf(fichier, "%d", &ligne);
    int s = ligne;
    fscanf(fichier, "%d", &ligne);
    int i = ligne;
    int *V = (int *)malloc(i * sizeof(int));
    for (int j = 0; j < i; j++) {
        fscanf(fichier, "%d", &ligne);
        V[j] = ligne;

    }
    for (int j = 0; j < i; j++) {
        printf("V[%d] : %d\n", j, V[j]);
    }
    int **T = (int **)malloc(s+1 * sizeof(int*));
    for (int j=0;j<s+1;j++) {
        T[j] = (int *)malloc(i+1 * sizeof(int));
    }
    int min1 = 0;
    int min2 = 0;
    for (int j=0;j<s+1;j++) {
        T[j][0] = INT_MAX;
    }
    for (int j=0;j<i+1;j++) {
        T[0][j] = 0;
    }
    for (int j=0;j<s;j++) {
        for (int k=0;k<i;k++) {
            if (s-V[k-1] < 0) {
                min1 = INT_MAX;
            }
            else {
                min1 = T[s-V[k]][k]+1;
            }
            min2 = T[s][k-1];
            T[s][k] = minimum(min1,min2);
        }
    }
    int s1 =s;
    int i1 = i;
    int* A = (int *)malloc(i1 * sizeof(int));
    for (int j=0;j<i1;j++) {
        A[j] = 0;
    }
    while (s1 != 0 && i1 != 0) {
        if (T[s1][i1] != T[s1][i1-1]) {
            A[i1]++;
            s1 -= V[i1-1];
            printf("bgf"); 
        }
        else {
            i1--;
        }
    }
    printf("A[k] : %d", A[i1]);
    return 0;
}
