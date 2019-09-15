#include <Servo.h>
#include "Motor.h"
#include "headTracing.h"
#include <Adafruit_ssd1306syp.h>

/*******************
 * 电机运行动作
*******************/
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

const int SideTrace[2] = {35, 36};                            //侧边循迹，从前到后
const int RearTrace = 37;

//const int E18Pin = ;  避障

/*******************
 * 气泵吸盘由两部分组成
 * bigMotor--大马达
 * smallMotor--小马达
*******************/
const int bigMotor = 7;
const int smallMotor = 8;

/*******************
 * 机械臂舵机数组
*******************/
Servo MyServo[3];                                               
Servo platform;
int SideD[2];                                                  //车身侧边传感器数据
int RearD;

void setup() {

  Serial.begin(9600);

//  pinMode(E18Pin, INPUT);

/*******************
 * 初始化气泵的两个马达
*******************/
  pinMode(bigMotor, OUTPUT);
  pinMode(smallMotor, OUTPUT);

/*******************
 * 初始化红外传感器
*******************/
  for(i = 0; i < 8; i++) {
    pinMode(HeadTrace[i], INPUT);
  }

pinMode(RearTrace, INPUT);

  for(i = 0; i < 2; i++) {
    pinMode(SideTrace[i], INPUT);
  }

/*******************
 * 连接四个舵机和引脚
*******************/
  MyServo[bigServo].attach(A0);
  MyServo[smallServo].attach(A1);
  MyServo[buttomServo].attach(A2);
  platform.attach(53);
  
/*******************
 * 初始化四个舵机角度
*******************/  
  MyServo[bigServo].write(80);
  MyServo[smallServo].write(180);
  MyServo[buttomServo].write(50);
  platform.write(110);
  
  delay(3000);
  platform.write(170);
}

/*******************
 * 吸气
*******************/
void inhale(){
  analogWrite(bigMotor, 250);
  analogWrite(smallMotor, 40);
}

/*******************
 * 放气
*******************/
void deflate() {
  analogWrite(bigMotor, 40);
  analogWrite(smallMotor, 250);  
}

/*******************
 * 机械臂抓取动作
*******************/
void armCatch() {
  servoMove(bigServo, 80, 120, 20);
  servoMove(smallServo, 180, 150, 20);
  inhale();
  delay(2000);
  servoMove(bigServo, 120, 80, 20);
  servoMove(smallServo, 150, 180, 20);

  servoMove(buttomServo, 50, 0, 20);
  delay(1000);
  deflate();
  servoMove(buttomServo, 0, 50, 20);
  
}

/*******************
 * 舵机函数
*******************/
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


int flag = 0;

void loop() {
/*
while(flag == 0) {
  for(i = 0; i < 2; i++) {
    SideD[i] = digitalRead(SideTrace[i]);
  }
  headTracing();
  if(SideD[0] && SideD[1] && HD[6] && HD[7]) {
      MyMotor.motorRun(STOP);
      delay(3000);
      armCatch();
      MyMotor.motorRun(FORWARD);
      delay(500);
      flag = 1;    
  }  
}

while(flag = 1) {
  headTracing();
  if(HD[0] && HD[1] && HD[2] && HD[3] && HD[4] && HD[5] && HD[6] && HD[7]) {
    flag = 2;
  }
}

while(flag = 2) {
  MyMotor.motorRun(STOP);
  delay(1000);
  MyMotor.motorRun(FORWARD);
  delay(1000);
  MyMotor.motorRun(STOP);
  delay(1000);  
  flag = 3;
}

while(flag = 3) {
  headTracing();
  if(SideD[0] && SideD[1] && HD[6] && HD[7]) {
      MyMotor.motorRun(STOP);
      delay(3000);
      armCatch();
      MyMotor.motorRun(FORWARD);
      delay(500);
      flag = 4;    
  }  
}

while(flag = 4) {
  headTracing();

  if(HD[0] && HD[1] && HD[2] && HD[3] && HD[4] && HD[5] && HD[6] && HD[7]) {
    while(1) {
      MyMotor.motorRun(STOP);
    }
  }  
}

*/
  headTracing();
  
  
  for(i = 0; i < 2; i++) {
    SideD[i] = digitalRead(SideTrace[i]);
  }

  
  
  if(SideD[0] && SideD[1] && HD[6] && HD[7]) {
      MyMotor.motorRun(STOP);
      delay(3000);
      armCatch();
      MyMotor.motorRun(FORWARD);
      delay(500);
   }
  
  

} 
