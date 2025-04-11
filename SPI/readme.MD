# Connecting Two Arduino Unos via SPI
These two sketches connect two Unos together, to send information to each other using SPI. <p>

In the 2-way folder, the sketches SPImaster.ino and SPIslave.ino allow for full-duplex (simultaneous) bi-directional communication of one byte.<br>
The minimal sketches <b>/2-way/SPImaster.ino</b> and <b>/2-way/SPIslave.ino</b> are written to only transfer one byte.<br>

These sketches were were made through very lengthy conversations with ChatGPT and Perplexity, and a lot of error checking. This is not an efficient way to code (yet!).

What if you'd like to transfer more than one byte, and they are different types? To make life easier, you could pack all of the data you want to transfer into a struct, and create a union with a char array. Then, send the char array over I2C, and have it read in on the other end, to a char array that has a union shared with the same complicated structure. Then, you can send many different variable types at once, all in one go. Sounds interesting? Check out the following two programs:<p>

<b>/struct/SPImaster_struct.ino</b> and <b>/struct/SPIslave_struct.ino</b>.<p>

The master sends a request byte to the slave. The slave then sends a struct back to the master. The master receives the data in its own variable called RXdata, then prints it out. There's a little bit of error checking with the response (nothing fancy).<p>
