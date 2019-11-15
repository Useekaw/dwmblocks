#include "block.h"
#include <stdlib.h>

struct block *block_create(struct config *cfg, struct block *next) {
    struct block *block;

    block = calloc(1, sizeof(block));
    if (!block)
        return NULL;

    block->cfg = cfg;
    block->next = next;

    return block;
}
