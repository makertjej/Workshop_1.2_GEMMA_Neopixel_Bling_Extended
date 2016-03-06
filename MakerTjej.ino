
// MAKERTJEJ.se
// Workshop 1: Gemma + NeopPixel Ring

// Low power program for GEMMA with a NeoPixel ring. 
// A nice blinky display that can be personalized by 
// choosing different colors, speeds & patterns.

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

    uint8_t myColorChart = 3; // ← Change this value to your desired color palette

  //********************************** CHOOSE BLINKING PATTERN **********************************

    // 0: LIGHT YOUR FIRST PIXEL, EXAMPLE
    // 1: FLUSHES THE RING WITH ONE COLOR AT A TIME
    // 2: RANDOM SPARKS - JUST ONE-FOUR LED(S) ON AT A TIME
    // 3: Spinny wheels (8 LEDs on at a time)
    // 4: COUNTER ROTATE
    // 5: TWO COLOR WORMS
    // ( 5: ROTATING FLAG )
    // 6: COLOR-WORM 
    // 7: LIGHT-WORM
    // 8: WRITE YOUR OWN PATTERN
    
    uint8_t  myPattern = 5; // ← Change this value to your desired pattern
    
  //********************************** CHOOSE A SPEED SETTING ***********************************
  
    // 0: FAST
    // 1: MEDIUM
    // 2: SLOW 

    uint8_t mySpeed = 2; // ← Change this value to your desired speed

//**********************************************************************************************
// YOU’RE DONE!! YOU CAN LOOK AT THE REST OF THE CODE LATER
//**********************************************************************************************

//**********************************************************************************************
// UTILITY VARIABLES
//**********************************************************************************************
  
  uint32_t prevTime; // Utility variable for timing
  uint32_t delayTime; // Utility variable for timing
  uint32_t color = 0xffffff; //default white
  uint8_t positionInPattern = 0; // Current position of moving pattern
  uint8_t positionInColorChart = 0; // Current position within colour chart

//**********************************************************************************************
// SETUP
//**********************************************************************************************

