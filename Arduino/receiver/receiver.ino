/*
Written by Stanley Seow
 stanleyseow@gmail.com
 */

#include <SPI.h>
#include "nRF24L01.h"
#include "RF24.h"
#include "printf.h"
#include <IRremote.h>

#define RF_SETUP 0x17

// Set up nRF24L01 radio on SPI pin for CE, CSN
RF24 radio(8,9);

// Example below using pipe5 for writing
// // const uint64_t pipes[2] = {0xF0F0F0F0E1LL, 0x7365727631LL };
const uint64_t pipes[2] = {0x7365727631LL, //para escribir
                           0xF0F0F0F0E1LL}; //para leer

char receivePayload[32];
uint8_t counter=0;
//int outpin = 6; // pin de salida
//int indiceActual =0;
//int maxLongitud =0;
//char textLargo[] = "Un texto muy largo, muy muy largo... que nunca termina porque es largo";
 int verde,amarillo,rojo;
IRsend irsend;
void setup(void){
  // Conor Switch
//  pinMode(outpin, OUTPUT); 
  //verde=LOW;
 // rojo=;
 // amarillo=0;
  //pinMode(4,OUTPUT);// verde
  pinMode(2,OUTPUT);// amarillo
  //pinMode(3,OUTPUT);// rojo
  
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
    /*******
    if(strcmp(receivePayload,"encendido")==0){
     Serial.println("Enviando encendido");
     irsend.sendLG(0x880094D,28);
    }else if (strcmp(receivePayload,"apagado")==0){
      Serial.println("Enviando apagado");
     irsend.sendLG(0x88C0051,28);
    }else{
      Serial.println("ninguna de las anteriores");
    }
    *****/
    /******
    if( strcmp(receivePayload,"verde")==0 ){
      verde = turnOnOff(4,verde);
    }else if( strcmp(receivePayload,"rojo")==0 ){
      rojo =  turnOnOff(3,rojo);
    }else if( strcmp(receivePayload,"amarillo")==0 ){
      amarillo =  turnOnOff(2,amarillo);
    }
    *****/
    /*
    for(int i=0;i<len;i++){
      sprintf(temp2,"%c",receivePayload[i]);
      printf(temp2);
    }
    radio.stopListening();
    radio.write(receivePayload,len);
    receivePayload[len]=0;
    Serial.println("Enviando Informacion de vuelta");
    printf("size=%i payload=%s pipe=%i \n\r",len,receivePayload,pipe);*/
    delay(1000);
    Serial.println("Reanudando escucha");
    radio.startListening();
    
    
  } //end while
  delay(1000);
}
/*****
int turnOnOff(int pin,int estado){
  if(estado==LOW ){
    estado= HIGH;
  }else{
    estado= LOW;
  }
  digitalWrite(pin,estado);
  return estado;
  
} ***/
/*
void loop2(void){
  maxLongitud  = strlen(textLargo);
   
  
  uint8_t Data1,Data2,Data3,Data4 = 0;
  
  char temp[5];
  char temp2[1];
  bool timeout=0;
  
  // Get the last two Bytes as node-id
  uint16_t nodeID = pipes[0] & 0xff;

  char outBuffer[32]=""; // Clear the outBuffer before every loop
  unsigned long send_time, rtt = 0;

  // Get readings from sensors, change codes below to read sensors
  Data1 = counter++;
  Data2 = digitalRead(inPin); //cambiar
  if(Data2 == HIGH){
	if(indiceActual+1>=maxLongitud){
       indiceActual = 0;
    }
	Data3 = textLargo[indiceActual];
	indiceActual++;
  }else{
	Data3 =0;  
  }
  if ( counter > 999 ){
    counter = 0;
  } 

  // Append the hex nodeID to the beginning of the payload
  sprintf(outBuffer,"%2X",nodeID);
  strcat(outBuffer,",");

  // Convert int to strings and append with zeros if number smaller than 3 digits
  // 000 to 999

  sprintf(temp,"%03d",Data1);
  strcat(outBuffer,temp);

  strcat(outBuffer,",");

  sprintf(temp,"%04d",Data2);
  strcat(outBuffer,temp);

  strcat(outBuffer,"|");
  sprintf(temp2,"%c",Data3);
  strcat(outBuffer,temp2);
  printf("outBuffer: %s len: %d\n\r",outBuffer, strlen(outBuffer));

  send_time = millis();

  // Stop listening and write to radio
  radio.stopListening();

  // Send to hub
  if ( radio.write( outBuffer, strlen(outBuffer)) ) {
    printf("Enviado Correctamente\n\r");
  }
  else{
    printf("FAllo al enviar\n\r");
  }

  radio.startListening();
  delay(20);

  while ( radio.available() && !timeout ){
    uint8_t len = radio.getDynamicPayloadSize();
    radio.read( receivePayload, len);
    receivePayload[len] = 0;
    printf("inBuffer:  %s\n\r",receivePayload); 
    // Compare receive payload with outBuffer
    if ( !strcmp(outBuffer, receivePayload) ){
      rtt = millis() - send_time;
      printf("inBuffer --> rtt: %i \n\r",rtt); 
    } 
    // Check for timeout and exit the while loop
    if ( millis() - send_time > 500 ) {
      Serial.println("Timeout!!!");
      timeout = 1;
    } 
    delay(10);
  } // End while 
  delay(250);
} //end void


*/


