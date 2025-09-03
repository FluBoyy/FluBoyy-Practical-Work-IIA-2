#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

int trepa_colinas(int sol[], int *mat, int vert, int num_iter,int gera_vizinhos)
{
    int *nova_sol, custo, custo_viz, i;

    nova_sol = malloc(sizeof(int)*vert);
    if(nova_sol == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }
    // Avalia solucao inicial
    custo = calcula_fit(sol, mat, vert);
    for(i=0; i<num_iter; i++)
    {
        // Gera vizinho
        if(gera_vizinhos==1){
            gera_vizinho(sol, nova_sol, vert);
        } else
        if(gera_vizinhos==2){
            gera_vizinho2(sol, nova_sol, vert);
        }
        else{
            printf("Erro na escolha de vizinhos");
        }
        // Avalia vizinho
        custo_viz = calcula_fit(nova_sol, mat, vert);
        // Aceita vizinho se o custo diminuir (problema de minimizacao)

        if(custo_viz <= custo) // custo igual, trocar < por <=
        {
            substitui(sol, nova_sol, vert);
            custo = custo_viz;
        }
        //probabilístico
        else {
            if(rand_01()<0.0005){
                substitui(nova_sol, sol, vert);
                custo_viz= custo;
            }
       }
    }

    free(nova_sol);
    return custo;
}



void gera_vizinho(int a[], int b[], int n)
{
    int i, p1, p2;

    for(i=0; i<n; i++)
        b[i]=a[i];
    // Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 0);
    // Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 1);
    // Troca
    b[p1] = 1;
    b[p2] = 0;
}

void gera_vizinho2(int a[], int b[], int n)
{
    int i, p1, p2;

    for(i=0; i<n; i++)
        b[i]=a[i];
    // Encontra posicao com valor 0
    do
        p1=random_l_h(0, n-1);
    while(b[p1] != 1);
    // Encontra posicao com valor 0
    do
        p2=random_l_h(0, n-1);
    while(b[p2] != 0);
    // Troca
    b[p1] = 0;
    b[p2] = 1;
}
