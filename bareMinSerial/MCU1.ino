/* SoftwareSerial example, MCU1 is controlling MCU2 and MCU3. This sketch is for MCU1 - the master. MCU2 is the sketch for both slaves.
 * Author: D. Dubins
 * Date: 11-Dec-24

 * Description: This project illustrates how to get one MCU to send commands to another two MCUs through SoftwareSerial connections.
 * This sketch is for the first MCU (MCU1). The second MCUs (MCU2 and MCU3) will be powered parasitically through the Vin and GND pins of MCU1.
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
SoftwareSerial MCU2Serial(2, 3);  // define software serial connection to MCU2 (RX:2, TX:3)
SoftwareSerial MCU3Serial(4, 5);  // define software serial connection to MCU3 (RX:4, TX:5)

#define TIMEOUT 2000  // threshold (in milliseconds) for communications timeout. 2 seconds is reasonable, depending on MCU2 and MCU3 response times.

void setup() {
  Serial.begin(57600);       // start serial connection
  MCU2Serial.begin(57600);   // start software serial connection with MCU2 (max speed for SoftwareSerial is 57600 for Uno)
  MCU3Serial.begin(57600);   // start software serial connection with MCU3 (max speed for SoftwareSerial is 57600 for Uno)
  delay(1000);               // wait for MCUs to boot up
  Serial_clear(MCU2Serial);  // clear MCU2Serial buffers
  Serial_clear(MCU3Serial);  // clear MCU3Serial buffers
  Serial.println("Enter number of flashes to send.");
}

void loop() {
  if (Serial.available()) {     // if user entered something on the serial monitor
    bool ret = 0;               // to store results from Serial_send() function
    int n = Serial.parseInt();  // store integer from Serial Monitor to n
    Serial.print("Sending to MCU2: ");
    Serial.println(n);                 // send snd to the regular Serial Monitor
    ret = Serial_send(MCU2Serial, n);  // send n to MCU2
    if (!ret) Serial.println("Communications failure with MCU2Serial.");
    Serial.print("Sending to MCU3: ");
    Serial.println(n);                 // send snd to the regular Serial Monitor
    ret = Serial_send(MCU3Serial, n);  // send n to MCU3
    if (!ret) Serial.println("Communications failure with MCU3Serial.");
  }
}

bool Serial_send(SoftwareSerial &serialport, int s) {  // send integer "s" to SoftwareSerial device "serialport"
  serialport.listen();                       // listen to port serialport
  unsigned long timer = millis();            // start the timer
  int r = 0;                                 // to receive integer from port serialport
  serialport.print(s);                       // send s to port serialport
  timer = millis();                          // start the timer
  while (!seriaport.available() && millis() - timer < TIMEOUT); // wait for response from MCU2, with TIMEOUT limit
  if (serialport.available()) {  // if there's something waiting from port serialport
    r = serialport.parseInt();   // store it to r
    Serial.print("Receiving: ");
    Serial.println(r);  // send rcv to the regular Serial Monitor
    if (s == r) {       // integers should match
      return 1;         // communication successful
    } else {
      Serial.println("Communication error.");
      return 0;  // send did not match receive.
    }
  } else {  // timeout feature
    Serial.println("Communication timed out.");
    Serial_clear(serialport);  // get rid of any residual data in the serial buffer
    return 0;         // response not received from MCU2
  }
}

void Serial_clear(SoftwareSerial &serialport) {  // used to clear the serial buffers from junk
  serialport.listen();                           // listen to port serialport
  while (serialport.available()) {               // while data are available in the buffer
    byte i = serialport.read();                  // read the data and store to i
  }
}
