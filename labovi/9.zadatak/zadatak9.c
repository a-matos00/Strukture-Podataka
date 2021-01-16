#include<stdio.h>
#include<stdlib.h>

struct _node;

typedef struct _node* position;

typedef struct _node{
	int number;
	position left;
	position right;
}Node;

position createNode(int);
position insert(position current, position el);
void printInOrder(position current);
position find(position current, int number);
position deleteNode(position current, int number);
position findMax(position current);
position findMin(position current);

int main(void)
{
	position root = NULL;
	int value;
	position el = NULL;
	
	printf("Enter an integer(enter 0 to stop):\t");
	scanf("%d", &value);

	el = createNode(value);
	root = insert(root, el);
	
	while(value != 0){
		printf("Enter an integer(enter 0 to stop):\t");
		scanf("%d", &value);

		el = createNode(value);
		root = insert(root, el);
	}

	printInOrder(root);	//print the binary tree

	return 0;
}
position deleteNode(position current, int number)
{
	if( NULL == current)
		return NULL;

	if(current->number == number) {

		if(current->left != NULL)
		{
			position tmp = findMax(current->left);
			current->number = tmp->number;
			current->left = deleteNode(current->left, tmp->number);
		}
		else if( current->right != NULL ){
			position tmp = findMin(current->right);
			current->number = tmp->number;
			current->left = deleteNode(current->left, tmp->number);
		}
		else{
			free(current);
			return NULL;
		}
	}

	else if( current->number < number )
		current->left = deleteNode(current->left, number);
	
	else if(current->number > number)
		current->right = deleteNode(current->right, number);
}

position findMax(position current)
{
	if(NULL == current)
		return NULL;
	
	while ( current->right != NULL )
		current = findMax(current->right);

	return current;
}

position findMin(position current)
{
	if (NULL == current)
		return NULL;

	while (current->left != NULL)
		current = findMin(current->left);

	return current;
}

position find(position current, int number)
{
	if ( NULL == current)
		return NULL;

	if( current->number == number )
		return current;
	else if(  current->number > number)
		return find(current->left, number);
	else if( current->number < number)
		return find(current->left, number);
}

void printInOrder(position current)
{
	if(current == NULL )
		return;

	printInOrder(current->left);
	printf("%d ", current->number);
	printInOrder(current->right);
}

position insert(position current, position el)
{
	if(current == NULL)
		return el;

	if ( current->number > el->number )
		current->left = insert(current->left, el);
	else if( current->number < el->number)
		current->left = insert(current->right, el);

	else{
		printf("Duplicirana vrijednost");
		free(el);
	}

	return current;
}

position createNode(int num){
	position p = NULL;

	p = (position)malloc(sizeof(Node));

	if( NULL == p){
		puts("Memory error");
		return NULL;
	}

	p->number = num;
	p->left = NULL;
	p->right = NULL;

	return p;
}
