//BTmaster.ino: Bluetooth Master, 2 MCUs Talking
//Author: D. Dubins
//Date: 07-Jun-25
//Wiring: MCU master - HC-05:
//+5V - Vcc
//GND - GND
//TXD - Pin 2
//Pin 3 - 1K - RXD - 2K - GND 

#define LEDpin 13     // onboard LED
#define RELAY_ON '1'  // char to turn relay on
#define RELAY_OFF '2' // char to turn relay off

// HC-05 Connections
#define RXD 3  // (TX MCU - HC-05 RXD)
#define TXD 2  // (RX MCU - HC-05 TXD)

#include <SoftwareSerial.h>
SoftwareSerial BTSerial(TXD, RXD);  // RX, TX

void setup() {
  pinMode(LEDpin, OUTPUT);
  Serial.begin(9600);      // start the Serial Monitor
  BTSerial.begin(9600);    // start Serial Bluetooth
  Serial_clear(BTSerial);  // clear the serial buffer
}

void loop() {
  sendBT(RELAY_ON);  // turn relay on
  delay(1000);       // wait a bit
  sendBT(RELAY_OFF); // turn relay off
  delay(1000);       // wait a bit
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

// To clear serial buffer:
void Serial_clear(SoftwareSerial &serialport) {
  serialport.listen();
  while (serialport.available()){
    byte i = serialport.read();
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
