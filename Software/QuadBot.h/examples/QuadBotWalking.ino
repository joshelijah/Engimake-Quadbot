/* QuadBot Walking example
  
  This example shows the walking functions of the QuadBot. The sequence includes:
  %%%%%  PRESS BUTTON TO START  %%%%%
  - A short walk forwards
  - Briefly stop and put all legs on the ground
  - A short left walk (whilst facing forwards)
  - A 180 degree rotation
  - A forwards walk
  - A 90 degree rotation
  - A forwards walk
  - A 90 degree rotation to get back to the starting position.
  
  Please note that due to small errors in leg movements, the QuadBot will not end 
  in exactly the same position that it started from. 
  
  Created 04 May 2017 by D Elijah
  This code is in the public domain. Feel free to alter and improve.
  QuadBot is made by and a trademark of Engimake
  
*/

#include <Servo.h>
#include <Adafruit_NeoPixel.h>
#include <QuadBot.h>

QuadBot quadBot;
int delayTime = 200, NumSteps=10; // Sets the delay times between steps. 
// NumSteps controlls the number of complete walking cycles to be played.

int i; // This increases within the program as QuadBot walks. 
// i then gets reset and increases again for each new type of walking

int button; // For holding the QuadBot at the start.

void setup() {
  quadBot.begin();
}

void loop() {
  // Remove this if you want QuadBot to keep walking 
  holdingFunction(button); // Press the button to start the program.
  
  // Walk forward
  for (i=0; i<NumSteps; i++) {
    quadBot.WalkForward(delayTime);
  }
  // Briefly stop and put all legs on the ground.
  quadBot.StandStill();
  delay(delayTime*2);
  
  // Walk right (without rotating)
  for (i=0; i<NumSteps; i++) {
    quadBot.WalkRight(delayTime);
  }
  
  // Rotate 180 degrees clockwise
  for (i=0; i<5; i++) {
    quadBot.RotateCW(delayTime/4);
  }
  
  // Walk forwards
  for (i=0; i<NumSteps; i++) {
    quadBot.WalkForward(delayTime);
  }
  
  // Rotate 90 degrees clockwise
  for (i=0; i<4; i++) {
    quadBot.RotateCW(delayTime/4);
  }
  
  // Walk forwards
  for (i=0; i<NumSteps; i++) {
    quadBot.WalkForward(delayTime);
  }
  
  // Rotate 90 degrees clockwise
  for (i=0; i<4; i++) {
    quadBot.RotateCW(delayTime/4);
  }
  
  quadBot.StandStill();
  
  // Now QuadBot should be back near its original position.
}

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

