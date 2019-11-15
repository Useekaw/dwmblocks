#include "bar.h"
#include "block.h"
#include "config.h"
#include "util.h"
#include <stdio.h>
#include <stdlib.h>

static int bar_start(struct bar *bar) {
    struct block *block;

    block = bar->blocks;
    while (block) {
        printf(block->cfg->fmt, block->cfg->func(block->cfg->args));
        block = block->next;
    }

    return 0;
}

static struct bar *bar_create() {
    struct bar *bar;
    struct block *block;
    int i;

    bar = calloc(1, sizeof(bar));
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

int bar_init() {
    struct bar *bar;
    bar = bar_create();
    if (!bar)
        return -1;

    bar_start(bar);

    bar_destroy(bar);

    return 0;
}
