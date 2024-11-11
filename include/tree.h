#ifndef TREE_H
#define TREE_H



struct NODE
{
    int data;
    NODE* parent;
    NODE* left;
    NODE* right;
};

enum ERROR_FLAGS
{
    NO_ERROR=0
};

// Создаёт узел
NODE* Create_Node(int data, NODE* parent,  NODE* left, NODE* right);

// Освобождает память
ERROR_FLAGS Destroy_Node(NODE* node);

// Добавить новый элемент в сортирующее дерево
ERROR_FLAGS Insert_Num_2Tree(NODE* node, int num);


// Заполнить dotfile.
void Node_Dump(const char* dump_fname, NODE* node);


#endif