#ifndef TREE_H
#define TREE_H

typedef char Tree_Elem_t;

enum Errors_of_tree
{
    NO_ERRORS                  = 0,
    ERROR_OF_PUSH              = 1,
    ERROR_OF_DUMP              = 2,
    ERROR_OF_DESTRUCTOR        = 3,
    ERROR_OF_READ_TREE         = 4,
    ERROR_OF_READ_FROM_FILE    = 5,
    ERROR_OF_CONSTRUCTOR       = 6,
    ERROR_OF_RUN               = 7,
    ERROR_OF_NO_DEFINITION     = 8,
    ERROR_OF_DANGEROUS_COMMAND = 9
};

struct Node
{
    struct Node *parent_node;
    struct Node *tmp_root;
    Tree_Elem_t *data;
    size_t size_of_data;
    struct Node *left;
    struct Node *right;
};

struct Tree
{
    struct Node *root;
    struct Node *tmp_root;
    size_t size_of_tree;
    Errors_of_tree error;
};

struct Akinator
{
    struct Tree *tree;
    int answer;
    int verdict;
    struct Node *last_root;
};

void Run(struct Tree *tree);
void Run_Akinator(struct Tree *tree);
Errors_of_tree add_new_node(struct Node *root);
//void create_new_node(struct Tree *tree, Tree_Elem_t element);
void print_tree(struct Node *root);
Errors_of_tree tree_destructor(struct Tree *tree);
Errors_of_tree tree_constructor(struct Tree *tree);

#endif
