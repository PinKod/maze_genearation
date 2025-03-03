#ifndef IO_CAVE_H
#define IO_CAVE_H

#include "./../../cave/include/cave.h"

//user input functions
void time_step_cave(cave* cave, lli N_milliseconds, lli birth_limit, lli death_limit);
void input_step_cave(cave* cave, lli birth_limit, lli death_limit);

#endif // IO_CAVE_H
