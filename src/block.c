#include "block.h"
#include "sys.h"
#include <stdlib.h>

block_t *block_create(config_t *cfg, block_t *next) {
    block_t *block;

    block = (block_t *)calloc(1, sizeof(block_t));
    if (!block)
        return NULL;

    block->cfg = cfg;
    block->next = next;

    return block;
}

void block_spawn(block_t *block) {
    return;
}

void block_touch(block_t *block) {
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
