#include<stdio.h>
#include<stdlib.h>

#include "tree.h"

int main()
{
    _node tree;

    addNode(5,&tree);
    addNode(3,&tree);
    addNode(7,&tree);
    printTree(&tree);

    return 0;
}