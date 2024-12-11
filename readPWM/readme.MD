MCU2 generates a changing PWM signal that MCU1 reads. This can be used to send information from MCU2 to MCU1.<p?

MCU1_timers.ino uses the Arduino Uno's timers to time the PWM pulse. It doesn't have any error checking and will not update if the PWM pulse disappears. Perhaps this is a project for a future day.<p>

MCU1_manual.ino is a brute-force wait for the digitalRead() function to go through a PWM cycle, and it calculates the pulse of 1 cycle maually. It also returns a -1 if it can't find a pulse within 2000 microseconds. This seems like a much better idea, and will work on other MCUs.
