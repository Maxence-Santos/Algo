#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

int algo_glouton(int s, int k, int* V) {
    int* A = (int *)malloc(k * sizeof(int));
    for (int j=0;j<k;j++) {
        A[j] = 0;
    }
    int s1 = s;
    int i = k;
    /*for (int i=s;i>=0;i--) {
        A[i] = s1/V[i];
        printf("vgdhh");
        s1 -= A[i]*V[i];
    }*/
    while (s1 != 0) {
        A[i] = s1/V[i];
        s1 -= A[i]*V[i];
        i--;
    }
    return A[k];
}

bool test_glouton_compatible(int k, int* V) {
    if (k >= 3) {
        for (int i=V[3]+2;i<V[k-1]+V[k]-1;i++) {
            for (int j=0;j<k;j++) {
                if (V[j] < i && algo_glouton(i,k,V)>1+algo_glouton(i-V[j],k,V)) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int S = 6;
    int k = 3;
    int* V = (int *)malloc(k * sizeof(int));
    /*for (int j=0;j<k;j++) {
        V[j] = j+1;
    }*/
    V[0] = 1;
    V[1] = 3;
    V[2] = 4;
    
    if (test_glouton_compatible(k,V)) {
        printf("Le test est compatible\n");
    }
    else {
        printf("Le test n'est pas compatible\n");
    }
    return 0;
}