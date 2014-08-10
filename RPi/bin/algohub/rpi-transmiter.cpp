/**
 * Este archivo tendra lo que el transmisor en el raspberry pi hara
 */
#include <stdio.h>

#include <iostream>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include <string>
#include <cstdlib>

#include "../RF24.h"
//define RF_SETUP 0X17
//define IF_SERIAL_DEBUG 
using namespace std;
// Radio pipe addresses for the 2 nodes to communicate.
// First pipe is for writing, 2nd, 3rd, 4th, 5th & 6th is for reading...
// Pipe0 in bytes is "serv1" for mirf compatibility
/*const uint64_t pipes[6] = { 0x7365727631LL, 
                            0xF0F0F0F0E1LL, 
                            0xF0F0F0F0E2LL, 
                            0xF0F0F0F0E3LL, 
                            0xF0F0F0F0E4, 
                            0xF0F0F0F0E5 };
*/
const uint64_t pipes[2] = { 0xF0F0F0F0E1LL, //para escribir
                            0x7365727631LL // Para leer
};
char receivePayload[32];
// CE and CSN pins On header using GPIO numbering (not pin numbers)
RF24 radio("/dev/spidev0.0",8000000,25);  // Setup for GPIO 25 CSN

void setup(void){
    printf("\nSetup - Preparando interface\n");
    radio.begin();//
    radio.enableDynamicPayloads();//
    radio.setAutoAck(1);
    radio.setRetries(15,15);//
    
    radio.setDataRate(RF24_1MBPS);//
    radio.setPALevel(RF24_PA_MAX);//
    radio.setChannel(76);//
    radio.setCRCLength(RF24_CRC_16);  

    radio.openWritingPipe(pipes[0]);
    radio.openReadingPipe(1,pipes[1]);
    radio.startListening();
    printf("\nSetup - A continuacion, detalles:\n");
    radio.printDetails();
    sleep(2);
    
}

bool enviarMensaje(char* mensaje){
    radio.stopListening();
    printf("Mensaje recibido: %s\n",mensaje);
    int i=0;
    for(;mensaje[i]!='\0';){
       i++;       
    }
   printf("Tamanyo enviado %i vs %i\n\r",i,sizeof("hola"));
   bool ok = radio.write(&mensaje,/*size:*/i+1);
    if(ok){
        printf("Ok . . . \n\r");        
    }else{
        printf("Fallo envio.\n\r");        
    }
    //En espera del ACK
    radio.startListening();
    usleep(20);
    //Se toma el tiempo de espera
    unsigned long se_empieza = __millis();
    bool timeout = false;
    while( radio.available() && ! timeout ){
	uint8_t len = radio.getDynamicPayloadSize();
	radio.read(receivePayload,len);
	unsigned long got_time;
	receivePayload[len]=0;
	printf("inBuffer: %s\n\r",receivePayload);
	//Comparacion de lo enviado con lo recivido
	if( !strcmp(mensaje,receivePayload) ){
	    radio.read(&got_time, sizeof(unsigned long) );
	    printf("Se recibio respuesta %lu, retraso envio: %lu\n\r",got_time,__millis()-got_time);
	    return true;
	}
    	    
         usleep(10);
    	if (__millis() - se_empieza > 5000 )
      	timeout = true;

    }
    if( timeout ){
        //Si se espero mucho, la transmision fallo
        printf("Error, El tiempo ya paso.\n\r");
        radio.printDetails();
        return false;
    }
	return true;
	/*else{
        //Si se recibio un mensaje a tiempo, se lee
        unsigned long got_time;
        radio.read( &got_time, sizeof(unsigned long) );
        printf("Se recibio respuesta %lu, retraso envio: %lu\n\r",got_time,__millis()-got_time);
        return true;        
    }
    */

    
}
int main (int argc, char ** argv){
    char opcion;
    setup();
    int contador=0;
    //definiendo opciones
    while((opcion = getopt(argc,argv,"f:"))!=-1){
        if(opcion=='f'){
            printf("\nEnviando comando!\n");
	    printf("\n%s\n",optarg);
            enviarMensaje(optarg);
        }else{
            //imprimiendo ayuda
            printf("\n\r====Ayuda=======\n");
            printf("\n\rUsar la opcion -f  ");
            printf("\nCodigo hex para enviar.");
            printf("\n\rPor ejemplo: ");
            printf("\nsudo ./rpi-transmiter -f 0x880001AA\n");
        }
        //retornar 0 si todo salio bien, 2 si no fue asi
        if ( contador < 5){
         return 0;
        }else{
         return 2;
        }
    }
    
}
