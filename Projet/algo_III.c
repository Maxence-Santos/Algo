#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int algo_glouton(int s, int k, int* V) {
    int A[k];
    int somme = 0;
    for (int j=0;j<k;j++) {
        A[j] = 0;
    }
    int s1 = s;
    int i = k-1;
    while (s1 != 0) {
        A[i] = s1/V[i];
        somme += A[i];
        s1 -= A[i]*V[i];
        i--;
    }
    for (int j=0;j<k;j++) {
        printf("A[%d] : %d\n", j, A[j]);
    }

    return somme;
}

bool test_glouton_compatible(int k, int* V) {
    if (k >= 3) {
        for (int i=V[2]+2;i<V[k-2]+V[k-1];i++) {
            for (int j=0;j<k;j++) {
                if ((V[j] < i) && (algo_glouton(i,k,V)>1+algo_glouton(i-V[j],k,V))) {
                    return false;
                }
            }
        }
    }
    return true;
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
    if (test_glouton_compatible(i,V)) {
        printf("Le test est compatible\n");
    }
    else {
        printf("Le test n'est pas compatible\n");
    }
    printf("Algo glouton : %d\n", algo_glouton(s, i, V));
    free(V); // Libérer la mémoire allouée
    fclose(fichier);
    return 0;
}
