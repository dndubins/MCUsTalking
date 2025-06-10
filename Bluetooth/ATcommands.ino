//ATcommands: Send AT Commands to Bluetooth Device
//Note: For HC-06, set Serial Monitor to "Both NL & CR".
//For BT-06, set Serial Monitor to "No Line Ending".
//Note: For HC-05, hold down SW while powering up to enter AT mode.
//      LED will flash slowly when in AT mode.
//
//Connections: 
//------------
//MCU to HC-05/HC-06:
//EN - NC (not connected)
//Vcc - +5V
//GND - GND
//Pin 3 - TXD
//Pin 2 - 1K - RXD - 2K - GND (voltage divider)
//State - NC

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(2, 3); // RX | TX
 
void setup(){
  Serial.begin(9600); //start the Serial Monitor
  BTSerial.begin(9600); //start Bluetooth Serial
  Serial.println(F("Serial monitor ready."));
}
 
void loop(){
  if(BTSerial.available()){
    Serial.write(BTSerial.read());
  }
  if(Serial.available()){
    BTSerial.write(Serial.read());
  }
}
