# MCUsTalking
This is a collection of example sketches linking microprocessors together, by SoftwareSerial, and PWM signals.<p>
The following projects are examples of SoftwareSerial connections between MCUs:<p>
"2KeyPads" is an example of one-way SoftwareSerial communication between two Arduino Unos set up as keypads. It was inspired by a student's design project in PHC435: a 2-handed Dactyl Manuform keyboard controlled by two Arduino Pro Micro Leonardos. Half-libraries of the SoftwareSerial.h library are used, since only one send-receive wire is needed.<p>
  "LeapFrog" is an example of using the full SoftwareSerial.h library. An LED receives an integer from the SoftwareSerial monitor, flashes its onboard LED that number of times, then sends that number + 1 through the SoftwareSerial monitor to the other MCU.<p>
In "simpleControl", MCU1 reads an integer from the regular serial monitor, sends it to MCU2, and MCU2 flashes the onboard LED that number of times. MCU2 returns the number back to MCU1 for error checking. The same process is repeated with MCU3. Some fundamental error checking is implemented, including a timeout for the software serial monitors, with buffer clearning to prevent communication errors.<p>
"bareMin" is a bare minimum sketch of "simpleControl" with only two MCUs and no error checking, just to get you going and to show you how simple the code can be.
