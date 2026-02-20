#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#define KB(x) ((size_t)(x) << 10)
#define MB(x) ((size_t)(x) << 20)
#define GB(x) ((size_t)(x) << 30)
#define TB(x) ((size_t)(x) << 40)

#define ALIGN_UP_POW_2(x,b) (((x) + (b) - 1)&(~((b) - 1))) // stole this from raddebugger
#define IS_POW_2(v) (((v) > 0) && (((v) & ((v)-1)) == 0))

#endif // BASE_MACROS_H
