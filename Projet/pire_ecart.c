#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <time.h>

int minimum(int a, int b) {
    return (a < b) ? a : b;
}

int algo2(int somme, int taille, int* valeurs) {
    int **tableau = (int **)malloc((somme + 1) * sizeof(int*));
    for (int j = 0; j <= somme; j++) {
        tableau[j] = (int *)malloc((taille + 1) * sizeof(int));
    }

    for (int j = 0; j <= somme; j++) {
        for (int k = 0; k <= taille; k++) {
            tableau[j][k] = INT_MAX;
        }
    }
    for (int j = 0; j <= taille; j++) {
        tableau[0][j] = 0;
    }

    for (int j = 1; j <= somme; j++) {
        for (int k = 1; k <= taille; k++) {
            int min1 = (j - valeurs[k - 1] < 0) ? INT_MAX : tableau[j - valeurs[k - 1]][k] + 1;
            int min2 = tableau[j][k - 1];
            tableau[j][k] = minimum(min1, min2);
        }
    }

    int somme1 = somme;
    int taille1 = taille;
    int* resultats = (int *)malloc(taille1 * sizeof(int));
    for (int j = 0; j < taille1; j++) {
        resultats[j] = 0;
    }
    while (somme1 != 0 && taille1 != 0) {
        if (tableau[somme1][taille1] != tableau[somme1][taille1 - 1]) {
            resultats[taille1 - 1]++;
            somme1 -= valeurs[taille1 - 1];
        } else {
            taille1--;
        }
    }
    int resultat_final = tableau[somme][taille];
    for (int j = 0; j <= somme; j++) {
        free(tableau[j]);
    }
    free(tableau);
    free(resultats);
    return resultat_final;
}

int algo_glouton(int somme, int taille, int* valeurs) {
    int resultats[taille];
    for (int j = 0; j < taille; j++) {
        resultats[j] = 0;
    }
    int somme1 = somme;
    int i = taille - 1;
    int compteur = 0;
    while (somme1 != 0) {
        resultats[i] = somme1 / valeurs[i];
        compteur += resultats[i];
        somme1 -= resultats[i] * valeurs[i];
        i--;
    }
    return compteur;
}

bool test_glouton_compatible(int taille, int* valeurs) {
    if (taille >= 3) {
        for (int i = valeurs[2] + 2; i < valeurs[taille - 2] + valeurs[taille - 1]; i++) {
            for (int j = 0; j < taille; j++) {
                if ((valeurs[j] < i) && (algo_glouton(i, taille, valeurs) > 1 + algo_glouton(i - valeurs[j], taille, valeurs))) {
                    return false;
                }
            }
        }
    }
    return true;
}

int main() {
    int somme = 50;
    srand(time(NULL));
    int p_max = 20;
    int facteur = 5; //  facteur pour determiner les valeurs de S
    int temp;
    int taille = 50;
    int *valeurs = (int *)malloc(taille * sizeof(int));
    
    int total_ecart = 0;
    int count_ecart = 0;
    int pire_ecart = 0;
    int total_systemes = 0;
    int non_glouton_compatible = 0;

    for (int m = 0; m < 500; m++) {
        valeurs[0] = 1;
        for (int j = 1; j < taille; j++) {
            valeurs[j] = rand() % (p_max) + 1;
            while (j > 0 && valeurs[j] < valeurs[j - 1]) {
                temp = valeurs[j];
                valeurs[j] = valeurs[j - 1];
                valeurs[j - 1] = temp;
                j--;
            }
        }  
        total_systemes++;
        if (!test_glouton_compatible(taille, valeurs)) {
            non_glouton_compatible++;
            for (int somme = p_max; somme <= facteur * p_max; somme++) {
                int ecart = abs(algo2(somme, taille, valeurs) - algo_glouton(somme, taille, valeurs));
                total_ecart += ecart;
                count_ecart++;
                if (ecart > pire_ecart) {
                    pire_ecart = ecart;
                }
            }
        }    
    }
    
    if (count_ecart > 0) {
        double ecart_moyen = (double)total_ecart / count_ecart;
        printf("Écart moyen: %f\n", ecart_moyen);
        printf("Pire écart: %d\n", pire_ecart);
    } else {
        printf("Aucun écart trouvé.\n");
    }

    printf("Total systèmes: %d\n", total_systemes);
    printf("Systèmes non glouton compatibles: %d\n", non_glouton_compatible);

    free(valeurs);
    return 0;
}
