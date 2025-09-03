#define _CRT_SECURE_NO_WARNINGS 1
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "algoritmo.h"
#include "utils.h"
#include <string.h>

int* init_dados(char *nome, struct info *x) {
    FILE *f;
    int *p;
    int *vertice;
    int i, j, lig, lin, col, custo;
    char str[100];

    f = fopen(nome, "r");
    if (!f) {
        printf("Erro no acesso ao ficheiro dos dados\n");
        exit(1);
    }

    fscanf(f, "k %d", &x->capacity);

    while(strcmp(str,"edge"))                   //Vertice
        fscanf(f,"%s %d %d",str, &x->numGenes, &lig);
    if (x->numGenes > MAX_OBJ)
    {
        printf("Number of itens is superior to MAX_OBJ\n");
        exit(1);
    }
    x->ro = 0.0;


    p = malloc(sizeof(int) * (x->numGenes) * (x->numGenes));
    if (!p) {
        printf("Erro na alocacao de memoria\n");
        exit(1);
    }

    // Preenchimento da matriz
    for (i = 0; i < x->numGenes; i++) {
        for (j = 0; j < x->numGenes; j++) {
            *(p + i * (x->numGenes) + j) = 0; // Inicializando todos os valores com 0
        }
    }

    // Preenchendo a matriz com os valores fornecidos
    for (i = 0; i < lig; i++) {
        fscanf(f, " e %d %d %d", &lin, &col, &custo);
        // Atribuindo o custo na posição correspondente
        *(p + (lin - 1) * (x->numGenes) + (col - 1)) = custo;  // p[lin-1][col-1] = custo
        // Se for um grafo não direcionado, atribua o custo também na posição oposta
        *(p + (col - 1) * (x->numGenes) + (lin - 1)) = custo;
    }

////------------------imprime matriz------------------
//    for (int i = 0; i < x->numGenes; i++) {            // MATRIZ 6x6 (teste.txt)
//        printf("\n");
//        for (int j = 0; j < x->numGenes; j++) {
//            printf("%d ", p[i*x->numGenes+j]);    // grafo[0*6+0] = grafo[0]
//        }
//    }
//------------------imprime matriz------------------
    printf("\n");
    return p;
    fclose(f);
}

pchrom init_pop(struct info d){
    int     i, j;
    pchrom  indiv; //ponteiro para individuos

    indiv = malloc(sizeof(chrom)*d.popsize); //alocacao dinamica de memoria
    if (indiv==NULL)
    {
        printf("Erro na alocacao de memoriaaa\n");
        exit(1);
    }
    for (i=0; i<d.popsize; i++) //preenche a populacao com individuos
    {
        gera_sol_inicial(indiv[i].p,d); //preenche o gene com 0 ou 1
    }
    return indiv;
}

void gera_sol_inicial(int *sol, struct info d) {
    int x;

    for(int i = 0; i < d.numGenes; i++)
    {
        sol[i] = 0;
    }

    for (int i = 0; i < d.capacity; i++)
    {
        do {
            x = random_l_h(0, d.numGenes-1);
        }while(sol[x] != 0);

        sol[x] = 1;
    }
}

chrom get_best(pchrom pop, struct info d, chrom best)
{
    int i;

    for (i=0; i<d.popsize; i++)  //percorre a populacao
    {
        if (best.fitness > pop[i].fitness) //se o fitness do individuo for melhor que o do best
            best=pop[i];
    }
    return best;
}
void write_best(chrom x, struct info d){
    int i;

    printf("\nBest individual: %4.1f\n", x.fitness);
    for (i=0; i<d.numGenes; i++)
        printf("%d", x.p[i]);
    putchar('\n');
}
int random_l_h(int min, int max){
    return min + rand() % (max-min+1);
}
float rand_01(){
    return ((float)rand())/RAND_MAX;
}
void init_rand(){
    srand((unsigned)time(NULL));
}
int flip(){
    if ((((float)rand()) / RAND_MAX) < 0.5)
        return 0;
    else
        return 1;
}
