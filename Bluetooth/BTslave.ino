//BTslave.ino: Slave device for Bluetooth UART connection between 2 MCUs.
//Author: D. Dubins
//Date: 07-Jun-25
//Wiring: MCU slave - HC-06/BT-06:
//+5V - Vcc
//GND - GND
//TXD - Pin 2
//Pin 3 - 1K - RXD - 2K - GND 

#define relayPin 13   // Digital pin for relay control (heater).
#define RELAY_ON '1'  // char to turn relay on
#define RELAY_OFF '2' // char to turn relay off

// BT-06 Connections
#define RXD 3           // Digital pin for BT-06 TX (pin 2). (RX MCU - TX BT-06)
#define TXD 2           // Digital pin for BT-06 RX (pin 3). (TX MCU - RX BT-06)

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  // RX, TX

void setup() {
  pinMode(relayPin, OUTPUT);   // set relayPin to OUTPUT mode
  Serial.begin(9600);      // start the Serial Monitor
  BTSerial.begin(9600);    // start Serial Bluetooth
  printMenu();             // print the menu over bluetooth
  Serial_clear(BTSerial);  // clear the serial buffer
}

void loop() {
  if (BTSerial.available()) {
    char choice = BTSerial.read();
    respondTo(choice);
  }
}

void respondTo(char c) {  // respond to character sent from bluetooth
  switch (c) {
    case RELAY_ON:  // turn relay on
      digitalWrite(relayPin, HIGH);
      Serial.println("Turned relay ON.");
      BTSerial.print("1"); // send success bit
      break;
    case RELAY_OFF:  // turn LED off
      digitalWrite(relayPin, LOW);
      Serial.println("Turned relay OFF.");
      BTSerial.print("1"); // send success bit
      break;
    default:
      Serial.println("ERROR command not recognized.");
      BTSerial.print("0"); // send fail bit
  }
  // now print menu:
  printMenu();             // print the menu over bluetooth
  Serial_clear(BTSerial);  // clear the serial buffer in case it is clogged with stuff
}

void Serial_clear(SoftwareSerial &serialport) {  // used to clear the serial buffers from junk
  //serialport is passed by value (prefix &) so the function operates on the actual serial port, and not a copy of it.
  serialport.listen();
  while (serialport.available()) {  // while data are available in the buffer
    byte i = serialport.read();     // read the data and store to i
  }
}

void printMenu(){
  Serial.println("1: turn relay ON");
  Serial.println("2: turn relay OFF");
}
