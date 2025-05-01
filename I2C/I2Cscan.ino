// I2Cscan.ino
// Scan for slave I2C devices as Master
// Adapted by David Dubins 
// Date: 13-Feb-25
// Original sketch by Nick Gammon, I2C_scanner.ino, 20th April 2011
// Previously available at: https://playground.arduino.cc/Main/I2cScanner
// and Tomas Inouk at https://gist.github.com/tomasinouk/b257c68fde96f5f03f87
// List of common addresses: https://learn.adafruit.com/i2c-addresses/the-list
// Error checking: https://docs.arduino.cc/language-reference/en/functions/communication/wire/endTransmission/

#include <Wire.h> // include Wire.h for I2C communications

void setup(){
  Serial.begin(9600); // Start the Serial Monitor
  Serial.println(F("Scanning for I2C devices."));
  byte n=0; // counter for devices
  Wire.begin(); // initialize I2C as Master
  for(byte i=8; i<120;i++){ // Note: Addresses 0x00-0x07 and >0x77 are reserved.
    Wire.beginTransmission(i); // start I2C transmission at address i
    byte ret=Wire.endTransmission();
    if (ret==0){
      Serial.print(F("Device "));
      Serial.print(++n);
      Serial.print(F(" address: "));
      printAddr(i);
    }else if(ret>0 && ret<5){ 
      //1: data too long to fit in transmit buffer
      //2: received NACK on transmit of address
      //3: received NACK on transmit of data
      //4: other error
      //5: timeout (no device)
      Serial.println(F("Error at address: "));
      printAddr(i);
    }
  }
  if(n==0)Serial.println(F("No devices found."));
  Serial.println (F("Scan finished. Press RST to scan again."));
}

void printAddr(byte addr){
  Serial.print(addr,DEC);  // print decimal address
  Serial.print(F(" (0x")); // print hexidecimal prefix
  if(addr<10)Serial.print(F("0")); // print leading zero
  Serial.print(addr,HEX); // print hexidecimal address
  Serial.println(F(")"));
}

void loop(){
}
