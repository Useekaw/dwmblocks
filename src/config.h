#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { datetime, "%s\n", "%H:%M", 1, 0 },
};

#endif
