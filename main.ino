/*
  MAX7219 DIGITAL VU METER FOR ARDUINO
  USING LEDMatrixDriver (install library by pressing Ctrl + Shift + I and searching for "LEDMatrixDriver")

  TAKES WAY LESS SPACE (on the Arduino's memory) THAN MD_MAX72XX, MD_PAROLA, MD_MAXPANEL OR MD_MAX72XX + MD_PAROLA TOGETHER
  MADE BY Mer08_ (Mer on YouTube, Mer_barrabaja on Twitch) in 25th March 2022.
  TESTED USING "MD_MAX72XX / MD_PAROLA FC16_HW" STYLE HARDWARE DISPLAY

  Open source. Tested on Arduino Uno.

  PINS:
    DISPLAY:
      Chip Select/CS  9
      Data In/DIN     11
      Clock/CLK       13
    AUDIO IN:
      LEFT CHANNEL    A0 //my 3.5mm to jumper was reversed so flip it in the #define section
      RIGHT CHANNEL   A1
    JUMPER WIRES:
     ENALBLE L/R TEXT 4 (short to GND)
      3 PIXELS        (default/no pin needed)
*/
#include <LEDMatrixDriver.hpp>
#include <stdlib.h>


#define INTENSITY       10 //Brightness. range is 1 to 10
#define CLIPPING_LEVELd 33 //use this as the value until clipping starts happening (default is 33, range is 0 - nothing higher than 39)
#define LEFT_CHANNEL    A1
#define RIGHT_CHANNEL   A0
#define LR_MODE_PIN     4

bool ENABLE_DEBUG_MODE = true; //Enables or disables Serial debugging.

LEDMatrixDriver lmd(4, 9);
void setup() {
  lmd.setEnabled(true);
  lmd.setIntensity(INTENSITY);
  if(ENABLE_DEBUG_MODE == false) {
    Serial.begin(9600);
  }
  pinMode(LEFT_CHANNEL, INPUT_PULLUP);
  pinMode(RIGHT_CHANNEL, INPUT_PULLUP);
  pinMode(LR_MODE_PIN, INPUT_PULLUP);
  analogReference(INTERNAL); //WARNING DO NOT DO ANALOGREAD BEFORE ANALOGREFERENCE!!! THIS WILL CAUSE AN INTERNAL SHORT AND COULD DAMAGE YOU MICROCONTROLLER! Used to change the reference that the analog input will use to calculate the binary equivalent. (INTERNAL WORKS THE BEST, YOU CAN USE EXTERNAL IF YOU WISH, BUT BE CAREFUL. USE AT YOUR OWN RISK AND CAREFULLY READ THE "AnalogReference()" DOCUMENT FROM ARDUINO.)
}

void loop() {
  //lmd.setPixel(int:x, int:y, bool:ledState);
  int left = analogRead(LEFT_CHANNEL);
  int right = analogRead(RIGHT_CHANNEL);
  int drawTime = 0;
  bool stateCHK = true;
  bool lR_State = !digitalRead(LR_MODE_PIN);
  
  if (left / 24 - 1 >= 40 || right / 24 - 1 >= 40) {   //check if readings are very high / check if cable is connected and display "N/C" not connected message
    drawTime = 26;
    while(drawTime > 20) {
      lmd.setPixel(drawTime,1,true);
      lmd.display();
      drawTime--;
      delay(20);
    }
    drawTime = 26;
    while(drawTime > 21) {
      lmd.setPixel(drawTime,6,true);
      lmd.display();
      drawTime--;
      delay(20);
    }
    drawTime = 0;
    while(drawTime < 6) {
      lmd.setPixel(26 - drawTime, 1 + drawTime, true);
      lmd.display();
      drawTime++;
      delay(20);
    }
    drawTime = 0;
    while(drawTime < 6) {
      lmd.setPixel(14 + drawTime, 1 + drawTime, true);
      lmd.display();
      drawTime++;
      delay(20);
    }
    drawTime = 0;
    while(drawTime < 5) {
      lmd.setPixel(7 + drawTime, 1, true);
      lmd.display();
      drawTime++;
      delay(20);  
    }
    drawTime = 0;
    while(drawTime < 4) {
      lmd.setPixel(12, 2 + drawTime, true);
      lmd.setPixel(6, 2 + drawTime, true);
      lmd.display();
      drawTime++;
      delay(20);
    }
    drawTime = 0;
    lmd.setPixel(11,6,true);
    lmd.setPixel(7,6,true);
    lmd.display();
      delay(2000);
  } else {                  //if not, display everything
    if (!digitalRead(LR_MODE_PIN) == true) {
    while (drawTime < left / 35 - 1 + ((rand() % 4) * 2)) { // if you remove the rand part, you disable the fake lows mids and highs
      lmd.setPixel(drawTime, 0, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < left / 35 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 1, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < left / 35 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 2, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < right / 35 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 5, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < right / 35 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 6, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < right / 35 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 7, true);
      drawTime++;
    }
    drawTime = 0;
    if (left / 32 >= CLIPPING_LEVELd || right / 32 >= CLIPPING_LEVELd) {
      while (drawTime < 32) {                                                                                                                                                                                                                                                                                             //Hey! You found an easter egg. I will definitely add more to my creations! Hope this made your day. ;)
        lmd.setPixel(drawTime, 3, stateCHK);
        lmd.setPixel(drawTime, 4, !stateCHK);
        stateCHK = !stateCHK;
        drawTime++;
      }
      if(ENABLE_DEBUG_MODE == true) {
      Serial.print("CLIPPING ||");
      }
    }
    drawTime = 0;
    while(drawTime < 3) {
      lmd.setPixel(31 - drawTime,0,true);
      lmd.setPixel(29, 0 + drawTime,true);
      drawTime++;
    }
    drawTime = 0;
    while(drawTime < 3) {
      lmd.setPixel(31 - drawTime,5,true);
      lmd.setPixel(32 - drawTime,6,true);
      lmd.setPixel(29,7,true);
      drawTime++;
    }
    drawTime = 0;
  } else {

    while (drawTime < left / 24 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 0, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < left / 24 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 1, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < left / 24 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 2, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < right / 24 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 5, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < right / 24 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 6, true);
      drawTime++;
    }
    drawTime = 0;
    while (drawTime < right / 24 - 1 + ((rand() % 4) * 2)) {
      lmd.setPixel(drawTime, 7, true);
      drawTime++;
    }
    drawTime = 0;
    if (left / 24 >= CLIPPING_LEVELd || right / 24 >= CLIPPING_LEVELd) {
      while (drawTime < 32) {                                                                                                                                                                                                                                                                                             //Hey! You found an easter egg. I will definitely add more to my creations! Hope this made your day. ;)
        lmd.setPixel(drawTime, 3, stateCHK);
        lmd.setPixel(drawTime, 4, !stateCHK);
        stateCHK = !stateCHK;
        drawTime++;
      }
      if(ENABLE_DEBUG_MODE == true) {
      Serial.print("CLIPPING ||");
      }
    }
    drawTime = 0;
  }
  }
  if(ENABLE_DEBUG_MODE == true) {
  Serial.print("LEFT: ");
  Serial.print(left / 24 - 1);
  Serial.print("RIGHT: ");
  Serial.print(right / 24 - 1);
  Serial.println("");
  }
  lmd.display();
  lmd.clear();
}
