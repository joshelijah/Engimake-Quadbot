long xA = -50;
long xB = -50;
long xC = 50;
long xD = 50;

long yA = 50;
long yB = -50;
long yC = -50;
long yD = 50;

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>
#include <math.h>

#define PIN            5
#define NUMPIXELS      8

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, PIN, NEO_GRB + NEO_KHZ800);


void setup() {

  pixels.begin();

}

void loop() {

  rainbowCycle(10);

}
