#include "bar.h"
#include "block.h"
#include "config.h"
#include "log.h"
#include "util.h"
#include "sys.h"
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <X11/Xlib.h>

static Display *dpy;

static bar_t *bar_create() {
    bar_t *bar;
    block_t *block;
    int i;

    bar = (bar_t *)calloc(1, sizeof(bar_t));
    if (!bar)
        return NULL;

    block = NULL;
    for (i = LEN(cfg) - 1; i >= 0; i--) {
        block = block_create(bar, &cfg[i], block);
    }
    bar->blocks = block;

    bar->status[0] = '\n';

    return bar;
}

static void bar_destroy(bar_t *bar) {
    free(bar);
}

static int bar_setup(bar_t *bar) {
    sigset_t *set = &bar->sigset;
    timer_t *timerid = &bar->timerid;
    block_t *block = bar->blocks;
    int err;
    int ival = 0;

    err = sys_sigemptyset(set);
    if (err)
        return err;

    // control signals
    err = sys_sigaddset(set, SIGTERM);
    if (err)
        return err;

    err = sys_sigaddset(set, SIGINT);
    if (err)
        return err;

    // timer signal
    err = sys_sigaddset(set, SIGALRM);
    if (err)
        return err;

    // child signal
    err = sys_sigaddset(set, SIGCHLD);
    if (err)
        return err;

    for (int i = SIGRTMIN; i <= SIGRTMAX; i++) {
        err = sys_sigaddset(set, i);
        if (err)
            return err;
    }

    // block signals we are interested in
    err = sys_sigsetmask(set);
    if (err)
        return err;

    // setup timer
    err = sys_createtimer(CLOCK_REALTIME, timerid, SIGALRM);
    if (err)
         return err;

    while (block) {
        if (block->cfg->ival > 0) {
            ival = gcd(block->cfg->ival, ival);
        }
        block = block->next;
    }

    debug("timer interval will be %d", ival);

    if (ival > 0) {
        err = sys_settimer(timerid, ival);
        if (err)
            return err;
    }
    
    return 0;
}

static void bar_timerexpired(bar_t *bar) {
    block_t *block = bar->blocks;

    while (block) {
        if (block->cfg->ival > 0) {
           const unsigned long next_ts = block->ts + block->cfg->ival;
           unsigned long now;
           int err;

           err = sys_gettime(&now);
           if (err)
               return;

           if (((long)(next_ts - now)) <= 0) {
               block_run(block);
           }
        }
        block = block->next;
    }

    return;
}

static void bar_childsignaled(bar_t *bar) {
    int status;
    pid_t pid;

    block_t *block = bar->blocks;

    while (block) {
        if (block->pid > 0) {
            pid = waitpid(block->pid, &status, WNOHANG);
            if (pid == -1) {
                printf("child process error\n");
            } else if (pid == 0) {
                printf("child process still running\n");
            } else if (pid == block->pid) {
                // printf("child process finished\n");
                block_finish(block);
            }
        }
        block = block->next;
    }

    return;
}

static void bar_sigrt(bar_t *bar, int sig) {
    block_t *block = bar->blocks;

    while (block) {
        if (block->cfg->sig == sig) {
            // found targeted block -> handling signal
            block_run(block);
            break;
        }
        block = block->next;
    }
}

static void bar_draw(bar_t *bar) {
    block_t *block = bar->blocks;
    int len = 0;

    while (block) {
        if (strlen(block->value) > 0 && block->value[0] != '\0')
            len += snprintf(bar->status + len, 1024 - len, block->cfg->fmt, block->value);

        block = block->next;
    }

    // TODO: proper error handling
    XStoreName(dpy, DefaultRootWindow(dpy), bar->status);
    XFlush(dpy);
}

static int bar_run(bar_t *bar) {
    block_t *block = bar->blocks;
    int sig;
    int err;

    while (block) {
        block_run(block);
        block = block->next;
    }

    while (1) {
        bar_draw(bar);

        err = sys_sigwaitinfo(&bar->sigset, &sig);
        if (err) {
            // TODO check for reasons not to break
            break;
        }

        if (sig == SIGTERM || sig == SIGINT)
            break;

        if (sig == SIGALRM) {
            debug("signal received: SIGALRM");
            bar_timerexpired(bar);
            continue;
        }

        if (sig == SIGCHLD) {
            bar_childsignaled(bar);
            continue;
        }

        if (sig >= SIGRTMIN && sig <= SIGRTMAX) {
            debug("signal received: SIGRTMIN+%d", sig - SIGRTMIN);
            bar_sigrt(bar, sig - SIGRTMIN);
            continue;
        }
    }

    return 0;
}

int bar_init() {
    log_debug("bar_init");

    bar_t *bar;

    dpy = XOpenDisplay(NULL);
    if (!dpy)
        return -1;

    bar = bar_create();
    if (!bar)
        return -1;

    bar_setup(bar);
    bar_run(bar);

    // bar_start(bar);
    bar_destroy(bar);

    return 0;
}
