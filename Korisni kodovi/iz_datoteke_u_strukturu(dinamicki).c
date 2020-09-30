//Iscitaj imena i prezimena studenata iz datoteke lista.txt i spremi ih u strukturu

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
    int n = 0;  //broj redaka u datoteci
    _student *studenti;   //niz struktura tipa _student
    FILE *fp;   //file pointer

    fp = fopen("lista.txt","r");    //otvaramo datoteku za citanje

    if( fp == NULL ) 
        puts("Greška pri otvaranju datoteke!");

    while( !feof(fp)){  //dok se ne dode od kraja datoteke moze i "feof(fp) == 0"
        if( fgetc(fp) == '\n' )
            n++;
    }
    
    rewind(fp); //nakon izvrsenja while petlje nalazimo se na kraju datoteke te se treba vratiti na
               //vrh da bi mogli ucitati imena studenata u strukturu novom while petljom

    printf("Broj studenata je %d\n", n);    //1 redak = 1 student

    studenti = (_student*)malloc(n * sizeof(_student)); //dinamicka alokacija niza struktura

    while( !feof(fp)){  //dok se ne dode od kraja datoteke moze i "feof(fp) == 0"
        for( i = 0; i < n; i++)    
            fscanf(fp, "%s %s %d", studenti[i].ime, studenti[i].prezime, &studenti[i].postotak);
    }

    puts("ISPIS STUDENATA I BODOVA:\n");
    for( i = 0; i < n; i++) //ispis
        printf("%s %s\t%d\n", studenti[i].ime, studenti[i].prezime, studenti[i].postotak);

    fclose(fp); //zatvaramo datoteku

    return 0;
}
