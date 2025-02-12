# Connecting Two Arduino Unos via I2C
These two sketches connect two Unos together, to send information to each other using an I2C bus. The slave sketch can be used for multiple slaves as long as the I2C address is changed to be a unique address. The master can control multiple slaves using the specific address of that slave.<p>

The sketches I2Cmaster.ino and I2Cslave.ino allow for bi-directional communication.<br>
The minimal sketches I2Cmaster1W.ino and I2Cslave1W.ino are written only to send data from the master to the slave.<br>

These sketches were adapted from the DroneBot Workshop YouTube video, https://www.youtube.com/watch?v=PnG4fO5_vU4&t=326s&ab_channel=DroneBotWorkshop<p>
If you are interested in learning more about I2C, this is an excellent intro video to get you going!<p>
For connecting an Arduino Uno to an ATtiny 85 chip using I2C, see example sketches here:<br>
https://github.com/dndubins/ATtiny85/tree/main/I2C

However, what if you'd like to transfer more than one variable, and they are different types? To make life easier, you could pack all of the data you want to transfer into a struct, and create a union with a char array. Then, send the char array over I2C, and have it read in on the other end, to a char array that has a union shared with the same complicated structure. Then, you can send many different variable types at once, all in one go. Sounds interesting? Check out the following two programs:

I2Cmaster_struct.ino and I2Cslave_struct.ino.

The implementation was easier and faster than I thought. The master sends TXdata to the slave. The slave then reads it into RXdata, then sends it back to the master. The master receives the data in its own variable called RXdata, then prints it out to show the journey was successful. The return trip isn't necessary, but the code is there if you need it. Maybe just a "true" that it worked.<p>

<b>Note:</b> When you are defining an I2C address, pick a unique number that is in the range 0x08 (DEC: 8) to 0x77 (DEC: 119). Numbers outside this range are reserved.
To see common I2C addresses of other devices (and to avoid hardware conflicts), see: https://learn.adafruit.com/i2c-addresses/the-list<p>
