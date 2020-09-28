//Iscitaj imena i prezimena studenata i postotak rijesenosti ispita iz datoteke lista.txt i spremi ih u strukturu

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define N 5

typedef struct student{
    char ime[20];
    char prezime[20];
    int postotak;
} _student;

int main()
{

    int i = 0;
    _student studenti[N];   //niz struktura tipa _student
    FILE *fp;   //file pointer

    fp = fopen("lista.txt","r");    //otvaramo datoteku za citanje

    if( fp == NULL ) 
        puts("Greška pri otvaranju datoteke!");

    while( !feof(fp)){  //dok se ne dode od kraja datoteke
        for( i = 0; i < N; i++)    
            fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].postotak);
    }

    for( i = 0; i < N; i++) //ispis
        printf("%s %s\t%d\n", studenti[i].ime, studenti[i].prezime, studenti[i].postotak);

    fclose(fp);

    return 0;
}
