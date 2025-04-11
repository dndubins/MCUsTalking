//SPImaster_struct.ino: SPI Master, 2 MCUs Talking
//Author: D. Dubins
//Date: 11-Apr-25
//Send a byte and receive a struct over SPI
//Wiring:
//Uno Master - Uno Slave:
//10 - 10 (CS-CS)
//11 – 11 (MOSI-MOSI)
//12 – 12 (MISO-MISO)
//13 - 13 (SCK-SCK)
//GND - GND

#include <SPI.h> // Load SPI library
byte CS = 10;    // Use as CS pin for Mega
byte requestByte = 0xFF; // Byte to send to request struct
int byteIndex = 0;  // Index for tracking which byte to receive

struct myStruct {
  long L;
  int I;
  byte B;
  char C;
  bool b;
  float F;
};

const byte structSize = sizeof(myStruct);

union myUnion {  // union to send struct as char array
  char myCharArr[sizeof(myStruct)];
  myStruct myData;
} RXdata;

void setup() {
  Serial.begin(9600);     // start the Serial Monitor
  //SPI settings (adjust as needed)
  //SPI.beginTransaction(SPISettings(4000000, MSBFIRST, SPI_MODE0)); // 4 MHz, MSB first, SPI mode 0
  SPI.begin();            // Start SPI as master
  pinMode(CS, OUTPUT);    // Chip Select pin
  digitalWrite(CS, HIGH); // Set CS high (deselect slave)
}

void loop() {
  digitalWrite(CS, LOW); // Select Uno
  SPI.transfer(requestByte); // Send request byte to slave. This resets byteIndex and prevents offsetting bits.
  delay(1);  // Wait for slave to process request

  // Receive struct byte-by-byte
  for (byteIndex = 0; byteIndex < structSize; byteIndex++) {
    RXdata.myCharArr[byteIndex] = SPI.transfer(0x00); // Receive byte
    delay(1);
  }

  Serial.println("Master received struct:"); // print received data from struct
  Serial.print("Long L: ");
  Serial.println(RXdata.myData.L);
  Serial.print("Int I: ");
  Serial.println(RXdata.myData.I);
  Serial.print("Byte B: ");
  Serial.println(RXdata.myData.B);
  Serial.print("Char C: ");
  Serial.println(RXdata.myData.C);
  Serial.print("Bool b: ");
  Serial.println(RXdata.myData.b);
  Serial.print("Float F: ");
  Serial.println(RXdata.myData.F); 
  digitalWrite(CS, HIGH); // Deselect slave
  delay(1000); // Wait before sending another request
}
