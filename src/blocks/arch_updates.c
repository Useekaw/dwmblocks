#include "../util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define CMD "~/bin/updates-arch-combined.sh"

static pid_t pacmanpid() {
    char pidline[1024];
    char *pid;

    FILE *fp = popen("pidof pacman", "r");
    if (!fgets(pidline, sizeof(pidline), fp))
        pidline[0] = '\0';
    fclose(fp);

    // get first pid
    pid = strtok(pidline, " ");
    if (pid == NULL)
        return 0;
    return atoi(pid);
}
    
static void waitforpacman() {
    pid_t pid;

    pid = pacmanpid();
    while (pid) {
        sleep(5);
        pid = pacmanpid();
    }
}

const int checkupdates(char *buffer, const char *fmt) {
    char *p;
    FILE *fp;
    char buf[80];

    waitforpacman();

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
