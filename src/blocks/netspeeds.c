#include "../util.h"
#include <limits.h>
#include <stdio.h>
#include <stdint.h>

const int netspeed_rx(char *buffer, const char *interface) {
    uintmax_t oldrxbytes;
    static uintmax_t rxbytes;
    extern const unsigned int interval;
    char path[PATH_MAX];

    oldrxbytes = rxbytes;

    if (snprintf(path, PATH_MAX, "/sys/class/net/%s/statistics/rx_bytes", interface) < 0) {
        return -1;
    }
    if (pscanf(path, "%ju", &rxbytes) != 1) {
        return -2;
    }
    if (oldrxbytes == 0) {
        return -3;
    }

    fmt_human(buffer, BUFFER_LEN, (rxbytes - oldrxbytes) * 1000 / interval, 1000);

    return 0;
}


const int netspeed_tx(char *buffer, const char *interface) {
    uintmax_t oldtxbytes;
    static uintmax_t txbytes;
    extern const unsigned int interval;
    char path[PATH_MAX];

    oldtxbytes = txbytes;

    if (snprintf(path, sizeof(path), "/sys/class/net/%s/statistics/tx_bytes", interface) < 0) {
        return -1;
    }
    if (pscanf(path, "%ju", &txbytes) != 1) {
        return -2;
    }
    if (oldtxbytes == 0) {
        return -3;
    }

    fmt_human(buffer, BUFFER_LEN, (txbytes - oldtxbytes) * 1000 / interval, 1000);

    return 0;
}
