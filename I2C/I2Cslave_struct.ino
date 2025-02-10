/* I2Cslave_struct.ino
Designed to send and receive struct data with I2master_struct.ino,
For Arduino Uno devices compatible with Wire.h (e.g. Uno, Mega).
Author: D. Dubins
Date: 10-Feb-25
For Arduino Uno devices compatible with Wire.h (e.g. Uno, Mega)
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

// Example of a structure to be sent over I2C (13 bytes total)
struct myStruct { // example structure to send over I2C. This was for a servo.
  float F; // float is 4 bytes
  long L; // long is 4 bytes
  int I;  // int is 2 bytes
  byte B;  // byte is 1 byte
  char C;  // char is 1 byte
  bool b;   // bool is 1 byte
};

// Declare union to help represent myData as char array
union myUnion { //declare union in global space
  char myCharArr[sizeof(myStruct)]; // char array to be shared with sData
  myStruct myData; //occupies same memory as myCharArr
}RXdata; //create a union instance called RXdata (to receive)

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

void requestEvent(){ // function that runs when master asks for information.
  Wire.write(RXdata.myCharArr,sizeof(myStruct)); // send RXdata to master
  Serial.println("Data sent to master."); // report event to Serial Monitor.
}

void receiveEvent(){ // function that runs when master sends information
  int i=0;
  while (Wire.available()>0){ // this can be expanded to receive a bigger message than 1 byte.
    RXdata.myCharArr[i++]=Wire.read();
  }
}
