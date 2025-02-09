/* I2Cslave.ino
Designed to send and receive data with I2Cmaster.ino,
For Arduino Uno devices compatible with Wire.h (e.g. Uno, Mega).
Author: D. Dubins
Date: 09-Feb-25
Modified from: https://www.youtube.com/watch?v=PnG4fO5_vU4&t=326s&ab_channel=DroneBotWorkshop
DroneBot Workshop 2019

Wiring:
Uno1 (master) -- Uno2 (slave):
SDA - SDA
SCL - SCL
GND - GND
-Wire 10K pull-up resistors on SDA and SCL pins of master
*/

#include <Wire.h> // Include Arduino Wire.h library
#define I2C_ADDR 0x08  // use a unique bit address 0x08 for the slave
#define BYTELEN 5      // number of bytes (or characters) to ask for from the slave
byte rcv = 0;          // to hold received data from master
String msg = "Hello";  // message to send

void setup(){
  Serial.begin(9600);   // Start the Serial Monitor
   Wire.begin(I2C_ADDR); // initialize I2C using slave address I2C_ADDR, in slave mode.
  Wire.onRequest(requestEvent); // attach interrupt function requestEvent, to run when data is requested from master.
  Wire.onReceive(receiveEvent); // attach interrupt function receiveEvent, to run when data is received from master.
  Serial.print("I2C slave ready at address: ");
  Serial.println(I2C_ADDR,HEX); // send slave ready message.
}

void loop(){
  delay(50); // short time delay recommended
}

void requestEvent(){ // function that runs when master asks for information
  byte response[BYTELEN];
  for (byte i=0; i<BYTELEN; i++){
    response[i]=(byte)msg.charAt(i); // I think you can safely replace this with msg[i]. charAT() is a function to index strings like arrays.
  }
  Wire.write(response,sizeof(response)); // send msg to master
  Serial.println("Sent to master: "); // report event to Serial Monitor.
  Serial.println(msg);  
}

void receiveEvent(){ // function that runs when master sends information
  rcv=0; // rcv defined in global space so you can use the value inside the loop() function.
  while (Wire.available()>0){ // this can be expanded to receive a bigger message than 1 byte.
    rcv=Wire.read();
  }
  Serial.print("Received from master: ");
  Serial.println(rcv);
}

