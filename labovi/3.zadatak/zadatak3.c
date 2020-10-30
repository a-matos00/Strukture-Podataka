#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct osoba* p_osoba; //pokazivac na strukturu

typedef struct osoba {
    char ime[20];
    char prezime[20];
    int godina;
    p_osoba next;
}_osoba;

void unosPodataka(p_osoba);
int ispis(p_osoba); //funkcija ispisuje clanove liste
int unosPocetak(p_osoba); //funkcija dodaje novi clan na pocetak liste
int unosKraj(p_osoba);    //funkcija unosi novi clan na kraj liste
p_osoba traziPrezime(p_osoba);    //funkcija trazi clan u listi po prezimenu
p_osoba traziPrethodni(p_osoba);    //funkcija trazi clan u listi po koji se nalazi ispred trazenog prezimena
int traziUkloni(p_osoba); //funkcija trazi clan po prezimenu te ga uklanja iz liste
int dodajIza(p_osoba);
int dodajIspred(p_osoba);
void sortiraj(p_osoba);
void uDatoteku(p_osoba);

int main()
{
    _osoba head;  //inicijalizacija pocetnog clana liste
    head.next = NULL; //postavljamo da prvi clan pokazuje na nista jer je trenutno jedini clan u listi

    
    unosKraj(&head);
    unosKraj(&head);
    unosKraj(&head);
    ispis(head.next);

    uDatoteku(head.next);

    return 0;
}

int unosPocetak(p_osoba p) //u funkciju smo poslali adresu HEAD clana
{
    p_osoba q = (p_osoba)malloc(sizeof(_osoba)); //stvaramo novu strukturu

    if (q == NULL) {
        puts("GREŠKA! Memorija nije alocirana");
        return -1;
    }

    unosPodataka(q);

    q->next = p->next;  //dodani clan sada pokazuje na ono na sto je prije pokazivao HEAD clan
    p->next = q;  //HEAD clan sada pokazuje na dodani clan

    return 0;
}

int unosKraj(p_osoba p)    //argument je adresa HEAD clana
{
    p_osoba q = (p_osoba)malloc(sizeof(_osoba)); //stvaramo novu strukturu

    if (q == NULL) {
        puts("GREŠKA! Memorija nije alocirana");
        return -1;
    }

    unosPodataka(q);

    while (p->next != NULL) {   //dok ne dodemo do zadnjeg clana u listi
        p = p->next;    //prebacujemo se na sljedeci clan
    }
    p->next = q;  //bivsi zadnji clan sada pokazuje na novi clan
    q->next = NULL;     //novi clan mora pokazivati na nista jer je zadnji u listi

    return 0;
}

