//This example shows the three methods of how sprites can be rendered on a VGA screen
//You need to connect a VGA screen cable and an external DAC (simple R2R does the job) to the pins specified below.
//cc by-sa 4.0 license
//bitluni

//include libraries
#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>

#include "sprites.h"

//pin configuration
const int redPins[] = {2, 4, 12, 13, 14};
const int greenPins[] = {15, 16, 17, 18, 19};
const int bluePins[] = {21, 22, 23, 27};
const int hsyncPin = 32;
const int vsyncPin = 33;

//VGA Device
VGA14Bit vga;

int incomingByte = 0; // for incoming serial data
int x_pos = 40;
int y_pos = 40;
  
//initial setup
void setup()
{
	//need double buffering
	vga.setFrameBufferCount(2);
 
	//initializing i2s vga
	vga.init(vga.MODE200x150, redPins, greenPins, bluePins, hsyncPin, vsyncPin);
  
	//setting the font
	vga.setFont(Font6x8);

  Serial.begin(115200);

  x_pos = 100;
  y_pos = 75;
}

void clearSerial(){
  while(Serial.available() > 0) {
    char t = Serial.read();
  }
}

//just draw each frame
void loop()
{
	//draw a background
  vga.fillRect(0, 0, vga.xres, vga.yres, vga.RGB(50, 50, 50));
  
	//print some labels
	vga.setCursor(x_pos, y_pos);
	vga.print("o");

  if (Serial.available() > 0) {
    // read the incoming byte:
    incomingByte = Serial.read();

    if(incomingByte == 'a')
       x_pos -= 1;
    if(incomingByte == 's')
       y_pos += 1;
    if(incomingByte == 'd')
       x_pos += 1;
    if(incomingByte == 'w')
       y_pos -= 1;

    clearSerial();
  }

  //x_pos += (int)random(-1,2);
  //y_pos += (int)random(-1,2);

  if(x_pos < 0) x_pos = 0;
  if(y_pos < 0) y_pos = 0;
  if(x_pos > vga.xres) x_pos = vga.xres;
  if(y_pos > vga.yres) y_pos = vga.yres; 

  delay(50);
 
	//swap the frame buffers and show the rendering
	vga.show();
}
