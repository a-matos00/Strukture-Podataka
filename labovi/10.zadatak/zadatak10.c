#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct node;
struct el;

typedef struct node* p_node;
typedef struct el* p_el;

typedef struct node {
	char item[3];
	p_node L;
	p_node R;

}_node;

typedef struct el {
	p_node adress;
	p_el next;
}_el;

int bufferSize(FILE*);
p_node readFromBuffer(char*);
p_node createNode(char*);
int push(p_el, p_node);	//head el i vrijednost novog elementa stoga
int ispisStoga(p_el);
p_node pop(p_el);
void printInOrder(p_node current);

int main()
{
	p_node root;
	_el stack;
	FILE* fp;
	char* read_buffer;

	fp = fopen("postfix.txt", "r");

	if (fp == NULL) {
		puts("Greska u otvaranju datoteke!");
		return -1;
	}

	read_buffer = (char*)calloc(bufferSize(fp) + 10, sizeof(char));
	fread(read_buffer, bufferSize(fp), 1, fp);
	*(read_buffer + bufferSize(fp)) = ' ';	//razmak iza zadnjeg znaka postfix izraza radi nekih sitnih pikanterija
	fclose(fp);
	printf("Procitani buffer je %s\n", read_buffer);

	root = readFromBuffer(read_buffer);

	printInOrder(root);

	system("pause");
	return 0;
}

p_node readFromBuffer(char* buffer)
{
	int r = 0;
	int num;
	int n = 0;
	int offset = 0;
	char operator[3];
	p_node tree_root = (p_node)malloc(sizeof(_node));
	char arg[3];
	p_node new_node;
	p_node L_child;
	p_node R_child;

	_el stack;
	stack.next = NULL;

	while (buffer != EOF) {

		printf("ostatak buffera ==> %s\n", buffer);
		r = sscanf(buffer, "%d%n", &num, &n);

		if (r == 1) {
			printf("ucitan broj! ==> %d\n", num);
			buffer += n;

			sprintf(arg, "%d", num);	//convert int to string

			new_node = createNode(arg);
			push(&stack, new_node);
		}
		else if (r == 0) {
			r = sscanf(buffer, " %s%n", operator, &n);
			//printf("ucitan operator! ==> %c\n", operator);
			buffer += n;

			strcpy(arg, operator);
			new_node = createNode(arg);
			tree_root = new_node;

			R_child = pop(&stack);
			L_child = pop(&stack);
			addChildren(L_child, R_child, tree_root);
			printf("DJECA %s %s\n", tree_root->R->item, tree_root->L->item);

			push(&stack, new_node);
		}
		else if (r == EOF) {
			break;
		}
		ispisStoga(&stack);

	}
	return tree_root;
}

void printInOrder(p_node current)
{
	if (current == NULL)
		return;

	printInOrder(current->L);
	printf("%s ", current->item);
	printInOrder(current->R);
}

int addChildren(p_node arg_left, p_node arg_right, p_node root)
{
	root->L = arg_left;
	root->R = arg_right;

	return 0;
}

p_node pop(p_el p)
{
	p_el temp;
	p_node copy_adress;

	temp = p->next;
	p->next = temp->next;

	copy_adress = temp->adress;

	printf("Uklonjen element stoga: %s\n", temp->adress->item);
	free(temp);

	return copy_adress;
}

int push(p_el p, p_node t_node)	//argument je head element
{

	p_el novi;

	if (p == NULL) {
		puts("Neispravan argument, null pokazivac");
		return -1;
	}

	novi = (p_el)malloc(sizeof(_el));	//stvara se novi element
	novi->adress = t_node;	//clan strukture je adresa cvora stabla
	printf("Dodan novi element u stog ==> %s\n", t_node->item);

	novi->next = p->next;
	p->next = novi;

	return 0;
}

int ispisStoga(p_el p)	//argument je head element
{
	p = p->next;

	printf("ispis stoga: ");
	while (p != NULL) {
		printf("%s ", p->adress->item);
		p = p->next;
	}
	puts("");

	return 0;
}

p_node createNode(char* value) {
	p_node p = NULL;

	p = (p_node)malloc(sizeof(_node));

	if (NULL == p) {
		puts("Memory error");
		return NULL;
	}

	strcpy(p->item, value);
	p->L = NULL;
	p->R = NULL;
	printf("Stvoren cvor %s\n", p->item);

	return p;
}

int bufferSize(FILE* fp)
{
	int buffer_size = 0;

	fseek(fp, 0, SEEK_END);
	buffer_size = ftell(fp);

	printf("Velicina buffera je %d znakova\n", buffer_size);
	rewind(fp);

	return buffer_size;
}
