#ifndef EVOLUTIVO_ALGORITMO_H
#define EVOLUTIVO_ALGORITMO_H

#define MAX_OBJ 500		// Numero maximo de objectos

// EStrutura para armazenar parametros
struct info
{
    // Tamanho da população
    int     popsize;
    // Probabilidade de mutação
    float   pm;
    // Probabilidade de recombinação
    float   pr;
    // Tamanho do torneio para seleção do pai da próxima geração
    int     tsize;
    // Constante para avaliação com penalização
    float   ro;
    // Número de objetos que se podem colocar na mochila
    int     numGenes;
    // Capacidade da mochila
    int     capacity;
    // Número de gerações
    int     numGenerations;
};

typedef struct individual chrom, *pchrom;

struct individual
{
    // Solu  o (objetos que est o dentro da mochila)
    int     p[MAX_OBJ];
    // Valor da qualidade da solu  o
    float   fitness;
    // 1 se for uma solu  o v lida e 0 se n o for
    int     valido;
};

void genetic_operators(pchrom parents, struct info d, pchrom offspring);
void tournament(pchrom pop, struct info d, pchrom parents);
void tournament2(pchrom pop, struct info d, pchrom parents);
void crossover(pchrom parents, struct info d, pchrom offspring);
void crossover2(pchrom parents, struct info d, pchrom offspring);
void mutation(pchrom offspring, struct info d);
void mutation_por_troca(pchrom offspring, struct info d);
void mutation2(pchrom offspring, struct info d);
#endif //EVOLUTIVO_ALGORITMO_H
