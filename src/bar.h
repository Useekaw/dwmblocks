#ifndef BAR_H
#define BAR_H

#include "block.h"
#include <signal.h>
#include <time.h>

struct bar {
    struct block *blocks;
    sigset_t sigset;
    timer_t timerid;
};

typedef struct bar bar_t;

int bar_init();

#endif
