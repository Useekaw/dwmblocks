#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { datetime, "%s", "%d.%m.%Y", 5, 0 },
    { datetime, "%s", "%H:%M", 5, 0 },
};

#endif
