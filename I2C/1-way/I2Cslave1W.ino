/* I2Cslave1W.ino - minimal sketch
Designed to receive data with I2Cmaster1W.ino,
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
byte rcv = 0;      // to hold data received from master

void setup(){
  Serial.begin(9600);   // start the Serial Monitor
  Wire.begin(I2C_ADDR); // initialize I2C as slave at
                        // address I2C_ADDR
// attach interrupt function receiveEvent, 
// to run when master sends data:
  Wire.onReceive(receiveEvent); 
}

void loop(){
  delay(50); // short time delay recommended
}

// function that runs when master sends information:
void receiveEvent(){ 
// this can be expanded to receive a message 
// larger than 1 byte:
  while (Wire.available()>0){ 
    rcv=Wire.read();
  }
  Serial.print("Received: ");
  Serial.println(rcv); // Other commands can go here
}
