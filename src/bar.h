#ifndef BAR_H
#define BAR_H

#include "block.h"
#include <signal.h>

struct bar {
    struct block *blocks;
    sigset_t sigset;
};

int bar_init();

#endif
