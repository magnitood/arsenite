#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/mman.h>

#include "base/base_inc.h"

#include "base/base_inc.c"

typedef struct {
    char *data;
    size_t length;
    size_t capacity;
} StringBuilderArena;

extern bool read_entire_file(Arena *a, StringBuilder *sb, const char *file);

int main(int argc, char *argv[])
{
    if (argc < 2)
        return 0;


    char *source_file = argv[1];
    StringBuilder source_code = {0};

    Arena a = {0};
    arena_init_growing(&a, GB(64), MB(1));

    // TODO: Improve error handling
    if (!read_entire_file(&a, &source_code, source_file)) {
        printf("Failed to read input file\n");
        exit(EXIT_FAILURE);
    }

    return 0;
}
