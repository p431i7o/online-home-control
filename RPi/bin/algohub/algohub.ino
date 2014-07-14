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
const uint64_t pipes[2] = { 
  0xF0F0F0F0E1LL, 0x7365727631LL };

char receivePayload[32];
uint8_t counter=0;
int inPin = 6;   // button connected to digital pin 6
int indiceActual =0;
int maxLongitud =0;
char textLargo[] = "Un texto muy largo, muy muy largo... que nunca termina porque es largo";
void setup(void){
  // Conor Switch
  pinMode(inPin, INPUT);

  Serial.begin(57600); 
  printf_begin();
  printf("Sending nodeID & 1 sensor data\n\r"); 
  radio.begin(); 
  // Enable this seems to work better
  radio.enableDynamicPayloads(); 
  radio.setDataRate(RF24_1MBPS);
  radio.setPALevel(RF24_PA_MAX);
  radio.setChannel(76);
  radio.setRetries(15,15);

  radio.openWritingPipe(pipes[0]);
  radio.openReadingPipe(1,pipes[1]);

  // Dump the configuration of the rf unit for debugging
  radio.printDetails();
  delay(1000);
}

void loop(void){
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
  Data2 = digitalRead(inPin);
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





