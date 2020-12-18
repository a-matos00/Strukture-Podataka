#pragma once

#define STR_SIZE 256

struct dir;
struct el;

typedef struct dir* p_dir;
typedef struct el* p_el;

typedef struct el{
	char name[STR_SIZE];	//debug
	p_el next;
}_el;

typedef struct dir {
	char name[STR_SIZE];
	p_dir child;
	p_dir brother;
	p_dir parent;

}_dir;

p_dir createDir(char*);
int addChild(p_dir, char*);
int addBrother(p_dir, char*);
int showContent(p_dir);
int remove(p_dir);

int remove(p_dir p)
{
	if( p == NULL)
		return 0;

	remove(p->brother);
	remove(p->child);
	printf("Uklonjen %s\n", p->name);
	free(p);

	return 0;
}

int addChild(p_dir p, char* name)
{

	if (p->child == NULL) {		//ako nema dijete
		p->child = createDir(name);
		p->child->parent = p;
	}

	else {
		addBrother(p, name);
	}

	return 0;
}

int addBrother(p_dir p, char* name)	//argument je parent
{
	p_dir parent = p;
	p_dir prev = NULL;

	p_dir new_child = createDir(name);
	new_child->parent = parent;

	p = p->child;	//P je sada prvo dijete
	prev = p;

	if ( strcmp(name, p->name) < 0 ) //ako je manji od prvog djeteta
	{
		parent->child = new_child;
		new_child->brother = p;
	}

	else {

		while (p->brother != NULL && strcmp(name, p->name) > 0)
		{
			prev = p;
			p = p->brother;
		}

		new_child->brother = prev->brother;
		prev->brother = new_child;
	}
	return 0;
}

p_dir createDir(char* arg_name)
{
	p_dir new_dir = (p_dir)malloc(sizeof(_dir));

	if (new_dir == NULL) {
		puts("Neuspjesna alokacija memorije za novi direktorij");
		return NULL;
	}

	strcpy(new_dir->name, arg_name);
	new_dir->child = NULL;
	new_dir->brother = NULL;

	printf("Created new directory %s\n", arg_name);

	return new_dir;
}

int showContent(p_dir p)
{
	if(p == NULL)
	{
		puts("MEMORY ERROR(pointer to directory has NULL value");
		return -1;
	}

	if( p->child == NULL )
	{
		printf("Directory %s is empty\n", p->name);
		return 0;
	}

	p = p->child;	//pokazivac se spusta na prvo dijete

	while (p != NULL)
	{
		printf("%s ", p->name);
		p = p->brother;
	}
	puts("");

	return 0;
}
