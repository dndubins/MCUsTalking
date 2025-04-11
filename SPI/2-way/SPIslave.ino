//SPIslave.ino: SPI Slave, 2 MCUs Talking
//Date: 10-Apr-25
//Send and receive 1 byte over SPI
//Wiring:
//Uno Master – Uno Slave:
//10 - 10 (CS-CS)
//11 – 11 (MOSI-MOSI)
//12 – 12 (MISO-MISO)
//13 - 13 (SCK-SCK)
//GND - GND

#include <SPI.h>

volatile byte rcv = 0;
volatile byte snd = 0x02; // response byte
volatile boolean dataReceived = false;

void setup() {
  Serial.begin(9600); //start the Serial Monitor
  pinMode(MISO, OUTPUT);   //Set MISO as output, other pins INPUT
  pinMode(MOSI, INPUT);
  pinMode(SCK, INPUT);
  pinMode(SS, INPUT);      //Must be input to remain a slave
  SPCR |= _BV(SPE);        //Enable SPI in slave mode
  SPCR |= _BV(SPIE);       //Enable SPI interrupt
  sei();                   //Enable global interrupts
}

ISR(SPI_STC_vect) {
  rcv = SPDR;         //Read byte from master
  SPDR = snd;         //Load next byte to send
  dataReceived = true;
}

void loop() {
  if (dataReceived) {
    Serial.print("Slave received: ");
    Serial.println(rcv, HEX);
    dataReceived = false;
  }
}
