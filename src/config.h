#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { checkupdates, "UPDATES: %s ", "%s", 3600, 1, 1 },
    { wifi, "%s ", "wlo1", 5, 0, 0 },
    { battery, "%s ", "BAT0", 5, 0, 0 },
    // { datetime, " %s ", "%d.%m.", 5, 0, 0 },
    { datetime, " %s", "%H:%M", 5, 0, 0 },
};

#endif
