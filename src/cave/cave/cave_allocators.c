#include "./include/cave.h"

#include <stdlib.h>

cave* new_cave(size_t rows, size_t cols) {
    unsigned char** map = malloc(sizeof(unsigned char*) * rows);
    if (!map)
        return NULL;
    for (size_t i = 0; i < rows; i++) {
        map[i] = malloc(sizeof(unsigned char) * cols);
        if (!map[i]) {
            for (size_t j = i - 1; j >= 0; j--) {
                free(map[j]);
            }
            free(map);
            return NULL;
        }
    }
    return map;
}

void free_cave(cave* cave) {
    if (!cave)
        return;
    if (cave->map) {
        for (size_t i = 0; i < cave->rows; i++) {
            if (cave->map[i])
                free(cave->map[i]);
        }
        free(cave->map);
    }
    free(cave);
}