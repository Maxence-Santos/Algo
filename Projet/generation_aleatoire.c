#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

int algo_glouton(int s, int k, int* V) {
    int A[k];
    for (int j=0;j<k;j++) {
        A[j] = 0;
    }
    int s1 = s;
    int i = k-1;
    int c = 0;
    while (s1 != 0) {
        A[i] = s1/V[i];
        c += A[i];
        s1 -= A[i]*V[i];
        i--;
    }
    return c;
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
    int s = 20;
    srand(time(NULL));
    int r_max = 20;
    int a;
    int i = 5;
    int *V = (int *)malloc(i * sizeof(int));
    V[0] = 1;
    for (int j = 1; j < i-1; j++) {
        V[j] = V[j-1] + rand()%(r_max/i) + 1;
        while (V[j] < V[j-1]) {
            a = V[j];
            V[j] = V[j-1];
            V[j-1] = a;
        }
    }
    // Afficher le tableau généré
    for (int j = 0; j < i; j++) {
        printf("V[%d] : %d\n", j, V[j]);
    }
    if (test_glouton_compatible(i,V)) {
        printf("Le test est compatible\n");
    }
    else {
        printf("Le test n'est pas compatible\n");
    }
    free(V);
    return 0;
}