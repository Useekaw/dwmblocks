#include "../util.h"
#include <sys/sysinfo.h>

const int ram(char *buffer, const char *fmt) {
    struct sysinfo info;
    int len = 0;

    if (sysinfo(&info) < 0)
        return -1;
     
    len += util_snprintf(buffer + len, BUFFER_LEN - len, " ");
    len += fmt_human(buffer + len, BUFFER_LEN - len, info.totalram - info.freeram, 1000);
    len += util_snprintf(buffer + len, BUFFER_LEN - len, "/");
    len += fmt_human(buffer+len, BUFFER_LEN - len, info.totalram, 1000);

    return 0;
}
