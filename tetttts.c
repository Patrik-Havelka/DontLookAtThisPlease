#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void menic(int* a);

int main(){


int a = 5;

printf("%d\n",a);

menic(&a);

printf("%d\n",a);

return 0;
}

void menic(int* a){

*a = 6;
}
