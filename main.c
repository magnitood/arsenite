#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <assert.h>
#include <string.h>
#include <errno.h>

#include <sys/mman.h>

#include "base/base_inc.h"

#include "base/base_inc.c"

#define NOB_IMPLEMENTATION
#define NOB_STRIP_PREFIX
#include "nob.h"

int main(int argc, char *argv[])
{
    char *source_code = "program.yac";

    String_Builder sb = {0};
    if (!nob_read_entire_file(source_code, &sb)) {
        fprintf(stderr, "Failed to read entire file");
        exit(EXIT_FAILURE);
    }

    printf("%.*s\n", (int) sb.count, sb.items);

    return 0;
}
