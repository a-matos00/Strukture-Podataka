#include<stdio.h>
#include<stdlib.h>

#include "tree.h"
#include "terminal.h"

int main()
{
	char input[STR_SIZE];
	char username[STR_SIZE];
	p_dir curr_dir = NULL;
	_dir root;

	strcpy(root.name, "root");
	root.child = NULL;
	root.brother = NULL;
	root.parent = NULL;

	curr_dir = &root;

	puts("Enter username: ");
	gets(username);
	
	while (1)
	{
		printf("%s/%s/ ",username, curr_dir->name);
		gets(&input);
		curr_dir = processCommand(&input, curr_dir);

		if (curr_dir == NULL)
			break;
	}

	return 0;
}
