#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

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
            printf("left\n");
            tree->tmp_root = (tree->tmp_root)->left;
            create_new_node(tree, element);
        }
        (tree->tmp_root)->left = (Node *) calloc(1, sizeof(Node));
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
            printf("right\n");
            tree->tmp_root = (tree->tmp_root)->right;
            create_new_node(tree, element);
        }
        (tree->tmp_root)->right = (Node *) calloc(1, sizeof(Node));
        if ((tree->tmp_root)->right == NULL)
        {
            tree->error = ERROR_OF_PUSH;
            return;
        }
        ((tree->tmp_root)->right)->data = element;
        tree->size_of_tree++;
        return;
    }
    // while (1)
    // {
    //     if (element < root->data)
    //     {
    //         if (root->left != NULL)
    //         {
    //             root = root->left;
    //             continue;
    //         }
    //         root->left = (Node *) calloc(1, sizeof(Node));
    //         (root->left)->data = element;
    //         break;
    //     }
    //     else
    //     {
    //         if (root->right != NULL)
    //         {
    //             root = root->right;
    //             continue;
    //         }
    //         root->right = (Node *) calloc(1, sizeof(Node));
    //         (root->right)->data = element;
    //         break;
    //     }
    // }
    // return NO_ERRORS;
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

