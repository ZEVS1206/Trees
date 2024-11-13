#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

static void clean_tree(struct Node *root);

void create_new_node(struct Tree *tree, Tree_Elem_t element)
{
    if (tree == NULL)
    {
        tree->error = ERROR_OF_PUSH;
        return;
    }
    if (tree->error != NO_ERRORS)
    {
        return;
    }

    if (tree->tmp_root == NULL)
    {
        return;
    }
    if (element < (tree->tmp_root)->data)
    {
        if ((tree->tmp_root)->left != NULL)
        {
            tree->tmp_root = (tree->tmp_root)->left;
            create_new_node(tree, element);
        }
        (tree->tmp_root)->left = (Node *) calloc(1, sizeof(Node));
        if ((tree->tmp_root)->right != NULL)
        {
            free((tree->tmp_root)->right);
        }
        (tree->tmp_root)->right = NULL;
        if ((tree->tmp_root)->left == NULL)
        {
            tree->error = ERROR_OF_PUSH;
            return;
        }
        ((tree->tmp_root)->left)->data = element;
        tree->size_of_tree++;
        return;
    }
    else
    {
        if ((tree->tmp_root)->right != NULL)
        {
            tree->tmp_root = (tree->tmp_root)->right;
            create_new_node(tree, element);
        }
        (tree->tmp_root)->right = (Node *) calloc(1, sizeof(Node));
        if ((tree->tmp_root)->left != NULL)
        {
            free((tree->tmp_root)->left);
        }
        (tree->tmp_root)->left = NULL;
        if ((tree->tmp_root)->right == NULL)
        {
            tree->error = ERROR_OF_PUSH;
            return;
        }
        ((tree->tmp_root)->right)->data = element;
        tree->size_of_tree++;
        return;
    }
}

void print_tree(struct Node *root)
{
    if (!root)
    {
        return;
    }
    printf("(");
    if (root->left)
    {
        print_tree(root->left);
    }
    printf("%d", root->data);
    if (root->right)
    {
        print_tree(root->right);
    }
    printf(")");
}


Errors_of_tree destructor(struct Tree *tree)
{
    if (tree == NULL)
    {
        return ERROR_OF_DESTRUCTOR;
    }
    tree->tmp_root = tree->root;
    tree->root->data = 0;
    tree->size_of_tree = 0;
    clean_tree(tree->tmp_root);
    if (tree->error != NO_ERRORS)
    {
        return tree->error;
    }
    return NO_ERRORS;
}


static void clean_tree(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        root->data = 0;
        clean_tree(root->left);
    }
    if (root->right != NULL)
    {
        root->data = 0;
        clean_tree(root->right);
    }
    free(root);
}
