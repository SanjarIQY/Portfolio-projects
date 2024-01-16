#ifndef CHECKING_FUNC
#define CHECKING_FUNC
#include "structs.h"
int check_for_id(block_list* all, int id);
int check_for_sync(block_list* all, node_list* n_list);
void prompt_identifier(node_list* n_list);
void path(int id, char* node_id, node_list* n_list);
void node_or_block(char** input, node_list** n_list);
#endif