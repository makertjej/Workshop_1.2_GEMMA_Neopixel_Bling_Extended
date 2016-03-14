// MAKERTJEJ.se
// Workshop 1.2: Gemma + NeopPixel Ring, Part 2
//
// Low power program for GEMMA with a NeoPixel ring. 
// A nice blinky display that can be personalized by 
// choosing different colors, speeds & patterns.
//
// Part 2 expands the basic code with more cases to
// play with and modify.

#include <Adafruit_NeoPixel.h>

#define PIN 0 // assign constant PIN to the pin D0~ on the Gemma

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(16, PIN);


//**********************************************************************************************
// MODIFIABLE PARAMETERS - PERSONALIZE YOUR GEMMA NEOPIXELS HERE
//**********************************************************************************************

  //***************************************** CHOOSE COLOR *************************************

    // 0: REDS-ORANGE
    // 1: BLUE-LILAC
    // 2: GREEN-YELLOW
    // 3: PINK-PURPLE
    // 4: TURQUOISE
    // 5: RAINBOW

    // Colors, hexadecimal code:
    uint32_t myColors[][6] = 
    {
      {0xff0000, 0xff3300, 0xff6600, 0xffcc00, 0xffff00}, // 0: REDS-ORANGE
      {0x0000ff, 0x3300ff, 0x6600ff, 0x9900ff, 0xcc00ff, 0xff00ff}, // 1: BLUE-LILAC
      {0x00ff00, 0x66ff00, 0xccff00, 0xffff00, 0xffee00, 0xffdd00}, // 2: GREEN-YELLOW
      {0x9900ff, 0xcc00ff, 0xff00ff, 0xff00cc, 0xff0099, 0xff0066}, // 3: PINK-PURPLE
      {0x0066ff, 0x0099ff, 0x00ccff, 0x00ffff, 0x00ffcc, 0x00ff99}, // 4: TURQUOISE
      {0x9900ff, 0x0033ff, 0x00ff33, 0xffff00, 0xff9900, 0xff0000} // 5: RAINBOW
    }; //Try to create your own color palette by adding a row in the matrix

    uint8_t myColorChart = 5; // ← Change this value to your desired color palette

  //********************************** CHOOSE BLINKING PATTERN **********************************

    // 0: LIGHT YOUR FIRST PIXEL
    // 1: FLUSHES THE RING WITH ONE COLOR AT A TIME
    // 2: RANDOM SPARKS - 1-4 LEDs ON AT A TIME
    // 3: Spinny wheels (2 LEDs ON AT A TIME)
    // 4: COUNTER-ROTATION + COUNTER-FADE
    // 5: TWO COLOR WORMS
    // 6: COLOR WORM 
    // 7: LIGHT WORM
    // 8: ROTATING FLAG
    // 9: WRITE YOUR OWN PATTERN
    
    uint8_t  myPattern = 8; // ← Change this value to your desired pattern
    
  //********************************** CHOOSE A SPEED SETTING ***********************************
  
    // 0: FAST
    // 1: MEDIUM
    // 2: SLOW 
    // 3: EXTRA SLOW (good for debugging!)

    uint8_t mySpeed = 3; // ← Change this value to your desired speed

//**********************************************************************************************
// YOU’RE DONE!! Keep reading if you'd like to try your hand at even more customization
//**********************************************************************************************

//**********************************************************************************************
// UTILITY VARIABLES
//**********************************************************************************************
  
  uint32_t prevTime; // Utility variable for timing
  uint32_t delayTime; // Utility variable for timing
  //uint32_t color = 0xffffff; // default white
  uint8_t positionInPattern = 0; // Current position of moving pattern
  uint8_t positionInColorChart = 0; // Current position within colour chart

//**********************************************************************************************
// SETUP
//**********************************************************************************************

void setup() // setup() runs once
{ 
  pixels.begin();
  
  pixels.setBrightness(20); // 1/5 brightness to save battery
  prevTime = millis(); // read the continuous timer (ms)

    switch (mySpeed) // where the speed timings are set
    { 
      case 0: // speed 0
          delayTime = 50;
      break;

      case 1: // speed 1
          delayTime = 150;
      break;
      
      case 2: // speed 1
          delayTime = 300;
      break;

      default: // speed 3 (or any integer other than 0, 1, or 2)
          delayTime = 750;
      break;
    }
    
}

//**********************************************************************************************
// LOOP THAT WILL RUN OVER AND OVER
//**********************************************************************************************

void loop() // after setup() runs, loop() will run over and over as long as the GEMMA has power
{ 
  uint8_t red, green, blue, pixel;

    //**********************************************************************************************
    // Case 8: Rotating Flag
    //**********************************************************************************************
     

      //This program relies on 'Bitshifting' binary R-G-B color numbers to modify colors

        static uint32_t leds[16]; //Initialize an array with 16 positions, to hold the color for each pixel. Color is stored as 32 bits
        
        static int8_t n = 0; //'start' pixel's position

        for (uint8_t i = 0; i < 16; ++i) //Turns all pixels off
        {
            leds[i] = 0;
        }

        //Set brightness of R-G-B part of pixels. 2 pixels off, 2 on all around. Makes sure position is 0-15
        leds[(2+n)%16] = color(255, 255, 255);
        leds[(3+n)%16] = color(255, 255, 255);

        leds[(6+n)%16] = color(0, 0, 255);
        leds[(7+n)%16] = color(100, 0, 0);
      
        leds[(10+n)%16] = color(255, 255, 255);
        leds[(11+n)%16] = color(255, 255, 255);
      
        leds[(14+n)%16] = color(255, 255, 255);
        leds[(15+n)%16] = color(255, 255, 255);
       
        for (uint8_t i = 0; i < 16; i++) //Sets each pixel to color in array
        {
            pixels.setPixelColor(i, leds[i]);
        }
      
        n = (n + 1) % 16; //'start' pixel rotates counter-clockwise, and makes sure it is 0-15
        
        pixels.show();
        delay(delayTime);
    
}

//Function used by case 8- Rotating flag
uint32_t color(uint8_t r, uint8_t g, uint8_t b) //Input integers of binary length up to 8 positions
{
    return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b; //Change formats of integers to 32 positions. Bitshift red input 16 places, green 8 places, and no shift to blue input. 
}
