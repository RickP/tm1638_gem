TM1638-GEM for Raspberry Pi
===========================

This is a ruby wrapper for driving the TM1638 module - a cheap board with 8 7-segment displays, 8 buttons and 8 Red/Green LEDs - on a Raspberry Pi. It's based on the excellent driver by Martin Oldfield.


Installation on your Pi:

- Compile and install the bcm2835 lib from http://www.airspayce.com/mikem/bcm2835/index.html
- Compile and install the pi-tm1638 lib from https://github.com/mjoldfield/pi-tm1638
- Download the gem from https://github.com/RickP/tm1638_gem/releases and install with `gem install tm1638-0.1.0.gem`


Ruby example:

    require 'tm1638'              # Include the gem
    
    Tm1638.init(17, 21, 22)       # Initialize the tm1638 on GPIO pins 17 (data), 21 (clock) and 22 (strobe)

    Tm1638.set_leds([1,1,1,0,0,0,0,0], [0,0,0,1,1,1,0,0])  # Set LEDs 1-3 to red and 4-6 to green

    Tm1638.set_intensity(5)       # Set display intensity to 5 (Valid values: 0-7)

    Tm1638.write("hello123", [0,0,0,0,0,1,1,1])   # Puts 'hello1.2.3.' on display (the array defines displayed decimal points)

    button_array = Tm1638.get_buttons()  # Read current value of the 8 buttons - returns an array with 8 ints (1 = pressed, 0 = not pressed)



You should use something like event-engine to poll the buttons.
