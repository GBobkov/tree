#include "tree.h"

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

NODE* Create_Node(int data, NODE* parent,  NODE* left, NODE* right)
{

    NODE* node = (NODE *) calloc(1, sizeof(NODE));
    node->data = data;
    node->parent = parent;
    node->left = left;
    node->right = right;

    return node;
}

ERROR_FLAGS Destroy_Node(NODE* node)
{
    assert(node != NULL);

    free(node);
    return NO_ERROR;
}

ERROR_FLAGS Insert_Num_2Tree(NODE* node, int num)
{
    if (num > node->data)
    {
        if (node->right) Insert_Num_2Tree(node->right, num);
        else node->right = Create_Node(num, node, NULL, NULL);
    }
    else if (num < node->data)
    {
        if (node->left) Insert_Num_2Tree(node->left, num);
        else node->left = Create_Node(num, node, NULL, NULL);
    }
    
    return NO_ERROR;
}


static void Nodes_Init_2Dump(FILE* dump_file, NODE* node)
{
    assert(dump_file != NULL);
    assert(node != NULL);

    #define TITLE_COLOR "\"lightblue\""
    fprintf (dump_file, "NODE_0x%p[label = \"{ <name>name = N_%p|<d>data = %d|<p>parent = %p|<l>left = %p|<r>right = %p }\", fillcolor =" TITLE_COLOR "];\n", node, node, node->data, node->parent, node->left, node->right);
    if (node->left) Nodes_Init_2Dump(dump_file, node->left);
    if (node->right) Nodes_Init_2Dump(dump_file, node->right);
    #undef TITLE_COLOR
}


static void Connections_2Dump(FILE* dump_file, NODE* node, int rank)
{
    assert(dump_file != NULL);
    assert(node != NULL);

    if (node->left)
    {
        fprintf(dump_file, "NODE_0x%p->NODE_0x%p [weight = 0, color = deeppink]\n", node, node->left);
        Connections_2Dump(dump_file, node->left, rank + 1);
    }
    if (node->right)
    {
        fprintf(dump_file, "NODE_0x%p->NODE_0x%p [weight = 0, color = deeppink]\n", node, node->right);
        Connections_2Dump(dump_file, node->right, rank + 1);
    }
}


void Node_Dump(const char* dump_fname, NODE* node)
{

    FILE* dump_file = fopen(dump_fname, "w");

    assert(dump_file != NULL);
    assert(node != NULL);

    #define FREE_COLOR  "\"lightgreen\""
    #define BUSY_COLOR  "\"coral\""


    fprintf (dump_file, "digraph G\n");
    fprintf (dump_file, "{\n");
    fprintf (dump_file, "splines=curved;\n");
    fprintf (dump_file, "nodesep=0.5;\n"); // расстояние между ячейками
    fprintf (dump_file, "node[shape=\"record\", style=\"rounded, filled\"];\n\n");

    Nodes_Init_2Dump(dump_file, node);
    fprintf (dump_file, "\n");

    const int start_rank = 0;    
    Connections_2Dump(dump_file, node, start_rank);
    fprintf (dump_file, "\n");

    fprintf (dump_file, "}\n");

    fclose(dump_file);
    #undef FREE_COLOR
    #undef BUSY_COLOR
}