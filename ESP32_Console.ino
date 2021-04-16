
/*
  //take the avarage from the surrounding pixels below
  int c0 = vga.get(x, y);
  int c1 = vga.get(x, y + 1);
  int c2 = vga.get(x - 1, y + 1);
  int c3 = vga.get(x + 1, y + 1);
  int r = ((c0 & 0x1f) + (c1 & 0x1f) + ((c2 & 0x1f) + (c3 & 0x1f)) / 2) / 3;
  int g = (((c0 & 0x3e0) + (c1 & 0x3e0) + ((c2 & 0x3e0) + (c3 & 0x3e0)) / 2) / 3) & 0x3e0;
  int b = (((c0 & 0x3c00) + (c1 & 0x3c00) + ((c2 & 0x3c00) + (c3 & 0x3c00)) / 2) / 3) & 0x3c00;
  //draw the new pixel
  vga.dotFast(x, y, r | g | b);
*/

//include libraries
#include <ESP32Lib.h>
#include <Ressources/Font6x8.h>
#include <stdint.h>


//pin configuration
const int redPins[] = {2, 4, 12, 13, 14};
const int greenPins[] = {15, 16, 17, 18, 19};
const int bluePins[] = {21, 22, 23, 27};
const int hsyncPin = 32;
const int vsyncPin = 33;

//VGA Device
VGA14Bit vga;

#include "raycast_renderer.h"
#include "player.h"


 
//initial setup
void setup()
{
  //need double buffering
  vga.setFrameBufferCount(2);
 
  //initializing i2s vga MODE200x150
  vga.init(vga.MODE200x150, redPins, greenPins, bluePins, hsyncPin, vsyncPin);
  
  //setting the font
  vga.setFont(Font6x8);

  Serial.begin(115200);

  renderer_init();
	player_init();
	
	// TODO: add main menu here
}

uint64_t last_time = 0;

//just draw each frame
void loop()
{
  
  player_update();
  renderer_render(&player_camera);

  
  vga.setCursor(2, 2);
  vga.print("FPS: ");
  vga.setCursor(26, 2);
  
  uint64_t frame_time = millis() - last_time;
  double fps = 1000.0 / (double)frame_time;
  vga.print(fps);

  last_time = millis();
}