void setup() // setup() runs once
{ 
  pixels.begin();
  
  pixels.setBrightness(20); // 1/3 brightness to save battery
  prevTime = millis(); //???

    switch (mySpeed) // where the speed timings are set
    { 
      case 0: // speed 0
          delayTime = 50;
      break;

      case 1: // speed 1
          delayTime = 150;
      break;

      default: // speed 2 (or any integer other than 0 or 1)
          delayTime = 300;
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
     
       //Choose pixel: 0-15
       pixel = 0;
    
       //Choose color values: 0-255
       red = 255;
       green = 200;
       blue = 100;
       
       //This is how we tell the gemma our choice of pixel and color
       pixels.setPixelColor(pixel, red, green, blue);
       pixels.setPixelColor(5, red, green, blue);
       pixels.show(); 
       delay(1000);
       
       pixels.setPixelColor(pixel, 0, 0, 0); 
       pixels.show(); 
       delay(1000); 
       
       break;

    //**********************************************************************************************
    // Case 1: Flushes the ring with one color at a time
    //**********************************************************************************************
    
    case 1:

      for(uint16_t pixel_index = 0; pixel_index < 16; pixel_index++) //Sets color to one pixel at the time
      {
          color = myColors[myColorChart][positionInColorChart]; //Selects color from myColors
          pixels.setPixelColor(pixel_index, color);
          
          pixels.show();
          delay(delayTime);
      }
      
      positionInColorChart++;
      
      if (positionInColorChart >= 6) 
      {
          positionInColorChart = 0;
      }
      
      for (uint16_t pixel_index = 0; pixel_index < 16; pixel_index++) //Turns of all pixels
      {
          pixels.setPixelColor(pixel_index, 0);
      }
      
      break;

    //**********************************************************************************************
    // Case 2 : Random sparks - just one-four LED(s) on at a time!
    //**********************************************************************************************
   
    case 2:

      for(uint8_t index = 0; index < 4; index++) //For-loop to set up to four random pixels
      {
          color = myColors[myColorChart][random(6)]; //Select random color from "myColorChart" at the top of the code
          uint8_t pixel_index = random(16); //Set random number between 0-15 
          pixels.setPixelColor(pixel_index, color); //Sets the selected random color at a random pixel
      }
      
      pixels.show();
      delay(delayTime+50);
      
      for(uint16_t pixel_index = 0; pixel_index < 16; pixel_index++) //Turns of all pixels
      {
          pixels.setPixelColor(pixel_index, 0);
      }
    
      break;

    //**********************************************************************************************
    // Case 3: Spinny wheels (8 LEDs on at a time)
    //**********************************************************************************************

    case 3: //NEEDS MORE COMMENTS
    
       for(uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Sets color to one pixel at the time
       {
          uint32_t color = 0; 
          
          if( ( (positionInPattern + pixel_index) & 7 ) < 2 ) //?????
          { 
             color = myColors[myColorChart][random(6)]; // 4 pixels on...
          }
          
          pixels.setPixelColor(pixel_index, color); // First eye
       }
       
       pixels.show();
       positionInPattern++;
       delay(delayTime);
       
       break;

    //**********************************************************************************************
    // Case 4: Counter rotate //NEEDS COMMENTS
    //**********************************************************************************************
     
    case 4: //NEEDS COMMENTS
       
        static int16_t c = 0;
        static int16_t d = 0;
   
        for (uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) 
        {
           uint8_t color_1 = 255 / (15 - ((pixel_index + 16 - c) % 16)); 
           uint8_t color_2 = 255 / ((pixel_index + d) % 16);
     
           pixels.setPixelColor(pixel_index, color_1, 0, color_2);
        }  
        
        c++;
        d++;
  
        c = c % 16;
        d = d % 16;
     
        pixels.show();
        delay(75);

        break;

    //**********************************************************************************************
    // Case 5: Two color worms //NEEDS WORK AND COMMENTS
    //**********************************************************************************************
    
    case 5: //NEEDS WORK AND COMMENTS

        static int16_t a = 0;
        static int16_t b = 0;
 
        for (uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) 
        {
            uint8_t color_1 = 255 / ((pixel_index + 8 + a) % 16);
            uint8_t color_2 = 255 / ((pixel_index + b) % 16);
            
            pixels.setPixelColor(pixel_index, color_1, 0, color_2);
        }
      
        a++;
        b++;
      
        a = a % 16;
        b = b % 16;
        
        pixels.show();
        delay(75);
        
        break;

    //**********************************************************************************************
    // Case 5: Rotating Flag //NEEDS WORK AND COMMENTS
    //**********************************************************************************************
     /*
    case 5: //NEEDS WORK AND COMMENTS

        uint32_t leds[16];

        uint32_t color(uint8_t r, uint8_t g, uint8_t b)
        {
            return ((uint32_t)r << 16) | ((uint32_t)g <<  8) | b; 
        }
        
        int8_t o = 0;

        for (uint8_t i = 0; i < 16; ++i) 
        {
            leds[i] = color(0, 0, 255);
        }

        leds[(2+o)%16] = color(255, 255, 0);
        leds[(3+o)%16] = color(255, 255, 0);

        leds[(6+o)%16] = color(255, 255, 0);
        leds[(7+o)%16] = color(255, 255, 0);
      
        leds[(10+o)%16] = color(255, 255, 0);
        leds[(11+o)%16] = color(255, 255, 0);
      
        leds[(14+o)%16] = color(255, 255, 0);
        leds[(15+o)%16] = color(255, 255, 0);
       
        for (uint8_t i = 0; i < 16; i++) 
        {
            pixels.setPixelColor(i, leds[i]);
        }
      
        o = (o + 1) % 16;
        
        pixels.show();
        delay(75);

        break;
        */

    //**********************************************************************************************
    // Case 6: COLOR-WORM (By Ingela Rossing)
    //**********************************************************************************************
     
     case 6:
     
       if(positionInPattern >= 16)
       {
          positionInPattern = 0;
       }
       
       for(uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Turns off all pixels
       {
           pixels.setPixelColor(pixel_index, 0);
       }
       
       for(uint8_t color_index = 0; color_index < 6; color_index++) //Sets color to one pixel at the time
       {
           uint32_t color = 0;
           uint8_t pixel_index = positionInPattern + (2 * color_index);
           color = myColors[myColorChart][color_index];
           
           //set pixels and make sure pixel_index is in value 0-15
           pixels.setPixelColor( pixel_index % 16, color);
           pixels.setPixelColor( (pixel_index + 1) % 16, color); 
       }
       
       pixels.show();
       positionInPattern++;
       delay(delayTime);
       
       break;
       
    //**********************************************************************************************
    // Case 7: LIGHT-WORM
    //**********************************************************************************************
       
    case 7:

       //color, change it if you like. Value can be 0-15.
       red = 15;
       green = 15;
       blue = 15;
       
       for(uint8_t pixel_index = 0; pixel_index < 16; pixel_index++) //Sets color to one pixel at the time
       {
          pixel = (positionInPattern + pixel_index) % 16;
          pixels.setPixelColor(pixel, red * pixel_index, green * pixel_index, blue * pixel_index); 
       }
       
       pixels.show();
       positionInPattern++;
       delay(delayTime);
       
       break;

    //**********************************************************************************************
    // Case 8: WRITE YOUR OWN PATTERN 
    //**********************************************************************************************
     
     case 8:
     
       // To run your pattern, remember to change the case/pattern in the top of the code
       
       pixels.show(); 
       delay(delayTime); 
       break; 
    }
}
