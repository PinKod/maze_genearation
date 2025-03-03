#include "./include/cave.h"

#include <stdlib.h>

int get_bit(unsigned char ch, int index) {
    if (index < 0 || index >= 6)
        return 0;
    return (ch >> index) & 1;
}

void set_bit(unsigned char* ch, int index, int bit) {
    if (index < 0 || index >= 6)
        return;
    if (bit == 1) {
        *ch |= 1 << index;
    } else {
        *ch &= ~(1 << index);
    }
}

int is_alive(unsigned char ch) {
    return get_bit(ch, 0);
}

void set_alive(unsigned char* ch) {
    set_bit(ch, 0, 1);
}

void set_alive_next_step(unsigned char* ch) {
    set_bit(ch, 3, 1);
}

void set_dead_next_step(unsigned char* ch) {
    set_bit(ch, 3, 0);
}

void set_state_next_step(unsigned char* ch) {
    set_bit(ch, 0, get_bit(*ch, 3));
}

size_t get_alive_neighbors(cave* cave, lli i, lli j) {
    size_t counter = 0;
    lli    max_row = cave->rows - 1;
    lli    max_col = cave->cols - 1;
    if (i - 1 < 0 || j - 1 < 0 || is_alive(cave->map[i - 1][j - 1]))
        counter++;
    if (i - 1 < 0 || is_alive(cave->map[i - 1][j]))
        counter++;
    if (i - 1 < 0 || j + 1 > max_col || is_alive(cave->map[i - 1][j + 1]))
        counter++;
    if (j + 1 > max_col || is_alive(cave->map[i][j + 1]))
        counter++;
    if (i + 1 > max_row || j + 1 > max_col || is_alive(cave->map[i + 1][j + 1]))
        counter++;
    if (i + 1 > max_row || is_alive(cave->map[i + 1][j]))
        counter++;
    if (i + 1 > max_row || j - 1 < 0 || is_alive(cave->map[i + 1][j - 1]))
        counter++;
    if (j - 1 < 0 || is_alive(cave->map[i][j - 1]))
        counter++;

    return counter;
}

int update_cave(cave* cave, lli birth_limit, lli death_limit) {
    if (!cave || !cave->map)
        return;

    int res = 0;

    lli rows = cave->rows;
    lli cols = cave->cols;
    for (lli i = 0; i < rows; i++) {
        for (lli j = 0; j < cols; j++) {
            size_t alive_neighbors = get_alive_neighbors(cave, i, j);
            if (is_alive(cave->map[i][j])) {
                if (alive_neighbors < death_limit) {
                    set_dead_next_step(&cave->map[i][j]);
                    res = 1;
                }
                // else {
                //     set_alive_next_step(&cave->map[i][j]);
                // }
            } else {
                if (alive_neighbors > birth_limit) {
                    set_alive_next_step(&cave->map[i][j]);
                    res = 1;
                }
                // else {
                //     set_dead_next_step(&cave->map[i][j]);
                // }
            }
        }
    }

    for (lli i = 0; i < rows && res == 1; i++) {
        for (lli j = 0; j < cols; j++) {
            set_state_next_step(&cave->map[i][j]);
        }
    }
    return res;
}
