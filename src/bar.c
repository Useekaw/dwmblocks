#include "bar.h"
#include "block.h"
#include "config.h"
#include "util.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

static int bar_start(struct bar *bar) {
    struct block *block;

    block = bar->blocks;
    while (block) {
        printf(block->cfg->fmt, block->cfg->func(block->cfg->args));
        block = block->next;
    }

    return 0;
}

static bar_t *bar_create() {
    bar_t *bar;
    struct block *block;
    int i;

    bar = (bar_t *)calloc(1, sizeof(bar_t));
    if (!bar)
        return NULL;

    block = NULL;
    for (i = LEN(cfg) - 1; i >= 0; i--) {
        block = block_create(&cfg[i], block);
    }
    bar->blocks = block;

    return bar;
}

static void bar_destroy(struct bar *bar) {
    free(bar);
}

static int bar_setup(struct bar *bar) {
    struct block *block = bar->blocks;
    sigset_t *set = &bar->sigset;
    timer_t *timerid = &bar->timerid;
    int err;

    while (block) {
        block = block->next;
    }

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

    // block signals we are interested in
    err = sys_sigsetmask(set);
    if (err)
        return err;

    // setup timer
    err = sys_createtimer(CLOCK_REALTIME, timerid, SIGALRM);
    if (err)
         return err;

    err = sys_settimer(timerid, 1);
    if (err)
        return err;
    
    return 0;
}

static int bar_run(struct bar *bar) {
    int sig;
    int err;

    while (1) {
        err = sys_sigwaitinfo(&bar->sigset, &sig);
        if (err) {
            // TODO check for reasons not to break
            break;
        }

        if (sig == SIGTERM || sig == SIGINT)
            break;

        if (sig == SIGALRM) {
            continue;
        }
    }

    return 0;
}

int bar_init() {
    struct bar *bar;
    bar = bar_create();
    if (!bar)
        return -1;

    bar_setup(bar);
    bar_run(bar);

    bar_destroy(bar);

    return 0;
}
