#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { battery_perc, "BATT: %s ", "BAT0", 5, 0 },
    { battery_remaining, "(%s) | ", "BAT0", 5, 0 },
    { datetime, "%s | ", "%d.%m.%Y", 5, 0 },
    { datetime, "%s", "%H:%M", 5, 0 },
};

#endif
