#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "algoritmo.h"
#include "funcao.h"
#include "utils.h"

#define DEFAULT_RUNS	50

int main()
{
    char        nome_fich[100];
    struct info EA_param;
    pchrom      pop = NULL, parents = NULL;
    chrom       best_run, best_ever;
    int         gen_actual, r, runs, i, inv;
    float       mbf = 0.0;
    int *grafo;

    EA_param.popsize = 250; //tamanho da população
    EA_param.pr = 0.5;     //probabilidade de recombinaçã
    EA_param.pm = 0.05;    //probabilidade de mutação
    EA_param.tsize = 2;    //tamanho do tornei
    EA_param.numGenerations = 5000;  //numero de geracoes

    // Lê os argumentos de entrada
    printf("Nome do Ficheiro: ");
    gets(nome_fich);

    // Se o número de execuções do processo for menor ou igual a 0, termina o programa
    do {
        printf("Numero de execucoes: ");
        scanf("%d", &runs);

    }   while (runs <= 0);
    //Inicializa a geração dos números aleatórios
    init_rand();
    // Preenche a matriz com dados dos objectos (peso e valor) e a estrutura EA_param que foram definidos no ficheiro de input
    grafo = init_dados(nome_fich, &EA_param);
    //imprime_matriz(*mat, EA_param.numGenes);
    // Faz um ciclo com o número de execuções definidas
    for (r=0; r<runs; r++)
    {
        printf("Repeticao %d\n",r+1);
        // Geração da população inicial
        pop = init_pop(EA_param);
        // Avalia a população inicial
        evaluate(pop, EA_param, grafo);
        gen_actual = 1;
        // Como ainda não existe, escolhe-se como melhor solução a primeira da população (poderia ser outra qualquer)
        best_run = pop[0];
        // Encontra-se a melhor solução dentro de toda a população
        best_run = get_best(pop, EA_param, best_run);
        // Reserva espaço para os pais da população seguinte
        parents = malloc(sizeof(chrom)*EA_param.popsize);
        // Caso não consiga fazer a alocação, envia aviso e termina o programa
        if (parents==NULL)
        {
            printf("Erro na alocacao de memoria\n");
            exit(1);
        }
        // Ciclo de optimização
        while (gen_actual <= EA_param.numGenerations)
        {
            // Torneio binário para encontrar os progenitores (ficam armazenados no vector parents)
            //if(flip()==1){
               tournament(pop, EA_param, parents);
            //} else{
            //
            //}
            // Aplica os operadores genéticos aos pais (os descendentes ficam armazenados na estrutura pop)
            genetic_operators(parents, EA_param, pop);
            // Avalia a nova população (a dos filhos)
            evaluate(pop, EA_param, grafo);
            // Actualiza a melhor solução encontrada
            best_run = get_best(pop, EA_param, best_run);
            gen_actual++;
        }
        // Contagem das soluções inválidas
        for (inv=0, i=0; i<EA_param.popsize; i++)
            if (pop[i].valido == 0)
                inv++;
        // Escreve resultados da repetição que terminou
        //printf("\nRepeticao %d:", r);
       // write_best(best_run, EA_param);
        printf("\nPercentagem Invalidos: %f\n", 100*(float)inv/EA_param.popsize);
        mbf += best_run.fitness;
        if (r==0 || best_run.fitness < best_ever.fitness)
            best_ever = best_run;
        // Liberta a memória usada
        free(parents);
        free(pop);
    }
    // Escreve resultados globais
    printf("\n\nMBF: %f\n", mbf/r);
    printf("\nMelhor solucao encontrada");
    write_best(best_ever, EA_param);
    return 0;
}