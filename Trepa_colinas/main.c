#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "utils.h"
#include "funcao.h"

#define DEFAULT_RUNS 1000   //// 30?

int main()
{
    char    nome_fich[100];
    int     vert,k, numero_ite = 10000,runs=10, custo, melhor_custo, nVertMax,gera_vizinhos;
    int     *grafo, *solucao, *best;
    float   mbf = 0.0;

    printf("Nome do Ficheiro: ");
    gets(nome_fich);
    printf("\n");
//    printf("Numero de runs: ");
//    scanf("%d", &runs);

    printf("Gera_vizinhos (1 ou 2): ");
    scanf("%d", &gera_vizinhos);

    if (runs <= 0)
        return 0;

    init_rand();

    grafo = init_dados(nome_fich, &vert, &nVertMax);

    imprime_matriz(grafo, vert);       // Imprimir matriz

    solucao = malloc(sizeof(int)*vert);
    best = malloc(sizeof(int)*vert);

    if(solucao == NULL || best == NULL)
    {
        printf("Erro na alocacao de memoria");
        exit(1);
    }

    for(k=0; k<runs; k++)
    {
        gera_sol_inicial(solucao, vert,nVertMax);
        puts("\n");
        printf("\nSolucao Inicial %d:", k);
        escreve_sol(solucao, vert);
        custo = trepa_colinas(solucao, grafo, vert, numero_ite,gera_vizinhos);

        printf("\nRepeticao %d:", k);
        escreve_sol(solucao, vert);
        printf("\nCusto final: %2d\n", custo);

        if(custo < 1000000)
            mbf += custo;

        if(k==0 || melhor_custo > custo)
        {
            melhor_custo = custo;
            substitui(best, solucao, vert);
        }
    }

    printf("\n\nMBF: %f\n", mbf/k);
    printf("\nMelhor solucao :");
    escreve_sol(best, vert);
    printf("\nCusto final: %2d\n", melhor_custo);
    puts("\n");

    //logtofile(num_iter,best_custo,mbf/k);

    free(grafo);
    free(solucao);
    free(best);
    return 0;
}