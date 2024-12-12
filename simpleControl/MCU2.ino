/* SoftwareSerial example, MCU1 is controlling MCU2 and MCU3. This sketch is for MCU2 and MCU3 - the slaves.
   Author: D. Dubins
   Date: 12-Dec-24

   Description: This project illustrates how to get one MCU to send commands to another two MCUs through SoftwareSerial connections.
   This sketch is for the slave MCUs (MCU2 and MCU3). The slave MCUs will be powered parasitically through the Vin and GND pins of MCU1.
   This is hookup is optional though, they can be independently powered - as long as they share a ground with the parent MCU.

   MCU1 reads a char variable c from the Serial Monitor, then sends a code to MCU2 or MCU3, through the SoftwareSerial connections.
   The other MCU sends the received code back to MCU1 for error checking, and run the routine.

   There are examples of two "flavours" of functions here:
      *flashLEDint() can be interrupted while it's doing something, then do the new thing as soon as possible (flashLEDint)
      *flashLED() will run until it's done, and clear any commands from the serial connection that were collected while it was doing it.
      
   Connections: (MCU1 - MCU2)
   Vin - Vin (or power independently)
   GND - GND
   Pin 2 - Pin 3 (RX - TX)
   Pin 3 - Pin 2 (TX - RX)

   Connections: (MCU1 - MCU3)
   Vin - Vin (or power independently)
   GND - GND
   Pin 4 - Pin 3 (RX - TX)
   Pin 5 - Pin 2 (TX - RX)
   Note: If using multiple software serial ports, only one can receive data at a time.
   Also see: https://docs.arduino.cc/learn/built-in-libraries/software-serial/
*/

#include <SoftwareSerial.h>       // include the software serial library
SoftwareSerial MCU1Serial(2, 3);  // define software serial connection to MCU1 (RX:2, TX:3)

#define LEDPIN 13

void setup() {
  MCU1Serial.begin(57600);   // start software serial connection (max speed for SoftwareSerial is 57600 for Uno)
  Serial_clear(MCU1Serial);  // clear MCU1Serial buffer
  pinMode(LEDPIN, OUTPUT);   // set LEDPIN to OUTPUT mode
}

void loop() {
  if (MCU1Serial.available()) {     // if there's something received from MC1Serial
    int r = MCU1Serial.parseInt();  // store it to r
    MCU1Serial.print(r);            // send r to MCU1 to confirm receipt
    switch (r) {
      case 901:               // make your cases specific multi-digit numbers (fewer false hits)
        flashLEDint(30, 200); // this function is interruptable with incoming data
        break;
      case 902:
        flashLEDint(40, 100); // this function is interruptable with incoming data
        break;
      case 903:
        flashLED(50, 50); // example of non-interruptable function (will run to completion).
        Serial_clear(MCU1Serial); // throw out any data collected while function ran
        break;
      default:
        Serial_clear(MCU1Serial); // clear MCU1Serial buffer
        // do nothing if command does not exist
        break;
    }
  }
}

void flashLED(int n, int d) {  // flash the LED n times with delay (non-interruptable)
  for (int i = 0; i < n; i++) {
    digitalWrite(LEDPIN, HIGH);  // turn on LED
    delay(d);                  // wait a bit
    digitalWrite(LEDPIN, LOW);   // turn off LED
    delay(d);                 // wait a bit
  }
}

void flashLEDint(int n, int d) {  // flash the LED n times with delay d (interruptable)
  int i = 0;
  while (i < n && !MCU1Serial.available()) { // how you can make your functions interrupable
    digitalWrite(LEDPIN, HIGH);  // turn on LED
    safeWait(d);                  // wait a bit
    digitalWrite(LEDPIN, LOW);   // turn off LED
    safeWait(d);                 // wait a bit
    i++;                      // increment i
  }
}

void safeWait(int w) { // interruptable delay
  unsigned long timer = millis(); //start the timer
  while (millis() - timer < w && !MCU1Serial.available()); // wait until timer is done
}

void Serial_clear(SoftwareSerial &serialport) {  // used to clear the serial buffers from junk
  //serialport is passed by value (prefix &) so the function operates on the actual serial port, and not a copy of it.
  serialport.listen();
  while (serialport.available()) {  // while data are available in the buffer
    byte i = serialport.read();     // read the data and store to i
  }
}
