/*
An example that uses the really useful colorInterpolation functions.
During library development I need a solid color interpolation function that
it's able to mix 2 different colors.
The first problem it's to unpack a 565 16bit color in 3x8bit colors,
not easy since the resulting colors missed some information so I first created Color565ToRGB
that it's not perfect (it's almost impossible reconstruct the exact 8 bit components) but a good approach.
Then was easy to build an interpolation function.
If you want the maximum precision use the rgb one that it's also faster.

*/

#include <SPI.h>
#include <RA8875.h>

/*
Teensy3.x
You are using 4 wire SPI here, so:
 MOSI:  11
 MISO:  12
 SCK:   13
 the rest of pin below:
 */
#define RA8875_CS 10 //see below...
/*
Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
*/
#define RA8875_RESET 9//any pin or 255 to disable it!

/*
Teensy3.x has small difference since it can use alternative SPI pins,
essential if you want to use this library with Audio Shield.
You can set alternative SPI pins:
RA8875(CSpin,RSTpin=255,MOSI=11,SCLK=13,MISO=12);//the default configuration
To use with Audio shield:-------------------------------
CS: 2,20,21 because are not used by audio shield
MOSI:7
SCLK:14
RA8875(2,255,7,14);//will not interfere with Audio Shield
Teensy LC
This cpu can use slight different configuration, it can be instanced
with the CS pin only so it will use SPI0 but you can use this:
//RA8875(CSp,RSTp,mosi_pin,sclk_pin,miso_pin);
RA8875 tft = RA8875(RA8875_CS,RA8875_RESET,0,20,1);
This will use the SPI1 (24Mhz)
--------------------------------------------------------
To omit Reset pin, set as 255
For CS you CANNOT use any pin!
Teensy 3.x can use: 2,6,9,10,15,20,21,22,23
The smallest instance can be:
RA8875(CSpin);
*/
RA8875 tft = RA8875(RA8875_CS, RA8875_RESET); //Teensy
//or
//RA8875 tft = RA8875(RA8875_CS);//Teensy (not using rst pin)



void setup()
{
  // Serial.begin(38400);
  // long unsigned debug_start = millis ();
  // while (!Serial && ((millis () - debug_start) <= 5000)) ;
  // Serial.println("RA8875 start");
  /*
  If you have an Adafruit RA8875 board + display choose:
  Adafruit_480x272
  Adafruit_640x480
  Adafruit_800x480
  If you have any other display you have to choose:
  RA8875_320x240
  RA8875_480x272
  RA8875_800x480
  RA8875_640x480
  */
  tft.begin(RA8875_800x480);
  /*
  By default the library init display at 16bit color depth but
  you can optionally force the display to work at 8 bit:

  tft.begin(RA8875_480x272,8);//force obit color depth
  */
  /*
  Now that board it's inited you can use any draw or text command:
  */

/*
The colorInterpolation it's quite simple and has 2 variants:
colorInterpolation(color1,color2,pos,divisions);
divisions:this is the amount of color division between the 2 colors
pos:this is the position between the mix, can go from 0 (color1) to divisions (color2)
There's another version that uses 8bit components for color1 and color2:
colorInterpolation(color1R,color1G,color1B,color2R,color2G,color2B,pos,divisions);
Has the same functionality but better precision and bit faster
 */
  for (int i = 0; i < tft.width(); i++) {
    tft.drawFastVLine(i, 0, 50, tft.colorInterpolation(RA8875_GREEN, RA8875_RED, i, tft.width()));
    tft.drawFastVLine(i, 50, 50, tft.colorInterpolation(RA8875_RED, RA8875_GREEN, i, tft.width()));
    tft.drawFastVLine(i, 100, 50, tft.colorInterpolation(RA8875_GRAYSCALE, RA8875_PINK, i, tft.width()));
    tft.drawFastVLine(i, 150, 50, tft.colorInterpolation(RA8875_YELLOW, RA8875_CYAN, i, tft.width()));
    tft.drawFastVLine(i, 200, 50, tft.colorInterpolation(23,0,127,64,127,0, i, tft.width()));//this one uses the rgb one
  }
}


void loop()
{


}