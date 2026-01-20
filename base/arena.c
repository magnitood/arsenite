#include <stdio.h>
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>

#include <sys/mman.h>

#include "arena.h"

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((x) << 40)

#define ALIGN_UP_POW_2(x,b) (((x) + (b) - 1)&(~((b) - 1))) // stole this from raddebugger
#define IS_POW_2(v) (((v) & ((v)-1)) == 0)

bool arena_init_growing(Arena *a, size_t reserve_size, size_t commit_size)
{
    assert(a != NULL);

    // TODO: support for winapi virtual alloc
    uint8_t *buf = mmap(NULL, reserve_size, PROT_NONE, MAP_ANONYMOUS | MAP_PRIVATE, -1, 0);
    if (buf == MAP_FAILED)
        return false;

    // TODO: support for winapi virtual alloc
    if (commit_size != 0) {
        if (mprotect(buf, commit_size, PROT_READ | PROT_WRITE) != 0)
           return false;
    }

    a->buf = buf;
    a->reserve_size = reserve_size;
    a->commit_size = commit_size;

    return true;
}

uint8_t *arena_push_(Arena *a, size_t size, size_t alignment, bool zeroed)
{
    assert(a != NULL);
    assert(IS_POW_2(alignment));

    size_t aligned_size = ALIGN_UP_POW_2(size, alignment);
    if (a->pos + aligned_size > a->commit_size) {
        a->commit_size *= 2;
        if (a->commit_size > a->reserve_size) {
            fprintf(stderr, "Exceeded arena reservation of %zu bytes\n", a->reserve_size);
            exit(EXIT_FAILURE);
        }
        if (mprotect(a->buf, a->commit_size, PROT_READ | PROT_WRITE) != 0) {
            fprintf(stderr, "Could not commit to arena: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    uint8_t *buf = a->buf + a->pos;
    a->pos += aligned_size;

    if (zeroed)
        memset(buf, 0, aligned_size);

    return buf;
}

bool arena_destroy(Arena *a) {
    assert(a != NULL);

    // TODO: support for winapi virtual alloc
    if (munmap(a->buf, a->reserve_size) != 0)
        return false;

    memset(a, 0, sizeof(*a));
    return true;
}

void arena_reset(Arena *a) {
    assert(a != NULL);
    a->pos = 0;
}
