/* I2Cmaster.ino
Designed to send and receive struct data with I2slave_struct.ino,
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
//Note you can message multiple slaves with this sketch. They should have unique bit addresses.
#define I2C_ADDR1 0x08 // use bit address 0x08 for the slave. 
bool rcv=false;   // receive flag for new data

// Example of a structure to be sent over I2C (13 bytes total)
struct myStruct { // example structure to send over I2C.
  float F; // float is 4 bytes
  long L; // long is 4 bytes
  int I;  // int is 2 bytes
  byte B;  // byte is 1 byte
  char C;  // char is 1 byte
  bool b;   // bool is 1 byte
};  

// Declare union to help represent struct as char array
union myUnion { //declare union in global space
  char myCharArr[sizeof(myStruct)]; // char array to be shared with sData
  myStruct myData; //occupies same memory as myCharArr
}TXdata,RXdata; //create two union instances called TXdata (to transmit) and RXdata (to receive)

void setup(){
  Wire.begin();       // Initialize Uno as a master device. Note there is no bit address here, because the master doesn't have one.
  Serial.begin(9600); // Start the Serial Monitor
  Serial.println("I2C Master ready.");
  // initialize TXdata.myData with values
  TXdata.myData.F=0.05; // significant data
  TXdata.myData.L=123456789;
  TXdata.myData.I=42;
  TXdata.myData.B=123;
  TXdata.myData.C='x';
  TXdata.myData.b=1;
}

void loop(){
  // First, we will send data to the slave:
  Wire.beginTransmission(I2C_ADDR1);  // Start I2C transmission to slave
  Wire.write(TXdata.myCharArr);  // Send the data as the char array myCharArr
  Wire.endTransmission();  // End the transmission
  Serial.println("Data sent to slave.");
  delay(500); // wait between receiving and sending

  // Next, we will request data from the slave:
  Wire.requestFrom(I2C_ADDR1,sizeof(myStruct));  // Request of size of struct (10 bytes here)
  int i=0;
  while(Wire.available()){    
    RXdata.myCharArr[i++] = Wire.read();  // Read the next byte from the slave
  }
  if(rcv){ // if new data received:
    // Print the received struct
    Serial.println(F("Received from slave: "));
    Serial.println(RXdata.myData.F);
    Serial.println(RXdata.myData.L);
    Serial.println(RXdata.myData.I);
    Serial.println(RXdata.myData.B);
    Serial.println(RXdata.myData.C);
    Serial.println(RXdata.myData.b);   
  }else{
    Serial.println("Data communications error.");
  }
}
