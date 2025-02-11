/* I2Cmaster1W.ino - minimal sketch
Designed to send data with I2Cslave1W.ino,
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
Wiring:
Uno1 (master) -- Uno2 (slave):
SDA - SDA
SCL - SCL
GND - GND
-Wire 10K pull-up resistors on SDA and SCL pins of master
*/

#include <Wire.h> // Include Arduino Wire.h library
#define I2C_ADDR1 0x08 // use bit address 0x08 for the slave.

void setup(){
  Wire.begin();  // Initialize Uno as a master device
}                //(no bit addr)

void loop(){
  byte snd=5;    // byte that we will send to slave1.
  // Tell slave1 at I2C_ADDR1 we are sending data:
  Wire.beginTransmission(I2C_ADDR1); 
  Wire.write(snd);  // send a character 0 to the slave1
  Wire.endTransmission(); // end transmission to slave
  delay(50);  // short delay
}
