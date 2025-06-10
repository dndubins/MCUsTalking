//BTslave.ino: Slave device for Bluetooth UART connection between 2 MCUs.
//Author: D. Dubins
//Date: 07-Jun-25
//Wiring: MCU slave - HC-06/BT-06:
//+5V - Vcc
//GND - GND
//TXD - Pin 2
//Pin 3 - 1K - RXD - 2K - GND 

#define relayPin 13   // pin for relay control
#define RELAY_ON '1'  // char to turn relay on
#define RELAY_OFF '2' // char to turn relay off
#define TIMEOUT 60000 // timeout for not receiving a signal (1 min)
unsigned long timer=millis(); // to keep track of time for TIMEOUT action

// HC-06/BT-06 Connections
#define RXD 3  // (TX MCU - HC-06 RXD)
#define TXD 2  // (RX MCU - HC-06 TXD)

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  // RX, TX

void setup() {
  pinMode(relayPin, OUTPUT);   // set relayPin to OUTPUT mode
  Serial.begin(9600);      // start the Serial Monitor
  BTSerial.begin(9600);    // start Serial Bluetooth
  Serial.println(F("Slave ready."));  // print message to Serial
  BTSerial.println(F("Slave ready."));  // print message to BTSerial
  Serial_clear(BTSerial);  // clear the serial buffer
}

void loop() {
  if (BTSerial.available()) {
    char choice = BTSerial.read();
    respondTo(choice);
  }
  if(millis()-timer>TIMEOUT){
    digitalWrite(relayPin, LOW);
    Serial.println(F("Timed out: Turned relay OFF."));
    timer=millis();  // reset the timer
  }
}

void respondTo(char c) {  // respond to character sent from bluetooth
  switch (c) {
    case RELAY_ON:  // turn relay on
      BTSerial.print(F("1")); // send success bit
      digitalWrite(relayPin, HIGH);
      Serial.println(F("Turned relay ON."));
      timer=millis(); // reset timer
      break;
    case RELAY_OFF:  // turn LED off
      BTSerial.print(F("1")); // send success bit
      digitalWrite(relayPin, LOW);
      Serial.println(F("Turned relay OFF."));
      timer=millis(); // reset timer
      break;
    default:
      BTSerial.print(F("0")); // send fail bit. Don't reset timer.
      Serial.println(F("ERROR: command not recognized."));
  }
  Serial_clear(BTSerial);  // clear the serial buffer in case it is clogged with stuff
}

void Serial_clear(SoftwareSerial &serialport) {  // used to clear the serial buffers from junk
  //serialport is passed by value (prefix &) so the function operates on the actual serial port, and not a copy of it.
  serialport.listen();
  while (serialport.available()) {  // while data are available in the buffer
    byte i = serialport.read();     // read the data and store to i
  }
}
