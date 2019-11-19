#include "../util.h"
#include <limits.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PATH_CAPACITY "/sys/class/power_supply/%s/capacity"
#define PATH_STATUS "/sys/class/power_supply/%s/status"
#define PATH_CHARGE "/sys/class/power_supply/%s/charge_now"
#define PATH_CURRENT "/sys/class/power_supply/%s/current_now"

static char path[PATH_MAX];

static bool battery_isdischarging(const char *bat) {
    int res;
    char state[12];

    res = snprintf(path, PATH_MAX, PATH_STATUS, bat);
    if (res < 0) {
        // TODO: proper error handling
        return true;
    }

    res = pscanf(path, "%12s", state);
    if (res < 0) {
        // TODO: proper error handling
        return true;
    }

    return !strcmp(state, "Discharging");
}

const int battery(char *buffer, const char *bat) {
    int len;
    int perc;
    int res;
    char *icon = "";
    uintmax_t charge_now;
    uintmax_t current_now;
    uintmax_t h;
    uintmax_t m;
    double timeleft;
    bool discharging = battery_isdischarging(bat);

    res = util_snprintf(path, PATH_MAX, PATH_CAPACITY, bat);
    if (res == -1)
        return -1;
    
    if (pscanf(path, "%d", &perc) != 1)
        return -1;

    if (!discharging) {
        icon = "";
    } else if (perc / 10 == 10) {
        icon = "";
    } else if (perc / 10 == 9) {
        icon = "";
    } else if (perc / 10 == 8) {
        icon = "";
    } else if (perc / 10 == 7) {
        icon = "";
    } else if (perc / 10 == 6) {
        icon = "";
    } else if (perc / 10 == 5) {
        icon = "";
    } else if (perc / 10 == 4) {
        icon = "";
    } else if (perc / 10 == 3) {
        icon = "";
    } else if (perc / 10 == 2) {
        icon = "";
    } else if (perc / 10 == 1) {
        icon = "";
    } else if (perc / 10 == 0) {
        icon = "";
    }

    res = util_snprintf(buffer, BUFFER_LEN, "%s %d%%", icon, perc); 
    if (res == -1)
        return -1;
    len = res;
   
    if (discharging) {
        res = util_snprintf(path, PATH_MAX, PATH_CHARGE, bat);
        if (res == -1)
            return -1;
        if (pscanf(path, "%ju", &charge_now) != 1)
            return -1;

        res = util_snprintf(path, PATH_MAX, PATH_CURRENT, bat);
        if (res == -1)
            return -1;
        if (pscanf(path, "%ju", &current_now) != 1)
            return -1;

        if (current_now == 0) {
            // TODO: really??
            return -1;
        }

        timeleft = (double)charge_now / (double)current_now;
        h = timeleft;
        m = (timeleft - (double)h) * 60;

        res = util_snprintf(buffer + len, BUFFER_LEN - len, " (%ju:%02ju)", h, m);
        if (res == -1)
            return -1;
        len += res;
    }

    return 0;
}
