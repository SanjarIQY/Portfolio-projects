#ifndef SYNC_FUNC
#define SYNC_FUNC
#include "structs.h"
block_list* unique_blocks(node_list* n_list);
void synch(block_list* all, node_list* n_list);
#endif