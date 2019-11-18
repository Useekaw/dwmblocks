#include "../util.h"
#include <limits.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define PATH_CAPACITY "/sys/class/power_supply/%s/capacity"
#define PATH_STATUS "/sys/class/power_supply/%s/status"
#define PATH_CHARGE "/sys/class/power_supply/%s/charge_now"
#define PATH_CURRENT "/sys/class/power_supply/%s/current_now"

const int battery_perc(char *buffer, const char *args) {
    int perc;
    char path[PATH_MAX];

    snprintf(path, PATH_MAX, PATH_CAPACITY, args);
    pscanf(path, "%d", &perc);
    snprintf(buffer, sizeof(buffer), "%d", perc);

    return 0;
}

const int battery_remaining(char *buffer, const char *args) {
    uintmax_t charge_now;
    uintmax_t current_now;
    uintmax_t h;
    uintmax_t m;
    double timeleft;
    char path[PATH_MAX];
    char state[12];

    snprintf(path, PATH_MAX, PATH_STATUS, args);
    pscanf(path, "%12s", state);

    if (!strcmp(state, "Discharging")) {
        snprintf(path, PATH_MAX, PATH_CHARGE, args);
        pscanf(path, "%ju", &charge_now);

        snprintf(path, PATH_MAX, PATH_CURRENT, args);
        pscanf(path, "%ju", &current_now);

        if (current_now == 0) {
            // TODO: really??
            return -1;
        }

        timeleft = (double)charge_now / (double)current_now;
        h = timeleft;
        m = (timeleft - (double)h) * 60;

        snprintf(buffer, sizeof(buffer), "%ju:%ju", h, m);
    } else {
        snprintf(buffer, sizeof(buffer), "%s", "");
    }

    return 0;
}

