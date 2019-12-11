#include "bar.h"
#include "block.h"
#include "config.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

static void sendsignal(const char *block) {
    char pidline[1024];
    char *ptr;
    pid_t pid;
    pid_t mypid = getpid();
    int signal = 0;

    for (int i = 0; i < LEN(cfg); i++) {
        if (strcmp(block, cfg[i].name) == 0) {
            signal = i + 1;
            break;
        }
    }

    if (signal == 0)
        return;

    // TODO: make binary name not hardcoded
    FILE *fp = popen("pidof dwmblocks", "r");
    if (!fgets(pidline, sizeof(pidline), fp))
        pidline[0] = '\0';
    fclose(fp);

    // get first pid
    ptr = strtok(pidline, " ");
    while (ptr) {
        pid = atoi(ptr);
        if (pid != mypid) {
            kill(pid, SIGRTMIN+signal);
        }
        ptr = strtok(NULL, " ");
    }
}

int main(int argc, char *argv[]) {
    int opt;

    while ((opt = getopt(argc, argv, "s:")) != -1) {
        if (opt == 's')
            sendsignal(optarg);
        else
            printf("error");
        exit(EXIT_SUCCESS);
    }

    bar_init(cfg, LEN(cfg));

    exit(EXIT_SUCCESS);
}


