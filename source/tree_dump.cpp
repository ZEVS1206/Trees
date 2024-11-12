#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "tree.h"
#include "tree_dump.h"


static void create_nodes_in_dump(struct Node *root, FILE *file_pointer);
static Errors_of_tree create_command_for_console(const char *file_in_name, const char *file_out_name);
static void create_connections(struct Node *root, FILE *file_pointer);

static Errors_of_tree create_command_for_console(const char *file_in_name, const char *file_out_name)
{
    if (file_in_name == NULL || file_out_name == NULL)
    {
        return ERROR_OF_DUMP;
    }
    char command_for_console[100] = "";
    snprintf(command_for_console, 100, "sudo dot -Tpng %s -o %s.png", file_in_name, file_out_name);
    system(command_for_console);
    return NO_ERRORS;
}

static void create_nodes_in_dump(struct Node *root, FILE *file_pointer)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        create_nodes_in_dump(root->left, file_pointer);
    }
    fprintf(file_pointer, "box%d [shape = record, label = \"{<node_adr>address = %p|<node_d>data = %d|{<node_l>left_node = %p|<node_r>right_node = %p}}\"];\n", root->index, root, root->data, root->left, root->left);
    if (root->right != NULL)
    {
        create_nodes_in_dump(root->right, file_pointer);
    }
}

static void create_connections(struct Node *root, FILE *file_pointer)
{
    if (root == NULL)
    {
        return;
    }
    if (root->left != NULL)
    {
        fprintf(file_pointer, "box%d:<node_l>->box%d [color=red];\n", root->index, (root->left)->index);
        create_connections(root->left, file_pointer);
    }
    if (root->right != NULL)
    {
        fprintf(file_pointer, "box%d:<node_r>->box%d [color=red];\n", root->index, (root->right)->index);
        create_connections(root->right, file_pointer);
    }
}

void graphic_dump(struct Tree *tree, char *operation)
{
    if (tree == NULL || operation == NULL)
    {
        tree->error = ERROR_OF_DUMP;
        return;
    }
    const char file_name[] = "dump/dump.txt";
    FILE *file_pointer = fopen(file_name, "w");
    fprintf(file_pointer, "digraph List {\n");
    fprintf(file_pointer, "node [margin = \"0.01\"];\nrankdir = \"TB\";\n");
    if (file_pointer == NULL)
    {
        tree->error = ERROR_OF_DUMP;
        return;
    }
    char file_out_name[100] = "dump/";
    strncat(file_out_name, operation, 100);
    create_nodes_in_dump(tree->tmp_root, file_pointer);
    create_connections(tree->tmp_root, file_pointer);
    fprintf(file_pointer, "}\n");
    fclose(file_pointer);
    Errors_of_tree error = create_command_for_console(file_name, file_out_name);
    if (error != NO_ERRORS)
    {
        tree->error = ERROR_OF_DUMP;
        return;
    }
    return;
}

