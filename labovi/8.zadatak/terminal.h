#pragma once

#include "tree.h"

p_dir processCommand(char*, p_dir);
p_dir ExecuteCmnd(char*, char*);
p_dir changeDir(p_dir, char*);
p_dir previousDir(p_dir);

p_dir processCommand(char* input, p_dir arg_dir)
{
	int r;
	char command[STR_SIZE] = { 0 };
	char arg[STR_SIZE] = { 0 };

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
		return arg_dir;
	}

	if (r == 0) {
		puts("INPUT ERROR");
		return arg_dir;
	}

	else
	{
		return ExecuteCmnd(&command, &arg, arg_dir);
	}

}

p_dir ExecuteCmnd(char* command, char* arg, p_dir arg_dir)
{

	if (strcmp(command, "mkdir") == 0)
	{
		addChild(arg_dir, arg);
	}

	else if (strcmp(command, "cd") == 0)
	{
		return changeDir(arg_dir, arg);
	}

	else if (strcmp(command, "cd..") == 0)
	{
		return previousDir(arg_dir);
	}

	else if (strcmp(command, "ls") == 0)
	{
		showContent(arg_dir);
	}

	else if (strcmp(command, "exit") == 0)
	{
		puts("Exiting terminal");
		return NULL;
	}

	else {
		printf("ERROR: Command  %s does not exist!\n\n", command);
	}

	return arg_dir;
}

p_dir previousDir(p_dir p)
{
	if (p->parent == NULL) {
		puts("ERROR: Current path is inside the root directory");
		return p;
	}
	else {
		return p->parent;
	}
}

p_dir changeDir(p_dir arg_p, char* arg_name)
{
	p_dir p = arg_p->child;

	if (*arg_name == '\0') {	//jer gets() dodaje '\0' na kraj
		puts("ERROR: new directory name is empty");
		return arg_p;
	}

	if (p == NULL) {
		printf("Directory with name %s does not exist\n", arg_name);
		return arg_p;
	}

	while ( strcmp(p->name, arg_name) != 0 && p != NULL)
	{
		p = p->brother;
	}

	if (strcmp(p->name, arg_name) == 0) {
		//puts("Directory found");	//debug
		return p;
	}

	else {
		printf("Directory with name %s does not exist\n", arg_name);
		return arg_p;
	}
}




