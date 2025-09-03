#ifndef TREPACOLINAS_UTILS_H
#define TREPACOLINAS_UTILS_H
void init_rand();
void substitui(int a[], int b[], int n);
void imprime_matriz(int *grafo, int vert);
void gera_sol_inicial(int *sol, int v,int k);
void escreve_sol(int *sol, int vert);
int* init_dados(char *nome, int *verice, int *nVerMax);
int random_l_h(int min, int max);
float rand_01();
#endif //TREPACOLINAS_UTILS_H