#include "block.h"
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
