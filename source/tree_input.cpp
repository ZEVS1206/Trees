#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <assert.h>

#include "tree_input.h"

static const char *end_pointer = NULL;

static void parse_information_from_file(struct Node *root, char **buffer);
static size_t get_size_of_file(FILE *file_pointer);
static char * save_root_data(struct Node *root, char *buffer);
static char * skip_spaces(char *buffer);

static char * skip_spaces(char *buffer)
{
    if (buffer == end_pointer)
    {
        return buffer;
    }
    while (isspace(*buffer))
    {
        buffer++;
    }
    return buffer;
}

static char * save_root_data(struct Node *root, char *buffer)
{
    // if (root == NULL || buffer == NULL)
    // {
    //     return ERROR_OF_READ_TREE;
    // }
    buffer++;
    buffer = skip_spaces(buffer);
    buffer++;
    char str[100] = {0};
    size_t i = 0;
    while (*buffer != '\"')
    {
        str[i] = *buffer;
        buffer++;
        i++;
    }
    str[i] = '\0';
    root->size_of_data = i;
    root->data = (Tree_Elem_t*) calloc(root->size_of_data, sizeof(Tree_Elem_t));
    // if (root->data == NULL)
    // {
    //     return ERROR_OF_READ_TREE;
    // }
    memcpy(root->data, str, root->size_of_data);
    buffer++;
    return buffer;
}

// static Errors_of_tree parse_buffer(char *new_buffer, char *buffer, size_t size_of_file)
// {
//     if (new_buffer == NULL || buffer == NULL)
//     {



Errors_of_tree get_tree_from_json(struct Tree *tree)
{
    if (tree == NULL)
    {
        return ERROR_OF_READ_TREE;
    }

    const char file_in_name[] = "source/tree.json";
    FILE *file_pointer = fopen(file_in_name, "r");
    if (file_pointer == NULL)
    {
        return ERROR_OF_READ_TREE;
    }
    size_t size_of_file = get_size_of_file(file_pointer);
    //printf("size_of_file = %lu\n", size_of_file);
    char *buffer = (char *)calloc(size_of_file, sizeof(char));
    end_pointer = &(buffer[size_of_file - 1]);
    size_t result_of_reading = fread(buffer, sizeof(char), size_of_file, file_pointer);
    // for (size_t i = 0; i < size_of_file; i++)
    // {
    //     printf("%c", buffer[i]);
    // }
    if (result_of_reading != size_of_file)
    {
        return ERROR_OF_READ_FROM_FILE;
    }
    fclose(file_pointer);

    // Errors_of_tree error = NO_ERRORS;
    char *old_buffer = buffer;
    buffer = save_root_data(tree->root, buffer);
    // if (error != NO_ERRORS)
    // {
    //     tree->error = error;
    //     return error;
    // }
    //buffer += (tree->root)->size_of_data + 4;
    tree->tmp_root = tree->root;
    parse_information_from_file(tree->tmp_root, &buffer);
    if (tree->error != NO_ERRORS)
    {
        return tree->error;
    }
    //buffer -= ((tree->root)->size_of_data) + 4;
    free(old_buffer);
    return NO_ERRORS;
}

static size_t get_size_of_file(FILE *file_pointer)
{
    fseek(file_pointer, 0L, SEEK_END);
    size_t size_of_file = (size_t)ftell(file_pointer);
    fseek(file_pointer, 0L, SEEK_SET);
    return size_of_file;
}

static void parse_information_from_file(struct Node *root, char **buffer)
{
    //printf("element = %c\n", *buffer[0]);
    if (isspace(*buffer[0]))
    {
        *buffer = skip_spaces(*buffer);
        //printf("*buffer after skip spaces = %c\n", *buffer[0]);
        //(*buffer)++;
        //printf("*buffer = %c\n", *buffer[0]);
        //(*buffer)--;
    }
    if (*buffer[0] == '\"')
    {
        (*buffer)++;
        char str[100] = {0};
        size_t i = 0;
        while (*buffer[0] != '\"')
        {
            str[i] = *buffer[0];
            (*buffer)++;
            i++;
        }
        str[i] = '\0';
        root->size_of_data = i;
        root->data = (Tree_Elem_t*) calloc(root->size_of_data, sizeof(Tree_Elem_t));
        if (root->data == NULL)
        {
            printf("Error of reading from file\n");
            return;
        }
        memcpy(root->data, str, root->size_of_data);
        (*buffer)++;
        //printf("*buffer after str = %c\n", *buffer[0]);

        *buffer = skip_spaces(*buffer);
        //printf("*buffer after skip spaces after str = %c\n", *buffer[0]);
    }
    while (*buffer[0] == '{')
    {
        *buffer = skip_spaces(*buffer);
        if (root->left == NULL)
        {
            //printf("go to left\n");
            root->left = (Node *) calloc(1, sizeof(Node));
            if (root->left == NULL)
            {
                printf("Error of creating left node\n");
                return;
            }
            (root->left)->parent_node = root;
            (root->left)->data = NULL;
            (root->left)->left = NULL;
            (root->left)->right = NULL;
            (*buffer)++;
            //getchar();
            parse_information_from_file(root->left, buffer);
            //printf("exit from left\n");
            continue;
        }
        if (root->right == NULL)
        {
            //printf("go to right\n");
            root->right = (Node *) calloc(1, sizeof(Node));
            if (root->right == NULL)
            {
                printf("Error of creating right node\n");
                return;
            }
            (root->right)->parent_node = root;
            (root->right)->data = NULL;
            (root->right)->left = NULL;
            (root->right)->right = NULL;
            (*buffer)++;
            //getchar();
            parse_information_from_file(root->right, buffer);
            //printf("exit from right\n");
        }
    }

    if (*buffer[0] == '}')
    {
        //printf("return\n");
        //getchar();
        (*buffer)++;
        *buffer = skip_spaces(*buffer);
        return;
    }
}


