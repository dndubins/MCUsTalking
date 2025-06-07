//BTmaster.ino: Bluetooth Master, 2 MCUs Talking
//Author: D. Dubins
//Date: 07-Jun-25
//Wiring: MCU slave - HC-05
//+5V - Vcc
//GND - GND
//TXD - Pin 10
//RXD - Pin 11 

#define LEDpin 13   // Digital pin for relay control (heater).
#define RELAY_ON '1'  // char to turn relay on
#define RELAY_OFF '2' // char to turn relay off

// BT-06 Connections
#define RXD 2            // Digital pin for BT-06 TX (pin 2). (RX MCU - TX BT-06)
#define TXD 3            // Digital pin for BT-06 RX (pin 3). (TX MCU - RX BT-06)

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  // RX, TX

void setup() {
  pinMode(LEDpin, OUTPUT);   // set relayPin to OUTPUT mode
  Serial.begin(9600);      // start the Serial Monitor
  BTSerial.begin(9600);    // start Serial Bluetooth
  Serial_clear(BTSerial);  // clear the serial buffer
}

void loop() {
  sendBT(RELAY_ON); // turn relay on
  delay(1000);
  sendBT(RELAY_OFF); // turn relay off
  delay(1000); // wait a bit
}

bool sendBT(char i){
  BTSerial.print(i); // send command to BT module
  unsigned long timer=millis();
  bool rcv=false; // received data flag
  while(millis()-timer<1000){ // timeout for response
    if(BTSerial.available()){ // check for response
      rcv=true; // set flag
      delay(100); // wait a bit
      char c = BTSerial.read();
      if(c=='1'){
        Serial.println("Sent: " + (String)i);
        break; // leave loop
      }
      if(c=='0'){
        flashLED(3);  // flash onboard LED
        Serial.println(F("Communications error."));
        break; // leave loop
      }
    }
  }
  if(!rcv){
    flashLED(5);  // flash onboard LED
    Serial.println(F("Communications timeout."));
  }
  Serial_clear(BTSerial); // clear the buffer
}

void Serial_clear(SoftwareSerial &serialport) {  // used to clear the serial buffers from junk
  //serialport is passed by value (prefix &) so the function operates on the actual serial port, and not a copy of it.
  serialport.listen();
  while (serialport.available()) {  // while data are available in the buffer
    byte i = serialport.read();     // read the data and store to i
  }
}

void flashLED(byte i){ // communications error signal
  for(int i=0;i<3;i++){
    digitalWrite(LEDpin,HIGH); // turn LED on
    delay(100);
    digitalWrite(LEDpin,LOW); // turn LED off
    delay(100);
  }
}
