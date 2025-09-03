#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"
#include <string.h>

int* init_dados(char *nome, int *verice, int *nVerMax) {
    FILE *f;
    int *p;
    int i, j, lig, lin, col, custo;
    char str[100];
    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    fscanf(f, "%s %d", str, nVerMax);

    while (strcmp(str, "edge")) {
        fscanf(f, "%s", str); //// edge numero_vertices numero_arestas
    }
    fscanf(f, "%d", verice);
    fscanf(f, "%d", &lig); // Corrigindo a leitura do número de arestas

    // Alocacao dinamica da matriz
    p = malloc(sizeof(int) * (*verice) * (*verice));
    if (!p) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    // Preenchimento da matriz
    for (i = 0; i < *verice; i++) {
        for (j = 0; j < *verice; j++) {
            *(p + i * (*verice) + j) = 0; // Inicializando todos os valores com 0
        }
    }

    // Preenchendo a matriz com os valores fornecidos
    for (i = 0; i < lig; i++) {
        fscanf(f, " e %d %d %d", &lin, &col, &custo);
        // Atribuindo o custo na posição correspondente
        *(p + (lin - 1) * (*verice) + (col - 1)) = custo;  // p[lin-1][col-1] = custo
        // Se for um grafo não direcionado, atribua o custo também na posição oposta
        *(p + (col - 1) * (*verice) + (lin - 1)) = custo;
    }

    fclose(f);
    return p;
}

void imprime_matriz(int *grafo, int vert){
    for (int i = 0; i < vert; i++) {            // MATRIZ 6x6 (teste.txt)
        printf("\n");
        for (int j = 0; j < vert; j++) {
            printf("%d ", grafo[i*vert+j]);    // grafo[0*6+0] = grafo[0]
        }
    }
}

void gera_sol_inicial(int *sol, int v,int k)
{
    int i, x;

    for(i=0; i<v; i++)
        sol[i]=0;
    for(i=0; i<k; i++)
    {
        do
            x = random_l_h(0, v-1);
        while(sol[x] != 0);
        sol[x]=1;
    }
}

void escreve_sol(int *sol, int vert)
{
    int i;
    //printf("\n[Conjunto A] : ");
//    for(i=0; i<vert; i++)
//        if(sol[i]==0)
//            printf("%2d  ", i+1);
    printf("\n[Conjunto B] : ");
    for(i=0; i<vert; i++)
        if(sol[i]==1)
            printf("%2d  ", i+1);
    printf("\n");
}

void substitui(int a[], int b[], int n)
{
    int i;
    for(i=0; i<n; i++)
        a[i]=b[i];
}

int random_l_h(int min, int max)
{
    return min + rand() % (max-min+1);
}

void init_rand()
{
    srand((unsigned)time(NULL));
}

float rand_01()
{
    return ((float)rand())/RAND_MAX;
}