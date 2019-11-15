#ifndef BLOCK_H
#define BLOCK_H

struct block {
    // config
    struct config *cfg;
    // nav
    struct block *next;
};

struct config {
    const char *(*func)();
    const char *fmt;
    const char *args;
    const unsigned int ival;
    const unsigned int sig;
};

struct block *block_create(struct config *cfg, struct block *next);

#endif
