#include<stdio.h>
#include<stdlib.h>

#include "tree.h"

int processCommand(char*);
int ExecuteCmnd(char*, char*);

int main()
{
	_dir root;
	char input[256];

	strcpy(root.name, "Home");
	root.child = NULL;
	root.brother = NULL;
	
	while (1)
	{
		printf("User: ");
		gets(&input);
		processCommand(&input);
	}

	return 0;
}

int processCommand(char* input)
{
	int r;
	char command[256] = {0};
	char arg[256] = {0};

	char* buffer = (char*)calloc(strlen(input) + 1, sizeof(char));

	strcpy(buffer, input);

	//printf("Print buffer %s\n", buffer); //debug

	r = sscanf(buffer, "%s %s", &command, &arg);
		
	/*printf("r === %d\n",r);	//debug
	printf("%s\n", command);
	printf("%s\n", name);
	*/

	if (r == -1) {
		puts("FATAL ERROR");
		return -1;
	}

	if (r == 0) {
		puts("INPUT ERROR");
		return -1;
	}

	else
	{
		ExecuteCmnd(&command, &arg);
	}

	return 0;
}

int ExecuteCmnd(char* command, char* arg)
{

	if (strcmp(command, "mkdir") == 0)
	{
		
	}

	else if (strcmp(command, "cd") == 0)
	{

	}

	else if (strcmp(command, "ls") == 0)
	{

	}

	else if (strcmp(command, "exit") == 0)
	{

	}

	else {
		puts("ERROR: Command not found!");
		return -1;
	}


	return 0;
}