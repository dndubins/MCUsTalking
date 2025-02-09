# Connecting Two Arduino Unos via I2C
These two sketches connect two Unos together, to send information to each other using an I2C bus. The slave sketch can be used for multiple slaves as long as the I2C address is changed to be a unique address. The master can control multiple slaves using the specific address of that slave.<p>

The sketches I2Cmaster.ino and I2Cslave.ino allow for bi-directional communication.<br>
The minimal sketches I2Cmaster1W.ino and I2Cslave1W.ino are written only to send data from the master to the slave.<br>

These sketches were adapted from the DroneBot Workshop YouTube video, https://www.youtube.com/watch?v=PnG4fO5_vU4&t=326s&ab_channel=DroneBotWorkshop<p>
If you are interested in learning more about I2C, this is an excellent intro video to get you going!<p>
For connecting an Arduino Uno to an ATtiny 85 chip using I2C, see example sketches here:<br>
https://github.com/dndubins/ATtiny85/tree/main/I2C
