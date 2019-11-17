#include "bar.h"
#include "block.h"
#include "sys.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

block_t *block_create(bar_t *bar, config_t *cfg, block_t *next) {
    block_t *block;

    block = (block_t *)calloc(1, sizeof(block_t));
    if (!block)
        return NULL;

    block->ts = 0;
    block->value[0] = '\n';

    block->cfg = cfg;
    block->next = next;
    block->bar = bar;

    return block;
}

static int block_execute(char *buffer, block_t *block) {
    int err;

    err = block->cfg->func(buffer, block->cfg->args);
    if (err)
        return err;
    // snprintf(buffer, sizeof(buffer), block->cfg->fmt, res);

    return 0;
}

static int block_child(block_t *block) {
    char buffer[100];
    int err;

    close(block->out[0]);

    err = block_execute(buffer, block);
    if (err)
        return -1;

    write(block->out[1], buffer, strlen(buffer) + 1);
    close(block->out[1]);

    return 0;
}

static int block_parent(block_t *block) {
    return 0;
}

int block_finish(block_t *block) {
    char buffer[100];
    
    read(block->out[0], buffer, 100);
    snprintf(block->bar->status, sizeof(block->bar->status), block->cfg->fmt, buffer);
    block->pid = 0;

    return 0;
}

static int block_fork(block_t *block) {
    int err;

    err = sys_fork(&block->pid);
    if (err)
        return err;

    if (block->pid == 0) {
        err = block_child(block);
        if (err) {
            // TODO: proper error handling
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }

    return block_parent(block);
}

static int block_run_sync(block_t *block) {
    int err;

    err = block_execute(block->value, block);
    if (err)
        return err;

    return 0;
}

static void block_touch(block_t *block) {
    unsigned long now;
    int err;

    err = sys_gettime(&now);
    if (err) {
        // TODO: proper error handling
        return;
    }

    if (block->ts == now) {
        // TODO: proper error handling
        return;
    }

    block->ts = now;
}

int block_run(block_t *block) {
    int err;

    err = block_run_sync(block);
    if (err)
        return err;

    block_touch(block);

    return 0;

    if (block->pid > 0) {
        // TODO: proper error handling
        return -1;
    }

    err = sys_pipe(block->out);
    if (err)
        return err;
    
    return block_fork(block);
    
    // return block_run(block);
}

