#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

struct config cfg[] = {
    { "sysupdate", checkupdates, "%s ", "%s", 3600, 1 },
    { "cpuperc", cpu_perc, "%s ", NULL, 1, 0 },
    { "ram", ram, "%s ", NULL, 5, 0 },
    { "volume", volume, "%s ", "%s", 0, 0 },
    { "wifi", wifi, "%s ", "wlo1", 60, 0 },
    { "battery", battery, "%s ", "BAT0", 60, 0 },
    // { datetime, " %s ", "%d.%m.", 5, 0, 0 },
    { "datetime", datetime, " %s", "%H:%M", 10, 0 },
};

#endif