int ispis(p_osoba p)   //argument je adresa prvog stvarnog clan liste
{
    puts("Ispis popisa ljudi:\n");

    while (p != NULL)   //petlja se odvija dok ne dodemo do zadnjeg clana( zadnji clan pokazuje na "nista" jer nema svog sljedbenika unutar liste dok svi ostali imaju)
    {
        printf("%s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis podataka trenutnog clana liste
        p = p->next;    //prebacujemo se na sljedeci clan u listi
    }

    return 0;
}

p_osoba traziPrezime(p_osoba p) //argument je adresa prvog stvarnog clan liste
{
    char prezime[20];   //u ovu varijablu upisujemo prezime koje trazimo

    puts("Upisi prezime koje trazite:");
    scanf("%s", prezime);   //unosimo trazeno prezime

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //petlja se vrti dok ne dodemo do zadnjeg clana i dok vrijednost varijable prezime ne odgovara trazenom prezimenu(vidi vrh za objasnjenje strcmp();
    {
        p = p->next;    //prebacujemo se na sljedeci clan liste
    }

    if (strcmp(prezime, p->prezime) == 0) {  //ako smo pronasli trazeni clan
        printf("p_osoba je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis trazenog clana
        return p;
    }
    else if (strcmp(prezime, p->prezime) != 0)  //ako trazeni clan nije pronaden
    {
        puts("Trazeno prezime ne postoji u listi"); //prigodna poruka
        return NULL;
    }
    
}

int traziUkloni(p_osoba p) //argument je adresa HEAD clana
{
    char prezime[20];
    p_osoba temp = (p_osoba)malloc(sizeof(_osoba));    //stvaramo privremenu varijablu koja sluzi za oznacavanje clana koji prethodi trazenom clanu

    if (temp == NULL) {
        puts("GREŠKA! Memorija nije alocirana");
        return -1;
    }

    puts("Upisi prezime osobe koju zelis ukloniti:");
    scanf("%s", prezime);

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //isti uvjet kao kod traziPrezime()
    {
        temp = p;   //spremamo adresu trenutnog clana jer ce nam poslije sluziti kao adresa clana koji prethodi trazenom clanu
        p = p->next;    //prebacujemo se na sljedeci clan
    }

    if (strcmp(prezime, p->prezime) == 0) { //ako smo pronasli trazeni clan
        temp->next = p->next;   //clan koji prethodi uklonjenom clanu ce sada pokazivati na clan liste koji slijedi nakon uklonjenog
        free(p);    //oslobadamo memoriju izbacenog clana liste
    }

    else if (strcmp(prezime, p->prezime) != 0)
        puts("Trazeno prezime ne postoji u listi");

    return 0;
}

int dodajIza(p_osoba p) //argument je prvi pravi clan liste
{
    p_osoba novi = (p_osoba*)malloc(sizeof(_osoba));    //alociramo memoriju za novi clan

    if (novi == NULL) {     //ako alokacija nije uspijel
        return -1;
    }

    p_osoba trazeni = traziPrezime(p);    //pronalazimo clan iza kojeg cemo dodati novi clan

    if (trazeni == NULL) {  //ako clan s trazenim prezimenom nije pronaden
        return -1;
    }

    novi->next = trazeni->next;
    trazeni->next = novi;

    unosPodataka(novi);

    return 0;
}

p_osoba traziPrethodni(p_osoba p) //argument je adresa prvog stvarnog clan liste
{
    char prezime[20];   //u ovu varijablu upisujemo prezime koje trazimo

    p_osoba prethodni = p;

    puts("Upisi prezime koje trazite:");
    scanf("%s", prezime);   //unosimo trazeno prezime

    while (p->next != NULL && strcmp(prezime, p->prezime) != 0) //petlja se vrti dok ne dodemo do zadnjeg clana i dok vrijednost varijable prezime ne odgovara trazenom prezimenu(vidi vrh za objasnjenje strcmp();
    {
        prethodni = p;
        p = p->next;    //prebacujemo se na sljedeci clan liste
    }

    if (strcmp(prezime, p->prezime) == 0) {  //ako smo pronasli trazeni clan
        printf("p_osoba je pronaden: %s\t%s\t%d\n", p->ime, p->prezime, p->godina); //ispis trazenog clana
        return prethodni;
    }

    else if (strcmp(prezime, p->prezime) != 0)  //ako trazeni clan nije pronaden
    {
        puts("Trazeno prezime ne postoji u listi"); //prigodna poruka
        return NULL;
    }
  
}

int dodajIspred(p_osoba p) //argument je prvi pravi clan liste
{
    p_osoba prethodni, novi;

    prethodni = traziPrethodni(p);    //pronalazimo clan iza kojeg cemo dodati novi clan

    if (prethodni == NULL) {  //ako clan s trazenim prezimenom nije pronaden
        return -1;
    }

    novi = (p_osoba*)malloc(sizeof(_osoba));    //alociramo memoriju za novi clan

    if (novi == NULL) {     //ako alokacija nije uspijela
        puts("GRESKA!!! Alokacija memorije za novi clan nije uspjela");
        return -1;
    }

    unosPodataka(novi);

    novi->next = prethodni->next;
    prethodni->next = novi;

    return 0;
}

void unosPodataka(p_osoba p)
{
    puts("Unesi ime:");     //unos podataka u novi clan
    scanf("%s", p->ime);
    puts("Unesi prezime:");
    scanf("%s", p->prezime);
    puts("Unesi godinu rodenja:");
    scanf("%d", &p->godina);

}

void sortiraj(p_osoba p)
{
    p_osoba  j, prev, temp, end;
    
    end = NULL;

    while (p->next != end)
    {
        prev = p;
        j = p->next;

        while (j->next != end)
        {
            if (strcmp(j->prezime, j->next->prezime) > 0) {

                temp = j->next;
                prev->next = temp;
                j->next = temp->next;
                temp->next = j;

                j = temp;
            }
            prev = j;
            j = j->next;
        }
        end = j;
    }
}

void uDatoteku(p_osoba p)
{
    FILE* fp = NULL;

    fp = fopen("osobe.txt", "w");

    while (p != NULL) {
        fprintf(fp, "%s\t%s\t%d\n", p->ime, p->ime, p->godina);

        p = p->next;
    }

    puts("GOTOVO!");
}
