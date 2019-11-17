#ifndef BAR_H
#define BAR_H

#include "block.h"
#include <signal.h>
#include <time.h>

typedef struct bar {
    char status[1024];
    block_t *blocks;
    sigset_t sigset;
    timer_t timerid;
} bar_t;

int bar_init();

#endif
