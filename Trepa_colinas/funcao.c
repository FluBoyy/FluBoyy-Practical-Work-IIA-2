#include "funcao.h"
#include "stdio.h"

int calcula_fit(int a[], int *mat, int vert) {
    int total = 0;
    int con[vert];

    for (int i = 0; i < vert; i++) {
        con[i] = 0;
    }

    for (int i = 0; i < vert; i++) {
        if (a[i] == 1) {
            for (int j = 0; j < vert; j++) {
                if (a[j] == 1 && mat[i * vert + j] != 0) {
                    con[i] = 1;
                    con[j] = 1;
                    total += mat[i * vert + j];
                }
            }
        }
    }
    //penalização
    for (int i = 0; i < vert; i++) {
        if (con[i] == 0 && a[i] == 1) {
            return 1000000;
        }
    }

    return total/2;
}


