#include<stdio.h>
#include<stdlib.h>
#include<time.h>

typedef struct el* p_el;

typedef struct el {
	int broj;
	p_el next;
}_el;

int randBr();
int push(p_el);
int pop(p_el);
int ispis(p_el);

int main()
{
	_el head;
	head.next = NULL;

	srand(time(NULL));

	push(&head);
	push(&head);
	push(&head);
	ispis(&head);
	pop(&head);

	ispis(&head);


	system("pause");
	return 0;
}

int pop(p_el p)
{
	p_el temp;

	temp = p->next;

	p->next = temp->next;

	free(temp);

	return 0;
}



int push(p_el p)	//argument je head element
{

	p_el novi;

	if( p == NULL){
		puts("Neispravan argument, null pokazivac");
		return -1;
	}
	
	novi = (p_el)malloc(sizeof(_el));	//stvara se novi element
	novi->broj = randBr();

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
