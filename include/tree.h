#ifndef TREE_H
#define TREE_H

typedef int Tree_Elem_t;

enum Errors_of_tree
{
    NO_ERRORS      = 0,
    ERROR_OF_PUSH  = 1,
    ERROR_OF_DUMP  = 2
};

struct Node
{
    int index;
    Tree_Elem_t data;
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

void create_new_node(struct Tree *tree, Tree_Elem_t element);
void print_tree(struct Node *root);

#endif
