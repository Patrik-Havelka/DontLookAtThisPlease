
#include <stdio.h>
#include <stdlib.h>
#include <string.h>



int vv(int n, FILE** ff, int* zaznamy, char*** polePrispevkov, char*** poleAutorov, char*** poleTypov, char*** poleCasov, char*** poleDatumov);
int nn(int n, FILE** ff, int* zaznamy, char*** polePrispevkov, char*** poleAutorov, char*** poleTypov, char*** poleCasov, char*** poleDatumov);



int main(){

FILE *f;
f = fopen("OrganizacnePodujatia.txt","r");

char** polePrispevkov;
char** poleAutorov;
char** poleTypov;
char** poleCasov;
char** poleDatumov;

int zaznamy = 0;


int n = 0;

char c;


int t = 1;
int v = 0;

while(t){
    printf("\nStlacte jedno z moznych tlacidiel(v,o,n,s,h,z,p,k): ");
    scanf("%c",&c);

    switch(c){

        case 'v':
            v = vv(n, &f, &zaznamy, &polePrispevkov, &poleAutorov, &poleTypov, &poleCasov, &poleDatumov);

            /*for(int i = 0; i < zaznamy; i++){
                printf("%s",polePrispevkov[i]);
                printf("%s",poleAutorov[i]);
                printf("%s",poleTypov[i]);
                printf("%s",poleCasov[i]);
                printf("%s",poleDatumov[i]);
                printf("\n");
                }*/

            printf("\nFunkcia dokoncena, stlacte ine pismeno: \n");
            scanf("%c",&c);

        break;

        case'n':
            if (nn(n,&f, &zaznamy, &polePrispevkov, &poleAutorov, &poleTypov, &poleCasov, &poleDatumov) == 1) n = 1;
            printf("%d",zaznamy);
            printf("\nFunkcia dokoncena, stlacte ine pismeno: \n");
            scanf("%c",&c);
        break;

        case'k':
            printf("\nUkoncenie programu a uvolnenie pamate\n");
            //t = 0;

            for (int i = 0; i < zaznamy; i++ ){
                free(polePrispevkov[i]);
            }
                free(poleAutorov);


            printf("\nFunkcia dokoncena, stlacte ine pismeno: \n");
            scanf("%c",&c);
        break;
    }
}

   /* for(int i = 0; i < zaznamy; i++){
        printf("%s",polePrispevkov[i]);
        printf("%s",poleAutorov[i]);
        printf("%s",poleTypov[i]);
        printf("%s",poleCasov[i]);
        printf("%s",poleDatumov[i]);
        printf("\n");
    }*/

    return 0;
}
/////////////////////////////////////////////////////////////////////////////
int vv(int n, FILE** ff, int* zaznamy, char*** polePrispevkov, char*** poleAutorov, char*** poleTypov, char*** poleCasov, char*** poleDatumov){

char c;

fseek(*ff, 0, SEEK_END); // tymto zistim pocet charov v subore, pretoze zacnem od 0 pos a idem na koniec a ftell mi povie poziciu kurzora
    int velkostSuboru = ftell(*ff);

    fseek(*ff, 0, SEEK_SET); // vratim kurzor na zaciatok


char s[velkostSuboru];


//*ff = fopen("OrganizacnePodujatia.txt","r");

    if(*ff == NULL){
        printf("Neotvoreny subor\n");
        return 0;
    }
    if(n == 1){
        printf("Polia boli vytvorene, vypisujem obsah poli: \n\n");


        //printf("%s",polePrispevkov);

       /* for(int i = 0; i < zaznamy; i++){
            printf("%s",*polePrispevkov[i]);
            printf("%s",*poleAutorov[i]);
            printf("%s",*poleTypov[i]);
            printf("%s",*poleCasov[i]);
            printf("%s",*poleDatumov[i]);
        printf("\n");
        }*/

        return 0;
    }
    else{
        printf("Polia neboli vytvorene, vypisujem obsah suboru: \n\n");
        while(fgets(s,velkostSuboru,*ff), feof(*ff)==0){
            printf("%s",s);
        }
    }

    return 0;
}
/////////////////////////////////////////////////////////////////////////////
int nn(int n, FILE** ff, int* zaznamy, char*** polePrispevkov, char*** poleAutorov, char*** poleTypov, char*** poleCasov, char*** poleDatumov){


int pocetZaznamov = 0;
int i = 0;

    //f = fopen("OrganizacnePodujatia.txt","r");
    if(n == 1){
        printf("Polia boli uz alokovane, vyprazdnujem...\n");
        //dealokovanie poli
    }

    fseek(*ff, 0, SEEK_END); // tymto zistim pocet charov v subore, pretoze zacnem od 0 pos a idem na koniec a ftell mi povie poziciu kurzora
    int velkostSuboru = ftell(*ff);

    fseek(*ff, 0, SEEK_SET); // vratim kurzor na zaciatok

    char s[velkostSuboru];

    while(fgets(s,velkostSuboru,*ff), feof(*ff)==0){ //prechadzam subor riadok po riadku dokym nenarazim na end of file a zvysujem counter hre zistenie poctu riadkov
            i++;
        }
    fseek(*ff, 0, SEEK_SET); //vratim kurzor na zaciatok

    char pomocnePole[i+1][150];

    //Alokovanie poli viem, ze i+1 je 36, a ked to podelim 6mi, dostanem celkovo 6 zaznamov, v pripade pridania zaznamu to bude 42/6 = 7, pretoze kazdy zaznam ma 5 udajov a jeden riadok s \n
    pocetZaznamov = (i+1)/6;

    i = 0;

    //Tento sposobm alokacie mam zo stack overflowu https://stackoverflow.com/questions/2614249/dynamic-memory-for-2d-char-array
    char** nazovPrispevku = calloc(pocetZaznamov, sizeof(char*)); // Tymto vytvorim vlastne pole pointrov a vytvorim mu nazovPrispevku[pocetZaznamov]
    for (int j = 0; j < pocetZaznamov; j++){
    nazovPrispevku[j] = (char*) calloc(150, sizeof(char)); //tu pre nazovPrispevku[pocetZaznamov] priradim [150]
    }

    //rovnaku alokaciu urobim pre ostatne prvky s roznmy poctami charov podla zadania

    char** menaAutorov = calloc(pocetZaznamov, sizeof(char*));
    for (int j = 0; j < pocetZaznamov; j++){
    menaAutorov[j] = (char*) calloc(100, sizeof(char));
    }

    char** typPrezentovania = calloc(pocetZaznamov, sizeof(char*));
    for (int j = 0; j < pocetZaznamov; j++){
    typPrezentovania[j] = (char*) calloc(3, sizeof(char));
    }

    char** casPrezentovania = calloc(pocetZaznamov, sizeof(char*));
    for (int j = 0; j < pocetZaznamov; j++){
    casPrezentovania[j] = (char*) calloc(5, sizeof(char));
    }

    char** datum = calloc(pocetZaznamov, sizeof(char*));
    for (int j = 0; j < pocetZaznamov; j++){
    datum[j] = (char*) calloc(9, sizeof(char));
    }



   while(fgets(s,velkostSuboru,*ff), feof(*ff)==0){
        strcpy(pomocnePole[i],s);               //nacitam si obsah suboru do pomocneho pola
        i++;
    }

    int tmp1[5]; // zistovac cisel pre podmienky vo fore
    int tmp2[5]; // inkrementacia
    //touto podmienkou budem pristupovat k poliam a urcovat ake cisla sa pricitavjau. tmp sa bude pohybovat vo fore pod tymto od 0 do 5 a tmp1 bude od 1-5, pretoze mam 5 udajov a potom sa len bude
    //pricitavat pre dalsie iteracie
        for(i = 0; i < 5; i++){
            tmp1[i] = i;
            tmp2[i] = 0;
        }


//Tato lupa mi vlozi cely obsah pomocneho pola, a teda obsah suboru do 5 roznych poli pre kazdy udaj
    for(i = 0; i < pocetZaznamov*6; i++){
        if (i == tmp1[0]){
            strcpy(nazovPrispevku[tmp2[0]],pomocnePole[i]);
            tmp1[0] += 6;
            tmp2[0]++;
       }
        else if(i == tmp1[1]){
            strcpy(menaAutorov[tmp2[1]],pomocnePole[i]);
            tmp1[1] += 6;
            tmp2[1]++;
       }
        else if(i == tmp1[2]){
            strcpy(typPrezentovania[tmp2[2]],pomocnePole[i]);
            tmp1[2] += 6;
            tmp2[2]++;
       }
        else if(i == tmp1[3]){
            strcpy(casPrezentovania[tmp2[3]],pomocnePole[i]);
            tmp1[3] += 6;
            tmp2[3]++;
       }
        else if(i == tmp1[4]){
            strcpy(datum[tmp2[4]],pomocnePole[i]);
            tmp1[4] += 6;
            tmp2[4]++;
       }
   }



    *polePrispevkov = nazovPrispevku;
    *poleAutorov = menaAutorov;
    *poleTypov = typPrezentovania;
    *poleCasov = casPrezentovania;
    *poleDatumov = datum;


    *zaznamy = pocetZaznamov;



  //testovanie vypisu obsahu poli
   /* for(i = 0; i < pocetZaznamov; i++){
        printf("%s",nazovPrispevku[i]);
        printf("%s",menaAutorov[i]);
        printf("%s",typPrezentovania[i]);
        printf("%s",casPrezentovania[i]);
        printf("%s",datum[i]);

        printf("\n");
    }*/

    printf("Nacitane data \n");

    return 1;
}
