These two sketches, I2Cmaster.ino and I2Cslave.ino, set up two Unos to send information to each other bi-directionally using an I2C bus. The slave sketch can be used for multiple slaves as long as the I2C address is changed to be a unique address. The master can control multiple slaves using the specific address of that slave.
These sketches were adapted from the DroneBot Workshop YouTube video, https://www.youtube.com/watch?v=PnG4fO5_vU4&t=326s&ab_channel=DroneBotWorkshop<p>
If you are interested in learning more about I2C, this is an excellent intro video to get you going!<p>
For connecting an Arduino Uno to an ATtiny 85 chip using I2C, see example sketches here:<br>
https://github.com/dndubins/ATtiny85/tree/main/I2C
