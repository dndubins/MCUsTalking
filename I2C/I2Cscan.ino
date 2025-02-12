// I2Cscan.ino
// Scan for slave I2C devices as Master
// Adapted by David Dubins 
// Date: 12-Feb-25
// Original sketch by Nick Gammon, I2C_scanner.ino, 20th April 2011
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
      delay(10);
      } 
  }
  Serial.println ("Scan finished.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  Serial.println("Press RST to scan again.");
}

void loop(){
}
