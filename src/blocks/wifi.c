#include "../util.h"
#include <ifaddrs.h>
#include <limits.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <unistd.h>

#define PATH_OPERSTATE "/sys/class/net/%s/operstate"
#define PATH_NETWIFI "/proc/net/wireless"

#define WIFI_BUF_SIZE 1024

static char path[PATH_MAX];
static char buffer[WIFI_BUF_SIZE];

static int wifi_isup(const char *interface) {
    int res;
    FILE *fp;
    char *p;
    char status[5];

    res = util_snprintf(path, PATH_MAX, PATH_OPERSTATE, interface);
    if (res == -1)
        return  -1;
    
    if (!(fp = fopen(path, "r")))
        return -1;
    p = fgets(status, 5, fp);
    fclose(fp);

    if (!p || strcmp(status, "up\n") != 0)
        return 0;

    return 1;
}

static int wifi_perc(const char *interface) {
    FILE *fp;
    int i;
    int cur;
    char *datastart;
    char *p;

    if (!(fp = fopen(PATH_NETWIFI, "r")))
        return -1;
    for (i = 0; i < 3; i++) {
        if (!(p = fgets(buffer, WIFI_BUF_SIZE -1, fp)))
            break;
    }
    fclose(fp);

    if (i < 2 || !p)
        return -1;

    if (!(datastart = strstr(buffer, interface)))
        return -1;

    datastart = (datastart + (strlen(interface) + 1));
    sscanf(datastart + 1, " %*d   %d  %*d  %*d\t\t  %*d\t   %*d\t\t%*d\t\t %*d\t  %*d\t\t %*d", &cur);

    return (int)((float)cur / 70 * 100);
}

const int wifi(char *buffer, const char *interface) {
    char *icon;
    bool up = wifi_isup(interface);
    int len;
    int perc = 0;

    if (up)
        icon = "直";
    else
        icon = "睊";

    len = util_snprintf(buffer, BUFFER_LEN, "%s", icon);

    if (!up)
        return 0;

    perc = wifi_perc(interface);

    util_snprintf(buffer + len, BUFFER_LEN - len, " %d%%", perc);

    return 0;
}
