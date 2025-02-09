/* I2Cmaster.ino
Designed to send and receive data with I2slave.ino,
For Arduino Uno devices compatible with Wire.h (e.g. Uno, Mega).
Author: D. Dubins
Date: 09-Feb-25
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
//Note you can message multiple slaves with this sketch, that should have unique bit addresses.
#define I2C_ADDR1 0x08 // use bit address 0x08 for the slave. 
#define BYTELEN 5     // number of bytes (or characters) to ask for from the slave

void setup(){
  Wire.begin();       // Initialize Uno as a master device. Note there is no bit address here, because the master doesn't have one.
  Serial.begin(9600); // Start the Serial Monitor
  Serial.println("I2C Master ready.");
}

void loop(){
  byte snd=0; // byte that we will send to slave. Feel free to change this as needed (e.g. any number between 0-255)
  Wire.beginTransmission(I2C_ADDR1); // Start a call to slave address I2C_ADDR
  Wire.write(snd);  // send a character 0 to the slave
  Wire.endTransmission(); // end transmission to slave
  Serial.print("Sent to slave: ");
  Serial.println(snd);

  // Get data back from the slave:
  Wire.requestFrom(I2C_ADDR1,BYTELEN); // ask for BITLEN bytes from slave
  String response=""; // get response string ready
  while (Wire.available()){
    char c=Wire.read(); // read character from slave
    response += c; // add char to String
  }
  Serial.print("Received from slave: ");
  Serial.println(response);
}
