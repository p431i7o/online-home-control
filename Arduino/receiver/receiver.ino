/*
 
Written by Stanley Seow
 stanleyseow@gmail.com
Modified by p431i7o
pablito dot federico at gmail dot com

Arduino sends the message throught the IR led,  it receives throught the nrf24l01
*/

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <IRremote.h>

#define RF_SETUP 0x17

// Set up nRF24L01 radio on SPI pin for CE, CSN
RF24 radio(8,9);

const uint64_t pipes[2] = {0x7365727631LL, //para escribir
                           0xF0F0F0F0E1LL}; //para leer

char receivePayload[32];
uint8_t counter=0;
int amarillo;
IRsend irsend;
void setup(void){
  pinMode(2,OUTPUT);// amarillo
  
  Serial.begin(57600); 
  printf_begin();
  printf("Helloo... inicializando...\n\r"); 
  radio.begin(); 
  // Enable this seems to work better
  radio.enableDynamicPayloads(); 
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(76);
  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);
  radio.startListening();
  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  printf("inicializado completo\n\r");
  delay(1000);
}

void loop(void){
  char receivePayload[32];
  char temp2[1];
  unsigned long numeroEnviar;
  char * pEnd;
  uint8_t pipe = 1;
  while(radio.available (&pipe) ){
    uint8_t len = radio.getDynamicPayloadSize();
    radio.read( receivePayload, len);
    receivePayload[len]=0;
    //Mostrando en la pantalla 
    Serial.println("Recibiendo informacion");
    printf("size: %i payload:%s pipe:%i \n\r",len,receivePayload,pipe);
    numeroEnviar=strtol(receivePayload,&pEnd,16);
    printf("Numero recibido %lu\n\r",numeroEnviar);
    if(len==9){
      Serial.println("Enviando por IR");
      irsend.sendLG(numeroEnviar,28);
    }else{
      Serial.println("Numero con longitud errada, no se envia");
    }
    
    delay(1000);
    Serial.println("Reanudando escucha");
    radio.startListening();   
    
  } //end while
  delay(1000);
}



