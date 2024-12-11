// readPWM Sketch
// Author: D. Dubins
// Date: 11-Dec-24
// Description: MCU1 Reads a PWM signal from MCU2 and reports the pulse width in divs on a 0-255 scale.
// Notes: For the Arudino Uno, Pin 2 is int_0, Pin 3 is int_1.
//
// Wiring:
//--------
// This sketch reads a PWM signal sent by MCU2, on Digital Pin 3 of MCU1. The PWM signal could be sent from the same MCU for testing, or between
// MCUs as a means of communicating.
// This routine is ok,  but at the low and high limits it kind of craps out (where there's no pulse). The lowest number I can get
// is 12. The working range of reads is from 15-250. There isn't any error checking if the PWM pulse isn't there.
//
// Here's what the timers look like:
//        _______             _______
//       |       |           |       |
// ______|       |___________|       |____
//     timer0  timer2     timer1
//     timer1
//    (rising)  (falling)  (rising)

byte pwmRead = 3;  //to read PWM signal

volatile long timer0 = millis();  //last rising edge
volatile long timer1 = millis();  //rising edge
volatile long timer2 = millis();  //falling edge
volatile long width = 0;          //to store width of pulse

void setup() {
  Serial.begin(9600); // Start the Serial Monitor
  attachInterrupt(1, risingISR, RISING);  // attach risingISR to pin 3 (int_1), on RISING signal.
}

void loop() {
  Serial.print("PWM Read: ");
  Serial.println(width);  // Print PWM width
  delay(100);             // wait a bit
}

void fallingISR() {   // This ISR will run when interrupt is triggered
  timer2 = micros();  // on RISING edge
  attachInterrupt(1, risingISR, RISING);
}

void risingISR() {
  timer0 = timer1;  // store last value of timer1 as timer0
  timer1 = micros();
  width = 255 * (timer2 - timer0) / (timer1 - timer0);  // gives a number from 0-255
  attachInterrupt(1, fallingISR, FALLING);
}
