#include<stdio.h>
#define N 10 //velicina niza

int main()
{
    int niz[N] = {1,2,3,4,5,6,7,8,9,10};    //zadani niz koji je slozen po velicini

    int trazeni = 3;   //trazeni broj
    int donja, gornja;  //donja i gornja granica 
    int sredina;    //aritmeticka sredina zbroja donje i gornje granice

    donja = 0;  //postavljamo donju granicu na najmanji indeks
    gornja = N - 1; // -1 jer je najveci indeks u nizu (N - 1)
    int broj = 0;   //ova varijabla bi u algoritmu mijenja vrijednost samo u uvjetu kada smo pronasli trazeni broj
    
    while (broj == 0 && (donja < gornja)) {
        sredina = (donja + gornja) / 2; //racunamo indeks aritmeticke sredine niza

        if (trazeni == niz[sredina]) {  //ako se trazeni broj nalazi tocno na sredini intervala koji gledamo
            broj = trazeni;   
            printf("trazeni broj je %d na [%d]", niz[sredina], sredina);
            return 0;   //pronašli smo broj te izlazimo iz programa
        }

        else if (trazeni < niz[sredina])
            gornja = sredina - 1;   //ako je trazeni broj manji od onog na aritmetickoj sredini onda spustamo gornju granicu

        else
            donja = sredina + 1;    //ako je broj veci od onog na aritmetickoj sredini onda podizemo donju granicu
    }

    if (donja == gornja && trazeni == niz[donja])   //ako se donja i gornja granica poklope tada imamo samo jedan preostali broj za provjeru
        printf("trazeni broj je %d na [%d]", niz[donja], donja);
    else
        puts("Trazeni broj nije pronaden!!!");  //ako i u slucaju poklapanja broj ne odgovara tada zakljucujemo da broj ne pripada nizu
    
    return 0;
}


