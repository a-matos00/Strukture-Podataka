#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define N 20 //velicina niza


int nasumicni(int [N], int);


int main()
{
    int niz[N];
    int i, j, temp;

    srand(time(NULL));  //da se nebi uvijek generirali isti brojevi

   for( i = 0; i < N; i++)          //upis nasumicnih brojeva u niz
        niz[i] =  nasumicni(niz, i);

    for( i = 0; i < N - 1; i++)     //sortira san niz da lakse provjerin ponavlja li se koji broj
        for( j = i + 1; j < N; j++)
            if( niz[i] > niz[j] ){
                temp = niz[i];
                niz[i] = niz[j];
                niz[j] = temp;
            }

    for( i = 0; i < N; i++)         //ispis
        printf("%d ", niz[i]);

    puts("");
    
    return 0;
}

int nasumicni(int niz[N], int n){

    int x;  // "x" generirani nasumicni broj koji vracamo
    int i = 0;
    int check = 0;    // pomocna varijabla za provjeru ponavljanja
    x = rand() % ( 50 - 20 + 1) + 20;   // "(b - a + 1) + a" za interval od <20,50>

    for( i = 0; i < n; i++)
        if( x == niz[i])    //ako generirani broj odgovara vec postojecem broju u nizu
            check++;
    
    if( check > 0 ) //ako generirani broj vec postoji, generiramo novi broj rekurzuvnim pozivom funkcije
        return nasumicni(niz, n);
    else
        return x;
        
}
