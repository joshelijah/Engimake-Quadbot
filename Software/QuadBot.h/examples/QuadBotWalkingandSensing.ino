/* QuadBot Walking example
  
  This example shows the walking and sensing functions of the QuadBot. It walks foward
  constantly sensing objects in its path by using the front LED and light sensor. When 
  something is detected, it turns 180 degrees and walks away.  
  
  The sequence includes:
  %%%%%  PRESS BUTTON TO START  %%%%%
  - Walk forwards
  - Use IR Sensor to detect obsticals in front of QuadBot.
  - When obstical is detected, rotate about 180 degrees clockwise.
  - Walk forwards again and repeat
  - For the 4th obstical, stay still and wait for button to be pushed to start routine again.
  
  Please note that due to small errors in leg movements, the QuadBot may drift to the left or 
  right. 
  
  Created 05 May 2017 by D Elijah.
  This code is in the public domain. Feel free to alter and improve.
  QuadBot is made by and a trademark of Engimake
*/

#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <QuadBot.h>

QuadBot quadBot;

int i, button, n, reading; // i increases and gets reset for easch walking pattern
// button stores the input from the button
// n increases as light is being measured
// reading stores the light reading.

// threshold is the obstruction thereshold. Increasing this means QuadBot must get closer 
// to an obstruction to detect it.
int threshold = 25;
// This is 0 when there is no object and 1 when an object is in front of the QuadBot.
int obstruct;
// delayTime controls the speed of walking, turnCount increases by 1 for every turn.
int delayTime = 150, turnCount = 0;
// These variables stro light readings and calculate the averge light levels.
long int readlightOFF = 0, readlightON = 0, meanlightOFF, meanlightON;

void setup() {
  quadBot.begin(); // Initilse the settings for the QuadBot.
  Serial.begin(9600);
}

void loop() {  
  holdingFunction(button); // Press the button to start the program.
  turnCount = 0;
  //obstruct = distanceCalc(threshold);
  //Serial.println(number);
  while (true) {
    obstruct = distanceCalc(threshold);
    if (obstruct == 0) { // No obstructions
      quadBot.WalkForward(delayTime);
    }
    else {
      for (i=0;i<7;i++) {
        quadBot.RotateCW(delayTime/4);
      }
      turnCount++;
    }
    if (turnCount > 3) {
      quadBot.StandStill();
      delay(delayTime*2);
      break;
    }
  }
}

/// %%%%% EXTRA FUNCTIONS ARE BELOW %%%%%

int distanceCalc(int threshold) {
  readlightOFF = 0; 
  readlightON = 0; //Reset these values to 0.
  // quadBot.LightRead(false);
  
  quadBot.LightRead(HIGH);
  for (n=0;n<100;n++) {
    // Take a reading with the IR LED ON
    reading = quadBot.LightRead(HIGH);
    //take the sum of the readings.
    readlightOFF = readlightOFF + reading;
  }
  
  delay(10);
  
  quadBot.LightRead(LOW);
  for (n=0;n<100;n++) {
    // Take a reading with the IR LED OFF
    reading = quadBot.LightRead(LOW);
    // Take the sum of the readings.
    readlightON = readlightON + reading;
  }
  
  quadBot.LightRead(LOW); // Turn the LED off.
  
  meanlightOFF = readlightOFF/n; // Take the average light level with no LED.
  meanlightON = readlightON/n; // Take the average light level with LED.
  // If there is a difference > threshold then there is an object reflecting 
  // light back at the sensor
  if ( (meanlightON - meanlightOFF) > threshold ) {
    return 1;
  }
  else {
    return 0;
  }
}

// 
void holdingFunction(int button) {
  if (button == 0) { 
    // Button not pressed
    while (true) {
      // This holds the program untill you press the button 
      button = quadBot.ReadButton();
      if (button > 0) {
        break;
      }
    }
  }
}

