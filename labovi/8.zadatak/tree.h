#pragma once
typedef struct dir* p_dir;
#define STR_SIZE 256
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


int addChild(p_dir p, char* name)
{

	if (p->child == NULL) {	//ako vec postoji dijete
		p->child = createDir(name);
		p->child->parent = p;
	}

	else {
		addBrother(p->child, name);
	}

	return 0;
}

int addBrother(p_dir p, char* name)	//first arg is the first child of parent
{
	while (p->brother != NULL)
	{
		p = p->brother;
	}

	p->brother = createDir(name);
	p->brother->parent = p->parent;

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
	p = p->child;

	while (p != NULL)
	{
		printf("%s ", p->name);
		p = p->name;
		p = p->brother;
	}
	puts("");

	return 0;
}