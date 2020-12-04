#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct el* p_el;

typedef struct el {
	int broj;
	p_el next;
	p_el last;
}_el;

int randBr();
int push(p_el);
int pop(p_el);
int ispis(p_el);

int main()
{
	_el head;
	head.next = NULL;
	head.last = NULL;

	srand(time(NULL));

	push(&head);
	push(&head);
	push(&head);

	ispis(&head);

	pop(&head);

	printf("Zadnji element je %d\n", head.last->broj);

	ispis(&head);
	
	system("pause");
	return 0;
}

int pop(p_el head)
{
	p_el i = head;

	while( i->next != head->last){

	}

	return 0;
}



int push(p_el p)	//argument je head element
{
	p_el novi;
	p_el temp = p->next;
	p_el head = p;

	if( p == NULL){
		puts("Neispravan argument");
		return -1;
	}

	novi = (p_el)malloc(sizeof(_el));

	if( novi == NULL){
		puts("Neuspjesna alokacija novog elementa!");
		return -1;
	}

	novi->broj = randBr();

	if( p->next == NULL){	//ako je lista prazna
		p->last = novi;
	}

	else{
		while(temp->next != NULL){
			temp = temp->next;
		}

		head->last = temp;
		
	}

	novi->next = p->next;
	p->next = novi;

	return 0;
}

int randBr()
{
	int rand_br;
	
	rand_br = rand() % (100 - 1 + 1) + 1;   // "(b - a + 1) + a" za interval od <a,b>

	return rand_br;
}

int ispis(p_el p)	//argument je head element
{
	p = p->next;

	while(p!= NULL){
		printf("%d ", p->broj);
		p = p->next;
	}

	puts("");

	
	return 0;
}
