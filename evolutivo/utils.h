//
// Created by andre on 16/12/2023.
//

#ifndef EVOLUTIVO_UTILS_H
#define EVOLUTIVO_UTILS_H
void init_rand();
int* init_dados(char *nome, struct info *x);
pchrom init_pop(struct info d);
int flip();
chrom get_best(pchrom pop, struct info d, chrom best);
int random_l_h(int min, int max);
float rand_01();
void write_best(chrom x, struct info d);
void gera_sol_inicial(int *sol, struct info d);
#endif //EVOLUTIVO_UTILS_H
