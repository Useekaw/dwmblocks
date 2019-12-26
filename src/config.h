#ifndef CONFIG_H
#define CONFIG_H

#include "block.h"
#include "blocks.h"

// interval between updates in ms
const unsigned int interval = 1000;

struct config cfg[] = {
    { "sysupdate", checkupdates, "%s ", "%s", 3600, 1 },
    { "volume", volume, "%s ", "%s", 0, 0 },
    { "date", datetime, " %s ", "%d.%m.", 10, 0,},
    { "time", datetime, " %s", "%H:%M", 10, 0 },
    { "battery", battery, ";%s", "BAT0", 60, 0 },
    { "cpuperc", cpu_perc, ";%s ", NULL, 1, 0 },
    { "ram", ram, "%s", NULL, 5, 0 },
    { "wifi", wifi, ";%s ", "wlo1", 60, 0 },
    { "netspeed_rx", netspeed_rx, "ﰮ %s/s ", "wlo1", 1, 0 },
    { "netspeed_tx", netspeed_tx, "ﰷ %s/s", "wlo1", 1, 0 },
};

#endif
