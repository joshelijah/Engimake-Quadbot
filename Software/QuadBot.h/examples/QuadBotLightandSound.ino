/*  Light and Sound example
  
  In this example, QuadBot is commanded to play three sounds from a Piezo speaker 
  and flash different colors from 4 color LEDs. Feel free to copy and modify the 
  program.
  
  Created 04 May 2017 by D Elijah
  This code is in the public domain.
  QuadBot is made by and a trademark of Engimake

*/
#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <QuadBot.h>

int LED, R = 0, G = 85, B = 170, delayTime = 100;
long int counter = 0; // a counter to control switching.
QuadBot quadBot;
//This creates the quadbot object. It contains all the functions from the QuadBot Library.

void setup() {
  quadBot.begin(); // This initialises the settings for the QuadBot. Run this only is setup.
  quadBot.SetBrightness(200); //Sets the maximum brightness of the LEDS.
  //Serial.begin(9600);
}

void loop() {
  if ( (counter > 0) && (counter < 10) ) {
    delayTime = 100;
    quadBot.SetTone(440); // Play a tone for 1000ms (A major)
  }
  else if ( (counter > 10) && (counter < 15) ) {
    delayTime = 200;
    quadBot.SetTone(330); // E Major
  }
  else if ( (counter > 15) && (counter < 65) ) {
    delayTime = 20;
    quadBot.SetTone(523); // C Major
  }
    
  for (LED=0;LED<4;LED++) {
    quadBot.SetLED(LED, R, G, B); // Set pixels 0-3 different colors
    delay(delayTime/2); // Add a delay.
    quadBot.SetLED(LED, 0, 0, 0);
    delay(delayTime/2); // Add a delay.
    R += 50; // Add 85 each run.
    G += 50;
    B += 50;
    // values go over 255 set to 0
    if (R>255) {R=0;} 
    if (G>255) {G=0;} 
    if (B>255) {B=0;} 
  }
  
  R += 10; // This changes the starting values for the LEDS so they display new colors.
  G += 10;
  B += 10;
  
  if (R>255) {R=0;} if (G>255) {G=0;} if (B>255) {B=0;}
  
  counter++;
  if (counter > 65) {
    counter = 0;
  }
  
  //Serial.println(counter);
  delay(10);
}
