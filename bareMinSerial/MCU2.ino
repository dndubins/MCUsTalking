/* SoftwareSerial example, MCU1 to MCU2. This sketch is for MCU2 - the slave, receiving commands from MCU1.
 * Author: D. Dubins
 * Date: 10-Dec-24

 * Description: This project illustrates how to get one MCU to send commands to another through a SoftwareSerial connection.
 * This sketch is for the second MCU (MCU2). The second MCU (MCU2) will be powered parasitically through the Vin and GND pins of MCU1.
 * This is hookup is optional though, they can be independently powered. GND should be connected between MCU1 and MCU2.
 * 
 * MCU1 reads an integer from the Serial Monitor, and sends a command to MCU2 through the SoftwareSerial connection.
 * MCU2 receives the command, executes a function, then reports back to MCU1 for error checking.

 * Connections: (MCU1 - MCU2)
 * Vin - Vin (or power independently)
 * GND - GND
 * Pin 2 - Pin 3 (RX - TX)
 * Pin 3 - Pin 2 (TX - RX)
*/

#include <SoftwareSerial.h>       // include the software serial library
SoftwareSerial MCU1Serial(2, 3);  // define software serial connection to MCU1 (RX:2, TX:3)

#define LEDPIN 13

void setup() {
  MCU1Serial.begin(57600);  // start software serial connection (max speed for SoftwareSerial is 57600 for Uno)
  pinMode(LEDPIN, OUTPUT);  // set LEDPIN to OUTPUT mode
}

void loop() {
  if (MCU1Serial.available()) {       // if there's something received by mySerial
    int rcv = MCU1Serial.parseInt();  // store it to rcv
    MCU1Serial.print(rcv);            // send rcv to MCU1
    flashLED(rcv);                    // flash onboard LED rcv times
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
