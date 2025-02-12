// I2C_Scanner.ino
// Written by David Dubins
// Adapted from: Nick Gammon's sketch I2C_scanner.ino, 20th April 2011
// List of common addresses: https://learn.adafruit.com/i2c-addresses/the-list

#include <Wire.h> // include Wire.h for I2C communications

void setup(){
  Serial.begin(9600); // Start the Serial Monitor
  Serial.println("Scanning for I2C devices.");
  byte count = 0;
  Wire.begin(); // initialize I2C as Master
  for(byte i=8; i<120;i++){ // Addresses 0-7 and >0x77 are reserved.
    Wire.beginTransmission(i);
    if (Wire.endTransmission()==0){
      Serial.print("Found address: ");
      Serial.print(i,DEC);
      Serial.print("(0x");
      Serial.print(i,HEX);
      Serial.println(")");
      count++;
      delay(1);  // maybe unneeded?
      } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  Serial.println("Press RST to scan again.");
}  // end of setup

void loop(){
}
