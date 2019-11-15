#ifndef BLOCK_H
#define BLOCK_H

typedef struct block block_t;
typedef struct config config_t;

struct block {
    // status
    unsigned long ts;
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

block_t *block_create(struct config *cfg, block_t *next);
void block_spawn(block_t *block);
void block_touch(block_t *block);

#endif
