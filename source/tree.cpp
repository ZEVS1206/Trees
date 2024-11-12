#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "tree_dump.h"

int main()
{
    struct Tree tree = {0};
    tree.error = NO_ERRORS;
    tree.root = (Node *) calloc(1, sizeof(Node));
    tree.tmp_root = tree.root;
    tree.root->data = 50;
    tree.root->index = 1;
    tree.root->left = (Node *) calloc(1, sizeof(Node));
    tree.root->right = (Node *) calloc(1, sizeof(Node));
    (tree.root->left)->data = 30;
    (tree.root->left)->index = 2;
    (tree.root->left)->left = (Node *) calloc(1, sizeof(Node));
    ((tree.root->left)->left)->data = 10;
    ((tree.root->left)->left)->index = 3;
    (tree.root->right)->data = 70;
    (tree.root->right)->index = 4;
    (tree.root->right)->left = (Node *) calloc(1, sizeof(Node));
    (tree.root->right)->right = (Node *) calloc(1, sizeof(Node));
    ((tree.root->right)->left)->data = 65;
    ((tree.root->right)->left)->index = 5;
    ((tree.root->right)->right)->data = 80;
    ((tree.root->right)->right)->index = 6;
    tree.size_of_tree = 6;
    //create_new_node(&tree, 66);
    if (tree.error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", tree.error);
        return 1;
    }
    graphic_dump(&tree, "no_operations\0");
    if (tree.error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", tree.error);
        return 1;
    }
    //print_tree(tree.root);
    printf("\n");
    free(((tree.root->right)->left)->right);
    free((tree.root->right)->right);
    free((tree.root->right)->left);
    free((tree.root->left)->left);
    free(tree.root->right);
    free(tree.root->left);
    return 0;
}
