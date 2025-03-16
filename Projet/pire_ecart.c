#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

int minimum(int a, int b) {
    if (a<b) {
        return a;
    }
    return b;
}

int algo2(int s, int i, int* V) {
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
}

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
    int i = 50;
    int *V = (int *)malloc(i * sizeof(int));
    
    int c=0;
    int d=0;
    for (int m=0;m<500;m++) {
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
        /*// Afficher le tableau généré
        for (int j = 0; j < i; j++) {
            printf("V[%d] : %d\n", j, V[j]);
        }*/
        if (!test_glouton_compatible(i,V)) {
            
        }        
    }
    
    free(V);
    return 0;
}
