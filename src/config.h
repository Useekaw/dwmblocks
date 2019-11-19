#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { battery, " %s | ", "BAT0", 5, 0 },
    { datetime, " %s ", "%d.%m.", 5, 0 },
    { datetime, " %s", "%H:%M", 5, 0 },
};

#endif
