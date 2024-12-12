/* SoftwareSerial example, MCU1 is controlling MCU2 and MCU3. This sketch is for MCU2 and MCU3 - the slaves.
 * Author: D. Dubins
 * Date: 10-Dec-24

 * Description: This project illustrates how to get one MCU to send commands to another two MCUs through SoftwareSerial connections.
 * This sketch is for the first MCU (MCU1). The slave MCUs (MCU2 and MCU3) will be powered parasitically through the Vin and GND pins of MCU1.
 * This is hookup is optional though, they can be independently powered.
 * 
 * MCU1 reads an integer from the Serial Monitor, and sends a command to MCU2 and MCU3 through the SoftwareSerial connections.
 * MCU2 and MCU3 receive the command, execute a function, then reports back to MCU1 for error checking.

 * Connections: (MCU1 - MCU2)
 * Vin - Vin (or power independently)
 * GND - GND
 * Pin 2 - Pin 3 (RX - TX)
 * Pin 3 - Pin 2 (TX - RX)
 *
 * Connections: (MCU1 - MCU3)
 * Vin - Vin (or power independently)
 * GND - GND
 * Pin 4 - Pin 3 (RX - TX)
 * Pin 5 - Pin 2 (TX - RX)
 * Note: If using multiple software serial ports, only one can receive data at a time.
 * Also see: https://docs.arduino.cc/learn/built-in-libraries/software-serial/
*/

#include <SoftwareSerial.h>       // include the software serial library
SoftwareSerial MCU1Serial(2, 3);  // define software serial connection to MCU1 (RX:2, TX:3)

#define LEDPIN 13

void setup() {
  MCU1Serial.begin(57600);   // start software serial connection (max speed for SoftwareSerial is 57600 for Uno)
  Serial_clear(MCU1Serial);  // clear MCU1Serial buffers
  pinMode(LEDPIN, OUTPUT);   // set LEDPIN to OUTPUT mode
}

void loop() {
  if (MCU1Serial.available()) {     // if there's something received from MC1Serial
    int r = MCU1Serial.parseInt();  // store it to r
    MCU1Serial.print(r);            // send r to MCU1 to confirm receipt
    flashLED(r);                    // flash onboard LED r times
    Serial_clear(MCU1Serial);       // clear MCU1Serial buffers (clears commands collected during execution)
  }
}

void flashLED(int n) {  // flash the LED n times
  for (int i = 0; i < n; i++) {
    digitalWrite(LEDPIN, HIGH);  // turn on LED
    delay(200);                  // wait a bit
    digitalWrite(LEDPIN, LOW);   // turn off LED
    delay(200);                  // wait a bit
  }
}

void Serial_clear(SoftwareSerial &serialport) {  // used to clear the serial buffers from junk. 
  //serialport is passed by value (prefix &) so the function operates on the actual serial port, and not a copy of it.
  serialport.listen();
  while (serialport.available()) {  // while data are available in the buffer
    byte i = serialport.read();     // read the data and store to i
  }
}
