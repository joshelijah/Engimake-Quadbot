/*
	QuadBot.cpp - Library that provides controlling functions for the QuadBot 
	(see comments in each function for details). 
	QuadBot is made by and a trademark of EngiMake.
	Created by Dan Elijah, May 01, 2017.
  	Released into the public domain.
  	Version 1 (first release).
  	
  	Please make sure you also include the Servo.h and Adafruit_NeoPixel.h 
  	libraries to your sketchbook before running this.
*/

#include "QuadBot.h"

Servo MA0;
Servo MA1;
Servo MB0;
Servo MB1;
Servo MC0;
Servo MC1;
Servo MD0;
Servo MD1;

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(4, 7, NEO_GRB + NEO_KHZ800);  
Adafruit_NeoPixel strip = Adafruit_NeoPixel(4, 7, NEO_GRB + NEO_KHZ800);

/*
You can attach 1 extra motor to each leg.
Servo MA2;
Servo MB2;
Servo MC2;
Servo MD2;
*/ 
// %%%%%%%%%%%%%	DEFAULT VALUES	%%%%%%%%%%%%%%
int Bright = 255, ProcessDelay = 5000;
bool NoTone = false;
int angleMin = 59;
int angleMax = 147;
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

// int R1, G1, B1;
void QuadBot::begin() {

// Analog pins - directions
	pinMode(A0, OUTPUT);	// Piezo Buzzer
	pinMode(A1, INPUT);		// IR Reciever
	pinMode(A2, INPUT);		// Potentiometer Input
	// MD2.attach(A3);	// Motor D2 (Use the servo.attach command to inisialise the servo pins)
	MD1.attach(A4);	// Motor D1
	MD0.attach(A5);	// Motor D0
	
	// Digital pins - directions
	pinMode(0, INPUT);		// Serial Rx 
	pinMode(1, OUTPUT);		// Serial Tx
	// pinMode(2, ); User defined
	// pinMode(3, ); User defined 
	// MB2.attach(4);		// Motor B2
	MC1.attach(5);		// Motor C1
	MB0.attach(6);		// Motor B0
	pinMode(7, OUTPUT);		// RGB LED control
	pinMode(8, INPUT);		// Button input
	pinMode(9, OUTPUT);		// IR LED control
	MC0.attach(10);	// Motor C0
	// pinMode(11, ); User defined // Breakout pin 1 (next to 5V)
	MB1.attach(12);	// Motor B1
	// MC2.attach(13);	// Motor C2
	// MA2.attach(14);	// Motor A2
	MA0.attach(15);	// Motor A0
	MA1.attach(16);	// Motor A1
	
	beginAngle = 90;
	MA0.write(beginAngle);
	MA1.write(beginAngle);
	// MA2.write(beginAngle); // Only use Mx2 if you add extra motors.
	MB0.write(beginAngle);
	MB1.write(beginAngle);
	// MB2.write(beginAngle);
	MC0.write(beginAngle);
	MC1.write(beginAngle);
	// MC2.write(beginAngle);
	MD0.write(beginAngle);
	MD1.write(beginAngle);
	pixelCounter = 0; // A Starting counter for assigning multiple pixel assignment.
	// MD2.write(beginAngle);
	pixels.setPixelColor(0, pixels.Color(0,0,0));
	pixels.setPixelColor(1, pixels.Color(0,0,0));
	pixels.setPixelColor(2, pixels.Color(0,0,0));
	pixels.setPixelColor(3, pixels.Color(0,0,0));
	pixels.show();
}

void QuadBot::SetMotor(char MotorNumber, int angle) {
/*
Here we write the angle numbers to specific motors. The motors are objects by the
Servo library.
Input MotorNumber M0-M7, (M0 = the proximal motor on A)
Input angles from 0 to 90;
*/
//MotorNumber = str(MotorNumber);
//int angleMin = 59;
//int angleMax = 147;
// 0   min 28  max  180
int angle0 = constrain(angle, 28, 180);  
int angle1 = constrain(angle, 51, 140);
	switch (MotorNumber) {
		case char ('M0'):
			MA0.write(angle0);
			break;
		case char ('M1'):
			MA1.write(angle1);
			break;
		case char ('M2'):
			MB0.write(angle0);
			break;
		case char ('M3'):
			MB1.write(angle1);
			break;
		case char ('M4'):
			MC0.write(angle0);
			break;
		case char ('M5'):
			MC1.write(angle1);
			break;
		case char ('M6'):
			MD0.write(constrain(angle, 28, 130));
			break;
		case char ('M7'):
			MD1.write(angle1);
			break;
	/* The disignations below are for extra servos. Only add this code if you have 
	added new servos.
		case char('M8'):
			MC0.write(angle);
			break;
		case char('M9'):
			MC1.write(angle);
			break;
		case char('M10'):
			MD0.write(angle);
			break;
		case char('M11'):
			MD1.write(angle);
			break;
	*/
	}
	delayMicroseconds(ProcessDelay);
}

