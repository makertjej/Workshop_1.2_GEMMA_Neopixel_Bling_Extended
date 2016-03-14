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
  
  uint32_t delayTime; // Utility variable for timing
  uint32_t color = 0xffffff; // default white
  uint8_t positionInPattern = 0; // Current position of moving pattern
  uint8_t positionInColorChart = 0; // Current position within colour chart

//**********************************************************************************************
// SETUP
//**********************************************************************************************
void setup() // setup() runs once
{ 
  pixels.begin();
  
  pixels.setBrightness(20); // 1/5 brightness to save battery
  
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

  switch(myPattern) {

    //**********************************************************************************************
    // Case 0: LIGHT YOUR FIRST PIXEL, EXAMPLE
    //**********************************************************************************************

    case 0:
     
       //Choose pixel position: 0-15
       pixel = 0;
    
       //Choose color values for the R-G-B positions: 0-255
       red = 80;
       green = 172;
       blue = 100;
       
       //This is how we tell the Gemma our choice of pixel and color
       pixels.setPixelColor(pixel, red, green, blue);
       pixels.show(); 
       delay(delayTime);
       
       //Turn the pixel off
       pixels.setPixelColor(pixel, 0, 0, 0); 
       pixels.show(); 
       delay(delayTime); 
       
       break;

    //**********************************************************************************************
    // Case 1: Flushes the ring with one color at a time
    //**********************************************************************************************
    
    case 1:
    
      //Remember: pixel position # increases as you rotate counter-clockwise

      for(uint16_t pixel_index = 0; pixel_index < 16; pixel_index++) //Sets color to one pixel at the time
      {
          color = myColors[myColorChart][positionInColorChart]; //Selects color from myColors
          pixels.setPixelColor(pixel_index, color);
          
          pixels.show();
          delay(delayTime);
      }
      
      positionInColorChart++; //use next color in set
      
      if (positionInColorChart >= 6) //Rotate only through color positions 0-5
      {
          positionInColorChart = 0;
      }
      
      for (uint16_t pixel_index = 0; pixel_index < 16; pixel_index++) //Turns off all pixels
      {
          pixels.setPixelColor(pixel_index, 0);
      }
      
      break;

    //**********************************************************************************************
    // Case 2 : Random sparks - 1-4 LED(s) on at a time!
    //**********************************************************************************************
   
    case 2:

      for(uint8_t index = 0; index < 4; index++) //For-loop to set up to four random pixels
      {
          color = myColors[myColorChart][random(6)]; //Selects a random color from "myColorChart" at the top of the code
          uint8_t pixel_index = random(16); //Selects a random number 0-15 (position)
          pixels.setPixelColor(pixel_index, color); //Sets the selected random color at a random pixel position
      }
      
      pixels.show();
      delay(delayTime);
      
      for(uint16_t pixel_index = 0; pixel_index < 16; pixel_index++) //Turns of all pixels
      {
          pixels.setPixelColor(pixel_index, 0);
      }
    
      break;

    //**********************************************************************************************
    // Case 3: Spinny wheels (2 LEDs on at a time)
    //**********************************************************************************************

    case 3:
    
       for(uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Sets color of one pixel at a time
       {
          uint32_t color = 0; //Default 'color' is off (no color)
          
          if( ( (positionInPattern + pixel_index) & 7 ) < 2 ) 
          {
            //This if-loop makes use of a 'Bitwise AND' to divide the 16 pixels in half (7 = 8 with 'off by one')
            //the 2 is for how many pixels will stay on
            
             color = myColors[myColorChart][random(6)]; //Set all colors randomly from color set
          }
          
          pixels.setPixelColor(pixel_index, color); //Set pixel position and color
       }
       
       pixels.show();
       positionInPattern++; //Rotate the pattern 1 position
       delay(delayTime);
       
       break;

    //**********************************************************************************************
    // Case 4: Counter-rotation + counter-fade
    //**********************************************************************************************
     
    case 4:
    
      //'static' variables persist beyond the function call, preserving their data between function calls
      static int16_t c = 0; //the 'start' position each time the code loops
      static int16_t d = 0;
   
      for (uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Loops pixel_index from 0-15
        {
          //Remember: pixel position # increases as you rotate counter-clockwise
          
          //Determines the strength (0-255) of color_1 (red) and color_2 (blue), with some of color_1 and color_2 in all 16 pixels
          uint8_t color_1 = 255 / (15 - ((pixel_index + 16 - c) % 16)); //brightness decreases with CW rotation: color leader rotates counter-clockwise
          uint8_t color_2 = 255 / ((pixel_index + d) % 16); //brightness decreases with CCW rotation: color leader rotates rotating clockwise
     
          pixels.setPixelColor(pixel_index, color_1, 0, color_2);
          //Sets each pixel position with R-G-B levels. 
          //Green part is set to off, red and blue parts merge into purple behind the start/leader pixel
       }  
        
        // ++ rotates 'start' pixel counter-clockwise
        c++;
        d++;
  
        c = c % 16; //Calculates the remainder of a / 16, to keep a and b = 0-15
        d = d % 16;
     
        pixels.show();
        delay(delayTime);

        break;

    //**********************************************************************************************
    // Case 5: Two color worms
    //**********************************************************************************************
    
    case 5:

        static int16_t a = 0; //the 'start' position each time the code loops
        static int16_t b = 0;

 
        for (uint8_t pixel_index = 0; pixel_index < 16; pixel_index++)  //Sets color to each pixel position
        {
          //Remember: pixel position # increases as you rotate counter-clockwise
          
          //Determines the strength (0-255) of color_1 (red) and color_2 (blue)
          //Strength decreases while rotating counter-clockwise, with some of color_1 and color_2 in all 16 pixels
          uint8_t color_1 = 255 / ((pixel_index + 8 + a) % 16); //offset by 8 pixels from color_2
          uint8_t color_2 = 255 / ((pixel_index + b) % 16);
            
          pixels.setPixelColor(pixel_index, color_1, 0, color_2);
          //Sets each pixel position with R-G-B levels. 
          //Green part is set to off, red and blue parts merge into purple behind the start/leader pixel
        }
      
        a++; // rotate start pixel clockwise
        b++;
      
        a = a % 16; //Calculates the remainder of a / 16, to keep a and b = 0-15
        b = b % 16;
        
        pixels.show();
        delay(delayTime);
        
        break;

    
    //**********************************************************************************************
    // Case 6: COLOR-WORM (By Ingela Rossing)
    //**********************************************************************************************
     
     case 6:
       
       if(positionInPattern >= 16) //limit positionInPattern from 0-15
       {
          positionInPattern = 0;
       }
       
       for(uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Turns off all pixels
       {
           pixels.setPixelColor(pixel_index, 0);
       }
       
       //Turn some pixels on with colors:
       for(uint8_t color_index = 0; color_index < 6; color_index++) //Rotates through color array positions 0-5
       {
           uint8_t pixel_index = positionInPattern + (2 * color_index); //Set position so 2 pixels are the same color
           color = myColors[myColorChart][color_index]; //Get color from color array
           
           //Set 2 pixels in a row to 'color', and make sure pixel_index is 0-15
           pixels.setPixelColor( pixel_index % 16, color);
           pixels.setPixelColor( (pixel_index + 1) % 16, color); 
       }
       
       pixels.show();
       positionInPattern++; //Rotate 'start' pixel one position counter-clockwise
       delay(delayTime);
       
       break;
       
    //**********************************************************************************************
    // Case 7: LIGHT-WORM
    //**********************************************************************************************
       
     case 7:

       //Color- choose the brightness of the R-G-B parts, value from 0-15
       red = 15;
       green = 15;
       blue = 15;
       
       for(uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Sets color of one pixel at the time
       {
          pixel = (positionInPattern + pixel_index) % 16; //Makes sure pixel position is 0-15
          pixels.setPixelColor(pixel, red * pixel_index, green * pixel_index, blue * pixel_index); //As pixel_index increases, so does brightness of each color
       }
      
       positionInPattern++; //Rotate 'start' pixel one position counter-clockwise
       pixels.show();
       delay(delayTime);
       
       break;

    //**********************************************************************************************
    // Case 8: Rotating Flag
    //**********************************************************************************************
     
     case 8:
       //This program relies on 'Bitshifting' to combine color brightnesses into a single value
      
       static uint32_t leds[16]; //Initialize an array with 16 positions, to hold the color for each pixel. Color is stored as 32 bits
      
       static int8_t n = 0; //'start' pixel's position
      
       for (uint8_t i = 0; i < 16; ++i) //Turns all pixels off
       {
         leds[i] = 0;
       }
       
       //Set brightness of R-G-B parts of pixels from 0-255. (2 pixels off, 2 on all around. Makes sure position is 0-15.)
       leds[(2+n)%16] = color8(255, 255, 0);
       leds[(3+n)%16] = color8(255, 255, 0);

       leds[(6+n)%16] = color8(0, 255, 0);
       leds[(7+n)%16] = color8(0, 255, 0);

       leds[(10+n)%16] = color8(0, 255, 255);
       leds[(11+n)%16] = color8(0, 255, 255);

       leds[(14+n)%16] = color8(0, 0, 255);
       leds[(15+n)%16] = color8(255, 0, 0);
       
       for (uint8_t i = 0; i < 16; i++) //Sets each pixel to color in array
       {
         pixels.setPixelColor(i, leds[i]);
       }
      
       n = (n + 1) % 16; //Increments n, and makes sure it is 0-15
      
       pixels.show();
       delay(delayTime);
      
       break;


    //**********************************************************************************************
    // Case 9: WRITE YOUR OWN PATTERN 
    //**********************************************************************************************
     
     case 9:
     
       // To run your pattern, remember to change the case/pattern in the top of the code
       
       pixels.show(); 
       delay(delayTime); 
       
       break; 
    
  }
}

//Function used by Case 8
uint32_t color8(uint8_t r, uint8_t g, uint8_t b)
       {
         return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b; 
         //Uses 'OR' to combine r-g-b (8-bit) values into one 32-bit value
       }
