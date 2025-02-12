// I2Cscan.ino
// Scan for slave I2C devices as Master
// Adapted by David Dubins 
// Date: 12-Feb-25
// Original sketch by Nick Gammon, I2C_scanner.ino, 20th April 2011
// Previously available at: https://playground.arduino.cc/Main/I2cScanner
// List of common addresses: https://learn.adafruit.com/i2c-addresses/the-list

#include <Wire.h> // include Wire.h for I2C communications

void setup(){
  Serial.begin(9600); // Start the Serial Monitor
  Serial.println(F("Scanning for I2C devices."));
  byte count=0;
  Wire.begin(); // initialize I2C as Master
  for(byte i=8; i<120;i++){ // Addresses 0-7 and >0x77 are reserved.
    Wire.beginTransmission(i);
    if (Wire.endTransmission()==0){
      Serial.print(F("Device "));
      Serial.print(++count);
      Serial.print(F(" address: "));
      Serial.print(i,DEC);
      Serial.print(F(" (0x"));
      Serial.print(i,HEX);
      Serial.println(F(")"));
      delay(10);
      } 
  }
  if(count==0)Serial.println(F("No I2C devices found."));
  Serial.println (F("Scan finished. Press RST to scan again."));
}

void loop(){
}