int QuadBot::LightRead(boolean readLED) {
	/*
	Here we record light from the IR reciever with the IR diode either on or 
	off. If the reading from the reciever changes (it reads lower for 
	increases in brigtness) between IR diode on and off then something is nearby
	and refrlecting light back at QuadBot. Use this for distance sensing. 
	*/
	if (readLED) {
		digitalWrite(9, HIGH);
	}
	else {
		digitalWrite(9, LOW);
	}
	return analogRead(A1);
}

boolean QuadBot::ReadButton() {
	/* Reads the input from the button
	output is reversed to read 0 off 1 on.
	*/
	return !digitalRead(8);
}

void QuadBot::SetBrightness(int Brightness) {
	/*
	This function changes the Bright value (default set at 255) to whatever the 
	user wants. It will reduce the RGB values equally by a factor of (255-x). 
	Setting brightness at 255 will give no dimming.
	NB/ For better dimming, consider using PWM (PWM(7, vlaue)).
	*/
	Bright = Brightness;
}

void QuadBot::SetLED(int NumLED, int R, int G, int B) {
	/*
	Function for lighting a given LED (NumLED) with an R G B color
	*/
	int R_1 = R - (255 - Bright); 
	if (R_1<0) {R_1=0;}
	int G_1 = G - (255 - Bright); 
	if (G_1<0) {G_1=0;}
	int B_1 = B - (255 - Bright); 
	if (B_1<0) {B_1=0;}
	
	pixels.setPixelColor(NumLED, pixels.Color(R_1, G_1, B_1));
	pixels.show();
	delayMicroseconds(ProcessDelay);
}

void QuadBot::SetLEDs(int R, int G, int B) {
	/*
	This Function lights all 4 LEDs with an R G B color.
	*/
	int R_1 = R - (255 - Bright); 
	if (R_1<0) {R_1=0;}
	int G_1 = G - (255 - Bright); 
	if (G_1<0) {G_1=0;}
	int B_1 = B - (255 - Bright); 
	if (B_1<0) {B_1=0;}
	
	pixels.setPixelColor(pixelCounter, pixels.Color(R_1,G_1,B_1));
	pixels.show();
	pixelCounter++;
	if (pixelCounter>4)	{pixelCounter=0;}
	delayMicroseconds(ProcessDelay);
}

void QuadBot::SetTone(int freq) {
	/*
	Sets and plays a tone of specified frequency.
	*/
	if (!NoTone) {
		tone(A0, freq);
	}
}

void QuadBot::StopTone() {
	/*
	Stops tones playing from the QuadBot.
	*/
	noTone(A0);
	// NoTone = true;
}

int QuadBot::ReadDial() {
	/*
	Reads the analog output from the dial.
	*/
	return analogRead(A2);
}

