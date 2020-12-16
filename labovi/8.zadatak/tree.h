#pragma once

#define NAME_SIZE 256
typedef struct dir* p_dir;

typedef struct dir {
	char name[NAME_SIZE];
	p_dir child;
	p_dir brother;
}_dir;

p_dir createDir();
int addChild(p_dir);
int addBrother(p_dir);
int showContent(p_dir p);

int addChild(p_dir p)
{

	if (p->child == NULL) {	//ako vec postoji dijete
		p->child = createDir();
	}

	else {
		addBrother(p->child);
	}

	return 0;
}

int addBrother(p_dir p)
{
	while (p->brother != NULL)
	{
		p = p->brother;
	}

	p->brother = createDir();

	return 0;
}

p_dir createDir()
{
	char name[NAME_SIZE];

	p_dir new_dir = (p_dir)malloc(sizeof(_dir));

	if (new_dir == NULL) {
		puts("Neuspjesna alokacija memorije za novi direktorij");
		return NULL;
	}

	puts("Unesi ime direktorija: ");
	scanf("%s", &name);

	strcpy(new_dir, name);

	strcpy(new_dir->name, name);
	new_dir->child = NULL;
	new_dir->brother = NULL;

	//printf("Ime novog direktorija %s\n", new_dir->name); //debug

	return new_dir;
}

int showContent(p_dir p)
{
	printf("Ispis sadrzaja direktorija: ");

	while (p != NULL)
	{
		printf("%s ", p->name);
		p = p->name;
		p = p->brother;
	}
	puts("");

	return 0;
}