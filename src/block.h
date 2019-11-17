#ifndef BLOCK_H
#define BLOCK_H

#include "bar.h"
#include <sys/types.h>

typedef struct block {
    // runtime info
    unsigned long ts;
    pid_t pid;
    char value[80];
    int out[2];
    // config
    struct config *cfg;
    // nav
    struct block *next;
    struct bar *bar;
} block_t;

typedef struct config {
    const int (*func)(char *, const char *);
    const char *fmt;
    const char *args;
    const unsigned int ival;
    const unsigned int sig;
} config_t;

block_t *block_create(struct bar *bar, config_t *cfg, block_t *next);
int block_run(block_t *block);
// void block_touch(block_t *block);
int block_finish(block_t *block);
#endif
