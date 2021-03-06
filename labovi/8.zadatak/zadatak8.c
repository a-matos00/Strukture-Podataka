#include<stdio.h>
#include<stdlib.h>

#include "tree.h"	//sadrzi funkcije vezane za upravljanje stablom
#include "terminal.h"	//sadrzi funkcije vezane za naredbe terminala


int main()
{
	char input[STR_SIZE];
	char username[STR_SIZE];

	p_dir curr_dir = NULL;
	
	_dir root;
	root.child = NULL;
	root.brother = NULL;
	root.parent = NULL;

	curr_dir = &root;	//trenutno otvoreni direktorij

	puts("Enter username(root directory name): ");	//unos naziva root direktorija
	gets(username);
	strcpy(root.name, username);
	
	while (1)
	{
		printf("%s/", curr_dir->name);	//ispis trenutno otvorenog direktorija
		gets(&input);	//korisnikov unos
		curr_dir = processCommand(&input, curr_dir);	//funkcija vraca direktorij koji je otvoren

		if (curr_dir == NULL)	//ako funkcija vrati NULL tada se izlazi iz programa
			break;
	}

	
	remove(root.child);	//brise se stablo, root direktorij se ne brise
	root.child = NULL;
	showContent(&root);	//provjera

	system("pause");
	return 0;
}
