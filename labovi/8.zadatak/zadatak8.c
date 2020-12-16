#include<stdio.h>

#define NAME_SIZE 256
typedef struct dir* p_dir;

typedef struct dir {
	char name[NAME_SIZE];
	p_dir child;
	p_dir brother;
}_dir;

p_dir createDir(char*);
int addChild(p_dir, p_dir);
int addBrother(p_dir, p_dir);

int main()
{
	_dir root;

	strcpy(root.name, "Home");
	root.child = NULL;
	root.brother = NULL;

	return 0;
}

int addChild(p_dir p, p_dir new_dir) 
{
	if (p->child == NULL) {	//ako vec postoji dijete
		p->child = new_dir;
		
	}

	else {
		addBrother(p->child, new_dir);
	}

	return 0;
}

int addBrother(p_dir p, p_dir new_dir)
{
	p_dir new_dir = NULL;

	new_dir = createDir("string"); //!!!!!!!!!!

	while (p->brother != NULL)
	{
		p = p->brother;
	}
	
	p->brother = new_dir;	//novi brat se dodaje na kraj liste
	

	return 0;
}

p_dir createDir(char* name)
{
	p_dir new_dir = (p_dir)malloc(sizeof(_dir));

	if (new_dir == NULL) {
		puts("Neuspjesna alokacija memorije za novi direktorij");
		return NULL;
	}

	strcpy(new_dir->name, name);
	new_dir->child = NULL;
	new_dir->brother = NULL;

	return ;
}