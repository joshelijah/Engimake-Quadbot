#ifndef QuadBot_h
#define QuadBot_h
#include<Servo.h>
#include<Arduino.h>
#include<Adafruit_NeoPixel.h>

class QuadBot
{
  public:
  	void begin();
  	void SetMotor(char MotorNumber, int angle);
  	int LightRead(boolean readLED);
  	boolean ReadButton();
  	void SetLED(int NumLED, int R, int G, int B);
  	void SetLEDs(int R, int G, int B);
  	void SetBrightness(int Brightness);
  	void SetTone(int freq);
  	void StopTone();
  	int ReadDial();
  	uint32_t Wheel(byte WheelPos);
  	int WheelR(byte WheelPos);
  	int WheelG(byte WheelPos);
  	int WheelB(byte WheelPos);
  	// %%%%%%	MOVEMENT FUNCTIONS	%%%%%
  	void StandStill();
  	void WalkForward(int delayTime);
  	void WalkBackward(int delayTime);
  	void WalkLeft(int delayTime);
  	void WalkRight(int delayTime);
  	void RotateCW(int delayTime);
  	void RotateCCW(int delayTime);
  	void KILL();
  	int pixelCounter, Brightness, angleMin, angleMax;
  private:
  	int beginAngle;

};

#endif
