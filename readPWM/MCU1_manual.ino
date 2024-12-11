// readPWM Sketch
// Author: D. Dubins
// Date: 11-Dec-24
// Description: MCU1 Reads a PWM signal from MCU2 and reports the pulse width in divs on a 0-255 scale.
// Notes: This routine does not use timers (safe for other MCUs).
//
// Wiring:
//--------
// This sketch reads a PWM signal sent by MCU2, on Digital Pin 3 of MCU1. The PWM signal could be sent from the same MCU for testing, or between
// MCUs as a means of communicating.
// The working range of reads is from 15-250.
// Here's what the timers look like:
//        _______             _______
//       |       |           |       |
// ______|       |___________|       |____
//     timer0  timer1     timer2
//    (rising)  (falling)  (rising)

byte readPin = 3;  //to read PWM signal

void setup() {
  Serial.begin(9600);  // Start the Serial Monitor
}

void loop() {
  Serial.print("PWM Read: ");
  int width = readPWM(readPin);
  if(width>0){
    Serial.println(width);  // Print PWM width
  }else{
    Serial.println("Timeout - no PWM signal detected.");
  }
  delay(100);             // wait a bit
}

int readPWM(byte pin) {
  pinMode(pin, INPUT);             // make sure pin is in INPUT mode
#define TIMEOUT 2000                //everything should happen within 2000 microseconds
  unsigned long timer = micros();  // for timeout
  unsigned long timer0;            //last rising edge
  unsigned long timer1;            //rising edge
  unsigned long timer2;            //falling edge
  //We need to catch the signal on the rising edge. So go through at leat one pulse:
  while (digitalRead(pin) && micros() - timer < TIMEOUT)
    ;  //wait for pin to go low
  //Now wait for the pulse to go high:
  while (!digitalRead(pin) && micros() - timer < TIMEOUT)
    ;                 //wait for pin to go high
  timer0 = micros();  //record starting time
  while (digitalRead(pin) && micros() - timer < TIMEOUT)
    ;                                                      //wait for pin to go low
  timer1 = micros();                                       //record starting time
  while (!digitalRead(pin) && micros() - timer < TIMEOUT)  //wait for pin to go high
    timer2 = micros();                                     // record ending time
  int w = 255 * (timer1 - timer0) / (timer2 - timer0);     // calculate pulse width
  if (micros() - timer > TIMEOUT) {
    return -1;  // error, timeout occurred
  } else {
    return w;  // return pulse width
  }
}
