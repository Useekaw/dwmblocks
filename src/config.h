#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { "archupdate", checkupdates, "UPDATES: %s ", "%s", 3600, 1, 1 },
    { "wifi", wifi, "%s ", "wlo1", 60, 0, 0 },
    { "battery", battery, "%s ", "BAT0", 60, 0, 0 },
    // { datetime, " %s ", "%d.%m.", 5, 0, 0 },
    { "datetime", datetime, " %s", "%H:%M", 10, 0, 0 },
};

#endif
