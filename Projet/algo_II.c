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

void afficher(int **T, int s, int i) {
    printf("\n");
    printf("Tableau (X = Inf) : \n");
    printf("i/s ");
    for (int j= 0;j<s+1;j++) {
        printf("%d ", j);
    }
    printf("\n");
    for (int j=0;j<i+1;j++) {
        printf("%d : ", j);
        for (int k=0;k<s+1;k++) {
            if (T[k][j] == INT_MAX) {
                printf("X ");
            }
            else {
            printf("%d ", T[k][j]);
            }
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    FILE *fichier;
    fichier = fopen("donnees.txt", "r");
    int ligne;
    fscanf(fichier, "%d", &ligne);
    int s = ligne;//151;
    printf("S = %d\n", s);
    fscanf(fichier, "%d", &ligne);
    int i = ligne;//3;
    printf("i = %d\n", i);
    int *V = (int *)malloc(i * sizeof(int));
    for (int j = 0; j < i; j++) {
        fscanf(fichier, "%d", &ligne);
        V[j] = ligne;

    }
    int **T = (int **)malloc((s+1) * sizeof(int*));
    for (int j=0;j<s+1;j++) {
        T[j] = (int *)malloc((i+1) * sizeof(int));
    }
    for (int j = 0; j < i; j++) {
        printf("V[%d] : %d\n", j, V[j]);
    }

    int min1 = 0;
    int min2 = 0;
    for (int j=0;j<s+1;j++) {
        for (int k=0;k<i+1;k++) {
            T[j][k] = INT_MAX;
        }
    }
    for (int j=0;j<i+1;j++) {
        T[0][j] = 0;
    }

    for (int j=1;j<s+1;j++) {
        for (int k=1;k<i+1;k++) {
            if (j-V[k-1] < 0) {
                min1 = INT_MAX;
            }
            else {
                min1 = T[j-V[k-1]][k]+1;
            }
            min2 = T[j][k-1];
            T[j][k] = minimum(min1,min2);
        }
    }

    afficher(T,s,i);

    int s1 =s;
    int i1 = i;
    int* A = (int *)malloc(i1 * sizeof(int));
    for (int j=0;j<i1;j++) {
        A[j] = 0;
    }
    while (s1 != 0 && i1 != 0) {
        if (T[s1][i1] != T[s1][i1-1]) {
            A[i1-1]++;
            s1 -= V[i1-1];
        }
        else {
            i1--;
        }
    }
    printf("Il faut : %d pots pour S = %d et i = %d\n", T[s][i], s, i);
    printf("Il y a : \n");
    for (int j=0;j<i;j++) {
        printf("- %d pot V[%d] (%d)\n", A[j], j, V[j]);
    }
    return 0;
}
