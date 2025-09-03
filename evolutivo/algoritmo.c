#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include "algoritmo.h"
#include "utils.h"

void genetic_operators(pchrom parents, struct info d, pchrom offspring)
{
    // Recombinação com um ponto de corte
    //crossover(parents, d, offspring);
    crossover2(parents, d, offspring);

    // Mutação binária
    //mutation(offspring, d);
    mutation2(offspring, d);

    // Mutação por troca
    //mutation_por_troca(offspring, d);
}


// Preenche uma estrutura com os progenitores da próxima geração, de acordo com o resultados do torneio binario (tamanho de torneio: 2)
// Parâmetros de entrada: população actual (pop), estrutura com parâmetros (d) e população de pais a encher
void tournament(pchrom pop, struct info d, pchrom parents)
{
    int i, x1, x2;

    // Realiza popsize torneios
    for (i=0; i<d.popsize;i++)
    {
        x1 = random_l_h(0, d.popsize-1);
        do
            x2 = random_l_h(0, d.popsize-1);
        while (x1==x2);
        if (pop[x1].fitness < pop[x2].fitness)		// Problema de minimização
            parents[i] = pop[x1];
        else
            parents[i] = pop[x2];
    }
}

void tournament2(pchrom pop, struct info d, pchrom parents) {
    int i, j, x, k, winner;
    int pos[d.tsize];

    if (d.tsize < 2 || d.tsize > d.numGenes) {
        fprintf(stderr, "<ERRO> T_SIZE tem de estar entre 2 e M.\n");
        exit(-1);
    }
}

// Operadores geneticos a usar na geração dos filhos
// Parâmetros de entrada: estrutura com os pais (parents), estrutura com parâmetros (d), estrutura que guardará os descendentes (offspring)

void crossover(pchrom parents, struct info d, pchrom offspring)
{
    int i, j, point;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01() < d.pr)
        {
            point = random_l_h(0, d.numGenes-1);
            for (j=0; j<point; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point; j<d.numGenes; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

void crossover2(pchrom parents, struct info d, pchrom offspring)
{
    int i, j, point1, point2;

    for (i=0; i<d.popsize; i+=2)
    {
        if (rand_01() < d.pr)
        {
            point1 = random_l_h(0, d.numGenes-1);
            do{
                point2 = random_l_h(0, d.numGenes-1);
            }while(point1 == point2);
            if(point1 > point2){
                int aux = point1;
                point1 = point2;
                point2 = aux;
            }
            for (j=0; j<point1; j++)
            {
                offspring[i].p[j] = parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
            for (j=point1; j<point2; j++)
            {
                offspring[i].p[j]= parents[i+1].p[j];
                offspring[i+1].p[j] = parents[i].p[j];
            }
            for (j=point2; j<d.numGenes; j++)
            {
                offspring[i].p[j]= parents[i].p[j];
                offspring[i+1].p[j] = parents[i+1].p[j];
            }
        }
        else
        {
            offspring[i] = parents[i];
            offspring[i+1] = parents[i+1];
        }
    }
}

// Mutação binária com vários pontos de mutação
// Parâmetros de entrada: estrutura com os descendentes (offspring) e estrutura com parâmetros (d)
void mutation(pchrom offspring, struct info d)
{
    int i, j;

    for (i=0; i<d.popsize; i++)
        for (j=0; j<d.numGenes; j++)
            if (rand_01() < d.pm)
                offspring[i].p[j] = !(offspring[i].p[j]);
}

void mutation_por_troca(pchrom offspring, struct info d)
{
    int i, pos1, pos2, aux;

    for (i=0; i<d.popsize; i++)
        if (rand_01() < d.pm)
        {
            do
                pos1 = random_l_h(0, d.numGenes-1);
            while (offspring[i].p[pos1] == 1);
            do
                pos2 = random_l_h(0, d.numGenes-1);
            while (offspring[i].p[pos2] == 0);
            aux = offspring[i].p[pos1];
            offspring[i].p[pos1] = offspring[i].p[pos2];
            offspring[i].p[pos2] = aux;
        }
}

void mutation2(pchrom offspring, struct info d)
{
    int i, p1,p2;

    for (i=0; i<d.popsize; i++)
        if (rand_01() < d.pm)
        {
            do{
                p1 = random_l_h(0, d.numGenes-1);
            }while(offspring[i].p[p1] != 0);
            do{
                p2 = random_l_h(0, d.numGenes-1);
            }while(offspring[i].p[p2] != 1);
            offspring[i].p[p1] = 1;
            offspring[i].p[p2] = 0;
        }
}