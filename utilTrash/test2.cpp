#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <string>
#include <cstdlib>

bool enviarMensaje(char* mensaje){
	printf("\nMensaje:\n");
	
	printf("Mensaje es: %s\n",mensaje);
	int actualSize=0,i=0;
	for(;mensaje[i]!='\0';){
		i++;
		actualSize++;
	}
	printf("\nSizeof %i\n",actualSize);
	return true;
}

int main(int argc,char ** argv){
	char opcion;
	int contador=0;
//	extern char *optarg;
	while((opcion = getopt(argc,argv,"f:"))!=-1){
		if(opcion=='f'){
	            printf("\nEnviando comando!\n");
		    enviarMensaje(optarg);
            	}else{	
			printf("\n\r====Ayuda=======\n");
 		        printf("\n\rUsar la opcion -f  ");
	                printf("\nCodigo hex para enviar.");
			printf("\n\rPor ejemplo: ");
			printf("\nsudo ./rpi-transmiter -f 0x880001AA\n");
		}
		if(contador<5){ return 0; } else { return 2;}
	}

}
