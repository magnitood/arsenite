typedef struct Arena {
    uint8_t *buf;
    size_t pos;
    size_t commit_size;;
    size_t reserve_size;
} Arena;

bool arena_init_growing(Arena *a, size_t reserve_size, size_t commit_size);
bool arena_destroy(Arena *a);
void arena_reset(Arena *a);
