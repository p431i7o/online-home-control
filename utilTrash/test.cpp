#include <stdio.h>
#include <stdlib.h>
int main(){
char cadena[] = "0x8808A46";
char * pEnd;
   unsigned long numero;
   numero = strtol(cadena,&pEnd,16);
   
   printf("numero %s=%ld",cadena,numero);
   return 0;
}
