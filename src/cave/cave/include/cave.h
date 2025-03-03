#ifndef CAVE_H
#define CAVE_H

#include "./../../includes/defines.h"

typedef long long int lli;

typedef struct {
    lli             rows;
    lli             cols;
    unsigned char** map;
} cave;

//cave allocators
cave* new_cave(lli rows, lli cols);
void  free_cave(cave* cave);

//cave generate functions
int update_cave(cave* cave, lli birth_limit, lli death_limit);

#endif // CAVE_H