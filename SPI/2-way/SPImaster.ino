//SPImaster.ino: SPI Master, 2 MCUs Talking
//Date: 10-Apr-25
//Send and receive 1 byte over SPI
//Wiring:
//Uno Master - Uno Slave:
//10 - 10 (CS-CS)
//11 – 11 (MOSI-MOSI)
//12 – 12 (MISO-MISO)
//13 - 13 (SCK-SCK)
//GND - GND

#include <SPI.h> // load SPI library
byte CS = 10;    // Use as CS pin for Uno
byte snd = 0x01; // byte to send

void setup() {
  Serial.begin(9600);     // Start the Serial Monitor
  SPI.begin();           // Start SPI as master
  pinMode(CS, OUTPUT);   // Chip Select for Uno
  digitalWrite(CS, HIGH); // Set pin high
}

void loop() {
  digitalWrite(CS, LOW); // Select Uno
  byte rcv = SPI.transfer(snd); // Send byte snd, receive byte rcv
  digitalWrite(CS, HIGH); // Deselect Uno
  Serial.print("Master received: ");
  Serial.println(rcv, HEX);
  delay(1000);
}
