// readPWM Sketch (MCU2.ino)
// Author: D. Dubins
// Date: 11-Dec-24
// Description: MCU2 generates a PWM signal to be read by MCU1. There's nothing special about this sketch, you could use analogWrite() to generate a signal
// between MCUs. This is just setting up a signal that changes once per second, and reports it on the Serial monitor.
//
// Wiring:
//--------
// MCU2 GND - MCU1 GND
// MCU2 Pin 5 - MCU2 Pin 3

byte pwmPin = 5;  // pin to send PWM signal

void setup() {
  Serial.begin(9600);  // Start the Serial Monitor
  Serial.println("Sending PWM."); // Message the user
}

void loop() {
  for(byte i=15;i<=250;i+=5){  // working range of PWM reads
    analogWrite(pwmPin,i); // write a PWM signal
    Serial.print("PWM Sent: ");
    Serial.println(i);  // Print PWM value to Serial Monitor
    delay(2000); 
  }
}

