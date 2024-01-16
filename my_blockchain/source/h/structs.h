#ifndef STRUCTS
#define STRUCTS
typedef struct block
{
    int id;
    struct block* next;
} block_list;

typedef struct node
 {
    int id;
    block_list* block;
    struct node* next;
} node_list;
int check_for_dublicates_b(int id, node_list* n_list);
int check_for_dublicates_n(int id, node_list* n_list);
void add_node(int id, node_list** list);
void add_block(int id, block_list** block);
int block_length(block_list* b_list);
int node_length(node_list* n_list);
int size_of_list(node_list* n_list);
void rm_print(int flag);
void free_node_list(node_list* n_list);
void free_block_list(block_list* l_list);
#endif