uint32_t QuadBot::Wheel(byte WheelPos) {
	/*
	Inputs a value from 0 to 255 and returns a HEX color value within a 
	graduated scale (R - G - B - R)
	*/
	WheelPos = 255 - WheelPos;
	if (WheelPos < 85) {
    	return pixels.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  	}
  	if(WheelPos < 170) {
    	WheelPos -= 85;
    	return pixels.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  	}
  	WheelPos -= 170;
  	return pixels.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

int QuadBot::WheelR(byte WheelPos) {
	/*
	Inputs a value from 0 to 255 and returns a RED value for a color wheel 
	(R G B R).
	*/
	WheelPos = 255 - WheelPos;
	int col;
	if (WheelPos < 85) {
		col = (255 - WheelPos * 3);
		if (col < 0) {col = 0;}
    	return col;
  	}
  	if (WheelPos < 170) {
    	WheelPos -= 85;
    	return 0;
  	}
  	WheelPos -= 170;
  	col = (WheelPos * 3);
  	if (col < 0) {col = 0;}
  	return col;
}

int QuadBot::WheelG(byte WheelPos) {
	/*
	Inputs a value from 0 to 255 and returns a GREEN value for a color wheel 
	(R G B R).
	*/
	WheelPos = 255 - WheelPos;
	int col;
	if (WheelPos < 85) {
    	return 0;
  	}
  	if (WheelPos < 170) {
    	WheelPos -= 85;
    	col = (WheelPos * 3);
    	if (col < 0) {col = 0;}
    	return col;
  	}
  	WheelPos -= 170;
  	col = (255 - WheelPos * 3);
  	if (col < 0) {col = 0;}
  	return col;
}

int QuadBot::WheelB(byte WheelPos) {
	/*
	Inputs a value from 0 to 255 and returns a BLUE value for a color wheel 
	(R G B R).
	*/
	WheelPos = 255 - WheelPos;
	int col;
	if (WheelPos < 85) {
		col = (WheelPos * 3);
		if (col < 0) {col = 0;}
    	return col;
  	}
  	if(WheelPos < 170) {
    	WheelPos -= 85;
    	col = (255 - WheelPos * 3);
    	if (col < 0) {col = 0;}
    	return col;
  	}
  	WheelPos -= 170;
  	return 0;
}

void QuadBot::StandStill() {
	// angle = constrain(angle+angleMin, angleMin, angleMax);
	int toeAngle = 110;
	
	MA0.write(beginAngle);
	MA1.write(toeAngle);
	// MA2.write(beginAngle);
	MB0.write(beginAngle);
	MB1.write(toeAngle);
	// MB2.write(beginAngle);
	MC0.write(beginAngle);
	MC1.write(toeAngle);
	// MC2.write(beginAngle);
	MD0.write(beginAngle);
	MD1.write(toeAngle);
}

void QuadBot::WalkForward(int delayT) {
	
	//int delayT = delayTime; // good value is around 150ms. 
	int delayD = int round(delayT/3);
	
	int down = 135, up = 90; // Values from Josh.
	
	// B and D UP
	MB1.write(up);
	MD1.write(up);
	
	//B and D BACK
	MB0.write(40);
	MD0.write(100);
	
	delay(delayD);
	
	//A and C BACK
	MA0.write(85);
	MC0.write(135);
	
	delay(delayD);
	
	//B and D FORWARD
	MB0.write(70);
	MD0.write(70);
	
	//B and D DOWN
	MB1.write(down);
	MD1.write(down);
	
	delay(delayT);
	
	//A and C UP
	MA1.write(up);
	MC1.write(up);
	
	delay(delayD);
	
	//B and D BACK
	MB0.write(40);
	MD0.write(100);
	
	delay(delayD);
	
	//A and C FORWARD
	
	MA0.write(110);
	MC0.write(110);
	
	
	//A and C DOWN
	MA1.write(down);
	MC1.write(down);
	delay(delayT);
}

void QuadBot::WalkBackward(int delayT) {
	
	//int delayT = delayTime; // good value is around 150ms. 
	int delayD = int round(delayT/3);
	
	int down = 135, up = 90, D = 200;
	
	// B and D UP
	MB1.write(up);
	MD1.write(up);
	
	//B and D FORWARD
	MB0.write(100);
	MD0.write(40);
	
	delay(delayD);
	
	//A and C FORWARD
	MA0.write(130);
	MC0.write(85);
	
	delay(delayD);
	
	//B and D BACK
	MB0.write(70);
	MD0.write(70);
	
	// B and D DOWN
	MB1.write(down);
	MD1.write(down);

	delay(delayT);
		
	//A and C UP
	MA1.write(up);
	MC1.write(up);
	
	delay(delayD);
	
	//B and D BACK
	MB0.write(100);
	MD0.write(40);
	
	delay(delayD);
	
	//A and C FORWARD
	
	MA0.write(110);
	MC0.write(110);
	
	//A and C DOWN
	MA1.write(down);
	MC1.write(down);
	delay(delayT);
}

void QuadBot::WalkLeft(int delayT) {
	/*
	Simple walking motion to the left. This command includes 1 complete walk 
	cycle.
	int delayT = delayTime between movements; // A good value is around 150ms.
	*/
	int delayD = int round(delayT/3);
	
	int down = 135, up = 90;
	
	// A and C UP
	MA1.write(up);
	MC1.write(up);
	
	//A and C BACK
	MC0.write(40);
	MA0.write(100);
	
	delay(delayD);
	
	//B and D BACK
	MB0.write(85);
	MD0.write(135);
	
	delay(delayD);
	
	//A and C FORWARD
	MC0.write(70);
	MA0.write(70);
	
	//A and C UP
	MC1.write(down);
	MA1.write(down);
	
	delay(delayT);
	
	//B and D UP
	MB1.write(up);
	MD1.write(up);
	
	delay(delayD);
	
	//A and C BACK
	MC0.write(40);
	MA0.write(100);
	
	delay(delayD);
	
	//B and D FORWARD
	MB0.write(110);
	MD0.write(110);
	
	//B and D DOWN
	MB1.write(down);
	MD1.write(down);
	delay(delayT);
}

void QuadBot::WalkRight(int delayT) {
	/*
	Simple walking motion to the right. This command includes 1 complete walk 
	cycle.
	int delayT = delayTime between movements; // good value is around 150ms. 
	*/
	int delayD = int round(delayT/3);
	
	int down = 135, up = 90;
	
	// A and C UP
	MA1.write(up);
	MC1.write(up);
	
	//A and C BACK
	MA0.write(40);
	MC0.write(100);
	
	delay(delayD);
	
	//B and D BACK
	MD0.write(85);
	MB0.write(135);
	
	delay(delayD);
	
	//A and C FORWARD
	MA0.write(70);
	MC0.write(70);
	
	//A and C DOWN
	MA1.write(down);
	MC1.write(down);
	
	delay(delayT);
	
	//B and D UP
	MD1.write(up);
	MB1.write(up);
	
	delay(delayD);
	
	//A and C BACK
	MA0.write(40);
	MC0.write(100);
	
	delay(delayD);
	
	//B and D FORWARD
	MD0.write(110);
	MB0.write(110);
	
	//B and D DOWN
	MD1.write(down);
	MB1.write(down);
	
	delay(delayT);
}

void QuadBot::RotateCCW(int delayT) {
	/*
	Counter-Clockwise rotation, with a movement step of 30 degrees. The input 
	is the delay time between movements. Make sure to leave sufficient time for 
	the	motors to react to your commands.
	*/
	int down = 135, up = 90, angle = 30;
	
	//A and C ROTATE
	MA0.write(90-angle);
	MC0.write(90-angle);
	
	delay(delayT);
	
	//B and D DOWN
	MB1.write(down);
	MD1.write(down);
	
	delay(delayT);
	
	//A and C UP
	MA1.write(up);
	MC1.write(up);
	
	delay(delayT);
	
	//B and D ROTATE
	MB0.write(90-angle);
	MD0.write(90-angle);
	
	delay(delayT);
	
	//A and C ROTATE BACK
	MA0.write(90);
	MC0.write(90);
	
	delay(delayT);
	
	//A and C DOWN
	MA1.write(down);
	MC1.write(down);
	
	delay(delayT);
	
	//B and D UP
	MB1.write(up);
	MD1.write(up);
	
	//B and D ROTATE BACK
	MB0.write(90);
	MD0.write(90);
	
	delay(delayT);
}

void QuadBot::RotateCW(int delayT) {
	/*
	Clockwise rotation, with a movement step of 30 degrees. The input is the 
	delay time between movements. Make sure to leave sufficient time for the 
	motors to react to your commands.
	*/
	int down = 135, up = 90, angle = 30;
	
	//A and C ROTATE
	MA0.write(90+angle);
	MC0.write(90+angle);
	
	delay(delayT);
	
	//B and D DOWN
	MB1.write(down);
	MD1.write(down);
	
	delay(delayT);
	
	//A and C UP
	MA1.write(up);
	MC1.write(up);
	
	delay(delayT);
	
	//B and D ROTATE
	MB0.write(90+angle);
	MD0.write(90+angle);
	
	delay(delayT);
	
	//A and C ROTATE BACK
	MA0.write(90);
	MC0.write(90);
	
	delay(delayT);
	
	//A and C DOWN
	MA1.write(down);
	MC1.write(down);
	
	delay(delayT);
	
	//B and D UP
	MB1.write(up);
	MD1.write(up);
	
	//B and D ROTATE BACK
	MB0.write(90);
	MD0.write(90);
	
	delay(delayT);
}

void QuadBot::KILL() {
	/*
	USE THIS WITH CARE. This function makes QuadBot turn itself off using one 
	of its legs (motor MD0). Remember, if you run this function it will also 
	run after you restart. You have 10 seconds to load in another function to 
	overide.
	*/
	int toeAngle = 135, up = 90;
	int deathAngle = 160;
	MA0.write(beginAngle);
	MA1.write(toeAngle);
	MB0.write(beginAngle);
	MB1.write(toeAngle);
	MC0.write(beginAngle);
	MC1.write(toeAngle);
	MD0.write(beginAngle);
	MD1.write(toeAngle);
	
	delay(9850);
	MD1.write(up);
	delay(150);
	MD0.write(deathAngle);
	delay(2000);
}

