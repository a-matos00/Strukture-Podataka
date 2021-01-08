#pragma once

struct node;

typedef struct node* p_node;

typedef struct node{
    int num;
    p_node L;
    p_node R;
}_node;

p_node addNode(int , p_node);
void printTree(p_node);

void printTree(p_node p)
{
    if(p != NULL)
    {
        printTree(p->L);
        printf("%d", p->num);
        printTree(p->R);
    }
}
p_node addNode(int arg_num, p_node p)
{
    if( p == NULL){

        p = (p_node)malloc(sizeof(_node));
        p->num = arg_num;
        p->L = NULL;
        p->R = NULL;

    }

    else if( arg_num < p->num)
    {
        p->L = addNode(arg_num, p->L);
    }

    else if( arg_num > p->num)
    {
        p->R = addNode(arg_num, p->R);
    }
    
    return p;
}

