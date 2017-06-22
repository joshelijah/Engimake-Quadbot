/*  Sensors example
  
  The QuadBot is equipped with a number of sensors and inputs. In this example, we will 
  read the outputs from the dial, button and the infra-red sensor and print their outputs
  using Serial.print().
  
  Make sure to use the serial monitor (in the top right corner of this window) 
  to display the values.
  
  Created 04 May 2017 by D Elijah
  This code is in the public domain.
  
*/

#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <QuadBot.h>

//This creates the quadbot object. It contains all the functions from the QuadBot Library.
QuadBot quadBot;

int Dial, Button, IRSensor, delayTime = 50;

void setup() {
 quadBot.begin(); // This initialises the settings for the QuadBot. Run this only is setup.
 Serial.begin(9600);
}

void loop() {
  Dial = quadBot.ReadDial(); // Read in the Dial value (0 - 1023);
  Button = quadBot.ReadButton(); // Read in the Button (0,1);
  IRSensor = quadBot.LightRead(LOW); 
  // Get light reading from the IR sensor. The Boolean input switches the IR LED on or off
  // while the sensor records. NB/ This is useful for detecting objects near the sensor.
  
  Serial.print("Dial = "); Serial.print(Dial); Serial.print("\t"); Serial.print("Button = ");
  Serial.print(Button); Serial.print("\t"); Serial.print("IR Sensor = "); 
  Serial.println(IRSensor);
  //Print the values to the display.
  
  delay(delayTime); // Add a delay time.
}
