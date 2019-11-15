#ifndef BLOCK_H
#define BLOCK_H

typedef struct block block_t;
typedef struct config config_t;

struct block {
    // config
    config_t *cfg;
    // nav
    block_t *next;
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
