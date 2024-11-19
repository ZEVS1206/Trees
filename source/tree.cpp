#include <stdio.h>
#include <stdlib.h>

#include "tree.h"
#include "tree_dump.h"
#include "tree_input.h"




int main()
{
    struct Tree tree = {0};
    Errors_of_tree error = tree_constructor(&tree);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", error);
        return 1;
    }
    error = get_tree_from_json(&tree);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", error);
        return 1;
    }
    // tree.error = NO_ERRORS;
    // tree.root = (Node *) calloc(1, sizeof(Node));
    // tree.tmp_root = tree.root;
    // tree.root->data = 50;
    // tree.root->left = (Node *) calloc(1, sizeof(Node));
    // tree.root->right = (Node *) calloc(1, sizeof(Node));
    // (tree.root->left)->data = 30;
    // (tree.root->left)->left = (Node *) calloc(1, sizeof(Node));
    // ((tree.root->left)->left)->data = 10;
    // (tree.root->right)->data = 70;
    // (tree.root->right)->left = (Node *) calloc(1, sizeof(Node));
    // (tree.root->right)->right = (Node *) calloc(1, sizeof(Node));
    // ((tree.root->right)->left)->data = 65;
    // ((tree.root->right)->right)->data = 80;
    tree.tmp_root = tree.root;
    if (tree.error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", tree.error);
        return 1;
    }
    tree.tmp_root = tree.root;
    graphic_dump(&tree, "no_operations\0");
    if (tree.error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", tree.error);
        return 1;
    }
    //print_tree(tree.root);
    printf("\n");
    error = tree_destructor(&tree);
    if (error != NO_ERRORS)
    {
        fprintf(stderr, "error = %d\n", error);
        return 1;
    }
    return 0;
}



