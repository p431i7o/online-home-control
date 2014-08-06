/*
Written by Stanley Seow
 stanleyseow@gmail.com
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"

#define RF_SETUP 0x17

// Set up nRF24L01 radio on SPI pin for CE, CSN
RF24 radio(8,9);

// Example below using pipe5 for writing
//const uint64_t pipes[2] = { 
//  0xF0F0F0F0E1LL, 0x7365727631LL };
const uint64_t pipes[6] = { 0x7365727631LL, 0xF0F0F0F0E1LL, 0xF0F0F0F0E2LL, 0xF0F0F0F0E3LL, 0xF0F0F0F0E4, 0xF0F0F0F0E5 };
//char receivePayload[32];
//uint8_t counter=0;
//int inPin = 6;   // button connected to digital pin 6
//int indiceActual =0;
//int maxLongitud =0;
//char textLargo[] = "Un texto muy largo, muy muy largo... que nunca termina porque es largo";
void setup(void){
  // Conor Switch
  //pinMode(inPin, INPUT);

  Serial.begin(57600); 
  printf_begin();
  printf("Setup - Arduino iniciando...\n\r"); 
  radio.begin(); 
  // Enable this seems to work better
  radio.enableDynamicPayloads(); 
  radio.setAutoAck(1);
  radio.setRetries(15,15);
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(76);
  radio.setCRCLength(RF24_CRC_16);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.openReadingPipe(2,pipes[2]);
  radio.openReadingPipe(3,pipes[3]);
  radio.openReadingPipe(4,pipes[4]);
  radio.openReadingPipe(5,pipes[5]);
  //radio.openWritingPipe(pipes[0]);
  //radio.openReadingPipe(1,pipes[1]);
 printf("Detalles:\n\r");
 radio.startListening();
  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  delay(1000);
}

void loop(void){
  char receivePayload[32];
  uint8_t pipe = 0;

  while(radio.available(&pipe)){
  	uint8_t len = radio.getDynamicPayloadSize();
	radio.read(receivePayload,len);
	printf("Recibido: tamanyo:%i payload:%s pipe:%i\r\n",len,receivePayload,pipe);
	radio.stopListening();
	if(pipe!=7){
	  radio.write(receivePayload,len);
	  receivePayload[len]=0;
	  printf("Respuesta enviada: tamanyo:%i payload:%s pipe: %i\n\r",len,receivePayload,pipe);
	}else{
	  printf("\nelse 7\n\r");
	}
	radio.startListening();
	pipe++;
	if(pipe > 5) pipe = 0;
  }
  usleep(20);
  
} //end void





