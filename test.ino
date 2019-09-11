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


#define bigServo 0
#define smallServo 1
#define buttomServo 2

Adafruit_ssd1306syp display(SDA_PIN,SCL_PIN);

//const int RearTrace[5] = {30, 31, 32, 33, 34};                    //车尾循迹
const int SideTrace[2] = {35, 36};                            //侧边循迹，从前到后
const int RearTrace = 37;

//const int E18Pin = ;  避障

const int bigMotor = 7;
const int smallMotor = 8;

Servo MyServo[3];                                               //机械臂舵机
Servo platform;
int SideD[2];                                                  //车身侧边传感器数据
int RearD;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);

  display.initialize();
  
//  pinMode(E18Pin, INPUT);

  pinMode(bigMotor, OUTPUT);
  pinMode(smallMotor, OUTPUT);
  
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

  MyServo[bigServo].attach(50);
  MyServo[smallServo].attach(51);
  MyServo[buttomServo].attach(52);
  platform.attach(53);
  
  MyServo[bigServo].write(80);
  MyServo[smallServo].write(180);
  MyServo[buttomServo].write(50);
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

void inhale(){
  analogWrite(bigMotor, 200);
  analogWrite(smallMotor, 40);
}

void deflate() {
  analogWrite(bigMotor, 40);
  analogWrite(smallMotor, 200);  
}

void armTest() {
  servoMove(bigServo, 80, 110, 20);
  servoMove(bigServo, 110, 80, 20);
  inhale();
  servoMove(smallServo, 180, 160, 20);
  servoMove(smallServo, 160, 180, 20);

  servoMove(buttomServo, 50, 0, 20);
  servoMove(buttomServo, 0, 50, 20);
  
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
      
   }
  */ 

} 
