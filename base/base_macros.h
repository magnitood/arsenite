#ifndef BASE_MACROS_H
#define BASE_MACROS_H

#define KB(x) ((x) << 10)
#define MB(x) ((x) << 20)
#define GB(x) ((x) << 30)
#define TB(x) ((x) << 40)

#define ALIGN_UP_POW_2(x,b) (((x) + (b) - 1)&(~((b) - 1))) // stole this from raddebugger
#define IS_POW_2(v) (((v) & ((v)-1)) == 0)

#endif // BASE_MACROS_H
