/* 
 * Stranger Things Message Wall
 * Written by Zach Hipps 2017 for byte sized YouTube channel: https://www.youtube.com/c/bytesized
 * 
 * Build instructions can be found at https://www.bytesizedelectronics.com/projects/how-to-make-a-stranger-things-message-wall
 * Video can be found at https://youtu.be/tG8sQMoKrb0
 * 
 * How to use: 
 * -----------
 * Connect string of WS2811 LEDs (or equivient) to the arduino with the data signal going to pin 3. 
 * Be sure to use a separate power supply as the arduino's voltage regulator cannot supply enough current for all these LEDs.
 * Send serial data to the program either using the serial monitor, or some external serial device (like HC-05 bluetooth module) connected to RX and TX pins. 
 * 
 * Known issues:
 * ------------
 * Due to strict timing requirments from the WS2811 LEDs, the FastLED library has to disable interrupts when writing to the LEDs. This will cause some serial data to be lost. 
 * The practical result is that messages longer than 6 characters seem to get truncated. Some sort of software buffering could potentially fix this. See https://github.com/FastLED/FastLED/wiki/Interrupt-problems
 * 
 */



#include "FastLED.h" // This is the library that does all the work with the LEDs

#define NUM_LEDS 28 // The number of LEDs in the string
#define DATA_PIN 3 // The pin that connects to the data signal on the LEDs

CRGB leds[NUM_LEDS]; // Define array with NUM_LEDS elements
CRGB led_color[NUM_LEDS]= // Define array to store LED colors
{
  led_color[0] = CRGB::Blue,
  led_color[1] = CRGB::Red,
  led_color[2] = CRGB::Orange,
  led_color[3] = CRGB::Green,
  led_color[4] = CRGB::White,
  led_color[5] = CRGB::Blue,
  led_color[6] = CRGB::Red,
  led_color[7] = CRGB::Orange,
  led_color[8] = CRGB::Green,
  led_color[9] = CRGB::White,
  led_color[10] = CRGB::Blue,
  led_color[11] = CRGB::Red,
  led_color[12] = CRGB::Orange,
  led_color[13] = CRGB::Green,
  led_color[14] = CRGB::White,
  led_color[15] = CRGB::Blue,
  led_color[16] = CRGB::Red,
  led_color[17] = CRGB::Orange,
  led_color[18] = CRGB::Green,
  led_color[19] = CRGB::White,
  led_color[20] = CRGB::Blue,
  led_color[21] = CRGB::Red,
  led_color[22] = CRGB::Orange,
  led_color[23] = CRGB::Green,
  led_color[24] = CRGB::White,
  led_color[25] = CRGB::Red,
  led_color[26] = CRGB::Red,
  led_color[27] = CRGB::Blue,
};

void setup() 
{
  Serial.begin(115200); // start serial peripheral
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS); // instantiate LED library with our information
  FastLED.clear(); // clear the LED display before doing anything else
	RGB_Blink();
	chase();

}

void loop() 
{
  if(Serial.available()) // If there is serial data waiting in the buffer
  { 
    ascii2ledIndex(Serial.read()); // read the data and convert each letter from ascii to the appropriate LED index in the string
  }
}


// Convert a letter from ascii to the appropriate LED index in the string
void ascii2ledIndex(int asciiLetter)
{
    //Serial.println(asciiLetter);
    int ledIndex = -1; // create variable to store led index
    int indexMap[]={20,21,22,23,24,25,26,27,18,17,16,15,14,13,12,11,10,0,1,2,3,4,5,6,7,8}; // When I hung the LED string on the wall the first letters in the string are R S T U V W X Y Z then it skips one LED and winds around to  Q P O N M L K J I then it skips one LED and winds to A B C D E F G H
    if(asciiLetter >= 97 && asciiLetter <= 122) // It's an ASCII Lowercase Letter
    {
      ledIndex = indexMap[asciiLetter - 97];
    }
    else if (asciiLetter >= 65 && asciiLetter <= 90) // It's an ASCII Uppercase Letter
    {
      ledIndex = indexMap[asciiLetter - 65];
    }
    Serial.println(ledIndex);
    if(ledIndex >= 0) // valid LED index converted from either uppercase or lowercase letter
    {
      leds[ledIndex] = led_color[ledIndex];
      FastLED.show();
      delay(500);
      FastLED.clear();
      FastLED.show();
      delay(250);
    }
    else // invalid led index. display blank. this is useful for spaces and other punctuation. 
    {
      FastLED.clear();
      FastLED.show();
      delay(750);
    }
    
}


// Test function that displays one LED at a time. This appears like the LED is chasing down the string. 
void chase() 
{
  for(int dot = 0; dot < NUM_LEDS; dot++) 
  { 
      leds[dot] = led_color[dot]; 
      FastLED.show();
      // clear this led for the next time around the loop
      leds[dot] = CRGB::Black;
      delay(100);
  }
}

// Test function that blinks all the LEDs 
void RGB_Blink()
{
  // Set all the colors
  leds[0] = led_color[0]; 
  leds[1] = led_color[1]; 
  leds[2] = led_color[2]; 
  leds[3] = led_color[3]; 
  leds[4] = led_color[4]; 
  leds[5] = led_color[5]; 
  leds[6] = led_color[6]; 
  leds[7] = led_color[7]; 
  leds[8] = led_color[8]; 
  leds[9] = led_color[9]; 
  leds[10] = led_color[10]; 
  leds[11] = led_color[11]; 
  leds[12] = led_color[12]; 
  leds[13] = led_color[13]; 
  leds[14] = led_color[14]; 
  leds[15] = led_color[15]; 
  leds[16] = led_color[16]; 
  leds[17] = led_color[17]; 
  leds[18] = led_color[18]; 
  leds[19] = led_color[19]; 
  leds[20] = led_color[20]; 
  leds[21] = led_color[21]; 
  leds[22] = led_color[22]; 
  leds[23] = led_color[23]; 
  leds[24] = led_color[24]; 
  leds[25] = led_color[25]; 
  leds[26] = led_color[26];
  leds[27] = led_color[27];  
  FastLED.show();
  delay(750);
  // Now turn the LED off, then pause
  FastLED.clear();
  FastLED.show();
  delay(500);
}

