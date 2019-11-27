#include "../util.h"
#include <stdio.h>
#include <string.h>

#define CMD "~/bin/updates-arch-combined.sh"
const int checkupdates(char *buffer, const char *fmt) {
    char *p;
    FILE *fp;
    char buf[80];

    if (!(fp = popen(CMD, "r"))) {
        return -1;
    }
    p = fgets(buf, sizeof(buf) - 1, fp);
    if (pclose(fp) < 0) {
        return -1;
    }
    if (!p) {
        return -1;
    }
    if ((p = strrchr(buf, '\n'))) {
        p[0] = '\0';
    }

    if (!buf[0]) {
        return -1;
    }

    util_snprintf(buffer, BUFFER_LEN, fmt, buf);

    return 0;
}
