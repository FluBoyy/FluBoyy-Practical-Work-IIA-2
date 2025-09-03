#ifndef EVOLUTIVO_FUNCAO_H
#define EVOLUTIVO_FUNCAO_H

#define _CRT_SECURE_NO_WARNINGS 1
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define GENERATIONS_TC  100
#define PROBGERAVIZ     1.0

void evaluate(pchrom pop, struct info d, int mat[3]);
int calcula_fit_reparado1(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_reparado2(int a[], int *mat, int vert, int k, int *v);
int calcula_fit_penalizado(int a[], int *mat, int vert, int k, int *v);
int calcula_fit(int a[], int *mat, int vert);
#endif //EVOLUTIVO_FUNCAO_H


