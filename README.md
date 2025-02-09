# MCUsTalking
This is a collection of example sketches linking microprocessors together, by SoftwareSerial, and PWM signals.<p>
The following projects are examples of SoftwareSerial connections between MCUs:<p>
"2KeyPads" is an example of one-way SoftwareSerial communication between two Arduino Unos set up as keypads. It was inspired by a student's design project in PHC435: a 2-handed Dactyl Manuform keyboard controlled by two Arduino Pro Micro Leonardos. Half-libraries of the SoftwareSerial.h library are used, since only one send-receive wire is needed.<p>
"LeapFrog" is an example of using the full SoftwareSerial.h library. An LED receives an integer from the SoftwareSerial monitor, flashes its onboard LED that number of times, then sends that number + 1 through the SoftwareSerial monitor to the other MCU.<p>
In "simpleControl", MCU1 reads an integer from the regular serial monitor, sends it to MCU2 through a software serial connection, then MCU2 flashes the onboard LED that number of times. MCU2 returns the number back to MCU1 for error checking. The same process is repeated from MCU1 to MCU3. Some fundamental error checking is implemented, including a timeout for the software serial monitors, with buffer clearning to prevent communication errors.<p>
"bareMin" is a bare minimum sketch of "simpleControl" with only two MCUs and no error checking, just to get you going and to show you how simple the code can be.<p>
In "readPWM" you will find sketches that send a PWM pulse to be sent by MCU2, and is read by MCU1. This is a quick way of transmitting data one way, although it is a smidge noisy (±1 div).<p>
"I2C" provides example sketches for linking two Arduino Unos together using the I2C bus protocol (the SDA, SCL pins: A4 and A5).
