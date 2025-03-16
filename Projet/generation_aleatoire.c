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
    int s = 50;
    srand(time(NULL));
    int p_max = 20;
    int a;
    int i = 100;
    int *V = (int *)malloc(i * sizeof(int));
    V[0] = 1;
    for (int j = 1; j < i; j++) {
        V[j] = rand()%(p_max) + 1;
        while (j>0 && V[j] < V[j-1]) {
            a = V[j];
            V[j] = V[j-1];
            V[j-1] = a;
            j--;
        }
    }
    // Afficher le tableau généré
    for (int j = 0; j < i; j++) {
        printf("V[%d] : %d\n", j, V[j]);
    }
    int c=0;
    int d=0;
    for (int m=0;m<100;m++) {
        if (test_glouton_compatible(i,V)) {
        //printf("Le test est compatible\n");
            c++;
        }
        else {
            //printf("Le test n'est pas compatible\n");
            d++;
        }
    
    }
    printf("Nombre de tests compatibles : %d\n",c);
    printf("Nombre de tests non compatibles : %d\n",d);
    free(V);
    return 0;
}
