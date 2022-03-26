# MAX7219-VU-Meter

Hello, it is me, the creator of this thing! I hope you like my creation. This is my first full project, so consider giving me feedback! If you’ve got any issues with the code, please let me know on the Issues tab! Thank you so much for visiting my project. I usually post my projects on [my website](http://www.mer08.cf/ "my website"), so take a quick look at it!

### List of materials

- Jumper wires
- Arduino Uno, Nano, Mega or compatible
- MAX7219 4-in-1 display or compatible

### How to build

- #### Step 1: Installing and running Arduino IDE

 - Download and install the Arduino IDE (if you haven't already)
 - Run the Arduino IDE
 - Open the "main.ino" file

- #### Step 2: Setting up the Arduino IDE

 - Click on 'Tools'
 - Click on 'Board:'
 - Select your Arduino Board
 - Click on 'Port: ""'
 - Select the port where your Arduino Board is listed
- #### Step 3: Compiling and uploading
 - Click on the arrow that is pointing to the left, located underneath the 'File' tab.
 - Wait for the process to finish.
- #### Step 4: Wiring
 - Display:
   · Hook VCC to 5V and GND to Ground.
   · Hook DIN to pin 11.
   · Hook CS to pin 9.
   · Hook CLK to pin 13.
  - Audio input:
   · Hook the left audio channel to A0 and the right audio channel to A1 (internal pullup.)
  - Optional:
   · Hook a jumper wire shorting Ground and digital pin 4. (adds L/R letters to the display)
- #### Step 5: Use the thing!
 - Congratulations! You are now in possession of whatever this thing is! If you want to tidy up the wire mess, you can tape the jumper wires for each of the sections together.
