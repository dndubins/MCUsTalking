//SPIslave.ino: SPI Slave, 2 MCUs Talking
//Author: D. Dubins
//Date: 11-Apr-25
//receive a byte and send a struct over SPI
//Wiring:
//Uno Master – Uno Slave:
//10 - 10 (CS-CS)
//11 – 11 (MOSI-MOSI)
//12 – 12 (MISO-MISO)
//13 - 13 (SCK-SCK)
//GND - GND

#include <SPI.h>

volatile byte rcv = 0;
volatile int byteIndex = 0;
volatile boolean dataReceived = false;

struct myStruct {
  long L;
  int I;
  byte B;
  char C;
  bool b;
  float F;
};

const byte structSize = sizeof(myStruct);

union myUnion {
  char myCharArr[sizeof(myStruct)];
  myStruct myData;
} TXdata;

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  pinMode(MISO, OUTPUT); // Set MISO as output, other pins INPUT
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT); // Must be input to remain a slave

  SPCR |= _BV(SPE);  // Enable SPI in slave mode
  SPCR |= _BV(SPIE); // Enable SPI interrupt
  sei(); // Enable global interrupts

  // Initialize TXdata.myData with values
  TXdata.myData.L = 123456789;
  TXdata.myData.I = 42;
  TXdata.myData.B = 123;
  TXdata.myData.C = 'x';
  TXdata.myData.b = 1;
  TXdata.myData.F = 0.05;
}

ISR(SPI_STC_vect) {
  rcv = SPDR;  // Receive byte from master

  //If request byte received (0xFF), reset byteIndex and start sending data
  if (rcv == 0xFF) {
    byteIndex = 0;
    //Serial.println("z");
  }

  // Send the next byte of the struct, carefully controlling byte order
  SPDR = TXdata.myCharArr[byteIndex];
  byteIndex++;

  // Check if all bytes have been sent
  if (byteIndex >= structSize) {
    byteIndex = 0; // Reset for the next transfer
    dataReceived = true; // Indicate that the full struct has been sent
  }
}

void loop() {
  // Check if the slave has sent the data (this could be extended to handle other operations)
  if (dataReceived) {
    Serial.println("Slave has sent the full struct!");
    dataReceived = false;  // Reset the flag
  }
}
