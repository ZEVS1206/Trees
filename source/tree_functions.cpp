#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "tree.h"

static void destructor_recursive(struct Node *root);
static void akinator_recursive(struct Tree *tree, char answer, int *verdict);

Errors_of_tree add_new_node(struct Node **root)
{
    *root = (Node *) calloc(1, sizeof(Node));
    if (*root == NULL)
    {
        return ERROR_OF_PUSH;
    }
    printf("Please, enter your answer:)\n");
    (*root)->left = NULL;
    (*root)->right = NULL;
    char str[100] = {0};
    fgets(str, 100, stdin);
    size_t len = strlen(str);
    (*root)->data = (Tree_Elem_t *) calloc(len, sizeof(Tree_Elem_t));
    if ((*root)->data == NULL)
    {
        return ERROR_OF_PUSH;
    }
    memcpy((*root)->data, str, len);
    printf("Thank you, I will correct the gaps in my knowledge!\n");
    return NO_ERRORS;
}


void Akinator(struct Tree *tree)
{
    if (tree == NULL)
    {
        tree->error = ERROR_OF_RUN;
        return;
    }
    tree->tmp_root = tree->root;
    int verdict = 0;
    akinator_recursive(tree, '\0', &verdict);
    if (tree->error != NO_ERRORS)
    {
        return;
    }
    // if (verdict == 0)
    // {
    //     tree->error = add_new_node(&(tree->tmp_root));
    // }
    return;
}

static void akinator_recursive(struct Tree *tree, char answer, int *verdict)
{
    if (tree->tmp_root == NULL && answer == 'y')
    {
        *verdict = 1;
        return;
    }
    else if (tree->tmp_root == NULL && answer != 'y')
    {
        printf("I don't know, who it can be(((\n");
        *verdict = 0;
        return;
    }

    if ((tree->tmp_root)->data == NULL)
    {
        tree->error = ERROR_OF_NO_DEFINITION;
        return;
    }
    for (size_t index = 0; index < (tree->tmp_root)->size_of_data; index++)
    {
        printf("%c", ((tree->tmp_root)->data)[index]);
    }
    printf("\n");

    char answer_of_user = 0;
    while (tolower(answer_of_user = getchar()) != 'y' && tolower(answer_of_user) != 'n')
    {
        printf("Incorrect input!\n");
    }
    while (getchar() != '\n');
    char low_answer = tolower(answer_of_user);

    if (low_answer == 'y')
    {
        tree->tmp_root = (tree->tmp_root)->left;
        akinator_recursive(tree, low_answer, verdict);
    }
    else if (low_answer == 'n')
    {
        tree->tmp_root = (tree->tmp_root)->right;
        akinator_recursive(tree, low_answer, verdict);
    }
}



// void create_new_node(struct Tree *tree, Tree_Elem_t element)
// {
//     if (tree == NULL)
//     {
//         tree->error = ERROR_OF_PUSH;
//         return;
//     }
//     if (tree->error != NO_ERRORS)
//     {
//         return;
//     }
//
//     if (tree->tmp_root == NULL)
//     {
//         return;
//     }
//     if (element < (tree->tmp_root)->data)
//     { // fix
//         if ((tree->tmp_root)->left != NULL)
//         {
//             tree->tmp_root = (tree->tmp_root)->left;
//             create_new_node(tree, element);
//         }
//         (tree->tmp_root)->left = (Node *) calloc(1, sizeof(Node));
//         if ((tree->tmp_root)->right != NULL)
//         {
//             free((tree->tmp_root)->right);
//         }
//         (tree->tmp_root)->right = NULL;
//         if ((tree->tmp_root)->left == NULL)
//         {
//             tree->error = ERROR_OF_PUSH;
//             return;
//         }
//         ((tree->tmp_root)->left)->data = element;
//         tree->size_of_tree++;
//         return;
//     }
//     else
//     {
//         if ((tree->tmp_root)->right != NULL)
//         {
//             tree->tmp_root = (tree->tmp_root)->right;
//             create_new_node(tree, element);
//         }
//         (tree->tmp_root)->right = (Node *) calloc(1, sizeof(Node));
//         if ((tree->tmp_root)->left != NULL)
//         {
//             free((tree->tmp_root)->left);
//         }
//         (tree->tmp_root)->left = NULL;
//         if ((tree->tmp_root)->right == NULL)
//         {
//             tree->error = ERROR_OF_PUSH;
//             return;
//         }
//         ((tree->tmp_root)->right)->data = element;
//         tree->size_of_tree++;
//         return;
//     }
// }
// const
// void print_tree(struct Node *root)
// {
//     if (!root)
//     {
//         return;
//     }
//     printf("(");
//     print_tree(root->left);
//     printf("%d", root->data);
//     print_tree(root->right);
//     printf(")");
// }


Errors_of_tree tree_constructor(struct Tree *tree)
{
    if (tree == NULL)
    {
        return ERROR_OF_CONSTRUCTOR;
    }
    tree->error = NO_ERRORS;
    tree->root = (Node *) calloc(1, sizeof(Node));
    if (tree->root == NULL)
    {
        return ERROR_OF_CONSTRUCTOR;
    }
    tree->tmp_root = tree->root;
    return NO_ERRORS;
}

Errors_of_tree tree_destructor(struct Tree *tree)
{
    if (tree == NULL)
    {
        return ERROR_OF_DESTRUCTOR;
    }
    tree->size_of_tree = 0;
    destructor_recursive(tree->root);
    if (tree->error != NO_ERRORS)
    {
        return tree->error;
    }
    return NO_ERRORS;
}


static void destructor_recursive(struct Node *root)
{
    if (root == NULL)
    {
        return;
    }

    destructor_recursive(root->left);
    destructor_recursive(root->right);
    free(root->data);
    free(root);
}
