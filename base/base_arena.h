#ifndef BASE_ARENA_H
#define BASE_ARENA_H

typedef struct Arena {
    uint8_t *buf;
    size_t pos;
    size_t commit_size;;
    size_t reserve_size;
} Arena;

bool arena_init_growing(Arena *a, size_t reserve_size, size_t commit_size);
bool arena_destroy(Arena *a);
void arena_reset(Arena *a);
uint8_t *arena_push_aligned(Arena *a, size_t size, size_t alignment, bool zeroed);

#endif // BASE_ARENA_H
