#include <Servo.h>
#include "Motor.h"
#include "headTracing.h"
#include <Adafruit_ssd1306syp.h>

#define SDA_PIN 20
#define SCL_PIN 21

#define STOP 0
#define FORWARD 1
#define BACKWARD 2
#define TURNRIGHT 3
#define TURNLEFT 4
#define TURNRIGHTLITTLE 5
#define TURNLEFTLITTLE 6


Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);

//const int RearTrace[5] = {30, 31, 32, 33, 34};                    //车尾循迹
const int SideTrace[2] = {35, 36};                            //侧边循迹，从前到后
const int RearTrace = 37;

const int E18Pin = 8;

Servo MyServo[3];                                               //机械臂舵机
Servo platform;
int SideD[2];                                                  //车身侧边传感器数据
int RearD;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  display.initialize();
  
  pinMode(E18Pin, INPUT);

  for(i = 0; i < 8; i++) {
    pinMode(HeadTrace[i], INPUT);
  }
/*
  for(i = 0; i < 5; i++) {
    pinMode(RearTrace[i], INPUT);
  }
*/
pinMode(RearTrace, INPUT);

  for(i = 0; i < 2; i++) {
    pinMode(SideTrace[i], INPUT);
  }

  MyServo[0].attach(50);
  MyServo[1].attach(51);
  MyServo[2].attach(52);
  platform.attach(53);
  
  MyServo[0].write(120);
  MyServo[1].write(180);
  MyServo[2].write(50);
  platform.write(110);
  
  oledShow();
  delay(3000);
  platform.write(170);
}

void oledShow()
{
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello, world!");
  display.update();
}

void armTest() {
  servoMove(0, 120, 170, 20);
  servoMove(0, 170, 120, 20);

  servoMove(1, 180, 160, 20);
  servoMove(1, 160, 180, 20);

  servoMove(2, 50, 0, 20);
  servoMove(2, 0, 50, 20);
}

void servoMove(int _which, int _start, int _finish, long _time) {
  static int Direct;
  static int Diff;
  static long DeltaTime;
  if (_start <= _finish)
    Direct = 1;
  else
    Direct = -1;
  Diff = abs(_finish - _start);
  //DeltaTime = (long)(t / Diff);
  DeltaTime = _time;
  for (int i = 0; i < Diff; i++)
  {
    MyServo[_which].write(_start + i * Direct);
    delay(DeltaTime);
  }
}

void loop() {
  headTracing();
  
  
  for(i = 0; i < 2; i++) {
    SideD[i] = digitalRead(SideTrace[i]);
  }
  RearD = digitalRead(RearTrace);
  
  if(SideD[0] && SideD[1]) {
      MyMotor.motorRun(STOP);
      delay(3000);
      armTest();
      MyMotor.motorRun(FORWARD);
      delay(500);
   }
/*
   if(SideD[0] && RearD) {
      MyMotor.motorRun(STOP);
      delay(3000);
      
      MyMotor.motorRun(FORWARD);
      delay(500);

      MyMotor.motorRun(STOP);
      delay(3000);
      
   }*/
} 
